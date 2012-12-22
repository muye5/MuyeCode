// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
//
// 两个大数相乘:char* multiply(char*,char*)(正整数)
// 给了两个字符串,每个都是代表了一个很长的10进制表示的数;
// 比如 char str1[] = "23456789009877666555544444"；char str2[] = "346587436598437594375943875943875",最后求出它们的乘积.
//
// A*B = (A1A2) * (B1B2) = (A1*B1)*10^(2*len) + (A1B2 + A2B1)*10^(len) + A2B2
// 注:
//  length(A) = length(B);
//  length(A1) = length(B1);
//  length(A2) = length(B2);
//  len = length(A2);

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <gtest/gtest.h>
using namespace std;

/*
 * 将左右操作数的位数补齐,用0填充
 */
size_t stralign(string &a, string &b) {
    size_t l = a.length() > b.length() ? a.length() : b.length();
    if(a.length() < l) {
        a.insert(a.begin(), l - a.length(), '0');
    }
    if(b.length() < l) {
        b.insert(b.begin(), l - b.length(), '0');
    }
    return l;
}

/*
 * 两个操作数相加
 */
string strplus(string a, string b) {
    stringstream s;
    size_t l = stralign(a, b);
    int carry = 0;
    for(int i = l - 1; i >= 0; --i) {
        int ca = (a[i] - '0') + (b[i] - '0') + carry;
        carry = ca / 10;
        s << (ca % 10);
    }
    s << carry;
    string r(s.str());
    reverse(r.begin(), r.end());
    size_t t = r.find_first_not_of('0');
    if(t == string::npos) {
        return string("");
    }
    return r.substr(t);
}
/*
 * 两个操作数相乘
 */
string multiply(string a, string b) {
    int l = stralign(a, b);
    if(l == 1) {
        int na, nb;
        stringstream(a) >> na;
        stringstream(b) >> nb;
        stringstream out;
        out << (na * nb);
        return out.str();
    }
    size_t m = l >> 1;
    size_t n = l - m;
    string a1 = a.substr(0, m);
    string a2 = a.substr(m);
    string b1 = b.substr(0, m);
    string b2 = b.substr(m);

    string s1 = multiply(a1, b1) + string(2 * n, '0');
    string s2 = multiply(a1, b2);
    string s3 = multiply(a2, b1);
    string s4 = multiply(a2, b2);
    s2 = strplus(s2, s3) + string(n, '0');
    s1 = strplus(s1, s2);
    return strplus(s1, s4);
}

class MultiplyTest : public ::testing::Test {
public:
    vector<int> va;
    vector<int> vb;
public:
#define CNT 100
    MultiplyTest() {
        srand((unsigned)time(NULL));
        for(int i = 0; i < CNT; ++i) {
            va.push_back(rand() % 10000);
            vb.push_back(rand() % 10000);
        }
    }
};

TEST_F(MultiplyTest, Integer) {
    vector<int>::iterator ita = va.begin();
    vector<int>::iterator itb = vb.begin();
    stringstream a;
    stringstream b;
    stringstream c;
    for(; ita != va.end(); ++ita, ++itb) {
        a.str("");
        b.str("");
        c.str("");
        a << *ita;
        b << *itb;
        c << (*ita) * (*itb);
        ASSERT_EQ(c.str(), multiply(a.str(), b.str())) << *ita << ", " << *itb;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

