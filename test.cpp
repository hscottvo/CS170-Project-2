#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>


using namespace std;

template <typename T>
bool contains(vector<T> vec, const T & elem)
{
    bool result = false;
    if( find(vec.begin(), vec.end(), elem) != vec.end() )
    {
        result = true;
    }
    return result;
}

int main() {
    vector<int> a;
    a.push_back(1);
    cout << contains(a, 1) << endl << contains(a, 2) << endl;
}