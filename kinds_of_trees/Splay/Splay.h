// Copyright (c) 2013 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef Splay_H_
#define Splay_H_
#include <iostream>
#include <cstdlib>
#include <ctime>

template<class T> class Splay_Node;
template<class T> class Splay;

template<class T>
class Splay_Node {
public:
    Splay_Node(const T &v, Splay_Node *l = NULL, Splay_Node *r = NULL);
public:
    T value;
    Splay_Node *left;
    Splay_Node *right;
};

template<class T>
Splay_Node<T>::Splay_Node(const T &v, Splay_Node *l, Splay_Node *r)
    : value(v), left(l), right(r) {
}

template<class T>
class Splay {
public:
    template<class InputIterator>
        Splay(InputIterator first, InputIterator last);
    ~Splay();
public:
    const Splay_Node<T>* Find(const T &value);
    void Insert(const T& value);
    void Delete(const T& value);
    void Print() const;
private:
    Splay_Node<T>* Find(const T& value, Splay_Node<T> *&p);
    void Insert(const T& value, Splay_Node<T> *&p);
    void Delete(const T& value, Splay_Node<T> *&p);
    void Print(Splay_Node<T> * const &p, int layer) const;
    void Free(Splay_Node<T> *&p);
private:
    Splay_Node<T>* Max_Node(Splay_Node<T> *&p);
    Splay_Node<T>* Min_Node(Splay_Node<T> *&p);
    void Splay_Left_Rotate(Splay_Node<T> *&p);
    void Splay_Right_Rotate(Splay_Node<T> *&p);
    void Splay_Left_Right_Rotate(Splay_Node<T> *&p);
    void Splay_Right_Left_Rotate(Splay_Node<T> *&p);
private:
    Splay_Node<T> *head;
    size_t num;
};

template<class T> template<class InputIterator>
Splay<T>::Splay(InputIterator first, InputIterator last) : head(NULL), num(0) {
    while(first != last) {
        Insert(*first);
        ++first;
    }
}

template<class T>
Splay<T>::~Splay() {
    Free(head);
    if(num != 0) {
        std::cerr << "Free Splay Failed: " << num << " Node Left." << std::endl;
    }
}

template<class T>
const Splay_Node<T>* Splay<T>::Find(const T& value) {
    return Find(value, head);
}

template<class T>
Splay_Node<T>* Splay<T>::Find(const T& value, Splay_Node<T> *&p) {
    if(p == NULL) {
        return NULL;
    }
    if(p->value == value) {
        return p;
    } else if(value < p->value) {
        if(Splay_Node<T>* tmp = Find(value, p->left)) {
            if(tmp == p->left) {
                // 自身为父节点
                if(p != head) {
                    // 自身不是head节点,直接将子节点返回
                    return tmp;
                } else {
                    // 自身是head节点,直接右旋
                    Splay_Right_Rotate(p);
                }
            } else if(tmp == p->left->left) {
                // case 1: left -- left
                Splay_Right_Rotate(p);
                Splay_Right_Rotate(p);
            } else {
                // case 2: left -- right
                Splay_Left_Right_Rotate(p);
            }
            return p;
        }
    } else {
        if(Splay_Node<T>* tmp = Find(value, p->right)) {
            if(tmp == p->right) {
                // 自身为父节点
                if(p != head) {
                    // 自身不是head节点,直接将子节点返回
                    return tmp;
                } else {
                    // 自身是head节点,直接右旋
                    Splay_Left_Rotate(p);
                }
            } else if(tmp == p->right->right) {
                // case 3: right -- right
                Splay_Left_Rotate(p);
                Splay_Left_Rotate(p);
            } else {
                // case 4: right -- left
                Splay_Right_Left_Rotate(p);
            }
            return p;
        }
    }
    return NULL;
}

template<class T>
void Splay<T>::Insert(const T& value) {
    Insert(value, head);
}

template<class T>
void Splay<T>::Insert(const T& value, Splay_Node<T> *&p) {
    if(p == NULL) {
        p = new Splay_Node<T>(value);
        ++num;
    } else if(value < p->value) {
        Insert(value, p->left);
    } else {
        Insert(value, p->right);
    }
}

template<class T>
void Splay<T>::Delete(const T& value) {
    Delete(value, head);
}

template<class T>
void Splay<T>::Delete(const T& value, Splay_Node<T> *&p) {
    if(p == NULL) {
        return;
    }
    if(Find(value, p)) {
        if(p->left) {
            Splay_Node<T>* tmp = Max_Node(p->left);
            Find(tmp->value, p->left);
            p->left->right = p->right;
            tmp = p;
            p = p->left;
            delete tmp;
        } else {
            Splay_Node<T>* tmp = p;
            p = p->right;
            delete tmp;
        }
    }
}

template<class T>
void Splay<T>::Print() const {
    Print(head, 0);
    std::cout << std::endl;
}

template<class T>
void Splay<T>::Print(Splay_Node<T> * const &p, int layer) const {
    if(p) {
        Print(p->right, layer + 1);
        for(int i = 0; i < layer; ++i) {
            std::cout << "\t";
        }
        std::cout << "[" << p->value << "]" << std::endl;
        Print(p->left, layer + 1);
    }
}

template<class T>
Splay_Node<T>* Splay<T>::Max_Node(Splay_Node<T> *&p) {
    if(p == NULL || p->right == NULL) {
        return p;
    } else {
        return Max_Node(p->right);
    }
}

template<class T>
Splay_Node<T>* Splay<T>::Min_Node(Splay_Node<T> *&p) {
    if(p == NULL || p->left == NULL) {
        return p;
    } else {
        return Min_Node(p->left);
    }
}

template<class T>
void Splay<T>::Splay_Left_Rotate(Splay_Node<T> *&p) {
    Splay_Node<T> *tmp = p->right;
    p->right = tmp->left;
    tmp->left = p;
    p = tmp;
}

template<class T>
void Splay<T>::Splay_Right_Rotate(Splay_Node<T> *&p) {
    Splay_Node<T> *tmp = p->left;
    p->left = tmp->right;
    tmp->right = p;
    p = tmp;
}

template<class T>
void Splay<T>::Splay_Left_Right_Rotate(Splay_Node<T> *&p) {
    Splay_Left_Rotate(p->left);
    Splay_Right_Rotate(p);
}

template<class T>
void Splay<T>::Splay_Right_Left_Rotate(Splay_Node<T> *&p) {
    Splay_Right_Rotate(p->right);
    Splay_Left_Rotate(p);
}

template<class T>
void Splay<T>::Free(Splay_Node<T> *&p) {
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

#endif  // Splay_H_

