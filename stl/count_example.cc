// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Foo {
public:
    Foo(int v = 0) : value(v) {}
    Foo(const Foo& f) : value(f.value) {}
    Foo& operator=(const Foo& f) {
        if(this == &f) {
            return *this;
        } else {
            value = f.value;
            return *this;
        }
    }
    bool operator==(const Foo& f) {
        return value == f.value;
    }
    int value;
};

int main(int argc, char **argv) {
    Foo foo(1), foo1(1), foo2(2), foo3(3);
    vector<Foo> v;
    v.push_back(foo);
    v.push_back(foo1);
    v.push_back(foo2);
    v.push_back(foo3);

    int f[] = {1, 1, 2, 3};
    int num = count(f, f + 4, 1);
    cout << "case int 1:" << num << endl;

    num = count(f, f + 4, 3);
    cout << "case int 1:" << num << endl;

    num = count(v.begin(), v.end(), 1);
    cout << "case Foo 1:" << num << endl;

    num = count(v.begin(), v.end(), 3);
    cout << "case Foo 1:" << num << endl;

    return 0;
}

