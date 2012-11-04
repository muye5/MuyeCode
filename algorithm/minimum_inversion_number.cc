// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=484

#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

const int M = 5001;
int tmp[5001];
int array[5001];
int backup[5001];

template <class T>
int do_merge(T a[], T b[], int l, int m, int r) {
    int i = l, j = m + 1, k = l - 1, cnt = 0;
    while(i <= m && j <= r) {
        if(a[i] < a[j]) {
            b[++k] = a[i++];
        } else {
            b[++k] = a[j++];
            cnt += m - i + 1;
        }
    }
    while(i <= m) {
        b[++k] = a[i++];
    }
    while(j <= r) {
        b[++k] = a[j++];
    }
    copy(b + l, b + r + 1, a + l);
    return cnt;
}

template <class T>
int merge_sort(T a[], T b[], int l, int r) {
    if(l >= r) {
        return 0;
    }
    int m = (l + r) / 2;
    int cnt = merge_sort(a, b, l, m);
    cnt += merge_sort(a, b, m + 1, r);
    cnt += do_merge(a, b, l, m, r);
    return cnt;
}

int main(int argc, char **argv) {
    int n;
    while(cin >> n) {
        for(int i = 1; i <= n; ++i) {
            cin >> array[i];
            backup[i] = array[i];
        }
        int num = INT_MAX;
        int cnt = merge_sort(array, tmp, 1, n);
        for(int i = 1; i <= n; ++i) {
            cnt = cnt - backup[i] + n - 1 - backup[i];
            if(cnt < num) {
                num = cnt;
            }
        }
        cout << num << endl;
    }
    return 0;
}

