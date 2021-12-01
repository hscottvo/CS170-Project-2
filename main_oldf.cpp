#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <limits>
#include <iostream>
#include <math.h>
using namespace std;


double cross_val(vector<vector<double> >& in, int rows, int cols, 
                 unordered_set<int> curr_features, int added_feature);

struct features_acc {
    unordered_set<int> features;
    double acc = 0;
};

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

void feature_search(vector<vector<double> >& in, int rows, int cols){
    unordered_set<int> feature_set = {};
    // https://thispointer.com/different-ways-to-iterate-over-a-set-in-c/
    for (int i = 1; i < cols; ++i) {
        cout << "Level " << i << endl;
        int this_level_feature = 0;
        double max_acc = 0;

        for (int k = 1; k < cols; ++k) {
            double accuracy = 0;
            // https://www.techiedelight.com/check-element-present-set-cpp/
            if (!(feature_set.count(k))){
                cout << "\tConsidering adding feature " << k << endl;
                accuracy = cross_val(in, rows, cols, feature_set, k);
            }
            if (accuracy > max_acc) {
                max_acc = accuracy;
                this_level_feature = k;
            }
        }
        feature_set.insert(this_level_feature);
    }
    // return {feature_set, max_acc};
}

double cross_val(vector<vector<double> >& in, int rows, int cols, 
                 unordered_set<int> curr_features, int added_feature){
    vector<vector<double> > curr_table;
    for(int i = 1; i < cols; ++i) {
        if (!(curr_features.count(i))){
                curr_table.push_back(in[i]);
        }
    }
    cols = curr_table.size();

    int num_correct = 0;

    for (int i = 0; i < rows; ++i) {
        vector<double> object_to_classify = in[i];
        int object_label = in[i][0];
        double nearest_neighbor_distance = numeric_limits<double>::max();
        int nearest_neighbor_label = 0;
        for (int k = 0; k < rows; ++k) {
            if (k != i) {
                double sum = 0;
                for (int a = 0; a < cols; a++) {
                    sum += (object_to_classify[a] - curr_table[k][a]) * (object_to_classify[a] - curr_table[k][a]);
                }
                double dist = sqrt(sum);
                // double dist = 0;

                if (dist < nearest_neighbor_distance) {
                    nearest_neighbor_distance = dist;
                    nearest_neighbor_label = curr_table[k][0];
                }
            }
        }
        if (object_label == nearest_neighbor_label){
            num_correct++;
        }
    }
    for(auto const &n: curr_features) {
    }
    double accuracy = num_correct / rows;
    cout << "accuracy: " << accuracy << endl;
    return accuracy;
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
