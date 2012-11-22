// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// 更多精彩: http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
// 这个宏定义搞的很高深啊!
// 先看 two bit的反转:
// 00 <===> 00
// 01 <===> 10
// 10 <===> 01
// 11 <===> 11
// 所以原本的 [0, 1, 2, 3] 变为 [0, 2, 1, 3]
// 故对于 8 bits 的 unsigned char, 只需分 3 次 递归反转 log8 = 3
/*
                  8
             /         \
           4             4
       /      \       /      \
     2          2   2          2
*/

#include <cstdio>

int main(int argc, char **argv) {
    static const unsigned char BitReverseTable[256] = {
#define R2(n) n, n + 2 * 64, n + 1* 64, n + 3 * 64
#define R4(n) R2(n), R2(n + 2 * 16), R2(n + 1 * 16), R2(n + 3 * 16)
#define R6(n) R4(n), R4(n + 2 * 4), R4(n + 1 * 4), R4(n + 3 * 4)
        R6(0), R6(2), R6(1), R6(3)
    };
    unsigned int v = 15;
    unsigned int c = (BitReverseTable[v & 0xff] << 24
                      | BitReverseTable[(v >> 8) & 0xff] << 16
                      | BitReverseTable[(v >> 16) & 0xff] << 8
                      | BitReverseTable[(v >> 24) & 0xff]);
    unsigned char *p = (unsigned char *)&v;
    unsigned char *q = (unsigned char *)&c;
    q[3] = BitReverseTable[p[0]];
    q[2] = BitReverseTable[p[1]];
    q[1] = BitReverseTable[p[2]];
    q[0] = BitReverseTable[p[3]];
    printf("v = %p\n", (void *)v);
    printf("c = %p\n", (void *)c);

    return 0;
}

