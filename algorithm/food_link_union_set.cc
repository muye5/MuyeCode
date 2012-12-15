// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// ���鼯��Ŀ:ʳ����
// http://poj.org/problem?id=1182

#include <cstdio>
using namespace std;

int lnk[50001];
int rnk[50001];

int query_set(int x) {
    if(lnk[x] == x) {
        return x;
    } else {
        // ����������Ҫ��һ��,��Ϊ֮ǰ�ϲ��������ϵ�ʱ��,���ϲ��ļ��ϵĸ��ڵ�״̬�����˸ı�,������ԭ�����ӽڵ�״̬ҲӦ�øı�
        // �����ڲ�ѯ��ʱ��,���µ�ǰ�ڵ�ĸ��ڵ�,��������ѯ�����ϲ�������Ľڵ��ʱ��,�Ϳ���ͨ�� (rnk[x] + rnk[tmp]) % 3 �����µ�ǰ��״̬.
        // ��һ������,��Ϊ����·��ѹ����,���е��ӽڵ㶼ֱ��ָ����ڵ�.�����ſ�����ȷ�ĸ���,һ��ʼ�ⵥ��û����ͨ.
        int tmp = lnk[x]; // ����ڵ�����ϵĸ��ڵ�
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

