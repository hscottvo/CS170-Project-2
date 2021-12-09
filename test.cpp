#include <fstream>
#include <string>
#include <iostream>
#include<unordered_set>
#include<vector>

#include "util.h"

using namespace std;

int main(int argc, char** argv) {
  double result, acc;
  int param;
  param = 500;
  acc = 0.12345;
  result = floor(log10 (param));
  printf ("log10(%i) => %f\n", param, pow(10, result) );
  cout << "rounded: " << floor(acc * pow(10, result)) / pow(10, result) << endl;
  return 0;
    
}