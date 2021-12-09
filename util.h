#ifndef __UTIL_H__
#define __UTIL_H__
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

bool contains(unordered_set<unsigned int>& s, const unsigned int & elem)
{
    bool result = false;
    // if( find(vec.begin(), vec.end(), elem) != vec.end() )
    // {
    //     result = true;
    // }
    if (s.find(elem) != s.end()) {
        result = true;
    }
    return result;
}

template <typename T>
void print(unordered_set<T>& s, bool endline){
    // for(unsigned int i = 0; i < vec.size(); ++i) {
    //     cout << vec[i] << ' ';
    // }
    for (auto const &i: s) {
        std::cout << i << " ";
    }
    if (endline) cout << endl;
}

template <typename T>
void print(vector<T>& vec, bool endline) {
    for(unsigned int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << endl;
}

template <typename T>
void print(vector<T>& vec, bool endline, int index){
    for(unsigned int i = index; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    if (endline) cout << endl;
}


string tostring(unordered_set<unsigned int> in){
    string out = "";
    for (auto const &s: in) {
        out += to_string(s) + " ";
    }
    return out;
}


vector<double> get_data(vector<double>& row, unordered_set<unsigned int>& features) {
    vector<double> ret;
    // cout << "row: ";print(row, true);
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

void parse_logs(vector<unordered_set<unsigned int> >& features_in, vector<double>& accs_in, string& string_in){
    stringstream ss(string_in);
    string curr;
    ss >> curr;
    accs_in.push_back(stod(curr.substr(0, curr.size()-1)));
    unordered_set<unsigned int> out;
    while(true){
        if (ss >> curr) {
            if (curr != "empty_set,"){
                if (curr.find(',') != std::string::npos){
                curr = curr.substr(0, curr.size()-1);
                }
                if (curr != "") {
                    out.insert(stoi(curr));
                }
                // out.insert(stoi(curr));
            }
            // out.insert(stoi(curr));
            // cout << curr.substr(0, curr.size()-1) << ' ';
        } else {
            break;
        }
        
    }
    features_in.push_back(out);
    // cout << endl;
}

double euclidean_distance_add(vector<vector<double> >& data, unsigned int i, unsigned int k, unordered_set<unsigned int> feature_set, unsigned int new_feature){
    
    double sum = 0;
    double a = 0;
    double b = 0;
    for(size_t j = 1; j < data[0].size(); ++j) {
        if (contains(feature_set, j)){
            sum += (data[i][j] - data[k][j]) * (data[i][j] - data[k][j]);
        }
    }
    sum += (data[i][new_feature] - data[k][new_feature]) * (data[i][new_feature] - data[k][new_feature]);
    return sqrt(sum);
}

double euclidean_distance_sub(vector<vector<double> >& data, unsigned int i, unsigned int k, unordered_set<unsigned int> feature_set, unsigned int new_feature){
    
    double sum = 0;
    double a = 0;
    double b = 0;
    for(size_t j = 1; j < data[0].size(); ++j) {
        if (contains(feature_set, j)){
            sum += (data[i][j] - data[k][j]) * (data[i][j] - data[k][j]);
        }
    }
    sum -= (data[i][new_feature] - data[k][new_feature]) * (data[i][new_feature] - data[k][new_feature]);
    return sqrt(sum);
}

double euclidean_distance(vector<vector<double> >& data, unsigned int i, unsigned int k, unordered_set<unsigned int> feature_set){
    double sum = 0;
    double a = 0;
    double b = 0;
    for(size_t j = 1; j < data[0].size(); ++j) {
        if (contains(feature_set, j)){
            sum += (data[i][j] - data[k][j]) * (data[i][j] - data[k][j]);
        }
    }
    return sqrt(sum);
}
#endif