// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include "Treap.h"
using namespace std;


int main(int argc, char **argv) {
    int ints[] = {1, 3, 5, 7, 9};
    char chars[] = {'A', 'B', 'C', 'D', 'E'};

    srand((unsigned)time(NULL));
    Treap<int> int_treap(ints, ints + 5);
    Treap<char> char_treap(chars, chars + 5);

    Treap_Node<char> *pchar = char_treap.Find('D');
    cout << pchar->value << endl;
    char_treap.Print();
    char_treap.Insert('F');
    char_treap.Print();
    cout << char_treap.Delete('G') << endl;
    cout << char_treap.Delete('A') << endl;
    char_treap.Print();

    Treap_Node<int> *pint = int_treap.Find(3);
    cout << pint->value << endl;
    int_treap.Print();
    int_treap.Insert(11);
    int_treap.Print();
    cout << int_treap.Delete(6) << endl;
    cout << int_treap.Delete(5) << endl;
    cout << int_treap.Delete(1) << endl;
    cout << int_treap.Delete(9) << endl;
    int_treap.Print();

    return 0;
}
