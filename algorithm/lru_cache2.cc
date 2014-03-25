// Copyright (c) 2014
// Author: Muye (muyepiaozhou@gmail.com)

#include <utility>
#include <list>
#include <map>
using std::map;
using std::list;
using std::pair;
using std::make_pair;

class LRUCache {
public:
    LRUCache(size_t _capacity);
public:
    int get(int key);
    int set(int key, int value);
private:
    size_t capacity;
    size_t size;
    list<pair<int, int> > Q;
    map<int, list<pair<int, int> >::iterator> hash;
};

LRUCache::LRUCache(size_t _capacity) : capacity(_capacity), size(0) {}

int LRUCache::get(int key) {
    if(hash.find(key) == hash.end()) return -1;
    list<pair<int, int> >::iterator it = hash[key];
    pair<int, int> node = *it;
    Q.erase(it);
    Q.push_front(node);
    hash[key] = Q.begin();
    return node.second;
}

int LRUCache::set(int key, int value) {
    if(get(key) != -1) Q.begin()->second = value;
    else {
        if(size == capacity) {
            hash.erase(Q.back().first);
            Q.pop_back();
        } else ++size;
        pair<int, int> node = make_pair(key, value);
        Q.push_front(node);
        hash[key] = Q.begin();
    }
}
