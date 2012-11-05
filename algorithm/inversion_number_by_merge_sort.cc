// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;
int array[5001];
int src[5001];
int backup[5001];

int do_merge(int a[], int l, int m, int r) {
    int cnt = 0, i = l, j = m + 1, k = l - 1;
    while(i <= m && j <= r) {
        if(a[i] < a[j]) {
            backup[++k] = a[i++];
        } else {
            backup[++k] = a[j++];
            cnt += m - i + 1;
        }
    }
    while(i <= m) {
        backup[++k] = a[i++];
    }
    while(j <= r) {
        backup[++k] = a[j++];
    }
    copy(backup + l, backup + r + 1, array + l);
    return cnt;
}

int merge_sort(int a[], int l, int r) {
    if(l >= r) {
        return 0;
    } else {
        int m = (l + r) / 2;
        int cnt = merge_sort(a, l, m);
        cnt += merge_sort(a, m + 1, r);
        cnt += do_merge(a, l, m, r);
        return cnt;
    }
}


int main(int argc, char **argv) {
    int n = 0;
    while(cin >> n) {
        for(int i = 1; i <= n; ++i) {
            cin >> src[i];
            array[i] = src[i];
        }
        int k = merge_sort(array, 1, n);
        int t = k;
        for(int i = 1; i <= n; ++i) {
            k = k - src[i] + n - 1 - src[i];
            if(k < t) {
                t = k;
            }
        }
        cout << t << endl;
    }
    return 0;
}

