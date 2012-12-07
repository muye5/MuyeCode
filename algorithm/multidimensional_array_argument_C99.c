// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// 数组名既可以表示其起始元素的地址,也可以指自身所占的内存,具体取决于数组名参与的运算决定.

#include <stdio.h>

void array_argument_test(int (*p)[3], int n) {
    // 测试多维数组参数传递方法:传递指向数组的指针,验证a[2][3]的a就是指向一位数组的指针(至少可以隐士转换)
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 3; ++j) {
            printf("%d%c", p[i][j], ' ');
        }
        printf("\n");
    }
}

void array_test() {
    // 测试数组名的地址,加操作,sizeof操作,取址操作!
    int b[3];
    printf("sizeof(b) : %d\n", sizeof(b)); // 首先, 数组名保存的数组内存信息是以字节为单位的, 不是以数组元素为单位的.

    int a[2][3];
    printf("&a[0][0] : %p\n", (void *)&a[0][0]); // 可见, a, a[0], &a[0][0], &a, &a[0]值都是一样的,不同的是其他的类型信息.
    printf("a : %p\n", (void *)a);
    printf("a + 1 : %p\n", (void *)(a + 1)); // a + 1 相对于a偏移了一个int[3]数组, 12 bytes, 可见默认是将a当做一维数组指针的.这也和传参数时的 int (*)[3]想对应.
    printf("sizeof(a) : %d\n", sizeof(a)); // !****诡异之处****!sizeof a 包含了整个二维数组的 byte 数. 这点似乎又和 a + 1 到 a 的偏移量只有 12 bytes 不是很符合啊 ~ ~
    printf("sizeof(*a) : %d\n", sizeof(*a)); // 这便成了一维数组的 byte 数.
    printf("sizeof(a[0]) : %d\n", sizeof(a[0]));
    printf("sizeof(int[3]) : %d\n", sizeof(int[3]));

    int (*p)[2][3] = &a;
    printf("a : %p\n", (void *)a);
    printf("&a : %p\n", (void *)&a); // 虽然 a 和 &a 的值一样,但是在其上的加法操作确不一样, 看下面:
    printf("&a + 1 : %p\n", (void *)(&a + 1)); // 这个与 a + 1的偏移是不同的,这个偏移是整个二维数组 24 bytes.
    printf("p : %p\n", (void *)p);
    printf("p + 1 : %p\n", (void *)(p + 1));

    a[0][0] = a[0][1] = a[0][2] = 1;
    a[1][0] = a[1][1] = a[1][2] = 2;
    array_argument_test(a, 2);
}

void array_argument_test_c99(int n, int (*p)[n], int m) {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            printf("%d%c", p[i][j], ' ');
        }
        printf("\n");
    }
}

void array_test_c99() {
    // 可变长数组,C99增加的新的数组标准,注意C++是C++,C99是C99;这两个并不兼容的!前者是C的标准.
    // 所以编译这段程序时,应该是用 gcc -std=c99
    // 但是对于变长的数组只可以是auto类的局部变量,也就是说只能在函数内部定义,且不能使static类别.
    // 变长数组的长度是在执行时确定的.而且一旦确定之后就不能再改变.
    // 因此对于变长数组名的sizeof操作也从编译时期推迟到运行时.(顺带说一句,sizeof操作不进行运算,即如果有sizeof(i = 3),那么执行之后i的值并不一定为3)
    // 对于变长数组的限制有如下:变长数组不能像普通数组一样在定义时初始化: int a[n] = {1, 2, 3};这是错误的.
    // 其次变长数组无法成为struct或者class的成员
    // 最后对于变长数组的参数传递,使用如下方式 (int k, int (*p)[k]),也就是说之前定长二维数组的参数传递需要的明确的一维维数在使用变长数组参数时,是通过另一个参数传递的.
    // 这个参数需要出现在参数列表中变长数组之前.
    int m = 2, n = 3; // 也可以从外部输入
    int b[n];
    int a[m][n];
    printf("============== In array_test_c99() ===============\n");
    a[0][0] = a[0][1] = a[0][2] = 1;
    a[1][0] = a[1][1] = a[1][2] = 2;
    array_argument_test_c99(n, a, m);

    printf("sizeof(b) : %d\n", sizeof(b));
    n = 5;
    printf("sizeof(b) : %d\n", sizeof(b)); // 数组长度一旦确定就不会再改变

    // 再看一个数组类型的字面常量,这也是C99的标准
    int *p = (int [2]){3, 4};
    printf("p[1] : %d\n", p[1]);
    array_argument_test_c99(3, (int [2][3]){1, 2, 3, 4, 5, 6}, 2);

}

int main(int argc, char **argv) {
    array_test();
    array_test_c99();
    return 0;
}

