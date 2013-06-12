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
    for(int i = 1, j = n >> 1, k; i < n - 1; ++i) {
        if(i < j) swap(p[i], p[j]);
        k = n >> 1;
        while(j >= k) {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
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
