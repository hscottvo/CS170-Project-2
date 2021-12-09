#include <fstream>
#include <string>
#include <iostream>
#include<unordered_set>
#include<vector>

#include "util.h"

using namespace std;

string filename;
vector<unordered_set<unsigned int> > feature_list;
vector<double> feature_accs;

int main(int argc, char** argv) {
    filename = argv[1];
    filename = filename.substr(0, filename.find('.'));
    ifstream fs(argv[1]);
    if(!fs.is_open()){
        cout << "Cannot read file. Exiting" << endl;
        exit(1);
    }

    string in;
    while(getline(fs, in)){
        // cout << in << endl;
        parse_logs(feature_list, feature_accs, in);
    }
    cout << "features 0: "; print(feature_list[2], true); 
    
}