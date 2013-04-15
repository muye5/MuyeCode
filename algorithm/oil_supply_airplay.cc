// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)
// http://blog.csdn.net/wcyoot/article/details/6427156
// 飞机加油

#include <iostream>
#include <cmath>
using namespace std;

int mincost(double n, double k) {
    double x = k, y, cost = 0.0;
    int h = 1;
    while(x < n) {
        ++h;
        y = x;
        x += k / (2 * h - 1);
    }
    y = n - y;
    cost = (h - 1) * k;
    cost += y * (2 * h - 1);
    return (int)ceil(cost);
}

int main(int argc, char **argv) {
    int n, k;
    cin >> n >> k;
    if(n <= k) {
        cout << n << endl;
    } else {
        cout << mincost(n, k) << endl;
    }
    return 0;
}

