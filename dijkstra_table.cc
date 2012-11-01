// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// http://acm.hdu.edu.cn/showproblem.php?pid=2544

#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int inf = INT_MAX >> 1;

class Edge {
public:
    int u, v;
    int distance;
public:
    Edge() : u(0), v(0), distance(inf) {}
    Edge(const int& i, const int& j, const int& dis) : u(i), v(j), distance(dis) {}
};

class Node {
public:
    bool flag;
    int k;
    int path;
    vector<Edge> edges;
public:
    Node(const int& i) : flag(false), k(i), path(inf) {}
    Node(const Node& node) : flag(node.flag), k(node.k), path(node.path) {
        edges.clear();
        edges.resize(node.edges.size());
        copy(node.edges.begin(), node.edges.end(), edges.begin());
    }
public:
    bool addedge(const Edge& e) {
        if(e.u != k) {
            cerr << "wrong edge" << endl;
            return false;
        }
        edges.push_back(e);
        return true;
    }
    Node& operator=(const Node& node) {
        if(&node == this) {
            return *this;
        } else {
            flag = node.flag;
            k = node.k;
            path= node.path;
            edges.clear();
            edges.resize(node.edges.size());
            copy(node.edges.begin(), node.edges.end(), edges.begin());
            return *this;
        }
    }
    friend bool operator<(const Node& u, const Node& v) {
        return (u.path > v.path);
    }
};

class Graph {
private:
    vector<Node> nodes;
public:
    Graph() {
        nodes.push_back(Node(0));
    }
    bool addnode(const int& i) {
        nodes.push_back(Node(i));
        return true;
    }
    bool addedge(const int& i, const int& j, const int& distance) {
        return (nodes[i].addedge(Edge(i, j, distance)) && nodes[j].addedge(Edge(j, i, distance)));
    }
    int shortest_path(const int& u, const int& v) {
        nodes[u].path = 0;
        nodes[u].flag = true;
        priority_queue<Node, vector<Node>, less<Node> > Q;
        Q.push(nodes[u]);
        while(!Q.empty()) {
            Node node = Q.top();
            nodes[node.k].flag = true;
            vector<Edge>& edges = node.edges;
            Q.pop();
            for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
                Node& vnode = nodes[it->v];
                if(!vnode.flag && vnode.path > node.path + it->distance) {
                    vnode.path = node.path + it->distance;
                    Q.push(vnode);
                }
            }
        }
        return nodes[v].path;
    }
    void clear() {
        nodes.erase(nodes.begin() + 1, nodes.end());
    }
};

int main(int argc, char **argv) {
    Graph G;
    int n, m;
    while(cin >> n >> m, m && n) {
        for(int i = 1; i <= n; ++i) {
            G.addnode(i);
        }
        int u, v, dis;
        for(int i = 0; i < m; ++i) {
            cin >> u >> v >> dis;
            G.addedge(u, v, dis);
        }
        cout << G.shortest_path(1, n) << endl;
        G.clear();
    }
    return 0;
}

