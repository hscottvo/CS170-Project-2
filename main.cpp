#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>

using namespace std;

template <typename T>

// https://thispointer.com/c-test-check-if-a-value-exist-in-vector/
bool contains(vector<T> vec, const T & elem)
{
    bool result = false;
    if( find(vec.begin(), vec.end(), elem) != vec.end() )
    {
        result = true;
    }
    return result;
}

template <typename T>
void print(vector<T> vec, bool endline){
    for(unsigned int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    if (endline) cout << endl;
}

vector<double> get_data(vector<double> row) {
    vector<double> ret;
    for(int i = 1; i < row.size(); ++i) {
        ret.push_back(row[i]);
    }
    return ret;
}

vector<double> get_data(vector<double> row, vector<unsigned int> features) {
    vector<double> ret;
    for(unsigned int i = 1; i < row.size(); ++i) {
        if (contains(features, i)) {
            ret.push_back(row[i]);
        } else {
            ret.push_back(0);
        }
    }
    return ret;
}

vector<double> parse_line(string& in) {
    vector<double> out;
    stringstream ss(in);
    string curr;
    while(true) {
        if (ss >> curr){
            out.push_back(stod(curr));

        } else {
            break;
        }
    }

    return out;    
}

double euclidean_distance(vector<double> train, vector<double> test){
    double sum = 0;
    for(size_t i = 0; i < train.size(); ++i) {
        sum += (train[i] - test[i]) * (train[i] - test[i]);
    }
    return sqrt(sum);
}

double cross_val(vector<vector<double> > in, vector<unsigned int> feature_set, unsigned int feature_to_add, const int rows, const int cols){
    int correct_count = 0;
    double a = 0;
    double nearest_neighbor_dist = std::numeric_limits<double>::max();
    double current_dist = std::numeric_limits<double>::max();
    vector<unsigned int> new_feature_set = feature_set;
    new_feature_set.push_back(feature_to_add);
    int obj_to_classify;
    int nearest_neighbor_label = -1;
    vector<double> test_row_features;
    vector<double> train_row_features;
    for(int i = 0; i < rows; ++i) {             // test (checking if the prediction would have been correct for this point)
        nearest_neighbor_dist = std::numeric_limits<double>::max(); // setting the inital distance to infinity (essentially)
        obj_to_classify = in[i][0];
        test_row_features = get_data(in[i], new_feature_set);


        for (int k = 0; k < rows; ++k) {        // train (checking for nearest neighbor)
            train_row_features = get_data(in[k], new_feature_set);
            // cout << "Checking if item " << k << " is the nearest neighbor to item " << i << endl;
            if(i == k) continue; // skips if train and test row are the same
            
            current_dist = euclidean_distance(train_row_features, test_row_features);
            if (current_dist < nearest_neighbor_dist) {
                nearest_neighbor_dist = current_dist;
                nearest_neighbor_label = in[k][0];
            }
            ++a;
        }
    // cout << "Object " << i << " should be class " << nearest_neighbor_label << endl;
        if (obj_to_classify == nearest_neighbor_label) {
            correct_count++;
        }
    }
    return (float)correct_count / (float)rows;
}


void feature_search(vector<vector<double> > in, const int rows, const int cols){
    vector<unsigned int> feature_set;

    for(unsigned int i = 1; i < cols; i++){
        // cout << "On the " << i << "th level of the search tree" << endl;
        int feature_to_add = -1;
        double best_so_far_acc = 0;
        double acc = 0;
        for (unsigned int k = 1; k < cols; k++) {
            if (contains(feature_set, k)) {
                continue;
                // cout << "this should not print" << endl;
            }
            cout << "\tConsidering adding the " << k << "th feature, seeing if ";
            print(feature_set, false);
            cout << k << " works" << endl;
            acc = cross_val(in, feature_set, k+1, rows, cols);
            cout << "acc " << acc << endl;

            if (acc > best_so_far_acc) {
                best_so_far_acc = acc;
                feature_to_add = k;
            }
        }

        feature_set.push_back(feature_to_add);
        cout << "On level " << i << ", added feature " << feature_to_add << " to current set" << endl;
        // print(feature_set, true);

    }
}


int main(int argc, char** argv)
{
	if (argc > 2) {
        cout << "Too many arguments. Exiting..." << endl;
        exit(1);
    }
    ifstream fs(argv[1]);
    if(!fs.is_open()){
        cout << "Cannot read file. Exiting..." << endl;
        exit(1);
    }
    string in;
    vector<vector<double> > table;
    while(getline(fs, in)){
        vector<double> x = parse_line(in);
        table.push_back(x);
    }
    int rows = table.size();
    int cols = table[0].size();
    feature_search(table, rows, cols);

    fs.close();

	return 0;
}