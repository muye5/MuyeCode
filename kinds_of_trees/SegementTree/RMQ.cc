// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)
// RMQ : 查询[l:r]之间的最大值

#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int l, r, mx;
    Node(int ll = 0, int rr = 0, int mmx = 0) : l(ll), r(rr), mx(mmx) {}
    int middle() {
        return (l + r) >> 1;
    }
};

Node trs[40010];

void BuildTree(int l, int r, int index) {
    trs[index].l = l;
    trs[index].r = r;
    if(l == r) {
        return;
    }
    int m = trs[index].middle();
    BuildTree(l, m, index << 1);
    BuildTree(m+1, r, index << 1 | 1);
}

void Insert(int index, int inv, int v) {
    if(trs[index].l == inv && trs[index].r == inv) {
        trs[index].mx = v;
    } else {
        int m = trs[index].middle();
        if(m >= inv) Insert(index << 1, inv, v);
        else Insert(index << 1 | 1, inv, v);
        if(trs[index].mx < v) trs[index].mx = v;
    }
}

int Query(int l, int r, int index) {
    if(trs[index].l == l && trs[index].r == r) return trs[index].mx;
    else {
        int m = trs[index].middle();
        if(m < l) {
            return Query(l, r, index << 1 | 1);
        } else if(m >= r) {
            return Query(l, r, index << 1);
        } else {
            int ml = Query(l, m, index << 1);
            int mr = Query(m+1, r, index << 1 | 1);
            return max(ml, mr);
        }
    }
}

int main(void) {
    int m, n, x, l, r;
    cin >> n;
    BuildTree(1, n, 1);
    for(int i = 1; i <= n; ++i) {
        cin >> x;
        Insert(1, i, x);
    }
    cin >> m;
    for(int i = 0; i < m; ++i) {
        cin >> l >> r;
        cout << Query(l+1, r+1, 1) << endl;
    }
    return 0;
}

