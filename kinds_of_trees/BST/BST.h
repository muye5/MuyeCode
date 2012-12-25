// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef BST_H_
#define BST_H_
#include <iostream>

template<class T> class BST_Node;
template<class T> class BST;

template<class T>
class BST_Node {
public:
    BST_Node(const T& v);
public:
    T value;
    BST_Node *left;
    BST_Node *right;
};

template<class T>
BST_Node<T>::BST_Node(const T& v) : value(v), left(NULL), right(NULL){
}

template<class T>
class BST {
public:
    template<class InputIterator>
        BST(InputIterator first, InputIterator last);
    ~BST();
public:
    BST_Node<T>* Find(const T& value);
    BST_Node<T>* Insert(const T& value);
    bool Delete(const T& value);
    void Print() const;
private:
    BST_Node<T>* Find(const T& value, BST_Node<T> *&p);
    BST_Node<T>* Insert(const T& value, BST_Node<T> *&p);
    bool Delete(const T& value, BST_Node<T> *&p);
    void Print(BST_Node<T> * const &p) const;
    void Free(BST_Node<T> *&p);
private:
    const T successor(BST_Node<T> *&p);
private:
    BST_Node<T> *head;
    size_t num;
};

template<class T> template<class InputIterator>
BST<T>::BST(InputIterator first, InputIterator last) : head(NULL), num(0) {
    while(first != last) {
        Insert(*first);
        ++first;
    }
}

template<class T>
BST<T>::~BST() {
    Free(head);
    if(num != 0) {
        std::cerr << "Free BST Failed: " << num << " Node Left." << std::endl;
    }
}

template<class T>
BST_Node<T>* BST<T>::Find(const T& value) {
    return Find(value, head);
}

template<class T>
BST_Node<T>* BST<T>::Find(const T& value, BST_Node<T> *&p) {
    if(p == NULL) {
        return NULL;
    }
    if(p->value == value) {
        return p;
    } else if(value <= p->value) {
        return Find(value, p->left);
    } else {
        return Find(value, p->right);
    }
}

template<class T>
BST_Node<T>* BST<T>::Insert(const T& value) {
    return Insert(value, head);
}

template<class T>
BST_Node<T>* BST<T>::Insert(const T& value, BST_Node<T> *&p) {
    if(p == NULL) {
        p = new BST_Node<T>(value);
        ++num;
        return p;
    } else if(value <= p->value) {
        return Insert(value, p->left);
    } else {
        return Insert(value, p->right);
    }
}

template<class T>
bool BST<T>::Delete(const T& value) {
    return Delete(value, head);
}

template<class T>
bool BST<T>::Delete(const T& value, BST_Node<T> *&p) {
    if(p == NULL) {
        return false;
    }
    if(p->value == value) {
        if(p->left && p->right) {
            p->value = successor(p->right);
        } else {
            if(p->left) {
                p = p->left;
            } else {
                p = p->right;
            }
        }
        --num;
        return true;
    } else if(value < p->value) {
        return Delete(value, p->left);
    } else {
        return Delete(value, p->right);
    }
}

template<class T>
void BST<T>::Print() const {
    Print(head);
    std::cout << std::endl;
}

template<class T>
void BST<T>::Print(BST_Node<T> * const &p) const {
    if(p) {
        Print(p->left);
        std::cout << p->value << "  ";
        Print(p->right);
    }
}

template<class T>
const T BST<T>::successor(BST_Node<T> *&p) {
    /*
     * 这里切记不可这么写,因为p传的是引用,这么写全都乱了!
     while(p->left) {
     p = p->left;
     }
     */
    if(p->left == NULL) {
        BST_Node<T> *q = p;
        T t = p->value;
        p = p->right;
        delete q;
        return t;
    } else {
        return successor(p->left);
    }
}

template<class T>
void BST<T>::Free(BST_Node<T> *&p) {
    if(p == NULL) {
        return;
    }
    if(p->left) {
        Free(p->left);
    }
    if(p->right) {
        Free(p->right);
    }
    delete p;
    p = NULL;
    --num;
}

#endif  // BST_H_

