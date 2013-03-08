// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include "BinaryHeap.h"
using namespace std;

int main(int argc, char **argv) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v(a, a + 9);
    random_shuffle(v.begin(), v.end());
    BinaryHeap<int> bheap(v);
    cout << "findMin() = " << bheap.findMin() << endl;
    cout << "DeleteMin()" << endl;
    bheap.deleteMin();
    cout << "findMin() = " << bheap.findMin() << endl;
    cout << "insert()" << endl;
    bheap.insert(0);
    cout << "findMin() = " << bheap.findMin() << endl;
    cout << "makeEmpty()" << endl;
    bheap.makeEmpty();
    cout << "insert() loop" << endl;
    for(int i = 1; i < 9; i += 2) {
        bheap.insert(a[i]);
    }
    cout << "findMin() = " << bheap.findMin() << endl;
    cout << "exception" << endl;
    bheap.makeEmpty();
    bheap.deleteMin();
    return 0;
}

