// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char **argv) {
    int f[] = {1, 2, 3, 4, 4, 5, 5, 6};
    vector<int> v(f, f + 8);
    vector<int>::iterator it = adjacent_find(v.begin(), v.end());
    if(it != v.end()) {
        // the evaluation order of elements in an expression is unspecified
        // so like this: the evaluation of it is not specified.
        cout << it - v.begin() << ":" << *it << endl;
        ++it;
        cout << it - v.begin() << ":" << *it << endl;
    }
    return 0;
}

