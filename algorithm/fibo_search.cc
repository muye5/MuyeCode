// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)
// 斐波那契搜索:按照斐波那契数选择分割节点坐标,gold search!

#include <iostream>
#include <ctime>
#include <climits>
#include <cassert>
#include <cstdlib>
#include <algorithm>
using namespace std;

int binsrch_geq(const int arr[], const int& len, const int& val) {
    register int low = 0, high = len-1, mid;
    int geq = -1;
    while(low <= high) {
        mid = low + ((high - low) >> 1);
        if(arr[mid] == val) {
            return mid;
        } else if(arr[mid] > val) {
            geq = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return geq;
}

int fibsrch(const int arr[], const int& len, const int& val) {
    const static int Fib[] = {
        0, 1, 1, 2, 3, 5, 8, 13, 21, 34,
        55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181,
        6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229,
        832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986,
        102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903, INT_MAX
    };
    int k = binsrch_geq(Fib, sizeof(Fib) / sizeof(int), val);
    register int idx, offset = 0;
    while(k > 0) {
        idx = offset + Fib[--k];
        if(idx >= len || arr[idx] > val) {
            continue;
        } else if(arr[idx] < val) {
            offset = idx;
            --k;
        } else {
            return idx;
        }
    }
    return -1;
}

int main(int argc, char **argv) {
    const int n = 1000000;
    int arr[n];
    int loop = 100;
    srand((unsigned)time(NULL));
    clock_t bintime = 0, fibtime = 0, start;
    while(--loop > 0) {
        int len = rand() % n + 1;
        for(int i = 0; i < len; ++i) {
            arr[i] = rand() >> 1;
        }
        sort(arr, arr + len);
        int cnt = 10000;
        while(--cnt > 0) {
            int key = rand() >> 1;
            //assert((fibsrch(arr, len, key) > -1) == binary_search(arr, arr + len, key));
            start = clock();
            fibsrch(arr, len, key);
            fibtime += clock() - start;
            start = clock();
            binary_search(arr, arr + len, key);
            bintime += clock() - start;
        }
    }
    cout << "fibtime: " << fibtime << endl;
    cout << "bintime: " << bintime << endl;
    return 0;
}

