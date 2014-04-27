// Copyright (c) 2014
// Author: Yanshi.WYS ()

#include "kdtree.h"
#include <climits>
#include <iostream>

// KDPoint member function
bool KDPoint::operator<(const KDPoint& t) const {
    for(int i = 0; i < DIM; ++i) {
        if(d[i] >= t.d[i]) return false;
    }
    return true;
}
bool KDPoint::operator==(const KDPoint& t) const {
    for(int i = 0; i < DIM; ++i) {
        if(d[i] != t.d[i]) return false;
    }
    return true;
}
bool KDPoint::lt(const KDPoint& t, const int& dim) const {
    return d[dim] < t.d[dim];
}
bool KDPoint::eq(const KDPoint& t, const int& dim) const {
    return d[dim] == t.d[dim];
}
bool KDPoint::gt(const KDPoint& t, const int& dim) const {
    return d[dim] > t.d[dim];
}

// KDSpace member function
bool KDSpace::inner(const KDSpace& s) const {
    return (s.x < x || s.x == x) && (y < s.y || y == s.y);
}
bool KDSpace::disjoint(const KDSpace& s) const {
    for(int i = 0; i < DIM; ++i) {
        if(!(x.gt(s.y, i) || y.lt(s.x, i))) return false;
    }
    return true;
}
bool KDSpace::contain(const KDPoint& pt) const {
    for(int i = 0; i < DIM; ++i) {
        if(x.gt(pt, i) || y.lt(pt, i)) return false;
    }
    return true;
}
// global function
void swap(KDNode * a, KDNode * b) {
    KDData * tmp = a->ptr;
    a->ptr = b->ptr;
    b->ptr = tmp;
}
// quick select method
KDNode * find_median(KDNode * start, KDNode * end, int dim) {
    if(end <= start) return NULL;
    if(start + 1 == end) return start;
    KDNode * mid = start + (end - start) / 2;
    KDNode * store, * cur;
    while(true) {
        int pivot = mid->x.d[dim];
        swap(mid, end - 1);
        for(cur = store = start; cur < end - 1; ++cur) {
            if(cur->x.d[dim] <= pivot) {
                if(cur != store) swap(cur, store);
                ++store;
            }
        }
        swap(store, end - 1);
        if(pivot == mid->x.d[dim]) return store;
        if(store > mid) end = store;
        else start = store;
    }
}
void make_space(KDNode * t, KDNode * start, int len) {
    int num = 0, sum = 0;
    int x[DIM], y[DIM];
    for(int i = 0; i < DIM; ++i) {
        x[i] = INT_MAX;
        y[i] = INT_MIN;
    }
    KDNode * end = start + len;
    while(start < end) {
        for(int i = 0; i < DIM; ++i) {
            if(x[i] > start->x.d[i]) x[i] = start->x.d[i];
            if(y[i] < start->x.d[i]) y[i] = start->x.d[i];
        }
        sum += start->ptr->data;
        ++start;
    }
    for(int i = 0; i < DIM; ++i) {
        t->space.x.d[i] = x[i];
        t->space.y.d[i] = y[i];
    }
    t->num = len;
    t->sum = sum;
}
KDNode * make_kdtree(KDNode * start, int len, int dim) {
    if(len <= 0) return NULL;
    KDNode * root = NULL;
    if((root = find_median(start, start + len, dim)) != NULL) {
        make_space(root, start, len);
        dim = (dim + 1) / DIM;
        root->left = make_kdtree(start, root - start, dim);
        root->right = make_kdtree(root + 1, start + len - (root + 1), dim);
    }
    return root;
}
void query(KDNode * root, int dim, const KDSpace& s, int& num, int& sum) {
    if(root == NULL || root->space.disjoint(s)) return;
    if(root->space.inner(s)) {
        num += root->num;
        sum += root->sum;
        return;
    }
    if(s.contain(root->x)) {
        sum += root->ptr->data;
        ++num;
    }
    dim = (dim + 1) % DIM;
    if(root->left && !(root->left->space.disjoint(s)))
        query(root->left, dim, s, num, sum);
    if(root->right && !(root->right->space.disjoint(s)))
        query(root->right, dim, s, num, sum);
}

void print_kdtree(KDNode * root, int indent) {
    using std::cout;
    using std::endl;
    if(!root) return;
    for(int i = 0; i < indent; ++i) cout << '-';

    // KDNode.x
    cout << "( " << root->x.d[0];
    for(int i = 1; i < DIM; ++i) {
        cout << ", " << root->x.d[i];
    }
    // KDNode.ptr->data
    cout << " )\t" << root->ptr->data;
    // KDNode.space
    cout << "\t[( " << root->space.x.d[0];
    for(int i = 1; i < DIM; ++i) {
        cout << ", " << root->space.x.d[i];
    }
    cout << " ), ( " << root->space.y.d[0];
    for(int i = 1; i < DIM; ++i) {
        cout << ", " << root->space.y.d[i];
    }
    cout << " )]" << endl;
    indent += 4;
    cout << endl;
    if(root->left) print_kdtree(root->left, indent);
    cout << endl;
    if(root->right) print_kdtree(root->right, indent);
}
