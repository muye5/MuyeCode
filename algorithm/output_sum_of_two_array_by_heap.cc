// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// ���������ź��������A��B,�����鳤�ȶ�ΪN,���Ǵ����������ȡһ��Ԫ�����,�����͵õ���N^2����
// Ҫ�����N^2���Ͱ������,�ռ䲻�ܳ���O(N)

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

