// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// disjoin
// http://poj.org/problem?id=1611

#include <cstdio>
using namespace std;

int lnk[30001];

int query(int x) {
    if(lnk[x] == x) {
        return x;
    } else {
        return lnk[x] = query(lnk[x]);
    }
}

int main(int argc, char **argv) {
    int n, m;
    int x, k;
    while(scanf("%d%d", &n, &m) && (m != 0 || n != 0)) {
        for(int i = 0; i < n; ++i) {
            lnk[i] = i;
        }
        for(int i = 0; i < m; ++i) {
            scanf("%d", &k);
            int a, b = n;
            for(int j = 0; j < k; ++j) {
                scanf("%d", &x);
                a = query(x);
                if(a > b) {
                    lnk[a] = b;
                } else {
                    lnk[b] = a;
                    b = a;
                }
            }
        }
        int num = 0;
        for(int i = n - 1; i >= 0; --i) {
            if(query(lnk[i]) == 0){
                ++num;
            }
        }
        printf("%d\n", num);
    }
    return 0;
}

