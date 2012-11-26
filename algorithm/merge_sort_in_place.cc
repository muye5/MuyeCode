// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// merge sort in place
// with O(n) time and O(1) space
// 用到了AuxSort算法
// 整体思想就是将数据分成若干块,之后用其中一个块作为临时交换空间完成 merge 过程
// 一般块的大小选为 sqrt(N), 细化步骤如下:
//
// 1、令n为N的平方根的近似整数,将R[1:N]分为m+2个区（zones）,记为Z(1)、Z(2)...,Z(m+2),其中Z(m+2)包含 N mod n 个元素,其他均包含n个元素
// 然后,将包含R[M]的某Z与Z[m+1]交换,并将Z(m+1)和Z(m+2)合并成一个区域,记为A(Auxiliary area).
//
// 2、考虑Z(1)...Z(m),按照每个Z的第一个元素作排序(如相等则再比较Z的最后一个元素)
// 具体方法为:找出R[1]、R[n+1]、...、R[(m-1)n+1]的最小值,如为R[(k-1)n+1],则将Z(1)和Z(k)作交换.然后在Z(2)...Z(m)中重复,直到排序完成
// 此时R[1]<=R[n+1]<=...<=R[(m-1)n+1].
//
// 3、对Z(1)和Z(2)利用A的空间作归并排序.具体方法为:首先交换Z(1)与A的前n个元素A'.然后对Z(2)和A'作常规的归并排序并输出到Z(1)Z(2)
// 此处TAOCP举了一个例子,看一下就理解了:设n=3并且x1<y2<x2<y2<x3<y3,排序过程如下:
// Z(1)         Z(2)         A'
// 初始状态:    x1 x2 x3     y1 y2 y3     a1 a2 a3
// 交换Z(1):    a1 a2 a3     y1 y2 y3     x1 x2 x3
// 交换x1:      x1 a2 a3     y1 y2 y3     a1 x2 x3
// 交换y1:      x1 y1 a3     a2 y2 y3     a1 x2 x3
// 交换x2:      x1 y1 x2     a2 y2 y3     a1 a3 x3
// 交换y2:      x1 y1 x2     y2 a2 y3     a1 a3 x3
// 交换x3:      x1 y1 x2     y2 x3 y3     a1 a3 a2
// 当A'中的元素全部交换完毕后,排序完成,此时A'中的元素顺序可以和原来不同.使用同样的方法排序Z(2)和Z(3)、Z(3)和Z(4)、...、Z(m-1)和Z(m).
// 每一次的时间复杂度为O(n),所以这一步的整体时间复杂度为O(mn)=O(N).注意:因为上一步所证明的性质,这一步完成后,R[1:mn]已完成排序.
//
// 4、对R[N+1-2s:N](即R中的末尾2s个元素,注意s为A的长度)作插入排序.这一步的时间复杂度为O(s^2)=O(N).
// 注意:这一步完成后,R[1:N-2s]和R[N+1-2s:N]已分别排序,并且R[N+1-s:N](R中的末尾s个元素)为R中最大的s个元素.
//
// 5、使用第3步的方法对R[1:N-2s]和R[N+1-2s:N-s]作归并排序,使用R[N+1-s:N]作辅助空间.只不过此时是R[N+1-s:N]和R[N+1-2s:N-s]交换,并且从右往左(从大到小)作归并.
// 注意:这一步完成后R[1:N-s]已排序,R[N+1-s:N]为R中最大的s个元素(但次序已打乱).
//
// 6、再次对R[N+1-s:N]作插入排序.这一步的时间复杂度为O(s^2)=O(N).

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <gtest/gtest.h>
using namespace std;

void do_merge(int a[], int l, int m, int h) {
    int N = h - l + 1;
    // 每块中的元素个数
    int n = (int)sqrt(N);
    // 这里的k对应上面介绍里的m, kz标记元素m所在的段,将其与倒数第二段交换,之后倒数第二段与最后一段合并作为临时的交换空间.
    int k = (N + n - 1) / n - 2, kz = (m - l + n) / n;
    swap_ranges(a+l+(kz-1)*n, a+l+kz*n, a+l+k*n);
    // 对块按照首元素排序
    for(int i = 0; i < k - 1; ++i) {
        int t = i;
        for(int j = i + 1; j < k; ++j) {
            if(a[l+t*n] > a[l+j*n]) {
                t = j;
            } else if(a[l+t*n] == a[l+j*n]) {
                if(a[l+t*n+n-1] > a[l+j*n+n-1]) { // 若第一个元素相同,则比较最后一个元素来判断块的次序.
                    t = j;
                }
            }
        }
        swap_ranges(a+l+t*n, a+l+t*n+n, a+l+i*n);
    }
    // 依次归并相邻的块,将最后两个块作为临时交换空间.
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
    int s = h - l + 1 - k * n; // 最后两个块的元素个数
    // 对最后2s个元素排序,这样可以将最大的s个元素交换到最后
    for(int i = h - 2 * s + 2; i <= h; ++i) {
        int t = i;
        while(t > l && a[t] < a[t - 1]) {
            swap(a[t], a[t-1]);
            --t;
        }
    }
    // 这个swap_ranges 会出问题,因为当前面只有一段时,这是交换的时候没有将s中最大的元素交换
    // 例如: [1, 2, 3]; s = 2. 交换后变成了 [2, 1, 3] 而不是[3, 2, 1]
    // swap_ranges(a+(h-2*s+1 > 0 ? h-2*s+1 : 0), a+h-s+1, a+h-s+1);
    for(int i = h - s; i > h - 2 * s && i >= 0; --i) {
        swap(a[i], a[i+s]);
    }
    int x = h - 2 * s;
    int y = h;
    int t = h - s; // 这里可能出现 h - s < 0 哦
    while(x >= l && y >= h - s + 1) {
        if(a[x] < a[y]) {
            swap(a[y--], a[t--]);
        } else {
            swap(a[x--], a[t--]);
        }
    }
    /*
     * 这步可以省略了,因为之前的x已经排好序了
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

