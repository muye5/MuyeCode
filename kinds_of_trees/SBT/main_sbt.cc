// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include "SBT.h"
using namespace std;


int main(int argc, char **argv) {
    int ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    SBT<int> int_sbt(ints, ints + 15);
    int_sbt.Print();
    int del;
    for(int i = 1; i <= 15; ++i) {
        cout << "[order:value] == [" << i << ":" << int_sbt.Select(i)->value << "]" << endl;
    }
    for(int i = 0; i < 15; ++i) {
        cout<<"please enter the number you want to delete"<<endl;
        cin >> del;
        if(del == -1) {
            break;
        }
        cout << "Rank[" << int_sbt.Rank(del) << "]" << endl;
        int_sbt.Delete(del);
        int_sbt.Print();
    }
    return 0;
}
