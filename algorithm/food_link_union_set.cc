// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// 并查集题目:食物链
// http://poj.org/problem?id=1182

#include <cstdio>
using namespace std;

int lnk[50001];
int rnk[50001];

int query_set(int x) {
    if(lnk[x] == x) {
        return x;
    } else {
        // 这是最最重要的一步,因为之前合并两个集合的时候,被合并的集合的根节点状态发生了改变,这样它原来的子节点状态也应该改变
        // 所以在查询的时候,记下当前节点的父节点,这样当查询到被合并集合里的节点的时候,就可以通过 (rnk[x] + rnk[tmp]) % 3 来更新当前的状态.
        // 这一步最妙,因为经过路径压缩后,所有的子节点都直接指向根节点.这样才可以正确的更新,一开始这单我没有想通.
        int tmp = lnk[x]; // 这个节点会是老的根节点
        lnk[x] = query_set(lnk[x]);
        rnk[x] = (rnk[x] + rnk[tmp]) % 3;
        return lnk[x];
    }
}

void union_set(int x, int y, int a, int b, int c) {
    if(c == 1) {
        // add y branch into x branch: x is the same with y
        rnk[b] = (rnk[x] - rnk[y] + 3) % 3;
    } else {
        // add y branch into x branch: x is not the same with y
        rnk[b] = (rnk[x] - rnk[y] + 2) % 3;
    }
    lnk[b] = a;
}

void init_set(int n) {
    for(int i = 1; i <= n; ++i) {
        lnk[i] = i;
        rnk[i] = 0;
    }
}

int main(int argc, char **argv) {
    int n, k, cnt = 0;
    int c, x, y;

    scanf("%d%d", &n, &k);
    init_set(n);
    for(int i = 0; i < k; ++i) {
        scanf("%d%d%d", &c, &x, &y);
        if(x > n || y > n || (c == 2 && x == y)) {
            ++cnt;
            continue;
        }
        int a = query_set(x);
        int b = query_set(y);
        if(a == b) {
            // in the same branch
            if(c == 1) {
                if(rnk[x] != rnk[y]) {
                    ++cnt;
                }
            } else {
                if(rnk[x] != (rnk[y] + 1)%3) {
                    ++cnt;
                }
            }
        } else {
            // union two branches
            union_set(x, y, a, b, c);
        }
    }
    printf("%d\n", cnt);
    return 0;
}

