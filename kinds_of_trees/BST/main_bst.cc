// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include "BST.h"
using namespace std;

int main(int argc, char **argv) {
    int ints[] = {1, 3, 5, 7, 9};
    char chars[] = {'A', 'B', 'C', 'D', 'E'};

    BST<int> int_bst(ints, ints + 5);
    BST<char> char_bst(chars, chars + 5);

    BST_Node<char> *pchar = char_bst.Find('D');
    cout << pchar->value << endl;
    char_bst.Print();
    char_bst.Insert('F');
    char_bst.Print();
    cout << char_bst.Delete('G') << endl;
    cout << char_bst.Delete('A') << endl;
    char_bst.Print();


    BST_Node<int> *pint = int_bst.Find(3);
    cout << pint->value << endl;
    int_bst.Print();
    int_bst.Insert(11);
    int_bst.Print();
    cout << int_bst.Delete(6) << endl;
    cout << int_bst.Delete(5) << endl;
    cout << int_bst.Delete(7) << endl;
    cout << int_bst.Delete(3) << endl;
    cout << int_bst.Delete(9) << endl;
    int_bst.Print();

    return 0;
}
