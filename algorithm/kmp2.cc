// Copyright (c) 2014
// Author: Yanshi.WYS ()

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

void Print(vector<string>& result) {
    copy(result.begin(), result.end(), ostream_iterator<string>(cout, "\n"));
}

void KMP(const string& s, const string& pattern) {
    vector<string> totalMatch;
    vector<int> T(pattern.size() + 1, -1);
    int plen = pattern.size(), slen = s.size();
    for(int i = 0; i < plen; ++i) {
        T[i+1] = T[i] + 1;
        while(T[i+1] > 0 && pattern[i] != pattern[T[i+1] - 1]) {
            T[i+1] = T[T[i+1] - 1] + 1;
        }
    }

    for(int i = 0, j = 0; i < slen;) {
        if(j < 0 || s[i] == pattern[j]) {
            ++i; ++j;
            if(j == plen) {
                totalMatch.push_back(s.substr(i-j, j));
                j = T[j]; // if overlap allowed
                // j = 0;
            }
        } else j = T[j];
    }
    Print(totalMatch);
}

int main(int argc, char **argv) {
    KMP("abcdecdecdft", "cdec");
    return 0;
}
