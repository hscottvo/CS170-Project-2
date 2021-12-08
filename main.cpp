#include <iostream>
#include <string>

#include <vector>
#include <algorithm>
#include <limits>
#include <unordered_set>
#include <math.h>

#include "util.h"

using namespace std;

// template <typename T>





// double euclidean_distance(vector<double>& train, vector<double>& test){
//     double sum = 0;
//     for(size_t i = 0; i < train.size(); ++i) {
//         // cout << "train[" << i << "]: " << train[i] << "\ttest[" << i << "]: " << test[i] << endl;
//         sum += (train[i] - test[i]) * (train[i] - test[i]);
//     }
//     // cout << sqrt(sum) << endl;
//     return sqrt(sum);
// }



double cross_val(vector<vector<double> >& in, unordered_set<unsigned int>& feature_set, unsigned int feature_to_add, const int rows, const int cols){
    int correct_count = 0;
    // double a = 0;
    double nearest_neighbor_dist = std::numeric_limits<double>::max();
    double current_dist = std::numeric_limits<double>::max();
    // unordered_set<unsigned int> new_feature_set = feature_set;
    // new_feature_set.insert(feature_to_add);
    int obj_to_classify;
    int nearest_neighbor_label = -1;
    // vector<double> test_row_features;
    // vector<double> train_row_features;

    int temp;
    double temp_dist;
    for(int i = 0; i < rows; ++i) {             // test (checking if the prediction would have been correct for this point)
        nearest_neighbor_dist = std::numeric_limits<double>::max(); // setting the inital distance to infinity (essentially)
        obj_to_classify = in[i][0];
        // test_row_features = get_data(in[i], new_feature_set);
        // cout << "label: " << obj_to_classify << " data: ";
        // for(int i = 0; i < test_row_features.size(); ++i) {
            // cout << test_row_features[i] << ' ';
        // } cout << endl;


        for (int k = 0; k < rows; ++k) {        // train (checking for nearest neighbor)
            // train_row_features = get_data(in[k], new_feature_set);
            // cout << "Checking if item " << k << " is the nearest neighbor to item " << i << endl;
            if(i == k) continue; // skips if train and test row are the same
            current_dist = euclidean_distance(in, i, k, feature_set, feature_to_add);
            // cout << "dist between row " << i << " and row " << k << " is " << current_dist << endl;
            if (current_dist < nearest_neighbor_dist) {
                nearest_neighbor_dist = current_dist;
                nearest_neighbor_label = in[k][0];
                temp = k;
                temp_dist = nearest_neighbor_dist;
            }
            
        }

        // cout << "Object " << i << " should be class " << nearest_neighbor_label << " because it is closest neighbors with " << temp << ", with distance " << temp_dist << endl;
        if (obj_to_classify == nearest_neighbor_label) {
            correct_count++;
        }
    }
    return correct_count / (float)rows;
}


void feature_search_forward(vector<vector<double> >& in, const int rows, const int cols, vector<unordered_set<unsigned int> >& feature_list, vector<double>& feature_accs){
    unordered_set<unsigned int> feature_set;
    double main_best_acc = 0;
    unordered_set<unsigned int> final_set;

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
            acc = cross_val(in, feature_set, k, rows, cols);
            cout << "\t\tThis-set Accuracy: " << acc << endl << endl;

            if (acc > best_so_far_acc) {
                best_so_far_acc = acc;
                feature_to_add = k;
            }
        }

        feature_set.insert(feature_to_add);
        feature_list.push_back(feature_set);
        feature_accs.push_back(best_so_far_acc);

        cout << "On level " << i << ", added feature " << feature_to_add << " to current set" << endl;
        // print(feature_set, true);
        if (best_so_far_acc > main_best_acc) {
            main_best_acc = best_so_far_acc;
            final_set = feature_set;
        }
        cout << "So-far best feature set with accuracy " << main_best_acc << ": "; print(final_set, true);
    }
    cout << "Overall best feature set: "; print(final_set, true);
}

void feature_search_backward(vector<vector<double> >& in, const int rows, const int cols, vector<unordered_set<unsigned int> >& feature_list, vector<double>& feature_accs){
    unordered_set<unsigned int> feature_set;
    double main_best_acc = 0;
    unordered_set<unsigned int> final_set;

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
            acc = cross_val(in, feature_set, k, rows, cols);
            cout << "\t\tThis-set Accuracy: " << acc << endl << endl;

            if (acc > best_so_far_acc) {
                best_so_far_acc = acc;
                feature_to_add = k;
            }
        }

        feature_set.insert(feature_to_add);
        feature_list.push_back(feature_set);
        feature_accs.push_back(best_so_far_acc);

        cout << "On level " << i << ", added feature " << feature_to_add << " to current set" << endl;
        // print(feature_set, true);
        if (best_so_far_acc > main_best_acc) {
            main_best_acc = best_so_far_acc;
            final_set = feature_set;
        }
        cout << "So-far best feature set with accuracy " << main_best_acc << ": "; print(final_set, true);
    }
    cout << "Overall best feature set: "; print(final_set, true);
}


int main(int argc, char** argv)
{
	if (argc > 2) {
        cout << "Too many arguments. Exiting..." << endl;
        exit(1);
    }
    string filename = argv[1];
    filename = filename.substr(0, filename.find('.'));
    ifstream fs(argv[1]);
    if(!fs.is_open()){
        cout << "Cannot read file. Exiting..." << endl;
        exit(1);
    }

    vector<unordered_set<unsigned int> > feature_list;
    vector<double> feature_accs;
    string in;
    int label_1_count = 0;
    vector<vector<double> > table;
    while(getline(fs, in)){
        vector<double> x = parse_line(in);
        table.push_back(x);
        if(x[0] == 1) label_1_count++; 
    }
    int rows = table.size();
    int cols = table[0].size();
    double default_rate;
    if(label_1_count * 2 > table.size()){
        default_rate = label_1_count/float(table.size());
    } else {
        default_rate =  (table.size()-label_1_count)/float(table.size());
    }
    cout << "Default rate: " << default_rate << endl;
    unordered_set<unsigned int> empty_set;
    feature_list.push_back(empty_set);
    feature_accs.push_back(default_rate);
    feature_search_forward(table, rows, cols, feature_list, feature_accs);


    ofstream outfile(filename + "_logs.csv");
    // cout << "Filename: " << filename << endl;
    cout << "Final accuracies: " << endl;
    for(unsigned int i = 0; i < feature_list.size(); ++i) { 
        cout << "\tAccuracy: " << feature_accs[i] << " with features ";
        outfile << to_string(feature_accs[i]) << ", ";
        if (feature_list[i].size()) {
            print(feature_list[i], true);
            outfile << tostring(feature_list[i]) << ", " << endl;
        } 
        else {
            cout << "___" << endl;
            outfile << "empty set" << ", " << endl;
        }

    
    }
    outfile.close();
    fs.close();

	return 0;
}