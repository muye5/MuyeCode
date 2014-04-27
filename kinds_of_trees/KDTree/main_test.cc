// Copyright (c) 2014
// Author: Yanshi.WYS ()

#include "kdtree.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

KDNode nodes[10001];
KDData datas[10001];
KDSpace queries[10001];

void create_data(int n) {
    int range = 10000;
    srand((unsigned)time(NULL));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < DIM; ++j) {
            nodes[i].x.d[j] = rand() % range;
        }
        datas[i].data = rand() % range;
        nodes[i].ptr = &datas[i];
    }
}

void create_query(int n) {
    int range = 20000;
    srand((unsigned)time(NULL));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < DIM; ++j) {
            int x = rand() % range - range / 4;
            int y = rand() % range - range / 4;
            queries[i].x.d[j] = min(x, y);
            queries[i].y.d[j] = max(x, y);
        }
    }
}

void brute_force(const KDSpace& s, int n, int& num, int& sum) {
    num = sum = 0;
    for(int i = 0; i < n; ++i) {
        if(s.contain(nodes[i].x)) {
            ++num;
            sum += nodes[i].ptr->data;
        }
    }
}

int main(int argc, char **argv) {
    int m = 10000, n = 500;
    create_data(n);
    create_query(m);

    KDNode * root = make_kdtree(nodes, n, 0);
    // print_kdtree(root, 0);

    for(int i = 0; i < m; ++i) {
        int num1 = 0, sum1 = 0, num2 = 0, sum2 = 0;
        brute_force(queries[i], n, num1, sum1);
        query(root, 0, queries[i], num2, sum2);
        if(num1 != num2 || sum1 != sum2) {
            printf("query range :\n");
            cout << "\t[( " << queries[i].x.d[0];
            for(int j = 1; j < DIM; ++j) {
                cout << ", " << queries[i].x.d[j];
            }
            cout << " ), ( " << queries[i].y.d[0];
            for(int j = 1; j < DIM; ++j) {
                cout << ", " << queries[i].y.d[j];
            }
            cout << " )]" << endl;
            printf("wrong anwser : expect [ %d, %d ], got [ %d, %d ]\n",
                   num1, sum1, num2, sum2);
            exit(1);
        }
    }
    printf("all test cases passed\n");
    return 0;
}
