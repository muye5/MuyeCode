// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// 给定一个无序的整数数组,怎么找到第一个大于0,并且不在此数组的最小整数.
// 比如[1,2,0] 返回 3, [3,4,-1,1] 返回 2r.最好能O(1)空间和O(n)时间
// http://blog.csdn.net/ju136/article/details/8153274

#include <iostream>
using namespace std;

int find(int *a, int n) {
    int i = n, t, temp;
    if (!a || n <= 0) return -1;

    while ((--i) >= 0) {
        while (0 < a[i] && a[i] < n && i != a[i]) {
            t = a[i];
            if (a[i] == a[t]) break;
            temp = a[i];
            a[i] = a[t];
            a[t] = temp;
        }
    }

    for (i = 1; i < n; ++i) {
        if (a[i] != i) {
            return i;
        }
    }

    return (n + (a[0] == n));
}

int main(int argc, char **argv) {
    const int len = 5;
    int a[len] = {2, 5, -1, 4, 7};
    cout << find(a, len) << endl;
    return 0;
}

