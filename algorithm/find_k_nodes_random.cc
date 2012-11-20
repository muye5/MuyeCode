// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
//
// 给定一个长度为N的链表. N很大,但是不确定N具体有多大.
// 任务是r:从这N个元素中随机取出k个元素,但是只能遍历这个链表一次.
// 需要保证从这个链表中取出的元素恰好有k个,且它们是完全随机的r(出现概率均等),如何实现?

// 算法:蓄水池抽样
// 先选中前k个, 从第k+1个元素到最后一个元素为止, 以k/i (i=k+1, k+2,...,N) 的概率选中第i个元素, 并且随机替换掉一个原先选中的元素.
// 这样遍历一次得到k个元素, 可以保证完全随机选取.这个算法叫做蓄水池抽样:
// 总是选择第一个对象,并使用1/2的概率选择第二个对象,使用1/3的概率选择第三个对象,以此类推.在过程结束时,每个对像被选中的概率都是1/n.
// 这里以k/i (i=k+1, k+2,...,N) 的概率选中第i个元素.
// 可以证明 对于前k个元素中的某一个最终能够被选中的情况是不被第k+1后的任意一个元素替换,其概率为k/n
// 对于第k个元素后面的某一个元素(假设为i)最终被选择的情况是,第i次被选中,从第i+1次以后不被任意元素替换,其概率为k/n.
//
// 我觉得这个很牛逼啊
// 与之等效的选择方法是:从N个元素中随机选择一个,与第一个元素交换.再从剩下的N-1个元素中随机选择一个与第二个元素交换.依此类推选出K个元素.

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int agrc, char **argv) {
    const int N = 10000, K = 10;
    int a[K];

    for(int i = 0; i < K; ++i) {
        a[i] = i + 1;
    }
    srand((unsigned)time(NULL));
    int p = 0, t = 0;
    for(int i = K + 1; i <= N; ++i) {
        p = rand() % i + 1;
        if(p <= K) {
            t = rand() % K;
            a[t] = i;
        }
    }
    for(int i = 0; i < K; ++i) {
        cout << a[i] << "\t";
    }
    cout << endl;
    return 0;
}

