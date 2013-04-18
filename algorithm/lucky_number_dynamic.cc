// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)
// 1个长度为2N的数，如果左边N个数的和 = 右边N个数的和，那么就是一个幸运号码。
// 例如：99、1230、123312是幸运号码
// 给出一个N，求长度为2N的幸运号码的数量。由于数量很大，输出数量 Mod 10^9 + 7的结果即可

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

