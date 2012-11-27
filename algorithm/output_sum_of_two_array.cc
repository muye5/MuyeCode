// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// 给定两个排好序的数组A和B,两数组长度都为N,我们从两个数组各取一个元素求和,这样就得到了N^2个和
// 要求把这N^2个和按序输出,空间不能超过O(N)

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int main(int argc, char **argv) {
    const int len = 8;
    int A[len], B[len], C[len] = {0};

    srand((unsigned)time(NULL));
    for(int i = 0; i < len; ++i) {
        A[i] = rand() % 10;
        B[i] = rand() % 10;
    }
    sort(A, A + len);
    sort(B, B + len);
    printf("=====================  A  ====================\n");
    for(int i = 0; i < len; ++i) {
        printf("%5d%c", A[i], (i + 1 == len ? '\n' : ' '));
    }
    printf("=====================  B  ====================\n");
    for(int i = 0; i < len; ++i) {
        printf("%5d%c", B[i], (i + 1 == len ? '\n' : ' '));
    }
    printf("==============================================\n");

    int num = 0;
    for(int i = 0; i < len;) {
        if(C[i] == len) {
            ++i;
            continue;
        }
        int tmp = A[i] + B[C[i]];
        int f = i;
        for(int j = i + 1; j < len; ++j) {
            if(C[j] == len) {
                continue;
            }
            if(tmp > A[j] + B[C[j]]) {
                tmp = A[j] + B[C[j]];
                f = j;
            }
        }
        ++C[f];
        printf("%5d%c", tmp, (++num % len ? ' ' : '\n'));
    }
    return 0;
}

