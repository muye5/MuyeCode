// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// 数组有N个元素，每个元素可能是红色、白色或蓝色。现在要把它们按照颜色排序（左红中白右蓝）。写出代码。

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void sort_color(int *p, int *&q, const int &v) {
    while(p < q) {
        while(*p != v && p < q) {
            ++p;
        }
        while(*q == v && p < q) {
            --q;
        }
        if(p < q) {
            swap(*q--, *p++);
        }
    }
    if(*q == v) {
        --q;
    }
}

int main(int argc, char **argv) {
    const int len = 20;
    int a[len];
    srand((unsigned)time(NULL));
    for(int i = 0; i < len; ++i) {
        a[i] = rand() % 3;
        cout << a[i] << (i + 1 == len ? '\n' : ' ');
    }
    int *p = a, *q = a + len - 1;
    sort_color(p, q, 2);
    sort_color(p, q, 1);
    for(int i = 0; i < len; ++i) {
        cout << a[i] << (i + 1 == len ? '\n' : ' ');
    }
    return 0;
}

