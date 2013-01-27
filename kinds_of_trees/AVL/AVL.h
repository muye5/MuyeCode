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
AVL_Node<T>::AVL_Node(const T& v, AVL_Node *l, AVL_Node *r, int h)
    : value(v), left(l), right(r), height(h) {
}

template<class T>
class AVL {
public:
    template<class InputIterator>
        AVL(InputIterator first, InputIterator last);
    ~AVL();
public:
    const AVL_Node<T>* Find(const T& value);
    void Insert(const T& value);
    void Delete(const T& value);
    void Print() const;
    bool Check() const; // 检查AVL树是否合法
private:
    const AVL_Node<T>* Find(const T& value, AVL_Node<T> *&p);
    void Insert(const T& value, AVL_Node<T> *&p);
    void Delete(const T& value, AVL_Node<T> *&p);
    void Print(AVL_Node<T> * const &p, int layer) const;
    void Free(AVL_Node<T> *&p);
    // AVL_Node<T> * const &p的const非常重要
    // 否则就不能被Check()调用
    int Check(AVL_Node<T> * const &p) const;
private:
    int height(AVL_Node<T> * const &p) const;
    AVL_Node<T>* Max_Node(AVL_Node<T> *&p);
    AVL_Node<T>* Min_Node(AVL_Node<T> *&p);
    void AVL_Left_Rotate(AVL_Node<T> *&p);
    void AVL_Right_Rotate(AVL_Node<T> *&p);
    void AVL_Left_Right_Rotate(AVL_Node<T> *&p);
    void AVL_Right_Left_Rotate(AVL_Node<T> *&p);
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
        ++num;
    } else if(value < p->value) {
        Insert(value, p->left);
        if(height(p->left) - height(p->right) == 2) {
            if(value < p->left->value) {
                // case 1: left -- left
                AVL_Right_Rotate(p);
            } else {
                // case 3: left -- right
                AVL_Right_Left_Rotate(p);
            }
        }
    } else {
        Insert(value, p->right);
        if(height(p->right) - height(p->left) == 2) {
            if(value > p->right->value) {
                // case 2: right -- right
                AVL_Left_Rotate(p);
            } else {
                // case 4: right -- left
                AVL_Left_Right_Rotate(p);
            }
        }
    }
    p->height = max(height(p->left), height(p->right)) + 1;
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
            if(height(p->left) > height(p->right)) {
                AVL_Node<T> *q = Max_Node(p->left);
                p->value = q->value;
                Delete(p->value, p->left);
            } else {
                AVL_Node<T> *q = Min_Node(p->right);
                p->value = q->value;
                Delete(p->value, p->right);
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
            return;
        }
    } else if(value < p->value) {
        Delete(value, p->left);
        if(height(p->right) - height(p->left) == 2) {
            if(height(p->right->right) - height(p->left) == 1) {
                // delete case 2: 从左子树删除一个节点导致right -- right节点比左子树高度高1(注意是高1)
                // delete case 2: right -- right - left = 1
                AVL_Left_Rotate(p);
            } else {
                // case 4: right -- left - right = 1
                AVL_Left_Right_Rotate(p);
            }
        }
    } else {
        Delete(value, p->right);
        if(height(p->left) - height(p->right) == 2) {
            if(height(p->left->left) - height(p->right) == 1) {
                // delete case 1: 从右子树删除一个节点导致left -- left节点比右子树高度高1(注意是高1)
                // delete case 1: left -- left - right = 1
                AVL_Right_Rotate(p);
            } else {
                // case 3: left -- right - right = 1
                AVL_Right_Left_Rotate(p);
            }
        }
    }
    p->height = max(height(p->left), height(p->right)) + 1;
}

template<class T>
void AVL<T>::Print() const {
    Print(head, 0);
    std::cout << std::endl;
}

template<class T>
void AVL<T>::Print(AVL_Node<T> * const &p, int layer) const {
    if(p) {
        Print(p->right, layer + 1);
        for(int i = 0; i < layer; ++i) {
            std::cout << "\t";
        }
        std::cout << "[" << p->value << ":" << p->height << "]" << std::endl;
        Print(p->left, layer + 1);
    }
}

template<class T>
bool AVL<T>::Check() const {
    return (Check(head) == height(head));
}

template<class T>
int AVL<T>::Check(AVL_Node<T> * const &p) const {
    if(p) {
        if(max(Check(p->left), Check(p->right)) + 1 == height(p)) {
            return height(p);
        } else {
            std::cerr << "Check(p->left) = "
               << Check(p->left)
               << "\nCheck(p->right) = "
               << Check(p->right)
               << "\nheight(p) = "
               << height(p)
               << "\np->value = "
               << p->value
               << std::endl;
            exit(-1);
        }
    } else {
        return -1;
    }
}

template<class T>
int AVL<T>::height(AVL_Node<T> * const &p) const {
    return p == NULL ? -1 : p->height;
}

template<class T>
AVL_Node<T>* AVL<T>::Max_Node(AVL_Node<T> *&p) {
    if(p == NULL || p->right == NULL) {
        return p;
    } else {
        return Max_Node(p->right);
    }
}

template<class T>
AVL_Node<T>* AVL<T>::Min_Node(AVL_Node<T> *&p) {
    if(p == NULL || p->left == NULL) {
        return p;
    } else {
        return Min_Node(p->left);
    }
}

template<class T>
void AVL<T>::AVL_Left_Rotate(AVL_Node<T> *&p) {
    AVL_Node<T> *tmp = p->right;
    p->right = tmp->left;
    tmp->left = p;
    p->height = max(height(p->left), height(p->right)) + 1;
    tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
    p = tmp;
}

template<class T>
void AVL<T>::AVL_Right_Rotate(AVL_Node<T> *&p) {
    AVL_Node<T> *tmp = p->left;
    p->left = tmp->right;
    tmp->right = p;
    p->height = max(height(p->left), height(p->right)) + 1;
    tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
    p = tmp;
}

template<class T>
void AVL<T>::AVL_Left_Right_Rotate(AVL_Node<T> *&p) {
    AVL_Left_Rotate(p->left);
    AVL_Right_Rotate(p);
}

template<class T>
void AVL<T>::AVL_Right_Left_Rotate(AVL_Node<T> *&p) {
    AVL_Right_Rotate(p->right);
    AVL_Left_Rotate(p);
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

