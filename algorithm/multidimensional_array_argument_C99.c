// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// �������ȿ��Ա�ʾ����ʼԪ�صĵ�ַ,Ҳ����ָ������ռ���ڴ�,����ȡ����������������������.

#include <stdio.h>

void array_argument_test(int (*p)[3], int n) {
    // ���Զ�ά����������ݷ���:����ָ�������ָ��,��֤a[2][3]��a����ָ��һλ�����ָ��(���ٿ�����ʿת��)
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 3; ++j) {
            printf("%d%c", p[i][j], ' ');
        }
        printf("\n");
    }
}

void array_test() {
    // �����������ĵ�ַ,�Ӳ���,sizeof����,ȡַ����!
    int b[3];
    printf("sizeof(b) : %d\n", sizeof(b)); // ����, ����������������ڴ���Ϣ�����ֽ�Ϊ��λ��, ����������Ԫ��Ϊ��λ��.

    int a[2][3];
    printf("&a[0][0] : %p\n", (void *)&a[0][0]); // �ɼ�, a, a[0], &a[0][0], &a, &a[0]ֵ����һ����,��ͬ����������������Ϣ.
    printf("a : %p\n", (void *)a);
    printf("a + 1 : %p\n", (void *)(a + 1)); // a + 1 �����aƫ����һ��int[3]����, 12 bytes, �ɼ�Ĭ���ǽ�a����һά����ָ���.��Ҳ�ʹ�����ʱ�� int (*)[3]���Ӧ.
    printf("sizeof(a) : %d\n", sizeof(a)); // !****����֮��****!sizeof a ������������ά����� byte ��. ����ƺ��ֺ� a + 1 �� a ��ƫ����ֻ�� 12 bytes ���Ǻܷ��ϰ� ~ ~
    printf("sizeof(*a) : %d\n", sizeof(*a)); // ������һά����� byte ��.
    printf("sizeof(a[0]) : %d\n", sizeof(a[0]));
    printf("sizeof(int[3]) : %d\n", sizeof(int[3]));

    int (*p)[2][3] = &a;
    printf("a : %p\n", (void *)a);
    printf("&a : %p\n", (void *)&a); // ��Ȼ a �� &a ��ֵһ��,���������ϵļӷ�����ȷ��һ��, ������:
    printf("&a + 1 : %p\n", (void *)(&a + 1)); // ����� a + 1��ƫ���ǲ�ͬ��,���ƫ����������ά���� 24 bytes.
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
    // �ɱ䳤����,C99���ӵ��µ������׼,ע��C++��C++,C99��C99;�������������ݵ�!ǰ����C�ı�׼.
    // ���Ա�����γ���ʱ,Ӧ������ gcc -std=c99
    // ���Ƕ��ڱ䳤������ֻ������auto��ľֲ�����,Ҳ����˵ֻ���ں����ڲ�����,�Ҳ���ʹstatic���.
    // �䳤����ĳ�������ִ��ʱȷ����.����һ��ȷ��֮��Ͳ����ٸı�.
    // ��˶��ڱ䳤��������sizeof����Ҳ�ӱ���ʱ���Ƴٵ�����ʱ.(˳��˵һ��,sizeof��������������,�������sizeof(i = 3),��ôִ��֮��i��ֵ����һ��Ϊ3)
    // ���ڱ䳤���������������:�䳤���鲻������ͨ����һ���ڶ���ʱ��ʼ��: int a[n] = {1, 2, 3};���Ǵ����.
    // ��α䳤�����޷���Ϊstruct����class�ĳ�Ա
    // �����ڱ䳤����Ĳ�������,ʹ�����·�ʽ (int k, int (*p)[k]),Ҳ����˵֮ǰ������ά����Ĳ���������Ҫ����ȷ��һάά����ʹ�ñ䳤�������ʱ,��ͨ����һ���������ݵ�.
    // ���������Ҫ�����ڲ����б��б䳤����֮ǰ.
    int m = 2, n = 3; // Ҳ���Դ��ⲿ����
    int b[n];
    int a[m][n];
    printf("============== In array_test_c99() ===============\n");
    a[0][0] = a[0][1] = a[0][2] = 1;
    a[1][0] = a[1][1] = a[1][2] = 2;
    array_argument_test_c99(n, a, m);

    printf("sizeof(b) : %d\n", sizeof(b));
    n = 5;
    printf("sizeof(b) : %d\n", sizeof(b)); // ���鳤��һ��ȷ���Ͳ����ٸı�

    // �ٿ�һ���������͵����泣��,��Ҳ��C99�ı�׼
    int *p = (int [2]){3, 4};
    printf("p[1] : %d\n", p[1]);
    array_argument_test_c99(3, (int [2][3]){1, 2, 3, 4, 5, 6}, 2);

}

int main(int argc, char **argv) {
    array_test();
    array_test_c99();
    return 0;
}

