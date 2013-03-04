// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// disjoin
// http://poj.org/problem?id=2524

#include <cstdio>
using namespace std;

int lnk[50001];

int query(int x) {
    if(lnk[x] == x) {
        return x;
    } else {
        return lnk[x] = query(lnk[x]);
    }
}

int main(int argc, char **argv) {
    int n, m;
    int x, y;
    int cnt = 0;
    while(scanf("%d%d", &n, &m) && m && n) {
        for(int i = 1; i <= n; ++i) {
            lnk[i] = i;
        }
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            int a = query(x);
            int b = query(y);
            if(a > b) {
                lnk[a] = b;
            } else if(a < b) {
                lnk[b] = a;
            }
        }
        int num = 0;
        for(int i = 1; i <= n; ++i) {
            if(lnk[i] == i) {
                ++num;
            }
        }
        printf("Case %d: %d\n", ++cnt, num);
    }
    return 0;
}

