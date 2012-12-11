// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// http://poj.org/problem?id=2559
// 主要是对左右第一个比自己小的元素的查询时使用的方法,很犀利的是O(n)

#include <cstdio>
#include <cstring>
#include <stdint.h>
using namespace std;

int64_t height[100000];
int left[100000], right[100000];

int main(int argc, char **argv) {
    int i, j, n;
    while(scanf("%d", &n) != EOF && n != 0) {
        memset(left, 0, n * sizeof(int));
        memset(right, 0, n * sizeof(int));
        for(i = 0; i < n; ++i) {
            scanf("%lld", height + i);
        }
        left[0] = -1;
        for(i = 0; i < n; ++i) {
            for(j = i - 1; j >= 0 && height[j] >= height[i]; j = left[j]);
            left[i] = j;
        }
        right[n-1] = n;
        for(i = n - 1; i >= 0; --i) {
            for(j = i + 1; j < n && height[j] >= height[i]; j = right[j]);
            right[i] = j;
        }
        int64_t mx = 0;
        for(i = 0; i < n; ++i) {
            if(height[i] * (right[i] - left[i] - 1) > mx) {
                mx = height[i] * (right[i] - left[i] - 1);
            }
        }
        printf("%lld\n", mx);
    }
    return 0;
}

