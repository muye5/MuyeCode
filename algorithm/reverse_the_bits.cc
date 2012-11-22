// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <cstdio>
#include <climits> // for CHAR_BIT

int main(int argc, char **argv) {
    unsigned int v = 15;
    unsigned int r = v;
    int s = sizeof(int) * CHAR_BIT - 1;
    printf("v = %p\n", (void *)v);
    for(v >>= 1; v; v >>= 1) {
        r <<= 1;
        r |= v & 1;
        --s;
    }
    r <<= s;
    printf("r = %p\n", (void *)r);
    printf("s = %d\n", s);
    return 0;
}

