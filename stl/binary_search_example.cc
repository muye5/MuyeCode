// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <algorithm>
using namespace std;

bool comp(int a, int b) {
    return (a < b);
}

int main(int argc, char **argv) {
    int f[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "binary_search : 3 " << binary_search(f, f + 10, 3) << endl;
    cout << "binary_search : 10 " << binary_search(f, f + 10, 10) << endl;
    return 0;
}

