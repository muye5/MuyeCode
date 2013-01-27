// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include "AVL.h"
using namespace std;


int main(int argc, char **argv) {
    int ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    AVL<int> int_avl(ints, ints + 15);
    int_avl.Print();
    int del;
    for(int i = 0; i < 15; ++i) {
        cout<<"please enter the number you want to delete"<<endl;
        cin >> del;
        if(del == -1) {
            break;
        }
        int_avl.Delete(del);
        int_avl.Print();
    }
    return 0;
}
