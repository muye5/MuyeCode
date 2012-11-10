// Copyright (c) 2012 .
// Author: Muye (muyepiaozhou@gmail.com)
// �Թ�����:http://weibo.com/1915548291/z4eTPtAnv#1352537447740
// ˼·:BFS
// [ע:�˴�ֻ���Ƕ�2�ɽ��������Ľⷨ]
// ������λ�ÿ�ʼѡ��·��,ͨ������������·�ٻص�����,˳��ʱ��,�������ַ���.
// ���⻹Ӧ��ӿɶ�2������������������,�ų�������Ҫ���·��.
// 2011 % 2 != 0, �ʵ�һ����Ϊ 2011 + 7 = 2018 �������ĵ�.
// 2012 % 3 != 0, �����һ����Ϊ 2017 - 5 = 2012 ����.
// ����ͨ����ÿ���ڵ��¼��ǰ��·��,��ʵ������·�������.
//
// ·�����:
// path_1 : [ '/' 2 '+' 7 ]
// path_2 : [ '+' 7 '/' 2 ]
// path_3 : [ '*' 3 '-' 5 ]
// path_4 : [ '-' 5 '*' 3 ]

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Node {
public:
    int value;  // ��ǰֵ
    vector<int> road;   // ��¼�����ֵ��·��
public:
    Node(const int& v, const int& from) : value(v) {
        road.push_back(from);
    }
    Node(const int& v, const int& from, const vector<int>& r) : value(v) {
        road.resize(r.size() + 1);
        copy(r.begin(), r.end(), road.begin());
        road.push_back(from);
    }
    Node(const Node& node) {
        if(&node == this) {
            return;
        }
        value = node.value;
        road.resize(node.road.size());
        copy(node.road.begin(), node.road.end(), road.begin());
    }
};

// ������·��
void print_path(const vector<int>& road) {
    size_t n = road.size(), i = 0;
    int v = 2011, from;
    cout << v << " + 7 = " << v + 7 << endl; // ��һ��
    v += 7;
    while(++i < n) {
        from = road[i];
        switch(from) {
        case 1:
            cout << v << " / 2 + 7 = " << v / 2 + 7 << endl;
            v = v / 2 + 7;
            break;
        case 2:
            cout << "(" << v << " + 7) / 2 = " << (v + 7) / 2 << endl;
            v = (v + 7) / 2;
            break;
        case 3:
            cout << v << " * 3 - 5 = " << v * 3 - 5 << endl;
            v = v * 3 - 5;
            break;
        case 4:
            cout << "(" << v << " - 5) * 3 = " << (v - 5) * 3 << endl;
            v = (v - 5) * 3;
            break;
        }
    }
    cout << v << " - 5 = " << v - 5 << endl; // ���һ��
}

// �����������Ѱ��2012
void find_2012_bfs() {
    queue<Node> Q;
    Q.push(Node(2018, 1)); // ��һ����Ϊ 2011 + 7 = 2018
    while(!Q.empty()) {
        const Node& node = Q.front();
        const int& from = node.road.back();
        // ���߻�ͷ·
        if(from != 2) {
            if(node.value % 2 == 0) {
                Q.push(Node(node.value / 2 + 7, 1, node.road));
            }
        }
        if(from != 1) {
            if((node.value + 7) % 2 == 0) {
                Q.push(Node((node.value + 7) / 2, 2, node.road));
            }
        }
        if(from != 4) {
            Q.push(Node(node.value * 3 - 5, 3, node.road));
        }
        if(from != 3) {
            if(node.value - 5 == 2012) {
                print_path(node.road);
                break;
            } else {
                Q.push(Node((node.value - 5) * 3, 4, node.road));
            }
        }
        Q.pop();
    }
}

int main(int argc, char **argv) {
    find_2012_bfs();
    return 0;
}

