// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)

#include "LeftistHeap.h"

template<typename Comparable>
LeftistHeap<Comparable>::LeftistHeap() : root(NULL) {}

template<typename Comparable>
LeftistHeap<Comparable>::LeftistHeap(const LeftistHeap& rhs) : root(NULL) {
    operator=(rhs);
}

template<typename Comparable>
LeftistHeap<Comparable>::~LeftistHeap() {
    makeEmpty();
}

template<typename Comparable>
bool LeftistHeap<Comparable>::isEmpty() const {
    return root == NULL;
}

template<typename Comparable>
const Comparable& LeftistHeap<Comparable>::findMin() const {
    if(isEmpty()) {
        throw std::underflow_error("Heap is empty");
    }
    return root->element;
}

template<typename Comparable>
void LeftistHeap<Comparable>::insert(const Comparable& x) {
    root = merge(new LeftistNode(x), root);
}

template<typename Comparable>
void LeftistHeap<Comparable>::deleteMin() {
    if(isEmpty()) {
        throw std::underflow_error("Heap is empty");
    }
    LeftistNode* tmp = root;
    root = merge(root->left, root->right);
    delete tmp;
}

template<typename Comparable>
void LeftistHeap<Comparable>::deleteMin(Comparable& minItem) {
    minItem = findMin();
    deleteMin();
}

template<typename Comparable>
void LeftistHeap<Comparable>::makeEmpty() {
    reclaimMemory(root);
    root = NULL;
}

template<typename Comparable>
void LeftistHeap<Comparable>::merge(LeftistHeap& rhs) {
    // if code like this:
    // if(*this == rhs)
    // you should overwrite the operator==(const LeftistHeap& rhs)
    if(this == &rhs) {
        return;
    }
    root = merge(root, rhs.root);
    rhs.root = NULL;
}

template<typename Comparable>
const LeftistHeap<Comparable>& LeftistHeap<Comparable>::operator=(const LeftistHeap& rhs) {
    // same with merge(LeftistHeap& rhs)
    if(this != &rhs) {
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::merge(LeftistNode* h1, LeftistNode* h2) {
    if(h1 == NULL || h2 == NULL) {
        return h1 == NULL ? h2 : h1;
    }
    if(h1->element < h2->element) {
        return merge1(h1, h2);
    } else {
        return merge1(h2, h1);
    }
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::merge1(LeftistNode* h1, LeftistNode* h2) {
    if(h1->left == NULL) {
        h1->left = h2;
    } else {
        h1->right = merge(h1->right, h2);
        if(h1->left->npl < h1->right->npl) {
            swapChildren(h1);
            h1->npl = h1->right->npl + 1;
        }
    }
    return h1;
}

template<typename Comparable>
void LeftistHeap<Comparable>::swapChildren(LeftistNode* t) {
    LeftistNode* tmp = t->left;
    t->left = t->right;
    t->right = tmp;
}

template<typename Comparable>
void LeftistHeap<Comparable>::reclaimMemory(LeftistNode* t) {
    if(t != NULL) {
        reclaimMemory(t->left);
        reclaimMemory(t->right);
        delete t;
    }
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::clone(LeftistNode* t) const {
    if(t != NULL) {
        return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
    } else {
        return NULL;
    }
}

