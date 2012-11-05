// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=484
// 4N的空间,让我汗了好久好久

#include <iostream>
using namespace std;

struct Node {
    int left, right;
    int num;
};

const int M = 5001;
int values[M];
Node seg_tree[4 * M];

void build_tree(int index, int l, int r) {
    seg_tree[index].left = l;
    seg_tree[index].right = r;
    seg_tree[index].num = 0;
    if(l == r) {
        return;
    } else {
        int m = (l + r) / 2;
        build_tree(2 * index, l, m);
        build_tree(2 * index + 1, m + 1, r);
    }
}

void insert_node(int index, int x) {
    if(seg_tree[index].left == x && seg_tree[index].right == x) {
        seg_tree[index].num = 1;
    } else {
        seg_tree[index].num += 1;
        int m = (seg_tree[index].left + seg_tree[index].right) / 2;
        if(x <= m) {
            insert_node(2 * index, x);
        } else {
            insert_node(2 * index + 1, x);
        }
    }
}

int query(int index, int l, int r) {
    if(seg_tree[index].left == l && seg_tree[index].right == r) {
        return seg_tree[index].num;
    } else {
        int num = 0;
        int m = (seg_tree[index].left + seg_tree[index].right) / 2;
        if(r <= m) {
            num += query(2 * index, l, r);
        } else if(l > m) {
            num += query(2 * index + 1, l, r);
        } else {
            num += query(2 * index, l, m);
            num += query(2 * index + 1, m + 1, r);
        }
        return num;
    }
}

int main(int argc, char **argv) {
    int cnt, num = 0;
    int n;
    while(cin >> n) {
        num = 0;
        build_tree(1, 0, n - 1);
        for(int i = 1; i <= n; ++i) {
            cin >> values[i];
            num += query(1, values[i], n - 1);
            insert_node(1, values[i]);
        }
        cnt = num;
        for(int i = 1; i <= n; ++i) {
            num = num - values[i] + n - 1 - values[i];
            if(cnt > num) {
                cnt = num;
            }
        }
        cout << cnt << endl;
    }
    return 0;
}

