// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// http://poj.org/problem?id=1001

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

char s[8];
int r[160];
int n, lr, dot;

void multiply(int v) {
    for(int i = 0; i < lr; ++i) {
        r[i] *= v;
    }
    for(int i = 0; i < lr; ++i) {
        int tmp = r[i], j = i;
        r[j] = tmp % 10;
        tmp /= 10;
        while(tmp > 0) {
            r[++j] += tmp % 10;
            tmp /= 10;
        }
        lr = max(lr, ++j);
    }
}

int main(int argc, char **argv) {
    while(cin >> s >> n) {
        dot = 0;
        int v = 0;
        for(int i = 0; i < 6; ++i) {
            if(s[i] == '.') {
                dot = i;
            } else {
                v = v * 10 + s[i] - '0';
            }
        }
        dot = (5 - dot) * n;
        if(v == 0) {
            cout << 0 << endl;
            continue;
        }
        memset(r, 0, sizeof(r));
        r[0] = 1;
        lr = 1;
        for(int i = 0; i < n; ++i) {
            multiply(v);
        }
        if(dot > 0) {
            int f = 0;
            while(r[f] == 0) {
                ++f;
            }
            if(f >= dot) {
                for(int i = lr - 1; i >= dot; --i) {
                    cout << r[i];
                }
            } else {
                lr = max(lr, dot);
                for(int i = lr - 1; i >= dot; --i) {
                    cout << r[i];
                }
                cout << '.';
                for(int i = dot - 1; i >= f; --i) {
                    cout << r[i];
                }
            }
        } else {
            for(int i = lr - 1; i >= 0; --i) {
                cout << r[i];
            }
        }
        cout << endl;
    }
    return 0;
}

