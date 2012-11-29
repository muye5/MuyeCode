// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)

// x & (x - 1) 的含义: 将x最右边的1变为0
// 两个例子:
// 1.统计一个数二进制表示的1的个数
// 2.判断一个数是否为2的n次方

#include <iostream>
#include <bitset>
using namespace std;

int count_bit_num(int x) {
    int num = 0;
    while(x) {
        ++num;
        x &= x - 1;
    }
    return num;
}

bool check_2(int x) {
    if(x & (x - 1)) {
        return false;
    }
    return true;
}

int main(int argc, char **argv) {
    int x = 102;
    // 顺便演示一下cout的二进制、八进制、十进制、十六进制的输出
    // 其实cout不支持二进制,只能用bitset模拟实现
    cout << "十进制: x = " << x << endl;
    cout << "八进制: x = 0" << oct << x << endl;
    cout << "十六进制: x = 0x" << hex << x << endl;
    cout << "二进制: x = " << bitset<sizeof(int) * 8>(x) << endl;
    cout << count_bit_num(x) << "个1" << endl;
    if(check_2(16)) {
        cout << "yes" << endl;
    }
    return 0;
}

