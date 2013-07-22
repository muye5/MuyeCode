// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
using namespace std;

const int N = 11, M = 11;
int A[N][M], C[N][M];

int lowbit(int k) {
    return k & (-k);
}

int Sum(int n, int m) {
    int sum = 0;
    for(int i = n; i > 0; i -= lowbit(i)) {
        for(int j = m; j > 0; j -= lowbit(j)) {
            sum += C[i][j];
        }
    }
    return sum;
}

void Update(int n, int m, int add) {
    for(int i = n; i < N; i += lowbit(i)) {
        for(int j = m; j < M; j += lowbit(j)) {
            C[i][j] += add;
        }
    }
}

void Init() {
    memset(A, 0, sizeof(A));
    memset(C, 0, sizeof(C));
    srand((unsigned)time(NULL));
    for(int i = 1; i < N; ++i) {
        for(int j = 1; j < M; ++j) {
            A[i][j] = rand() % 100;
            Update(i, j, A[i][j]);
            A[i][j] += A[i-1][j] + A[i][j-1] - A[i-1][j-1];
        }
    }
}

void Test() {
    for(int k = rand() % 10 + 1; k > 0; --k) {
        int i = rand() % N;
        int j = rand() % M;
        assert(A[i][j] == Sum(i, j));
    }
}

int main(int argc, char **argv) {
    Init();
    Test();
    return 0;
}

