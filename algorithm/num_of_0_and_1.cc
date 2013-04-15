// 2013/4/10 ��һ����д��һ����,���ֲ��������Ӳ������ʱ������,̫���׷�����2B����
// ���int64_tд��int16_t���´�����ʱ���~~~�鲻������~~
// ����һ������a-b,ͳ�����������0-9���ֵĴ���.
// ���� 10-19,1����11�Σ�10,11,12,13,14,15,16,17,18,19,����11����2��1),�������ָ�����1��
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

