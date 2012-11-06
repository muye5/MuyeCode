// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// 有一队人,每个人都知道自己的身高A[N]和前面比自己高的人数Higher[N],队伍解散后怎么才能恢复队伍?

#include <iostream>
#include <ctime>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

class Person {
private:
    int rank;
    static bool flag;
public:
    int height;
    int higher;
public:
    Person(int rk, int ht) : rank(rk), height(ht), higher(0) {}
    Person(const Person& p) {
        rank = p.rank;
        height = p.height;
        higher = p.higher;
    }
    friend void queue_init(vector<Person>& v, int num);
    friend bool queue_check(vector<Person>& v);
    friend bool operator<(const Person& p1, const Person& p2) {
        if(flag) {
            if(p1.height == p2.height) {
                return (p1.rank < p2.rank);
            }
            return (p1.height > p2.height);
        } else {
            return (p1.rank < p2.rank);
        }
    }
};

bool Person::flag = true;

template<class T>
void print(T fst, T ed);

void queue_init(vector<Person>& v, int num) {
    v.clear();
    int height;
    for(int i = 0; i < num; ++i) {
        height = rand()% 30 + 1;
        v.push_back(Person(i, height));
    }
    sort(v.begin(), v.end(), less<Person>());
    /*
     * correct the queue order
     */
    for(int i = 0; i < num; ++i) {
        int rk = v[i].rank;
        for(int j = i + 1; j < num; ++j) {
            if(v[j].rank > rk) {
                v[j].higher += 1;
            }
        }
    }
    Person::flag = false;
    sort(v.begin(), v.end(), less<Person>());
    Person::flag = true;
}

void queue_recover(vector<Person>& v) {
    sort(v.begin(), v.end());
    deque<Person> foo;
    for(vector<Person>::iterator it = v.begin(); it != v.end(); ++it) {
        if(foo.begin() + it->higher <= foo.end()) {
            foo.insert(foo.begin() + it->higher, *it);
        } else {
            foo.push_back(*it);
        }
    }
    copy(foo.begin(), foo.end(), v.begin());
}

bool queue_check(vector<Person>& v) {
    int i = 0;
    for(vector<Person>::iterator it = v.begin(); it != v.end(); ++it) {
        if(it->rank != i++) {
            return false;
        }
    }
    return true;
}

template<class T>
void print(T fst, T ed) {
    cout << "=============================================================" << endl;
    for(T it = fst; it != ed; ++it) {
        cout << it->height << ":" << it->higher << '\t';
    }
    cout << endl;
    cout << "=============================================================" << endl;
}

int main(int argc, char **argv) {
    const int len = 10;
    vector<Person> foo;
    srand((unsigned)time(NULL));

    cout << "init..." << endl;
    queue_init(foo, len);
    print(foo.begin(), foo.end());

    cout << "shuffle..." << endl;
    random_shuffle(foo.begin(), foo.end());
    print(foo.begin(), foo.end());

    cout << "recover ..." << endl;
    queue_recover(foo);
    print(foo.begin(), foo.end());

    if(!queue_check(foo)) {
        cerr << "recover failed" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

