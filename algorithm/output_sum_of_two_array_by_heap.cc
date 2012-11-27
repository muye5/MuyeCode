// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// 给定两个排好序的数组A和B,两数组长度都为N,我们从两个数组各取一个元素求和,这样就得到了N^2个和
// 要求把这N^2个和按序输出,空间不能超过O(N)

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

class Node {
public:
    int value;
    int index;
public:
    Node(int v, int i) : value(v), index(i) {}
    Node(const Node& n) {
        value = n.value;
        index = n.index;
    }
};

class Cmp{
public:
    bool operator()(const Node& a, const Node& b) {
        return a.value > b.value;
    }
};

int main(int argc, char **argv) {
    const int len = 8;
    int A[len], B[len], C[len] = {0};
    vector<Node> heap;

    srand((unsigned)time(NULL));
    for(int i = 0; i < len; ++i) {
        A[i] = rand() % 100 + 1;
        B[i] = rand() % 100 + 1;
    }
    sort(A, A + len);
    sort(B, B + len);
    for(int i = 0; i < len; ++i) {
        heap.push_back(Node(A[i] + B[0], i));
    }

    Cmp cmp;
    make_heap(heap.begin(), heap.end(), cmp);
    printf("=====================  A  ====================\n");
    for(int i = 0; i < len; ++i) {
        printf("%-5d%c", A[i], (i + 1 == len ? '\n' : ' '));
    }
    printf("=====================  B  ====================\n");
    for(int i = 0; i < len; ++i) {
        printf("%-5d%c", B[i], (i + 1 == len ? '\n' : ' '));
    }
    printf("==============================================\n");

    int num = 0;
    while(!heap.empty()) {
        pop_heap(heap.begin(), heap.end(), cmp);
        Node& n = heap.back();
        printf("%-5d%c", n.value, (++num % len ? ' ' : '\n'));
        ++C[n.index];
        if(C[n.index] < len) {
            n.value = A[n.index] + B[C[n.index]];
            push_heap(heap.begin(), heap.end(), cmp);
        } else {
            heap.pop_back();
        }
    }
    return 0;
}

