// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
using namespace std;

const int N = 11;
int A[N], C[N];

int lowbit(int k) {
    return k & (-k);
}

int Sum(int k) {
    int sum = 0;
    while(k > 0) {
        sum += C[k];
        k -= lowbit(k);
    }
    return sum;
}

void Update(int k, int add) {
    while(k <= N) {
        C[k] += add;
        k += lowbit(k);
    }
}

void Init() {
    memset(A, 0, sizeof(A));
    memset(C, 0, sizeof(C));
    srand((unsigned)time(NULL));
    for(int i = 1; i < N; ++i) {
        A[i] = rand() % 50;
        Update(i, A[i]);
        A[i] += A[i-1];
    }
}

void Test() {
    for(int i = rand() % 10 + 1; i > 0; --i) {
        int k = rand() % N;
        assert(A[k] == Sum(k));
    }
}

int main(int argc, char **argv) {
    Init();
    Test();
    return 0;
}
