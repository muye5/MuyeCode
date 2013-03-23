// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <string>
#include <map>
#include <locale>
#include <stdexcept>
using namespace std;

class Comp {
public:
    Comp() {
        init();
    }

    bool operator()(const wstring& a, const wstring& b) {
        size_t la = a.length(), lb = b.length();
        size_t i = 0;
        while(i < la && i < lb) {
            int r = compare(a[i], b[i]);
            if(r > 0) return false;
            else if(r < 0) return true;
            else ++i;
        }
        if(i == la) return true;
        else return false;
    }

private:
    void init() {
        pinyinMap[L'张'] = "zhang";
        pinyinMap[L'王'] = "wang";
        pinyinMap[L'李'] = "li";
        pinyinMap[L'赵'] = "zhao";

        pinyinMap[L'三'] = "san";
        pinyinMap[L'四'] = "si";
        pinyinMap[L'五'] = "wu";
        pinyinMap[L'六'] = "liu";
    }

    int compare(const wchar_t& a, const wchar_t& b) {
        map<wchar_t, string>::const_iterator ita = pinyinMap.find(a);
        map<wchar_t, string>::const_iterator itb = pinyinMap.find(b);
        if(ita == pinyinMap.end() || itb == pinyinMap.end()) {
            throw new runtime_error("No PinYin Found");
        }
        if(ita->second > itb->second) return 1;
        else if(ita->second < itb->second) return -1;
        else return 0;
    }
private:
    map<wchar_t, string> pinyinMap;
};

int main(int argc, char **argv) {
    locale::global(locale(""));
    map<wstring, int, Comp> m;
    m.insert(make_pair<wstring, int>(L"张三", 20));
    m.insert(make_pair<wstring, int>(L"张四", 21));
    m.insert(make_pair<wstring, int>(L"张五", 22));
    m.insert(make_pair<wstring, int>(L"张六", 23));

    m.insert(make_pair<wstring, int>(L"王三", 24));
    m.insert(make_pair<wstring, int>(L"王四", 25));
    m.insert(make_pair<wstring, int>(L"王五", 26));
    m.insert(make_pair<wstring, int>(L"王六", 27));

    m.insert(make_pair<wstring, int>(L"李三", 28));
    m.insert(make_pair<wstring, int>(L"李四", 29));
    m.insert(make_pair<wstring, int>(L"李五", 30));
    m.insert(make_pair<wstring, int>(L"李六", 31));

    m.insert(make_pair<wstring, int>(L"赵三", 32));
    m.insert(make_pair<wstring, int>(L"赵四", 33));
    m.insert(make_pair<wstring, int>(L"赵五", 34));
    m.insert(make_pair<wstring, int>(L"赵六", 35));

    for(map<wstring, int>::const_iterator it = m.begin(); it != m.end(); ++it) {
        wcout << it->first << " : " << it->second << endl;
    }
    return 0;
}


