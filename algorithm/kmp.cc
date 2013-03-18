// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

void kmp_init(const string& t, vector<int>& p) {
    p.resize(t.length());
    p[0] = -1;
    int len = t.length();
    for(int i = 0; i < len - 1; ++i) {
        if(t[i+1] == t[p[i]+1]) {
            p[i+1] = p[i] + 1;
        } else {
            int j = p[i];
            while(j >= 0 && t[p[j]+1] != t[i+1]) {
                j = p[j];
            }
            if(j < 0) {
                p[i+1] = -1;
            } else {
                p[i+1] = p[j] + 1;
            }
        }
    }
}

void kmp_match(const string& s, const string& t, vector<int>& v) {
    vector<int> p;
    kmp_init(t, p);
    int i = -1, j = -1;
    while(true) {
        if(s[i+1] == t[j+1]) {
            ++i; ++j;
            if(j + 1 == (int)t.length()) {
                v.push_back(i-j);
                j = p[j];
            }
        } else {
            while(j > -1 && s[i+1] != t[j+1]) j = p[j];
            if(s[i+1] != t[j+1]) {
                ++i;
            } else {
                ++i; ++j;
            }
        }
        if(i + 1 == (int)s.length()) break;
    }
}

int main(int argc, char **argv) {
    int m = 100, n = 2;
    string s, t;
    vector<int> v;
    srand((unsigned)time(NULL));
    for(int i = 0; i < 90; ++i) {
        s.clear();
        t.clear();
        v.clear();
        for(int k = 0; k < m; ++k) {
            s.push_back(rand()%26+'a');
        }
        for(int k = 0; k < n; ++k) {
            t.push_back(rand()%26+'a');
        }
        kmp_match(s, t, v);
        if(v.size() == 0) continue;
        cout << "========================================================" << endl;
        cout << "s = " << s << endl;
        cout << "t = " << t << endl;
        for(vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
            cout << s.substr(*it, t.length()) << endl;
        }
    }
    return 0;
}

