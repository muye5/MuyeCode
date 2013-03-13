// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Disjoint {
    int ancestor;
    bool visited;
    Disjoint(int a = -1, bool v = false) : ancestor(a), visited(v) {}
};

template<class Comparable>
class Node {
public:
    Node(const Comparable& c);
    Node(const Node<Comparable>& rhs);
    Node& operator=(const Node<Comparable>& rhs);

    Comparable value;
    vector<int> children;
};

template<class Comparable>
Node<Comparable>::Node(const Comparable& c) : value(c) {
    children.reserve(10);
}

template<class Comparable>
Node<Comparable>::Node(const Node<Comparable>& rhs) : value(rhs.value) {
    children.resize(rhs.children.size());
    copy(rhs.children.begin(), rhs.children.end(), children.begin());
}

template<class Comparable>
Node<Comparable>& Node<Comparable>::operator=(const Node<Comparable>& rhs) {
    if(this == &rhs) {
        return *this;
    }
    value = rhs.value;
    children.clear();
    children.resize(rhs.children.size());
    copy(rhs.children.begin(), rhs.children.end(), children.begin());
    return *this;
}

int Ancestor(vector<Disjoint>& joint, const int& index) {
    if(joint[index].ancestor != index) {
        joint[index].ancestor = Ancestor(joint, joint[index].ancestor);
        return joint[index].ancestor;
    } else {
        return index;
    }
}

template<class Comparable>
void Tarjain(const vector<Node<Comparable> >& tree, vector<Disjoint>& joint, const int& index, const int& u, const int& v) {
    const vector<int>& children = tree[index].children;
    joint[index].ancestor = index;
    for(vector<int>::const_iterator it = children.begin(); it != children.end(); ++it) {
        Tarjain(tree, joint, *it, u, v);
        joint[*it].ancestor = index;
    }
    joint[index].visited = true;
    if(index == u && joint[v].visited) {
        cout << "LCA[" << v << ":" << u << "] = " << Ancestor(joint, v) << endl;
    }
    if(index == v && joint[u].visited) {
        cout << "LCA[" << u << ":" << v << "] = " << Ancestor(joint, u) << endl;
    }
}

int main(int argc, char **argv) {
    int cnt;
    cin >> cnt;
    vector<Node<int> > tree;
    vector<Disjoint> joint;
    // node information
    for(int i = 0; i < cnt; ++i) {
        tree.push_back(Node<int>(i));
        joint.push_back(Disjoint(i));
    }
    // edge information
    int u, v;
    for(int i = 0; i < cnt - 1; ++i) {
        cin >> u >> v;
        tree[u].children.push_back(v);
    }
    // find the least common ancestor
    cin >> u >> v;
    Tarjain(tree, joint, 0, u, v);
    return 0;
}

