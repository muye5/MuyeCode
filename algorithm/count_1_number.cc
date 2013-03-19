// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)
// 给定一个十进制正整数N,写下从1开始,到N的所有正数,计算出其中出现所有1的个数.
// 例如:n = 12,包含了5个1: 1,10,12共包含3个1,11包含2个1,总共5个1.
#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    int factor[] = {
        0, 1, 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000, 1000000000
    };
    vector<int> g;
    int n, x;
    cin >> n;
    x = n;
    while(n/10) {
        g.push_back(n%10);
        n /= 10;
    }
    g.push_back(n);
    int k = g.size();
    int m = 0;
    while(k > 0) {
        m += g[k-1] * (k-1) * factor[k-1];
        if(g[k-1] > 1) {
            m += factor[k];
        } else if(g[k-1] == 1) {
            m += x % factor[k] + 1;
        }
        --k;
    }
    cout << m << endl;
    return 0 ;
}


