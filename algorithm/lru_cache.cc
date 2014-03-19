// Copyright (c) 2014
// Author: Yanshi.WYS ()
// double direction list && map

#include <iostream>
#include <map>
using namespace std;

struct Node {
    int val;
    Node *pre, *next;
    Node(int v = 0) : val(v), pre(NULL), next(NULL) {}
};

class LRUCache{
public:
    LRUCache(int capacity) : cap(capacity), head(NULL), tail(NULL) {
        tail = head = new Node();
        int i = 0;
        while(++i < capacity) {
            Node *cur = new Node();
            tail->next = cur;
            cur->pre = tail;
            tail = cur;
        }
        tail = NULL;
    }

    ~LRUCache() {
        while(head) {
            Node *cur = head;
            head = head->next;
            delete cur;
        }
    }
public:
    int get(int key) {
        if(table.find(key) == table.end()) return -1;
        Node *cur = table[key];
        if(cur != head) {
            if(cur == tail) tail = cur->pre;
            cur->pre->next = cur->next;
            if(cur->next) cur->next->pre = cur->pre;
            cur->next = head;
            cur->pre = NULL;
            head->pre = cur;
            head = cur;
        }
        return cur->val;
    }

    void set(int key, int value) {
        if(get(key) != -1) head->val = value;
        else {
            if(table.size() == cap) {
                Node *cur = tail;
                if(cur != head) {
                    tail = cur->pre;
                    tail->next = NULL;
                    cur->next = head;
                    cur->pre = NULL;
                    head->pre = cur;
                    head = cur;
                }
                head->val = value;
                table.erase(rtable[head]);
                rtable[head] = key;
                table.insert(pair<int, Node *>(key, head));
            } else {
                if(tail) tail = tail->next;
                else tail = head;
                tail->val = value;
                table.insert(pair<int, Node *>(key, tail));
                rtable.insert(pair<Node *, int>(tail, key));
                get(key);
            }
        }
    }
private:
    int cap;
    Node *head, *tail;
    map<int, Node *> table;
    map<Node *, int> rtable;
};

int main() {
    LRUCache cache(2);
    // input: set(2,1),set(2,2),get(2),set(1,1),set(4,1),get(2)
    // output: [2, -1]
    cache.set(2, 1);
    cache.set(2, 2);
    cout << cache.get(2) << endl;
    cache.set(1, 1);
    cache.set(4, 1);
    cout << cache.get(2) << endl;
    return 0;
}

