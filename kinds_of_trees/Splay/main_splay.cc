// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include "Splay.h"
using namespace std;


int main(int argc, char **argv) {
    int ints[] = {7, 6, 5, 4, 3, 2, 1};

    Splay<int> int_splay(ints, ints + 7);
    int_splay.Print();
    int finder;
    cout<<"please enter the number you want to delete"<<endl;
    while(cin >> finder) {
        if(int_splay.Find(finder) == NULL) {
            cerr << "No Found " << finder << endl;
        }
        cout << "====================== before delete =========================" << endl;
        int_splay.Print();
        cout << "======================= after delete ========================" << endl;
        int_splay.Delete(finder);
        int_splay.Print();
        cout << "===============================================" << endl;
        cout<<"please enter the number you want to delete"<<endl;
    }
    return 0;
}
