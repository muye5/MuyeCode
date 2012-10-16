// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// 有面额不等的发票若干张, 但是报销的额度只有C, 怎么样找到最接近报销额度的发票组合?
// 如果有多种组合, 找到需要张数最少的组合!

#include <iostream>
#include <cstring>
#include <stdint.h>
#include <algorithm>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

int32_t mindiff(const int32_t N, const int32_t C, const vector<int32_t>& w) {
    int32_t **d = new int32_t*[N+1];
    int32_t **p = new int32_t*[N+1];
    for(int32_t i = 0; i <= N; ++i) {
        d[i] = new int32_t[C+1];
        p[i] = new int32_t[C+1];
        memset(d[i], 0, (C+1)*sizeof(int32_t));
        memset(p[i], 0, (C+1)*sizeof(int32_t));
    }
    // init matrice
    for(int32_t i = 0; i <= C; ++i) {
        d[0][i] = i;
    }
    // run...
    for(int32_t n = 1; n <= N; ++n) {
        for(int32_t c = 1; c <= C; ++c) {
            if(w[n] >= c) {
                d[n][c] = (d[n-1][c] > w[n] - c) ? (w[n] - c) : d[n-1][c];
                if(d[n][c] == w[n] - c) {
                    p[n][c] = 1;
                } else {
                    p[n][c] = p[n-1][c];
                }
            } else {
                d[n][c] = (d[n-1][c] > d[n-1][c-w[n]]) ? d[n-1][c-w[n]] : d[n-1][c];
                if(d[n][c] == d[n-1][c]) {
                    p[n][c] = p[n-1][c];
                } else {
                    p[n][c] = p[n-1][c-w[n]] + 1;
                }
                if(d[n-1][c] == d[n-1][c-w[n]]) {
                    p[n][c] = (p[n-1][c] > p[n-1][c-w[n]] + 1) ? (p[n-1][c-w[n]] + 1) : p[n-1][c];
                }
            }
        }
    }
    // print32_t result
    cout << "==========================================" << endl;
    cout << "C = " << C << " && Diff = " << d[N][C] << endl;
    cout << "==========================================" << endl;
    int32_t *result = new int32_t[N+1];
    memset(result, 0, (N+1)*sizeof(int32_t));
    for(int32_t n = N, c = C; n > 0; --n) {
        if(w[n] >= c) {
            if(d[n-1][c] >= w[n] - c) {
                result[n] = 1;
                break;
            } else {
                result[n] = 0;
            }
        } else {
            if(d[n-1][c] >= d[n-1][c-w[n]]) {
                if(d[n-1][c] == d[n-1][c-w[n]]) {
                    if(p[n-1][c] < p[n-1][c-w[n]] + 1) {
                        result[n] = 0;
                    } else {
                        result[n] = 1; c -= w[n];
                    }
                } else {
                    result[n] = 1; c -= w[n];
                }
            } else {
                result[n] = 0;
            }
        }
    }

    for(int32_t n = 1; n <= N; ++n) {
        cout << w[n] << ":" << result[n] << "\t";
    }
    cout << endl;
    int32_t rvalue = d[N][C];
    for(int32_t i = 0; i <= N; ++i) {
        delete[] d[i];
        delete[] p[i];
    }
    delete[] d;
    delete[] p;
    delete[] result;
    return rvalue;
}

TEST(mindiff, test) {
    int32_t array[] = {3, 0, 7, 9, 12, 20, 25};
    vector<int32_t> w(array, array + 7);
    int32_t n = w.size() - 1;
    sort(w.begin(), w.end(), less<int32_t>());

    EXPECT_TRUE(1 == mindiff(n, 4, w));
    EXPECT_TRUE(0 == mindiff(n, 19, w));
    EXPECT_TRUE(0 == mindiff(n, 31, w));

    int32_t A[] = {7, 5, 2, 4, 5}, alen = 5;
    int32_t B[] = {6, 6, 1}, blen = 3;
    int32_t sum = 0;
    w.clear();
    w.push_back(0);
    for(int32_t i = 0; i < alen; ++i) {
        w.push_back(A[i]);
        sum += A[i];
    }
    for(int32_t i = 0; i < blen; ++i) {
        w.push_back(B[i]);
    }
    n = w.size() - 1;
    //sort(w.begin(), w.end(), less<int32_t>());
    EXPECT_TRUE(0 == mindiff(n, sum, w));
}

int32_t main(int32_t argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

