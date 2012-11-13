// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// http://acm.nyist.net/JudgeOnline/status.php?pid=9
// Mayor's posters[POJ:2528好像处理离散化有问题]
// 原题目的原始线段数是10,000,000.若直接用来建造线段树会造成内存溢出
// 需要进行离散化:10,000张海报,总计20,000个点.
// 离散化后会大大减少数据的范围,但需注意在离散化过程中,原本不相邻的仍然要保证不相邻,原本相邻的依然要相邻.
// 之后用线段树解决.
// 这里学到的:
// 1.每次更新不应该更新到叶子节点,一旦可以判断出结果就应该停止更新
//   若再次更新,则需要将原始信息push_down一下.这样可以保存上次更新的信息.
// 2.每次查询,切记注意对边界的更改.这次我乱更改浪费了很多时间啊!

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int M = 20001;
class Transfer{
public:
    int x;
    int k;
public:
    Transfer() : x(0), k(0) {}
}cache[M]; // 用于离散化:对海报的端点数据排序.有陷阱哦!

int poster[M << 1]; // 存储离散化后的海报端点[2x - 1, 2x]为一个海报的两端
bool check_ids[M]; // 记录一个海报是否已经被计数过:因为一张海报可能出现在线段树的不同子树中!

class Node {
public:
    int l;
    int r;
    int id;
public:
    Node() : l(0), r(0), id(0) {}
    int middle() {
        return ((l + r) >> 1);
    }
}seg_tree[M << 4];

bool cmp(const Transfer& a, const Transfer& b) {
    if(a.x == b.x) {
        return (a.k < b.k);
    }
    return (a.x < b.x);
}

void build_tree(int l, int r, int index) {
    seg_tree[index].l = l;
    seg_tree[index].r = r;
    seg_tree[index].id = 0;
    if(l == r) {
        return;
    }
    int m = seg_tree[index].middle();
    build_tree(l, m, index << 1);
    build_tree(m + 1, r, index << 1 | 1);
}

void push_down(int parent) {
    if(seg_tree[parent].id == 0 || seg_tree[parent].l == seg_tree[parent].r) {
        return;
    }
    seg_tree[parent << 1].id = seg_tree[parent].id;
    seg_tree[parent << 1 | 1].id = seg_tree[parent].id;
    seg_tree[parent].id = 0;
}

void update_tree(int id, int L, int R, int index) {
    if(L <= seg_tree[index].l && seg_tree[index].r <= R) {
        seg_tree[index].id = id;
        return;
    }
    int m = seg_tree[index].middle();
    push_down(index);
    if(L <= m) {
        update_tree(id, L, R, index << 1); // 这里不要更改子节点的更新范围,比如更改成 [L, m],打错特错啊!
    }
    if(R > m) {
        update_tree(id, L, R, index << 1 | 1); // 这里一样,更新的范围是不应该变的,只要改变对更新范围和节点自身范围的判断即可!
    }
}

int query_tree(int L, int R, int index) {
    if(seg_tree[index].id > 0) {
        if(check_ids[seg_tree[index].id]) {
            return 0;
        } else {
            check_ids[seg_tree[index].id] = true;
            return 1;
        }
    }
    if(seg_tree[index].l == seg_tree[index].r) {
        return 0;
    }
    int m = seg_tree[index].middle();
    int num = 0;
    if(L <= m) {
        num += query_tree(L, R, index << 1); // 这里对子节点的查询范围一开始搞错了,浪费了很多时间,不要更改查询的范围.
    }
    if(R > m) {
        num += query_tree(L, R, index << 1 | 1); // 这里对子节点的查询范围一开始搞错了,浪费了很多时间,不要更改查询的范围.
    }
    return num;
}

int main(int argc, char **argv) {
    int c;
    cin >> c;
    while(c-- > 0) {
        int n;
        cin >> n;
        for(int i = 1; i <= 2 * n; ++i) {
            cin >> cache[i].x;
            cache[i].k = i;
        }
        sort(cache + 1, cache + 2 * n + 1, cmp);
        int cnt = 1;
        int tmp = cache[1].x;
        for(int i = 1; i <= 2 * n; ++i) {
            // 离散化处理陷阱
            if(cache[i].x == tmp) {
                poster[cache[i].k] = cnt;
            } else {
                if(cache[i - 1].x + 1 == cache[i].x) {
                    ++cnt;
                } else {
                    cnt += 2;
                }
                poster[cache[i].k] = cnt;
                tmp = cache[i].x;
            }
        }
        for(int i = 1; i <= 2 * n; ++i) {
        }
        build_tree(1, cnt, 1);
        for(int i = 1; i <= n; ++i) {
            update_tree(i, poster[2 * i - 1], poster[2 * i], 1);
        }
        memset(check_ids, 0, sizeof(check_ids) * sizeof(bool));
        cout << query_tree(1, cnt, 1) << endl;
    }
    return 0;
}

