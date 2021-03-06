// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include "LeftistHeap.h"
using namespace std;

int main(int argc, char **argv) {
    int numItems = 10000;
    LeftistHeap<int> h, h1, h2;
    int i = 37;
    for(i = 37; i != 0; i = (i + 37) % numItems) {
        if(i % 2 == 0) {
            h1.insert(i);
        } else {
            h.insert(i);
        }
    }
    h.merge(h1);
    h2 = h;
    for(i = 1; i < numItems; ++i) {
        int x;
        h2.deleteMin(x);
        if(x != i) {
            cout << "Oops! " << i << endl;
        }
    }
    if(!h1.isEmpty()) {
        cout << "Oops! h1 shoulld have been empty!" << endl;
    }
    return 0;
}

