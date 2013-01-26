// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include "AVL.h"
using namespace std;


int main(int argc, char **argv) {
    int ints[] = {1, 3, 5, 7, 9};
    char chars[] = {'A', 'B', 'C', 'D', 'E'};

    AVL<int> int_avl(ints, ints + 5);
    AVL<char> char_avl(chars, chars + 5);

    const AVL_Node<char> *pchar = char_avl.Find('D');
    cout <<"pchar->value = " << pchar->value << endl;
    cout <<"pchar->height = " << pchar->height << endl;
    char_avl.Print();
    char_avl.Insert('F');
    char_avl.Print();
    char_avl.Delete('G');
    char_avl.Delete('A');
    char_avl.Print();
    char_avl.Check();

    const AVL_Node<int> *pint = int_avl.Find(3);
    cout <<"pint->value = " << pint->value << endl;
    cout <<"pint->height = " << pint->height << endl;
    int_avl.Print();
    int_avl.Insert(11);
    int_avl.Print();
    int_avl.Delete(6);
    int_avl.Delete(5);
    int_avl.Delete(1);
    int_avl.Delete(9);
    int_avl.Print();
    int_avl.Check();

    return 0;
}
