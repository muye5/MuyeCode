// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)
// 1������Ϊ2N������������N�����ĺ� = �ұ�N�����ĺͣ���ô����һ�����˺��롣
// ���磺99��1230��123312�����˺���
// ����һ��N���󳤶�Ϊ2N�����˺�������������������ܴ�������� Mod 10^9 + 7�Ľ������

#include <iostream>
#include <stdint.h>
using namespace std;

int64_t mod = 1000000007LL;
int64_t v[10000] = {0}, u[10000] = {0};

int64_t luckyNumber(int64_t n) {
    int64_t k = n * 9, ans = 0;
    int64_t *p = v, *q = u;
    v[0] = u[0] = 1;

    for(int64_t i = 1; i <= n; ++i) {
        swap(p, q);
        for(int64_t t = 1; t <= k; ++t) {
            p[t] = (p[t-1] + q[t]) % mod;
            if(t > 9) p[t] = (p[t] - q[t-10]) % mod;
        }
    }
    for(int64_t t = 1; t <= k; ++t) {
        ans = (ans + (p[t] - q[t]) * p[t] % mod) % mod;
    }
    return ans;
}

int main() {
    int64_t n;
    cin >> n;
    cout << luckyNumber(n) << endl;
    return 0;
}

