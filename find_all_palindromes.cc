// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
//
// 找出字符串中所有的回文序列
//


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int longest_palindrome(vector<int> &p, const int& tag) {
    int len = p.size(), sublen = 0, start = 0;
    for(int i = 1; i < len; ++i) {
        if(p[i] > sublen) {
            sublen = p[i];
            start = i;
        }
    }
    for(int i = start - sublen + 1; i < start + sublen; ++i) {
        p[i] = tag;
    }
    return sublen;
}

void find_all_palindromes(const string& strs) {
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

    int tag = 0;
    while(longest_palindrome(p, --tag) > 1);
    tag = 0;
    cout << "====================================" << endl;
    cout << "string = \"" << strs << "\"" << endl;
    cout << tag << ": \"" << s[2];
    for(int i = 4; i < len; i += 2) {
        if(p[i-2] != p[i]) {
            cout << "\"\n" << ++tag << ": \"" << s[i];
        } else {
            cout << s[i];
        }
    }
    cout << "\"" << endl;
    cout << "====================================" << endl;
}

int main(int argc, char **argv) {
    find_all_palindromes("a");
    find_all_palindromes("abc");
    find_all_palindromes("habbafg");
    find_all_palindromes("abccbaabccba");
    return 0;
}

