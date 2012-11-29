// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// ���������ź��������A��B,�����鳤�ȶ�ΪN,���Ǵ����������ȡһ��Ԫ�����,�����͵õ���N^2����
// Ҫ�����N^2���Ͱ������,�ռ䲻�ܳ���O(N)

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

