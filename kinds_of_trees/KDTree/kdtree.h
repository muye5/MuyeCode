// Copyright (c) 2014
// Author: Yanshi.WYS ()


#ifndef KDTREE_H_
#define KDTREE_H_

#include <cstdio>
#define DIM 2

class KDPoint {
public:
    bool operator<(const KDPoint& t) const;
    bool operator==(const KDPoint& t) const;
    bool lt(const KDPoint& t, const int& dim) const;
    bool eq(const KDPoint& t, const int& dim) const;
    bool gt(const KDPoint& t, const int& dim) const;
public:
    int d[DIM]; // point coorrdinate
};

class KDSpace {
public:
    bool inner(const KDSpace& s) const;
    bool disjoint(const KDSpace& s) const;
    bool contain(const KDPoint& pt) const;
public:
    KDPoint x, y; // space coorrdinate
};

class KDData {
public:
    int data;
};

class KDNode {
public:
    KDNode() : ptr(NULL), left(NULL), right(NULL) {}
public:
    KDData * ptr;
    KDNode * left, * right;
    KDSpace space;
    KDPoint x;
public:
    // statistic info
    int num; // number of subnodes
    int sum; // sum of subnodes' data
};

void swap(KDNode * a, KDNode * b);
KDNode * find_median(KDNode * start, KDNode * end, int dim);
void make_space(KDNode * t, KDNode * start, int len);
KDNode * make_kdtree(KDNode * start, int len, int dim);
// query the number of nodes which are contained in space s
void query(KDNode * root, int dim, const KDSpace& s,
           int& num, int& sum); // output arguments for statistics
void print_kdtree(KDNode * root, int indent);

#endif  // KDTREE_H_

