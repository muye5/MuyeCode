// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>
#include <algorithm>
using namespace std;

int main() {
    int64_t st = -1, ed = -1;
    int64_t n, k, x, sum = 0;
    map<int64_t, vector<int64_t> > vmap;
    map<int64_t, vector<int64_t> >::iterator it;
    cin >> n >> k;
    for(int64_t i = 1; i <= n; ++i) {
        cin >> x;
        sum += x;
        if(sum == k && st == -1) {
            st = 1; ed = i;
        }
        it = vmap.find(sum);
        if(it != vmap.end()) {
            it->second.push_back(i);
        } else {
            vmap.insert(make_pair<int64_t, vector<int64_t> >(sum, vector<int64_t>(1, i)));
        }
    }
    if(st == -1) {
        for(map<int64_t, vector<int64_t> >::iterator its = vmap.begin(); its != vmap.end(); ++its) {
            x = its->first - k;
            it = vmap.find(x);
            if(it != vmap.end()) {
                vector<int64_t>& u = its->second;
                vector<int64_t>& v = it->second;
                vector<int64_t>::iterator iu = u.begin(), iv = v.begin();
                while(iu != u.end() && iv != v.end()) {
                    if(*iu > *iv) {
                        int64_t s = *iv + 1;
                        int64_t t = *iu;
                        if(st == -1 || st > s || (st == s && ed > t)) {
                            st = s;
                            ed = t;
                        }
                        break;
                    }
                    ++iu;
                    ++iv;
                }
            }
        }
    }
    if(st == -1)
        cout << "No Solution" << endl;
    else
        cout << st << ' ' << ed << endl;
    return 0;
}

