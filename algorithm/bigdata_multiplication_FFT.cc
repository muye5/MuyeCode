// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <complex>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const double Pi = acos(-1);
const int LEN = 262145;
int ans[LEN] = {0};
complex<double> A[LEN], B[LEN], C[LEN];

int Init(string& sa, string& sb) {
    int la = sa.length();
    int lb = sb.length();
    int lc = 1;
    int l = max(la, lb) * 2 - 1;
    while(lc < l) lc <<= 1;
    for(int i = 0; i < la; ++i) A[i] = sa[la - i - 1] - '0';
    for(int i = la; i < lc; ++i) A[i] = 0;
    for(int i = 0; i < lb; ++i) B[i] = sb[lb - i - 1] - '0';
    for(int i = lb; i < lc; ++i) B[i] = 0;
    return lc;
}

void Bit_Reverse_Copy(complex<double> *p, int n) {
    // 这两段代码都能实现位反转置换,可惜我都看不懂!!!
    for(int i = 1, j = 0; i < n - 1; ++i) {
        for(int s = n; j ^= s >>= 1, ~j & s;);
        if(i < j) swap(p[i], p[j]);
    }
    /*
     * 懂了!位反转置换就是实现将0001位置的值换成1000位置去
     * 那么,只要我们能及时的找到与i对应的位置,这个问题就搞定了
     * 这里的j其实是模仿了从高位开始的加运算,每次加1,像i一样,不同的是进位的时候,j是向低位进位
    for(int i = 1, j = n >> 1, k; i < n - 1; ++i) {
        if(i < j) swap(p[i], p[j]);//这里保证了只交换一次,要不就又交换回来了,等于没有交换
        k = n >> 1;//这里其实是为了判断j的最高位的情况
        while(j >= k) {//看这里,如果j < k说明j的最高位是0,对j加1,不会产生进位,所以就可以直接把最高位至0,其实就相当于给j加了1
            //如果j的最高位是1,那么再加1就会产生进位,所以需要从左到右找到第一个不是1的位,把这一位变成1,就相当于进位了,之后把它前面的变成0
            //j -= k 之后,当前位从1变成了0,接着看下一位,也就是k >>= 1.直到找到第一个为0的位,也就是满足j < k的时候,通过循环外的 j += k将该位置成1
            j -= k;
            k >>= 1;
        }
        j += k;
    }
    */
}

void Iterative_FFT(complex<double> *p, int n, int inverse = 1) {
    Bit_Reverse_Copy(p, n);
    for(int m = 2; m <= n; m <<= 1) {
        complex<double> wn(cos(inverse * 2 * Pi / m), sin(inverse * 2 * Pi / m));
        for(int k = 0; k < n; k += m) {
            complex<double> w(1, 0);
            for(int j = 0; j < m >> 1; ++j) {
                complex<double> t = w * p[k + j + m / 2];
                complex<double> u = p[k + j];
                p[k + j] = u + t;
                p[k + j + m / 2] = u - t;
                w = w * wn;
            }

        }
    }
    if(inverse == -1) {
        for(int i = 0; i < n; ++i) p[i] /= n;
    }
}

int main() {
    string sa, sb;
    cin >> sa >> sb;
    int n = Init(sa, sb);
    Iterative_FFT(A, n);
    Iterative_FFT(B, n);
    for(int i = 0; i < n; ++i) C[i] = A[i] * B[i];
    Iterative_FFT(C, n, -1);
    for(int i = 0; i < n; ++i) ans[i] = C[i].real() + 0.5;
    for(int i = 0; i < n; ++i) {
        ans[i+1] += ans[i] / 10;
        ans[i] %= 10;
    }
    while(!ans[--n] && n);
    while(n >= 0) cout << ans[n--];
    cout << endl;
    return 0;
}
