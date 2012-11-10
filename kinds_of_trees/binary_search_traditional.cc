// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <algorithm>
using namespace std;

int binary_search_traditional(int x, int v[], int n) {
    int low = 0, high = n - 1, m;
    while(low <= high) {
        m = (low + high) >> 1;
        if(v[m] < x) {
            low = m + 1;
        } else if(v[m] > x) {
            high = m - 1;
        } else {
            return m;
        }
    }
    return -1;
}

/*
 * always return the first element which is same with x
 */

int binary_search_better(int x, int v[], int n) {
    int low = -1, high = n, m;
    while(low + 1 < high) {
        m = (low + high) >> 1;
        if(v[m] < x) {
            low = m;
        } else {
            high = m;
        }
    }
    if(high == n || v[high] != x) {
        return -1;
    } else {
        return high;
    }
}

int main(int argc, char **argv) {
    int v[] = {1, 2, 3, 3, 3, 4, 5, 6, 7, 8};
    cout << "v[" << binary_search_traditional(3, v, 10) << "] = " << 3 << endl;
    cout << "v[" << binary_search_better(3, v, 10) << "] = " << 3 << endl;
    cout << "v[" << find(v, v + 10, 3) - v << "] = " << 3 << endl;
    return 0;
}

