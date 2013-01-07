// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
// Treap = Tree + Heap

#ifndef Treap_H_
#define Treap_H_
#include <iostream>
#include <cstdlib>
#include <ctime>

template<class T> class Treap_Node;
template<class T> class Treap;

template<class T>
class Treap_Node {
public:
    Treap_Node(const T& v);
public:
    int fix;
    T value;
    Treap_Node *left;
    Treap_Node *right;
};

template<class T>
Treap_Node<T>::Treap_Node(const T& v) : fix(rand()), value(v), left(NULL), right(NULL){
}

template<class T>
class Treap {
public:
    template<class InputIterator>
        Treap(InputIterator first, InputIterator last);
    ~Treap();
public:
    Treap_Node<T>* Find(const T& value);
    Treap_Node<T>* Insert(const T& value);
    bool Delete(const T& value);
    void Print() const;
private:
    Treap_Node<T>* Find(const T& value, Treap_Node<T> *&p);
    Treap_Node<T>* Insert(const T& value, Treap_Node<T> *&p);
    bool Delete(const T& value, Treap_Node<T> *&p);
    void Print(Treap_Node<T> * const &p) const;
    void Free(Treap_Node<T> *&p);
private:
    void Treap_Left_Rotate(Treap_Node<T> *&p);
    void Treap_Right_Rotate(Treap_Node<T> *&p);
private:
    Treap_Node<T> *head;
    size_t num;
};

template<class T> template<class InputIterator>
Treap<T>::Treap(InputIterator first, InputIterator last) : head(NULL), num(0) {
    while(first != last) {
        Insert(*first);
        ++first;
    }
}

template<class T>
Treap<T>::~Treap() {
    Free(head);
    if(num != 0) {
        std::cerr << "Free Treap Failed: " << num << " Node Left." << std::endl;
    }
}

template<class T>
Treap_Node<T>* Treap<T>::Find(const T& value) {
    return Find(value, head);
}

template<class T>
Treap_Node<T>* Treap<T>::Find(const T& value, Treap_Node<T> *&p) {
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
Treap_Node<T>* Treap<T>::Insert(const T& value) {
    return Insert(value, head);
}

template<class T>
Treap_Node<T>* Treap<T>::Insert(const T& value, Treap_Node<T> *&p) {
    if(p == NULL) {
        p = new Treap_Node<T>(value);
        ++num;
        return p;
    } else if(value <= p->value) {
        Treap_Node<T> *result = Insert(value, p->left);
        if(p->left->fix < p->fix) {
            Treap_Right_Rotate(p);
        }
        return result;
    } else {
        Treap_Node<T> *result = Insert(value, p->right);
        if(p->right->fix < p->fix) {
            Treap_Left_Rotate(p);
        }
        return result;
    }
}

template<class T>
bool Treap<T>::Delete(const T& value) {
    return Delete(value, head);
}

template<class T>
bool Treap<T>::Delete(const T& value, Treap_Node<T> *&p) {
    if(p == NULL) {
        return false;
    }
    if(p->value == value) {
        if(p->left && p->right) {
            if(p->left->fix < p->right->fix) {
                Treap_Right_Rotate(p);
                return Delete(value, p->right);
            } else {
                Treap_Left_Rotate(p);
                return Delete(value, p->left);
            }
        } else {
            Treap_Node<T> *q = p;
            if(p->left) {
                p = p->left;
            } else {
                p = p->right;
            }
            delete q;
            --num;
            return true;
        }
    } else if(value < p->value) {
        return Delete(value, p->left);
    } else {
        return Delete(value, p->right);
    }
}

template<class T>
void Treap<T>::Print() const {
    Print(head);
    std::cout << std::endl;
}

template<class T>
void Treap<T>::Print(Treap_Node<T> * const &p) const {
    if(p) {
        Print(p->left);
        std::cout << p->value << "  ";
        Print(p->right);
    }
}

template<class T>
void Treap<T>::Treap_Left_Rotate(Treap_Node<T> *&p) {
    Treap_Node<T> *tmp = p->right;
    p->right = tmp->left;
    tmp->left = p;
    p = tmp;
}

template<class T>
void Treap<T>::Treap_Right_Rotate(Treap_Node<T> *&p) {
    Treap_Node<T> *tmp = p->left;
    p->left = tmp->right;
    tmp->right = p;
    p = tmp;
}

template<class T>
void Treap<T>::Free(Treap_Node<T> *&p) {
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

#endif  // Treap_H_

