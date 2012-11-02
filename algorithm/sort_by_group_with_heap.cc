// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
    const int len = 100, piece = 20;
    int a[len] = {0};
    srand((unsigned)time(NULL));
    for(int i = 0; i < len; ++i) {
        a[i] = rand() % len + 1;
    }
    sort(a, a + len);
    int num = 0;
    while(num < len) {
        int count = rand() % piece + 1;
        if(num + count > len) {
            random_shuffle(a + num, a + len);
        } else {
            random_shuffle(a + num, a + num + count);
        }
        num += count;
    }
    cout << "========================================" << endl;
    for(int i = 0; i < len; ++i) {
        printf("%-3d%c", a[i], ((i + 1) % piece) ? ' ' : '\n');
    }
    cout << "========================================" << endl;
    vector<int> v(a, a + ((piece > len) ? len : piece));
    make_heap(v.begin(), v.end(), greater<int>());
    for(int i = piece, index = 0; i < len; ++i) {
        pop_heap(v.begin(), v.end(), greater<int>());
        a[index++] = v.back();
        v.back() = a[i];
        push_heap(v.begin(), v.end(), greater<int>());
    }
    sort_heap(v.begin(), v.end(), greater<int>());
    for(int i = len - v.size(); i < len; ++i) {
        a[i] = v.back();
        v.pop_back();
    }
    cout << "========================================" << endl;
    for(int i = 0; i < len; ++i) {
        printf("%-3d%c", a[i], ((i + 1) % piece) ? ' ' : '\n');
    }
    cout << "========================================" << endl;
    return 0;
}




