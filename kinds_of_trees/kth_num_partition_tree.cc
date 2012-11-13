// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// http://poj.org/problem?id=2104
// http://blog.csdn.net/acceptedxukai/article/details/6937084
// 求索引区间内的Kth值
// 感觉有点类似快速排序,最后的叶子节点是排好序的.
// 记录了中间的排序过程
// 建树、更新、查询. 这里没有更新

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class Node {
public:
    int l;
    int r;
public:
    Node(int ll = 0, int rr = 0) : l(ll), r(rr) {}
};

int middle(int l, int r) {
    return (l + r) / 2;
}

const int N = 100001;

Node tree[N * 4];
int sorted[N];
int val[20][N];
int toleft[20][N];

void build_tree(int l, int r, int index, int dimension);
int query_tree(int k, int l, int r, int index, int dimension);

void build_tree(int l, int r, int index, int dimension) {
    tree[index].l = l;
    tree[index].r = r;
    if(l == r) {
        // 这里已经有了val[dimension][i],它是在 dimension - 1 时填入的;
        // 但是否还需对toleft[dimension][i]初始化? (toleft[dimension][i] = 0)
        // 不需要.因为后面会在使用之前进行初始化赋值.
        return;
    }

    int m = middle(l, r);
    // 为什么sorted[m]恰巧就是当前[l, r]的中值; sorted[]数组是不变的,而[l,r]的值是在不断变化的? Why...
    // 因为val[][]的每一层其实都是对区间[l, r]的一次排序,只是排序的标准是由中值来定的.类似于快排.
    // 所以排序后左右子区间[l, r]内的元素其实与sorted[l, r]内的元素是一样的,只是顺序不同,所以sorted[m]就是这个区间的中值
    int mid = sorted[m];
    // 这里先假设左侧全部是 mid, 然后再减去比 mid 小的元素个数, 那么这里可否根据 sorted[l...r] 来判断呢?
    // 能,正如上面分析的区间val[dimension][l, r]的元素与sorted[l, r]内的元素是相同的,只是顺序不同而已!
    int leftsame = m - l + 1;
    for(int i = l; i <= r; ++i) {
        if(val[dimension][i] < mid) { // 这里应该换成sorted[i] < mid 来判断
            --leftsame;
        }
    }

    int lpos = l; // 这里的 lpos 和 rpos 都是 val[dimension + 1] 维的下标
    int rpos = m + 1;
    for(int i = l; i <= r; ++i) {
        if(i == l) {
            toleft[dimension][i] = 0;
        } else {
            toleft[dimension][i] = toleft[dimension][i - 1]; // 这个toleft[][]的矩阵应该输出好好看看
        }
        if(val[dimension][i] < mid) {
            ++toleft[dimension][i];
            val[dimension + 1][lpos++] = val[dimension][i];
        } else if(val[dimension][i] > mid) {
            val[dimension + 1][rpos++] = val[dimension][i];
        } else {
            if(leftsame > 0) {
                --leftsame;
                ++toleft[dimension][i];
                val[dimension + 1][lpos++] = val[dimension][i];
            } else {
                val[dimension + 1][rpos++] = val[dimension][i];
            }
        }
    }
    build_tree(l, m, index << 1, dimension + 1);
    build_tree(m + 1, r, index << 1 | 1, dimension + 1);
}

int query_tree(int k, int l, int r, int index, int dimension) {
    if(l == r) {
        return val[dimension][l];
    }
    // 这里默认需要查询区间 [l, r] 是在 [tree[index].l, tree[index].r] 之间的
    int s; // [l, r] 区间里在左子树中的元素个数.
    int ss; // [tree[index].l, l - 1] 区间里在左子树中的元素个数
    if(l == tree[index].l) {
        ss = 0;
        s = toleft[dimension][r];
    } else {
        // 对应的是区间 [l, r] 包含在区间 [tree[index].l, tree[index].r] 之中
        ss = toleft[dimension][l - 1];
        s = toleft[dimension][r] - toleft[dimension][l - 1];
    }

    if(s >= k) {
        // 在左子树中寻找
        // 这两个新的坐标为什么是这样? 参数里的 l, r 以及 n 到底是什么含义? n 需要有什么限制?
        // 这里的l, r, n都是数组下标,它只与数组中元素的个数有关,并与数组中存什么元素没有关系.
        // 这里主要是对n的理解,它是元素个数.
        int newl = tree[index].l + ss;
        int newr = tree[index].l + ss + s - 1;
        return query_tree(k, newl, newr, index << 1, ++dimension);
    } else {
        // 在右子树中寻找
        // 这里注意下标的变化,去右子树中寻找时,原来的第k小的元素就不是第k小了
        // 成了第 k - s 小了.
        int m = middle(tree[index].l, tree[index].r);
        int g = l - 1 - tree[index].l + 1 - ss;
        int gg = r - l + 1 - s;
        int newl = m + 1 + g;
        int newr = m + 1 + g + gg - 1;
        return query_tree(k - s, newl, newr, index << 1 | 1, ++dimension);
    }
}

void print(int n) {
    for(int i = 1; i <= n; ++i) {
        cout << sorted[i] << "\t";
    }
    cout << endl;
    int d = (int)(log(n) / log(2.0)) + 1;
    for(int i = 0; i <= d; ++i) {
        for(int j = 1; j <= n; ++j) {
            cout << val[i][j] << "\t";
        }
        cout << endl;
        for(int j = 1; j <= n; ++j) {
            cout << toleft[i][j] << "\t";
        }
        cout << endl;
    }
}

int main(int argc, char **argv) {
    int n, m;
    while(cin >> n >> m) {
        for(int j = 1; j <= n; ++j) {
            cin >> val[0][j];
            sorted[j] = val[0][j];
        }
        sort(sorted + 1, sorted + n + 1);
        build_tree(1, n, 1, 0);
        int s, t, k;
        for(int h = 0; h < m; ++h) {
            cin >> s >> t >> k;
            cout << query_tree(k, s, t, 1, 0) << endl;
        }
        print(n);
    }
    return 0;
}

