// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// merge sort in place
// with O(n) time and O(1) space
// �õ���AuxSort�㷨
// ����˼����ǽ����ݷֳ����ɿ�,֮��������һ������Ϊ��ʱ�����ռ���� merge ����
// һ���Ĵ�СѡΪ sqrt(N), ϸ����������:
//
// 1����nΪN��ƽ�����Ľ�������,��R[1:N]��Ϊm+2������zones��,��ΪZ(1)��Z(2)...,Z(m+2),����Z(m+2)���� N mod n ��Ԫ��,����������n��Ԫ��
// Ȼ��,������R[M]��ĳZ��Z[m+1]����,����Z(m+1)��Z(m+2)�ϲ���һ������,��ΪA(Auxiliary area).
//
// 2������Z(1)...Z(m),����ÿ��Z�ĵ�һ��Ԫ��������(��������ٱȽ�Z�����һ��Ԫ��)
// ���巽��Ϊ:�ҳ�R[1]��R[n+1]��...��R[(m-1)n+1]����Сֵ,��ΪR[(k-1)n+1],��Z(1)��Z(k)������.Ȼ����Z(2)...Z(m)���ظ�,ֱ���������
// ��ʱR[1]<=R[n+1]<=...<=R[(m-1)n+1].
//
// 3����Z(1)��Z(2)����A�Ŀռ����鲢����.���巽��Ϊ:���Ƚ���Z(1)��A��ǰn��Ԫ��A'.Ȼ���Z(2)��A'������Ĺ鲢���������Z(1)Z(2)
// �˴�TAOCP����һ������,��һ�¾������:��n=3����x1<y2<x2<y2<x3<y3,�����������:
// Z(1)         Z(2)         A'
// ��ʼ״̬:    x1 x2 x3     y1 y2 y3     a1 a2 a3
// ����Z(1):    a1 a2 a3     y1 y2 y3     x1 x2 x3
// ����x1:      x1 a2 a3     y1 y2 y3     a1 x2 x3
// ����y1:      x1 y1 a3     a2 y2 y3     a1 x2 x3
// ����x2:      x1 y1 x2     a2 y2 y3     a1 a3 x3
// ����y2:      x1 y1 x2     y2 a2 y3     a1 a3 x3
// ����x3:      x1 y1 x2     y2 x3 y3     a1 a3 a2
// ��A'�е�Ԫ��ȫ��������Ϻ�,�������,��ʱA'�е�Ԫ��˳����Ժ�ԭ����ͬ.ʹ��ͬ���ķ�������Z(2)��Z(3)��Z(3)��Z(4)��...��Z(m-1)��Z(m).
// ÿһ�ε�ʱ�临�Ӷ�ΪO(n),������һ��������ʱ�临�Ӷ�ΪO(mn)=O(N).ע��:��Ϊ��һ����֤��������,��һ����ɺ�,R[1:mn]���������.
//
// 4����R[N+1-2s:N](��R�е�ĩβ2s��Ԫ��,ע��sΪA�ĳ���)����������.��һ����ʱ�临�Ӷ�ΪO(s^2)=O(N).
// ע��:��һ����ɺ�,R[1:N-2s]��R[N+1-2s:N]�ѷֱ�����,����R[N+1-s:N](R�е�ĩβs��Ԫ��)ΪR������s��Ԫ��.
//
// 5��ʹ�õ�3���ķ�����R[1:N-2s]��R[N+1-2s:N-s]���鲢����,ʹ��R[N+1-s:N]�������ռ�.ֻ������ʱ��R[N+1-s:N]��R[N+1-2s:N-s]����,���Ҵ�������(�Ӵ�С)���鲢.
// ע��:��һ����ɺ�R[1:N-s]������,R[N+1-s:N]ΪR������s��Ԫ��(�������Ѵ���).
//
// 6���ٴζ�R[N+1-s:N]����������.��һ����ʱ�临�Ӷ�ΪO(s^2)=O(N).

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <gtest/gtest.h>
using namespace std;

void do_merge(int a[], int l, int m, int h) {
    int N = h - l + 1;
    // ÿ���е�Ԫ�ظ���
    int n = (int)sqrt(N);
    // �����k��Ӧ����������m, kz���Ԫ��m���ڵĶ�,�����뵹���ڶ��ν���,֮�����ڶ��������һ�κϲ���Ϊ��ʱ�Ľ����ռ�.
    int k = (N + n - 1) / n - 2, kz = (m - l + n) / n;
    swap_ranges(a+l+(kz-1)*n, a+l+kz*n, a+l+k*n);
    // �Կ鰴����Ԫ������
    for(int i = 0; i < k - 1; ++i) {
        int t = i;
        for(int j = i + 1; j < k; ++j) {
            if(a[l+t*n] > a[l+j*n]) {
                t = j;
            } else if(a[l+t*n] == a[l+j*n]) {
                if(a[l+t*n+n-1] > a[l+j*n+n-1]) { // ����һ��Ԫ����ͬ,��Ƚ����һ��Ԫ�����жϿ�Ĵ���.
                    t = j;
                }
            }
        }
        swap_ranges(a+l+t*n, a+l+t*n+n, a+l+i*n);
    }
    // ���ι鲢���ڵĿ�,�������������Ϊ��ʱ�����ռ�.
    for(int i = 0; i < k - 1; ++i) {
        swap_ranges(a+l+i*n, a+l+i*n+n, a+l+k*n);
        int x = l + (i + 1) * n;
        int y = l + k * n;
        int t = l + i * n;
        while(x < l + (i + 2) * n && y < l + (k + 1) * n) {
            if(a[y] <= a[x]) {
                swap(a[y++], a[t++]);
            } else {
                swap(a[x++], a[t++]);
            }
        }
        while(x < l + (i + 2) * n) {
            swap(a[t++], a[x++]);
        }
        while(y < l + (k + 1) * n) {
            swap(a[t++], a[y++]);
        }
    }
    int s = h - l + 1 - k * n; // ����������Ԫ�ظ���
    // �����2s��Ԫ������,�������Խ�����s��Ԫ�ؽ��������
    for(int i = h - 2 * s + 2; i <= h; ++i) {
        int t = i;
        while(t > l && a[t] < a[t - 1]) {
            swap(a[t], a[t-1]);
            --t;
        }
    }
    // ���swap_ranges �������,��Ϊ��ǰ��ֻ��һ��ʱ,���ǽ�����ʱ��û�н�s������Ԫ�ؽ���
    // ����: [1, 2, 3]; s = 2. ���������� [2, 1, 3] ������[3, 2, 1]
    // swap_ranges(a+(h-2*s+1 > 0 ? h-2*s+1 : 0), a+h-s+1, a+h-s+1);
    for(int i = h - s; i > h - 2 * s && i >= 0; --i) {
        swap(a[i], a[i+s]);
    }
    int x = h - 2 * s;
    int y = h;
    int t = h - s; // ������ܳ��� h - s < 0 Ŷ
    while(x >= l && y >= h - s + 1) {
        if(a[x] < a[y]) {
            swap(a[y--], a[t--]);
        } else {
            swap(a[x--], a[t--]);
        }
    }
    /*
     * �ⲽ����ʡ����,��Ϊ֮ǰ��x�Ѿ��ź�����
     while(x >= l) {
     swap(a[x--], a[t--]);
     }
     */
    while(y >= h - s + 1 && t >= 0) {
        swap(a[y--], a[t--]);
    }
    for(int i = h - s + 2; i <= h; ++i) {
        int t = i;
        while(t > l && a[t] < a[t-1]) {
            swap(a[t], a[t-1]);
            --t;
        }
    }
}

void merge_sort(int a[], int l, int h) {
    if(l == h) {
        return;
    }
    if(l + 1 == h) {
        if(a[l] > a[h]) {
            swap(a[l], a[h]);
        }
        return;
    }
    int m = (l + h) >> 1;
    merge_sort(a, l, m);
    merge_sort(a, m + 1, h);
    do_merge(a, l, m, h);
}

ptrdiff_t random(ptrdiff_t i) {
    return rand() % i;
}

TEST(merge_sort, foo) {
    const int len = 20;
    int a[len];
    srand((unsigned)time(NULL));
    ptrdiff_t (*prandom)(ptrdiff_t) = random;

    for(int k = 1; k < 10000; ++k ) {
        for(int i = 0; i < len; ++i) {
            a[i] = rand() % 100;
        }
        random_shuffle(a, a + len, prandom);
        merge_sort(a, 0, len - 1);
        for(int i = 0; i < len - 1; ++i) {
            ASSERT_LE(a[i], a[i+1]);
        }
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

