// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// http://acm.nyist.net/JudgeOnline/status.php?pid=9
// Mayor's posters[POJ:2528��������ɢ��������]
// ԭ��Ŀ��ԭʼ�߶�����10,000,000.��ֱ�����������߶���������ڴ����
// ��Ҫ������ɢ��:10,000�ź���,�ܼ�20,000����.
// ��ɢ�������������ݵķ�Χ,����ע������ɢ��������,ԭ�������ڵ���ȻҪ��֤������,ԭ�����ڵ���ȻҪ����.
// ֮�����߶������.
// ����ѧ����:
// 1.ÿ�θ��²�Ӧ�ø��µ�Ҷ�ӽڵ�,һ�������жϳ������Ӧ��ֹͣ����
//   ���ٴθ���,����Ҫ��ԭʼ��Ϣpush_downһ��.�������Ա����ϴθ��µ���Ϣ.
// 2.ÿ�β�ѯ,�м�ע��Ա߽�ĸ���.������Ҹ����˷��˺ܶ�ʱ�䰡!

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
}cache[M]; // ������ɢ��:�Ժ����Ķ˵���������.������Ŷ!

int poster[M << 1]; // �洢��ɢ����ĺ����˵�[2x - 1, 2x]Ϊһ������������
bool check_ids[M]; // ��¼һ�������Ƿ��Ѿ���������:��Ϊһ�ź������ܳ������߶����Ĳ�ͬ������!

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
        update_tree(id, L, R, index << 1); // ���ﲻҪ�����ӽڵ�ĸ��·�Χ,������ĳ� [L, m],����ش�!
    }
    if(R > m) {
        update_tree(id, L, R, index << 1 | 1); // ����һ��,���µķ�Χ�ǲ�Ӧ�ñ��,ֻҪ�ı�Ը��·�Χ�ͽڵ�����Χ���жϼ���!
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
        num += query_tree(L, R, index << 1); // ������ӽڵ�Ĳ�ѯ��Χһ��ʼ�����,�˷��˺ܶ�ʱ��,��Ҫ���Ĳ�ѯ�ķ�Χ.
    }
    if(R > m) {
        num += query_tree(L, R, index << 1 | 1); // ������ӽڵ�Ĳ�ѯ��Χһ��ʼ�����,�˷��˺ܶ�ʱ��,��Ҫ���Ĳ�ѯ�ķ�Χ.
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
            // ��ɢ����������
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

