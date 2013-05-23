// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char **argv) {
    char a[] = "hello world";
    char b[] = "world";
    char *p = strstr(a, b);
    cout << p << endl;
    return 0;
}

