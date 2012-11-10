// Copyright (c) 2012 .
// Author: Muye (muyepiaozhou@gmail.com)
// 迷宫问题:http://weibo.com/1915548291/z4eTPtAnv#1352537447740
// 思路:BFS
// [注:此答案只考虑对2可进行整除的解法]
// 从中心位置开始选择路径,通过左右两条环路再回到中心,顺逆时针,共有四种方案.
// 此外还应添加可对2进行整除的限制条件,排除不符合要求的路径.
// 2011 % 2 != 0, 故第一步必为 2011 + 7 = 2018 到达中心点.
// 2012 % 3 != 0, 故最后一步比为 2017 - 5 = 2012 结束.
// 另外通过对每个节点记录其前驱路径,来实现最终路径的输出.
//
// 路径标号:
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
    int value;  // 当前值
    vector<int> road;   // 记录到达该值的路径
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

// 输出结果路径
void print_path(const vector<int>& road) {
    size_t n = road.size(), i = 0;
    int v = 2011, from;
    cout << v << " + 7 = " << v + 7 << endl; // 第一步
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
    cout << v << " - 5 = " << v - 5 << endl; // 最后一步
}

// 广度优先搜索寻找2012
void find_2012_bfs() {
    queue<Node> Q;
    Q.push(Node(2018, 1)); // 第一步必为 2011 + 7 = 2018
    while(!Q.empty()) {
        const Node& node = Q.front();
        const int& from = node.road.back();
        // 不走回头路
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

