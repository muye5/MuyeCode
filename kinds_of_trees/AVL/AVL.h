// Copyright (c) 2013 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef AVL_H_
#define AVL_H_
#include <iostream>
#include <cstdlib>
#include <ctime>

template<class T> class AVL_Node;
template<class T> class AVL;

template<class T>
class AVL_Node {
public:
    AVL_Node(const T& v, AVL_Node *l = NULL, AVL_Node *r = NULL, int h = -1);
public:
    T value;
    AVL_Node *left;
    AVL_Node *right;
    int height;
};

template<class T>
AVL_Node<T>::AVL_Node(const T& v, AVL_Node *l = NULL, AVL_Node *r = NULL, int h = -1)
    : value(v), left(l), right(r), height(h) {
}

template<class T>
class AVL {
public:
    template<class InputIterator>
        AVL(InputIterator first, InputIterator last);
    ~AVL();
public:
    AVL_Node<T>* Find(const T& value);
    void Insert(const T& value);
    void Delete(const T& value);
    void Print() const;
private:
    const AVL_Node<T>* Find(const T& value, AVL_Node<T> *&p);
    void Insert(const T& value, AVL_Node<T> *&p);
    void Delete(const T& value, AVL_Node<T> *&p);
    void Print(AVL_Node<T> * const &p) const;
    void Free(AVL_Node<T> *&p);
private:
    int height(AVL_Node<T> *&p);
    void AVL_Left_Rotate(AVL_Node<T> *&p);
    void AVL_Right_Rotate(AVL_Node<T> *&p);
    void AVL_Double_Left_Rotate(AVL_Node<T> *&p);
    void AVL_Double_Right_Rotate(AVL_Node<T> *&p);
private:
    AVL_Node<T> *head;
    size_t num;
};

template<class T> template<class InputIterator>
AVL<T>::AVL(InputIterator first, InputIterator last) : head(NULL), num(0) {
    while(first != last) {
        Insert(*first);
        ++first;
    }
}

template<class T>
AVL<T>::~AVL() {
    Free(head);
    if(num != 0) {
        std::cerr << "Free AVL Failed: " << num << " Node Left." << std::endl;
    }
}

template<class T>
const AVL_Node<T>* AVL<T>::Find(const T& value) {
    return Find(value, head);
}

template<class T>
const AVL_Node<T>* AVL<T>::Find(const T& value, AVL_Node<T> *&p) {
    if(p == NULL) {
        return NULL;
    }
    if(p->value == value) {
        return p;
    } else if(value < p->value) {
        return Find(value, p->left);
    } else {
        return Find(value, p->right);
    }
}

template<class T>
void AVL<T>::Insert(const T& value) {
    Insert(value, head);
}

template<class T>
void AVL<T>::Insert(const T& value, AVL_Node<T> *&p) {
    if(p == NULL) {
        p = new AVL_Node<T>(value);
        p->height = 0;
        ++num;
    } else if(value < p->value) {
        Insert(value, p->left);
        if(height(p->left) - height(p->right) == 2) {
            if(value < p->left->value) {
                // case 1: left -- left
                AVL_Right_Rotate(p);
            } else {
                // case 3: left -- right
                AVL_Double_Right_Rotate(p);
            }
        }
        // 这个有点问题,如何更新树的高度
        p->height = ;
    } else {
        Insert(value, p->right);
        if(height(p->right) - height(p->left) == 2) {
            if(value > p->right->value) {
                // case 2: right -- right
                AVL_Left_Rotate(p);
            } else {
                // case 4: right -- left
                AVL_Double_Left_Rotate(p);
            }
        }
    }
}

template<class T>
void AVL<T>::Delete(const T& value) {
    Delete(value, head);
}

template<class T>
void AVL<T>::Delete(const T& value, AVL_Node<T> *&p) {
    if(p == NULL) {
        return;
    }
    if(p->value == value) {
        if(p->left && p->right) {
            if(p->left->fix < p->right->fix) {
                AVL_Right_Rotate(p);
                return Delete(value, p->right);
            } else {
                AVL_Left_Rotate(p);
                return Delete(value, p->left);
            }
        } else {
            AVL_Node<T> *q = p;
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
void AVL<T>::Print() const {
    Print(head);
    std::cout << std::endl;
}

template<class T>
void AVL<T>::Print(AVL_Node<T> * const &p) const {
    if(p) {
        Print(p->left);
        std::cout << p->value << "  ";
        Print(p->right);
    }
}

template<class T>
int AVL<T>::height(AVL_Node<T> *&p) {
    if(p == NULL) {
        return -1;
    } else {
        // 这个也有问题
        return max(height(p->left), height(p->right)) + 1;
    }
}

template<class T>
void AVL<T>::AVL_Left_Rotate(AVL_Node<T> *&p) {
    AVL_Node<T> *tmp = p->right;
    p->right = tmp->left;
    tmp->left = p;
    p = tmp;
}

template<class T>
void AVL<T>::AVL_Right_Rotate(AVL_Node<T> *&p) {
    AVL_Node<T> *tmp = p->left;
    p->left = tmp->right;
    tmp->right = p;
    p = tmp;
}

template<class T>
void AVL<T>::AVL_Double_Left_Rotate(AVL_Node<T> *&p) {
}

template<class T>
void AVL<T>::AVL_Double_Right_Rotate(AVL_Node<T> *&p) {
}

template<class T>
void AVL<T>::Free(AVL_Node<T> *&p) {
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

#endif  // AVL_H_

