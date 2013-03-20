// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isOdd(int i) {
    return (i%2);
}
int main(int argc, char **argv) {
    int f[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << count_if(f, f + 9, isOdd) << endl;
    return 0;
}


