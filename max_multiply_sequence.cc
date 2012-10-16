// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
//
// ��һ������������,ȡ���˻������е�ֵ.
// ���� -2.5, 4, 0, 3, 0.5, 8, -1
// ȡ�������˻�������Ϊ 3, 0.5, 8
// ˼·:
// ��Ԫ��i��β�����ṩ������������� pos, ��С�������� nag
// a[n] ������ʱ:
//      pos[n] = max{pos[n-1] * a[n], a[n]}
//      max_value = max{max_value, pos[n]}
//      ��n-1λ�ô�����С����, ���� nag[n] = nag[n-1] * a[n]
// a[n] С����ʱ:
//      pos[n] = max{nag[n-1] * a[n], 0.0}
//      max_value = max{max_value, pos[n]}
//      ���� nag[n] = min{pos[n-1] * a[n], a[n]}
// a[n] ������ʱ:
//      ��� nag[n] �� pos[n]

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

inline double max(const double& a, const double& b) {
    return (a > b) ? a : b;
}

inline bool equal(const double& a, const double& b) {
    if(fabs(a - b) < 1e-6) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char **argv) {
    const int len = 10;
    double a[len] = {0.0};
    srand((unsigned)time(NULL));
    for(int i = 0; i < len; ++i) {
        printf("%-8d", i + 1);
    }
    cout << endl;
    for(int i = 0; i < len; ++i) {
        a[i] = rand() % 50 * 0.1 - 2.5;
        printf("%-8.1f", a[i]);
    }
    cout << endl;
    double Max = 0.0, pos = 0.0, old = 0.0, nag = 1.0;
    int start = 0, over = -1;
    int bn1 = 0, bn2 = 0;
    for(int i = 0; i < len; ++i) {
        if(a[i] > 1e-6) {
            pos = max(old * a[i], a[i]);
            if(equal(pos, a[i])) {
                bn1 = i;
            }
            Max = max(Max, pos);
            if(equal(Max, pos)) {
                start = bn1; over = i;
            }
            if(nag < -1e-6) {
                nag *= a[i];
            }
        } else if(a[i] < -1e-6) {
            int index = bn1;
            pos = max(0.0, nag * a[i]);
            if(equal(pos, 0.0)) {
                bn1 = i + 1;
            } else {
                bn1 = bn2;
            }
            Max = max(Max, pos);
            if(equal(Max, pos)) {
                start = bn1; over = i;
            }
            nag = (old * a[i] > a[i]) ? a[i] : old * a[i];
            if(equal(nag, a[i])) {
                bn2 = i;
            } else {
                bn2 = index;
            }
        } else {
            nag = 1.0; pos = 0.0;
            bn1 = bn2 = i + 1;
        }
        old = pos;
    }
    cout << "max = " << Max << " : [" << start + 1 << ", " << over + 1 << "]" << endl;
    return 0;
}

