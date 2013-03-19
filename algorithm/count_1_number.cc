// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)
// ����һ��ʮ����������N,д�´�1��ʼ,��N����������,��������г�������1�ĸ���.
// ����:n = 12,������5��1: 1,10,12������3��1,11����2��1,�ܹ�5��1.
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


