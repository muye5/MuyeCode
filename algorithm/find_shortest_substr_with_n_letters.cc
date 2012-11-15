// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// http://blog.163.com/zhaohai_1988/blog/static/20951008520128641030596/
// 原来这叫做"最短摘要算法"
// 哈哈今天又学一招
// 从一个长字符串中查找包含给定字符集合的最短子串
// 例如,长串为 "aaaaaaaaaacbebbbbbdddddddcccccc",字符集为{abcd},那么最短子串是"acbebbbbbd"
// 如果将条件改为"包含且只包含给定字符集合",你的算法和实现又将如何改动。

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <gtest/gtest.h>
using namespace std;

bool check(const map<char, int>& mmap) {
    for(map<char, int>::const_iterator it = mmap.begin(); it != mmap.end(); ++it) {
        if(it->second == 0) {
            return false;
        }
    }
    return true;
}

bool shortest_substr(const string& strs, const string& collection, string& result) {
    map<char, int> mmap;
    for(string::const_iterator it = collection.begin(); it != collection.end(); ++it) {
        mmap[*it] = 0;
    }
    string::const_iterator p = strs.begin();
    while(p != strs.end()) {
        if(mmap.find(*p) != mmap.end()) {
            break;
        }
        ++p;
    }
    if(p == strs.end()) {
        return false;
    }
    mmap[*p] = 1;
    string::const_iterator q = p + 1;
    while(q != strs.end()) {
        if(mmap.find(*q) != mmap.end()) {
            ++mmap[*q];
            if(check(mmap)) {
                break;
            }
        }
        ++q;
    }
    if(q == strs.end()) {
        return false;
    }
    int len = q - p + 1;
    string::const_iterator start = p;
    while(q != strs.end()) {
        while(mmap.find(*p) == mmap.end() || --mmap[*p] > 0) {
            ++p;
        }
        if(q - p + 1 < len) {
            len = q - p + 1;
            start = p;
        }
        ++p;
        while(++q != strs.end() && !check(mmap)) {
            if(mmap.find(*q) != mmap.end()) {
                ++mmap[*q];
                if(check(mmap)) {
                    break;
                }
            }
        }
    }
    result = strs.substr(start - strs.begin(), len);
    return true;
}

bool shortest_substr_without_gap(const string& strs, const string& collection, string& result) {
    set<char> sset(collection.begin(), collection.end());
    int ssize = static_cast<int>(sset.size());
    vector<string> vstr;
    string::const_iterator p = strs.begin(), q;
    while(p != strs.end()) {
        while(p != strs.end()) {
            if(sset.find(*p) != sset.end()) {
                break;
            }
            ++p;
        }
        if(p == strs.end()) {
            break;
        }
        q = p++;
        while(sset.find(*p) != sset.end()) {
            ++p;
        }
        if(p - q >= ssize) {
            vstr.push_back(strs.substr(q - strs.begin(), p - q));
        }
    }
    if(vstr.size() == 0) {
        return false;
    }
    string piece;
    result = strs;
    for(vector<string>::iterator it = vstr.begin(); it != vstr.end(); ++it) {
        if(shortest_substr(*it, collection, piece)) {
            if(result.length() > piece.length()) {
                result = piece;
            }
        }
    }
    if(result == strs && piece != strs) {
        return false;
    }
    return true;
}

TEST(shortest_substr, muye1) {
    string result;
    cout << "===================== shortest_substr ===========================" << endl;
    EXPECT_TRUE(shortest_substr("aaaaaaaaaacbebbbbbdddddddcccccc", "abcd", result));
    cout << "**********************************************" << endl;
    cout << "string:\"aaaaaaaaaacbebbbbbdddddddcccccc\"" << endl;
    cout << "collection:\"abcd\"" << endl;
    cout << "substr:\"" << result << "\"" << endl;
    cout << "**********************************************" << endl;
    EXPECT_TRUE(shortest_substr("deaabbdec", "abde", result));
    cout << "**********************************************" << endl;
    cout << "string:\"deaabbdec\"" << endl;
    cout << "collection:\"abde\"" << endl;
    cout << "substr:\"" << result << "\"" << endl;
    cout << "**********************************************" << endl;
    EXPECT_TRUE(shortest_substr("ajhdaasksssjjjjsdhdkasssdsaa", "dahks", result));
    cout << "**********************************************" << endl;
    cout << "string:\"ajhdaasksssjjjjsdhdkasssdsaa\"" << endl;
    cout << "collection:\"dahks\"" << endl;
    cout << "substr:\"" << result << "\"" << endl;
    cout << "**********************************************" << endl;
    EXPECT_FALSE(shortest_substr("abcefgh", "abcde", result));
    cout << "===================== shortest_substr ===========================" << endl;
}

TEST(shortest_substr_without_gap, muye2) {
    string result;
    cout << "===================== shortest_substr_without_gap ===========================" << endl;
    EXPECT_TRUE(shortest_substr_without_gap("abcdeaabbdec", "abde", result));
    cout << "**********************************************" << endl;
    cout << "string:\"abcdeaabbdec\"" << endl;
    cout << "collection:\"abde\"" << endl;
    cout << "substr:\"" << result << "\"" << endl;
    cout << "**********************************************" << endl;
    EXPECT_TRUE(shortest_substr_without_gap("ajhdaasksssjjjjsdhdkasssdsaa", "dahks", result));
    cout << "**********************************************" << endl;
    cout << "string:\"ajhdaasksssjjjjsdhdkasssdsaa\"" << endl;
    cout << "collection:\"dahks\"" << endl;
    cout << "substr:\"" << result << "\"" << endl;
    cout << "**********************************************" << endl;
    cout << "===================== shortest_substr_without_gap ===========================" << endl;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

