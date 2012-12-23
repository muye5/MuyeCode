// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// http://poj.org/problem?id=2980
// ����⿴�Ƽ�,д����������,һ��ʼ��Ϊ����̰���㷨,���������һ��yellʱ�ж�һ��,��������wa
// ���˱��˵Ĵ���,����������!
// ����:��r = 10��ʱ��,̰�ĺܿ���������һ��ִ��ʱֻ����1 unit������,�����Ҫȡ�����һ�ε�yell�����n_��Ч��,�����������Ͷ���ô?
// ���ǵ�,��Ϊ�ܿ�����Ҫȡ��9�ε�yell,����������������ʮ��ÿ�ζ�ȫ����r��unit,�������Ϳ������9��n_��Ч��.
// ����˵������Ⲣ����̰���㷨�㶨��.

#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char **argv) {
    int a, b, c, r;
    int h[50];
    while(cin >> a >> b >> c >> r && a + b + c + r != 0) {
        int rc = (100 + r - 1) / r * c;
        int n = (100 + r + 1) / (r + 2);
        for(int i = 0; i < n; ++i) {
            h[i] = a * i + (100 - (r + 2) * i + r - 1) / r * a + b * i + (100 - (r - 1) * i + r - 1) / r * b;
        }
        int tmp = a * n + b * n + (100 - (r - 1) * n + r - 1) / r * b;
        for(int i = 0; i < n; ++i) {
            if(tmp > h[i]) {
                tmp = h[i];
            }
        }
        cout << tmp + rc << endl;
    }
    return 0;
}

