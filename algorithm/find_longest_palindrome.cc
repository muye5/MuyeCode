// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
//
// Manacher算法
// O(n)时间找出字符串最长回文序列.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
using namespace std;

int find_longest_palindrome(const string& strs) {
    string s("##");
    for(string::const_iterator it = strs.begin(); it != strs.end(); ++it) {
        s.push_back(*it);
        s.push_back('#');
    }
    int len = s.length(), id = 0, mx = 0;
    vector<int> p(len, 0);
    for(int i = 1; i < len; ++i) {
        p[i] = mx > i ? min(mx - i, p[2*id-i]) : 1;
        while(s[i+p[i]] == s[i-p[i]]) {
            ++p[i];
        }
        if(i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }

    int start = 0, sublen = 0;
    for(int i = 1; i < len; ++i) {
        if(p[i] > sublen) {
            sublen = p[i];
            start = i;
        }
    }
    cout << "===========================================" << endl;
    cout << "string = \"" << strs << "\"" <<  endl;
    cout << "start = " << (start - sublen) / 2 << " length = " << sublen - 1 << endl;
    cout << "longest palindromes = \"" << strs.substr((start - sublen) / 2, sublen - 1) << "\"" << endl;
    cout << "===========================================" << endl;
    return sublen - 1;
}

TEST(find_longest_palindrome, palindromes) {
    EXPECT_TRUE(1 == find_longest_palindrome("abcdefgh"));
    EXPECT_TRUE(4 == find_longest_palindrome("habbafgh"));
    EXPECT_TRUE(12 == find_longest_palindrome("abcdeffedcba"));
    EXPECT_TRUE(12 == find_longest_palindrome("abccbaabccba"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

