// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv) {
    const int len = 8;
    int a[len] = {0};
    srand((unsigned)time(NULL));
    for(int i = 0; i < len; ++i) {
        printf("%-4d", i + 1);
    }
    cout << endl;
    for(int i = 0; i < len; ++i) {
        a[i] = rand() % 10 - 5;
        printf("%-4d", a[i]);
    }
    cout << endl;
    int max = 0, start = 0, over = -1, sum = 0, begin = 0, end = -1;
    for(int i = 0; i < len; ++i) {
        if(sum < 0) {
            sum = 0; begin = i; end = i - 1;
        }
        sum += a[i]; ++end;
        if(sum > max) {
            max = sum; start = begin; over = end;
        }
    }
    cout << "max = " << max << " : [" << start + 1 << ", " << over + 1 << "]" << endl;
    return 0;
}

