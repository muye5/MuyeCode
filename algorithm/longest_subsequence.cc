// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)
// 最长递增子序列:最小差为d

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
using namespace std;

int longest_subsquence(const vector<int>& v) {
    int len = v.size(), mx = 1;
    vector<int> ad;
    ad.push_back(v[0]);
    for(int i = 1; i < len; ++i) {
        if(v[i] > ad.back()) {
            ad.push_back(v[i]);
            ++mx;
        }
        else {
            vector<int>::reverse_iterator it = ad.rbegin();
            for(; it != ad.rend(); ++it) {
                if(*it < v[i]) {
                    *(it-1) = v[i];
                    break;
                }
            }
            if(it == ad.rend()) ad[0] = v[i];
        }
    }
    cout << ad.back() << "\t";
    return mx;
}

int longest_subsquence_distance_d(const vector<int>& v, int d) {
    int len = v.size(), mx = 1;
    vector<int> ad;
    ad.push_back(v[0]);
    for(int i = 1; i < len; ++i) {
        if(v[i] > ad.back() + d) {
            ad.push_back(v[i]);
            ++mx;
        }
        else {
            vector<int>::reverse_iterator it = ad.rbegin();
            for(; it != ad.rend(); ++it) {
                if(*it < v[i]) {
                    if(v[i] > *it + d) *(it-1) = v[i];
                    break;
                }
            }
            if(it == ad.rend()) ad[0] = v[i];
        }
    }
    cout << ad.back() << "\t";
    return mx;
}

int main(int argc, char **argv) {
    vector<int> v;
    int cnt = 10;
    srand((unsigned)time(NULL));
    for(int i = 0; i < cnt; ++i) {
        v.push_back(rand() % 100 + 1);
        cout << setw(4) << v[i];
    }
    cout << endl;
    cout << longest_subsquence(v) << endl;
    cout << longest_subsquence_distance_d(v, 2) << endl;
    return 0;
}

