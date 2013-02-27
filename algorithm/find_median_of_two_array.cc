// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)
// 从两个排好序的数组中寻找中位数.
// 这个程序时间复杂度为O(log(max(m,n)))

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cassert>
using namespace std;

void print(vector<int> &v, int l, int r, ostream& out) {
    for(;l <= r; ++l) {
        out << v[l] << " ";
    }
    out << endl;
}

int find_median(vector<int> &a, int la, int ra, vector<int> &b, int lb, int rb, const int &key, ostream& out) {
    if(la > ra || lb > rb) {
        return -1;
    }
    int ma = la + ((ra - la) >> 1);
    int mb = lb + ((rb - lb) >> 1);
#ifdef __DEBUG__
    out << "A[" << la << ":" << ra << "] ";
    print(a, la, ra, out);
    out << "B[" << lb << ":" << rb << "] ";
    print(b, lb, rb, out);
    out << "A[" << ma << "] = " << a[ma] << endl;
    out << "B[" << mb << "] = " << b[mb] << endl;
#endif
    if(la == ra || lb == rb) {
        int z;
        if(ma + mb + 1 > key) {
            z = min(a[ma], b[mb]);
            z = max(z, (ma == 0 ? INT_MIN : a[ma-1]));
            z = max(z, (mb == 0 ? INT_MIN : b[mb-1]));
        } else {
            z = max(a[ma], b[mb]);
            z = min(z, (ma == (int)a.size()-1 ? INT_MAX : a[ma+1]));
            z = min(z, (mb == (int)b.size()-1 ? INT_MAX : b[mb+1]));
        }
        return z;
    }
    if(a[ma] < b[mb]) {
        int step = min(ra-ma, mb-lb);
        if(step%2 == 0) {
            return find_median(a, ma, ma+step, b, mb-step, mb, key, out);
        } else {
            return find_median(a, ma+1, ma+step, b, mb-step, mb-1, key, out);
        }
    } else if(a[ma] > b[mb]) {
        int step = min(ma-la, rb-mb);
        if(step%2 == 0) {
            return find_median(a, ma-step, ma, b, mb, mb+step, key, out);
        } else {
            return find_median(a, ma-step, ma-1, b, mb+1, mb+step, key, out);
        }
    } else {
        return a[ma];
    }
}

int main(int argc, char **argv) {
    int lena, lenb, key;
    srand((unsigned)time(NULL));
    vector<int> A, B, C;

    for(int g = 0; g < 10000; ++g) {
        A.clear();
        B.clear();
        C.clear();
        lena = rand() % 100 + 1;
        lenb = rand() % 100 + 1;
        for(int i = 0; i < lena; ++i) {
            int tmp = rand() % 1000;
            A.push_back(tmp);
            C.push_back(tmp);
        }
        for(int i = 0; i < lenb; ++i) {
            int tmp = rand() % 1000;
            B.push_back(tmp);
            C.push_back(tmp);
        }
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        sort(C.begin(), C.end());
        key = (C.size()-1) >> 1;
#ifndef __DEBUG__
        assert(find_median(A, 0, lena-1, B, 0, lenb-1, key, cout) == C[key]);
#else
        if(find_median(A, 0, lena-1, B, 0, lenb-1, key, cout) != C[key]) {
            cerr << "=================== Error ===================" << endl;
            cerr << "C[0:" << lenb+lena-1 << "] ";
            print(C, 0, lenb+lena-1, cerr);
            cerr << "lena = " << lena << endl;
            cerr << "lenb = " << lenb << endl;
            cerr << "Wrong : " << find_median(A, 0, lena-1, B, 0, lenb-1, key, cerr) << endl;
            cerr << "Right : " << C[key] << endl;
            cerr << "=================== ***** ===================" << endl;
            exit(-1);
        }
#endif
    }
    cout << "Test Done" << endl;
    return 0;
}

