// Author: Muye (muyepiaozhou@gmail.com)
//
// 正整数数组 A, B;
// 在保持SUM(A)不变的情况下, 用B中若干元素替换A中若干元素,使得A中元素个数最少?

#include <iostream>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;

int minCount(const int* const &A, const int& la, const int* const &B, const int& lb) {
    int N = la + lb, C = 0, *W = new int[N + 1];
    W[0] = 0;
    for(int i = 0; i < la; ++i) {
        C += A[i];
    }
    copy(A, A + la, W + 1);
    copy(B, B + lb, W + la + 1);
    int **f = new int*[N+1], **count = new int*[N+1];	// count[n][c]记录f[n][c]所用元素个数
    for(int i = 0; i <= N; ++i) {
        f[i] = new int[C+1];
        count[i] = new int[C+1];
        memset(f[i], 0, (C+1)*sizeof(int));
        memset(count[i], 0, (C+1)*sizeof(int));
    }

    for(int n = 1; n <= N; ++n) {
        for(int c = C; c >= W[n]; --c) {
            f[n][c] = (f[n-1][c] > f[n-1][c-W[n]] + W[n]) ? f[n-1][c] : f[n-1][c-W[n]] + W[n];
            if(f[n][c] == f[n-1][c-W[n]] + W[n]) {
                count[n][c] = count[n-1][c-W[n]] + 1;
            } else {
                count[n][c] = count[n-1][c];
            }
            if(f[n-1][c] == f[n-1][c-W[n]] + W[n]) {
                count[n][c] = (count[n-1][c-W[n]] + 1 > count[n-1][c]) ? count[n-1][c] : count[n-1][c-W[n]] + 1;
            }
        }
    }
    int *result = new int[N+1];
    memset(result, 0, (N+1)*sizeof(int));
    for(int n = N, c = C; n > 0; --n) {
        if(W[n] <= c) {
            if(f[n-1][c] > f[n-1][c-W[n]] + W[n]) {
                result[n] = 0;
            } else if(f[n-1][c] == f[n-1][c-W[n]] + W[n]) {
                if(count[n-1][c] < count[n-1][c-W[n]] + 1) {
                    result[n] = 0;
                } else {
                    result[n] = 1; c -= W[n];
                }
            } else {
                result[n] = 1; c -= W[n];
            }
        }
    }
    /*
    cout << "=====================================================" << endl;
    for(int n = 1; n <= N; ++n) {
        for(int c = 1; c <= C; ++c) {
            cout << f[n][c] << " ";
        }
        cout << endl;
    }
    cout << "=====================================================" << endl;
    for(int n = 1; n <= N; ++n) {
        for(int c = 1; c <= C; ++c) {
            cout << count[n][c] << " ";
        }
        cout << endl;
    }
    cout << "=====================================================" << endl;
    */
    cout << "C = " << f[N][C] << endl;
    cout << "=====================================================" << endl;
    for(int i = 1; i <= N; ++i) {
        if(result[i]) {
            cout << W[i] << "\t";
        }
    }
    cout << endl;
    cout << "=====================================================" << endl;

    for(int i = 0; i <= N; ++i) {
        delete[] f[i];
        delete[] count[i];
    }
    delete[] f;
    delete[] W;
    delete[] count;
    delete[] result;
    return 0;
}

int main(int argc, char **argv) {
    const int la = 5, lb = 3;
    int A[la], B[lb];
    srand((unsigned)time(NULL));
    for(int i = 0; i < la; ++i) {
        A[i] = rand() % 10 + 1;
        cout << A[i] << "\t";
    }
    cout << endl;
    for(int i = 0; i < lb; ++i) {
        B[i] = rand() % 10 + 1;
        cout << B[i] << "\t";
    }
    cout << endl;
    minCount(A, la, B, lb);
    return 0;
}

