// Copyright (c) 2013 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef SBT_H_
#define SBT_H_
#include <iostream>
#include <cstdlib>
#include <ctime>

template<class T> class SBT_Node;
template<class T> class SBT;

template<class T>
class SBT_Node {
public:
    SBT_Node(const T& v, SBT_Node *l = NULL, SBT_Node *r = NULL, unsigned s = 1);
public:
    T value;
    SBT_Node *left;
    SBT_Node *right;
    unsigned sz;
};

template<class T>
SBT_Node<T>::SBT_Node(const T& v, SBT_Node *l, SBT_Node *r, unsigned s)
    : value(v), left(l), right(r), sz(s) {
    }

template<class T>
class SBT {
public:
    template<class InputIterator>
        SBT(InputIterator first, InputIterator last);
    ~SBT();
public:
    const SBT_Node<T>* Find(const T& value);
    const SBT_Node<T>* Select(unsigned rank);
    unsigned Rank(const T& value);

    void Insert(const T& value);
    void Delete(const T& value);
    void Print() const;
    bool Check() const; // 检查SBT树是否合法
private:
    const SBT_Node<T>* Find(const T& value, SBT_Node<T> *&p);
    const SBT_Node<T>* Select(unsigned rank, SBT_Node<T> *&p);
    unsigned Rank(const T& value, SBT_Node<T> *&p);

    void Insert(const T& value, SBT_Node<T> *&p);
    void Delete(const T& value, SBT_Node<T> *&p);
    void Print(SBT_Node<T> * const &p, int layer) const;
    void Free(SBT_Node<T> *&p);
    // SBT_Node<T> * const &p的const非常重要
    // 否则就不能被Check()调用
    unsigned Check(SBT_Node<T> * const &p) const;
private:
    unsigned size(SBT_Node<T> * const &p) const;
    SBT_Node<T>* Max_Node(SBT_Node<T> *&p);
    SBT_Node<T>* Min_Node(SBT_Node<T> *&p);
    void Maintain(SBT_Node<T> *&p, bool flag);
    void SBT_Left_Rotate(SBT_Node<T> *&p);
    void SBT_Right_Rotate(SBT_Node<T> *&p);
    void SBT_Left_Right_Rotate(SBT_Node<T> *&p);
    void SBT_Right_Left_Rotate(SBT_Node<T> *&p);
private:
    SBT_Node<T> *head;
    size_t num;
};

template<class T> template<class InputIterator>
SBT<T>::SBT(InputIterator first, InputIterator last) : head(NULL), num(0) {
    while(first != last) {
        Insert(*first);
        ++first;
    }
}

template<class T>
SBT<T>::~SBT() {
    Free(head);
    if(num != 0) {
        std::cerr << "Free SBT Failed: " << num << " Node Left." << std::endl;
    }
}

template<class T>
const SBT_Node<T>* SBT<T>::Find(const T& value) {
    return Find(value, head);
}

template<class T>
const SBT_Node<T>* SBT<T>::Find(const T& value, SBT_Node<T> *&p) {
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
const SBT_Node<T>* SBT<T>::Select(unsigned rank) {
    return Select(rank, head);
}

template<class T>
const SBT_Node<T>* SBT<T>::Select(unsigned rank, SBT_Node<T> *&p) {
    if(p == NULL || rank > p->sz) {
        return NULL;
    }
    unsigned order = size(p->left) + 1;
    if(rank < order) {
        return Select(rank, p->left);
    } else if(rank > order){
        return Select(rank - order, p->right);
    } else {
        return p;
    }
}

template<class T>
unsigned SBT<T>::Rank(const T& value) {
    return Rank(value, head);
}

template<class T>
unsigned SBT<T>::Rank(const T& value, SBT_Node<T> *&p) {
    if(p == NULL) {
        return 0;
    }
    if(value == p->value) {
        return size(p->left) + 1;
    } else if(value < p->value) {
        return Rank(value, p->left);
    } else {
        unsigned order = Rank(value, p->right);
        return ++order + size(p->left);
    }
    return 0;
}

template<class T>
void SBT<T>::Insert(const T& value) {
    Insert(value, head);
}

template<class T>
void SBT<T>::Insert(const T& value, SBT_Node<T> *&p) {
    if(p == NULL) {
        p = new SBT_Node<T>(value);
        ++num;
    } else {
        if(value < p->value) {
            Insert(value, p->left);
        } else {
            Insert(value, p->right);
        }
        p->sz = size(p->left) + size(p->right) + 1;
        Maintain(p, value > p->value);
    }
}

template<class T>
void SBT<T>::Delete(const T& value) {
    Delete(value, head);
}

template<class T>
void SBT<T>::Delete(const T& value, SBT_Node<T> *&p) {
    if(p == NULL) {
        return;
    }
    if(p->value == value) {
        if(p->left && p->right) {
            if(size(p->left) > size(p->right)) {
                SBT_Node<T> *q = Max_Node(p->left);
                p->value = q->value;
                Delete(p->value, p->left);
                p->sz = size(p->left) + size(p->right) + 1;
                Maintain(p, true);
            } else {
                SBT_Node<T> *q = Min_Node(p->right);
                p->value = q->value;
                Delete(p->value, p->right);
                p->sz = size(p->left) + size(p->right) + 1;
                Maintain(p, false);
            }
        } else {
            SBT_Node<T> *q = p;
            if(p->left) {
                p = p->left;
            } else {
                p = p->right;
            }
            delete q;
            --num;
        }
    } else {
        if(value < p->value) {
            Delete(value, p->left);
        } else {
            Delete(value, p->right);
        }
        p->sz = size(p->left) + size(p->right) + 1;
        Maintain(p, value < p->value);
    }
}

template<class T>
void SBT<T>::Print() const {
    Check();
    Print(head, 0);
    std::cout << std::endl;
}

template<class T>
void SBT<T>::Print(SBT_Node<T> * const &p, int layer) const {
    if(p) {
        Print(p->right, layer + 1);
        for(int i = 0; i < layer; ++i) {
            std::cout << "\t";
        }
        std::cout << "[" << p->value << ":" << p->sz << "]" << std::endl;
        Print(p->left, layer + 1);
    }
}

template<class T>
bool SBT<T>::Check() const {
    return (Check(head) == size(head));
}

template<class T>
unsigned SBT<T>::Check(SBT_Node<T> * const &p) const {
    if(p) {
        if(Check(p->left) + Check(p->right) + 1 == size(p)) {
            return size(p);
        } else {
            std::cerr << "Check(p->left) = "
                << Check(p->left)
                << "\nCheck(p->right) = "
                << Check(p->right)
                << "\nsize(p) = "
                << size(p)
                << "\np->value = "
                << p->value
                << std::endl;
            exit(-1);
        }
    } else {
        return 0;
    }
}

template<class T>
unsigned SBT<T>::size(SBT_Node<T> * const &p) const {
    return p == NULL ? 0 : p->sz;
}

template<class T>
SBT_Node<T>* SBT<T>::Max_Node(SBT_Node<T> *&p) {
    if(p == NULL || p->right == NULL) {
        return p;
    } else {
        return Max_Node(p->right);
    }
}

template<class T>
SBT_Node<T>* SBT<T>::Min_Node(SBT_Node<T> *&p) {
    if(p == NULL || p->left == NULL) {
        return p;
    } else {
        return Min_Node(p->left);
    }
}

template<class T>
void SBT<T>::Maintain(SBT_Node<T> *&p, bool flag) {
    if(p == NULL) {
        return;
    }
    if(!flag) {
        if(p->left) {
            if(size(p->left->left) > size(p->right)) {
                SBT_Right_Rotate(p);
                Maintain(p->right, true);
                Maintain(p, false);
                Maintain(p, true);
            } else if(size(p->left->right) > size(p->right)) {
                SBT_Left_Right_Rotate(p);
                Maintain(p->left, false);
                Maintain(p->right, true);
                Maintain(p, false);
                Maintain(p, true);
            }
        }
    } else {
        if(p->right) {
            if(size(p->right->right) > size(p->left)) {
                SBT_Left_Rotate(p);
                Maintain(p->left, false);
                Maintain(p, false);
                Maintain(p, true);
            } else if(size(p->right->left) > size(p->left)) {
                SBT_Right_Left_Rotate(p);
                Maintain(p->left, false);
                Maintain(p->right, true);
                Maintain(p, false);
                Maintain(p, true);
            }
        }
    }
}

template<class T>
void SBT<T>::SBT_Left_Rotate(SBT_Node<T> *&p) {
    SBT_Node<T> *tmp = p->right;
    p->right = tmp->left;
    tmp->left = p;
    tmp->sz = p->sz;
    p->sz = size(p->left) + size(p->right) + 1;
    p = tmp;
}

template<class T>
void SBT<T>::SBT_Right_Rotate(SBT_Node<T> *&p) {
    SBT_Node<T> *tmp = p->left;
    p->left = tmp->right;
    tmp->right = p;
    tmp->sz = p->sz;
    p->sz = size(p->left) + size(p->right) + 1;
    p = tmp;
}

template<class T>
void SBT<T>::SBT_Left_Right_Rotate(SBT_Node<T> *&p) {
    SBT_Left_Rotate(p->left);
    SBT_Right_Rotate(p);
}

template<class T>
void SBT<T>::SBT_Right_Left_Rotate(SBT_Node<T> *&p) {
    SBT_Right_Rotate(p->right);
    SBT_Left_Rotate(p);
}

template<class T>
void SBT<T>::Free(SBT_Node<T> *&p) {
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

#endif  // SBT_H_

