// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
//
// 一个大小为100亿数据的数组,是从小到大排好序的,现该数组分成若干段,每个段的数据小于20个,然后将每段的数据进行乱序,形成一个新数组.
// 请写一个算法,将所有数据从小到大进行排序.提醒:每段数据长度不固定,只是说小于20
// 原题见此文：http://t.cn/zlvj7AA 第83题第3小题
//
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

void join(int *p, int len) {
    int *q = p - 1, num = 0;
    while(*q > *p && num < len) {
        int *t = p;
        while(*q > *t) {
            int temp = *t;
            *t = *q;
            *q = temp;
            t = q--;
        }
        q = p++;
        ++num;
    }
}

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
    int piece_num = len / piece + ((len % piece) ? 1 : 0);
    for(int i = 0; i < piece_num; ++i) {
        if(i == 0) {
            sort(a, a + ((piece > len) ? len : piece));
        } else if(i + 1 == piece_num) {
            sort(a + piece * i, a + len);
            join(a + piece * i, len - piece * i);
        } else {
            sort(a + piece * i, a + piece * (i + 1));
            join(a + piece * i, piece);
        }
    }
    cout << "========================================" << endl;
    for(int i = 0; i < len; ++i) {
        printf("%-3d%c", a[i], ((i + 1) % piece) ? ' ' : '\n');
    }
    cout << "========================================" << endl;
    return 0;
}




