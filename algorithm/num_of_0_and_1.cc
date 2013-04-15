// 2013/4/10 这一题我写了一晚上,发现不能再脑子不清楚的时候做题,太容易犯各种2B错误
// 错吧int64_t写成int16_t导致大数据时溢出~~~查不出来啊~~
// 给出一段区间a-b,统计这个区间内0-9出现的次数.
// 比如 10-19,1出现11次（10,11,12,13,14,15,16,17,18,19,其中11包括2个1),其余数字各出现1次
#include <iostream>
#include <stdint.h>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

uint64_t fa[10] = {0LL};
uint64_t fb[10] = {0LL};


uint64_t POW(uint64_t i) {
    uint64_t ans = 1;
    while(i--) {
        ans *= 10;
    }
    return ans;
}

void num(vector<uint64_t>& v, int i, uint64_t *p) {
    uint64_t x = v[i-1];
    uint64_t k = POW(i - 1);
    uint64_t h = k / 10 * (i - 1);
    if(i > 1) {
        ++p[x];
        while(x) {
            p[--x] += k;
            for(int j = 0; j < 10; ++j) {
                p[j] += h;
            }
        }
        if(i == (int)v.size()) {
            uint64_t t = 0, j = i;
            while(--j) t = (t + 1) * 10;
            p[0] -= t;
        }
        h = i;
        k = 0;
        while(--h) {
            k = k * 10 + v[h-1];
        }
        p[v[i-1]] += k;
        num(v, i - 1, p);
    } else {
        do {
            ++p[x];
        } while(x--);
    }
}

void factor(uint64_t n, vector<uint64_t>& v) {
    v.clear();
    while(n / 10) {
        v.push_back(n%10);
        n /= 10;
    }
    v.push_back(n);
}


int main(void) {
    uint64_t a, b;
    cin >> a >> b;
    vector<uint64_t> v;
    factor(a-1, v);
    num(v, v.size(), fa);
    factor(b, v);
    num(v, v.size(), fb);

    for(int i = 0; i < 10; ++i) {
        cout << fb[i] - fa[i] << endl;
    }
    return 0;
}

