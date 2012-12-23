// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// http://poj.org/problem?id=2980
// 这道题看似简单,写起来还不简单,一开始以为就是贪心算法,顶多在最后一次yell时判断一下,后来总是wa
// 看了别人的代码,终于明白了!
// 比如:当r = 10的时候,贪心很可能造成最后一次执行时只做了1 unit的任务,因此需要取消最后一次的yell来提高n_的效率,问题是这样就对了么?
// 不是的,因为很可能需要取消9次的yell,这样可以令这最后的十次每次都全部做r个unit,而这样就可以提高9次n_的效率.
// 所以说这个问题并不是贪心算法搞定的.

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

