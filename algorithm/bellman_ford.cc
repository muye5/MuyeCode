// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// http://acm.hdu.edu.cn/showproblem.php?pid=2544

#include <iostream>
#include <climits>
#include <vector>
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
    int k;
    int path;
public:
    Node(const int& i) : k(i), path(inf) {}
    Node(const Node& node) : k(node.k), path(node.path) {}
};

class Graph {
private:
    vector<Node> nodes;
    vector<Edge> edges;
public:
    Graph() {
        nodes.push_back(Node(0));
    }
    void addnode(const int& i) {
        nodes.push_back(Node(i));
    }
    void addedge(const int& i, const int& j, const int& distance) {
        edges.push_back(Edge(i, j, distance));
        edges.push_back(Edge(j, i, distance));
    }
    bool bellman_ford(const int& s, const int& t, int& path) {
        nodes[s].path = 0;
        size_t num = nodes.size() - 1;
        for(size_t i = 1; i < num; ++i) {
            for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
                relax(*it);
            }
        }
        for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
            if(!check(*it)) {
                return false;
            }
        }
        path = nodes[t].path;
        return true;
    }
    void clear() {
        nodes.erase(nodes.begin() + 1, nodes.end());
        edges.clear();
    }
private:
    void relax(Edge& e) {
        int &u = e.u, &v = e.v;
        if(nodes[v].path > nodes[u].path + e.distance) {
            nodes[v].path = nodes[u].path + e.distance;
        }
    }
    bool check(Edge& e) {
        int &u = e.u, &v = e.v;
        if(nodes[v].path > nodes[u].path + e.distance) {
            return false;
        }
        return true;
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
        int path = 0;
        if(G.bellman_ford(1, n, path)) {
            cout << path << endl;
        }
        G.clear();
    }
    return 0;
}

