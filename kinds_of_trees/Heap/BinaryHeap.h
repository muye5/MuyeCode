// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_
#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename Comparable>
class BinaryHeap {
public:
    explicit BinaryHeap(int capacity = 100);
    explicit BinaryHeap(const std::vector<Comparable>& items);

    bool isEmpty() const;
    const Comparable& findMin() const;

    void insert(const Comparable& x);
    void deleteMin();
    void deleteMin(Comparable& minItem);
    void makeEmpty();

private:
    int currentSize;
    std::vector<Comparable> array;

    void buildHeap();
    void percolateDown(int hole);
};

template<typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(int capacity) : currentSize(0) {
    array.resize(capacity);
}

template<typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const std::vector<Comparable>& items) : currentSize(items.size()) {
    array.resize(items.size() + 10);
    copy(items.begin(), items.end(), array.begin());
    buildHeap();
}

template<typename Comparable>
bool BinaryHeap<Comparable>::isEmpty() const {
    return currentSize == 0;
}

template<typename Comparable>
const Comparable& BinaryHeap<Comparable>::findMin() const {
    return array.front();
}

template<typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable& x) {
    if(currentSize == (int)array.size() - 1) {
        array.resize(2 * array.size());
    }
    int i = currentSize++;
    for(; i > 0 && x < array[(i-1)/2]; i = (i-1)/2) {
        array[i] = array[(i-1)/2];
    }
    array[i] = x;
}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteMin() {
    if(isEmpty()) {
        throw std::underflow_error("Heap is empty");
    }
    array[0] = array[--currentSize];
    percolateDown(0);
}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteMin(Comparable& minItem) {
    if(isEmpty()) {
        throw std::underflow_error("Heap is empty");
    }
    minItem = array[0];
    array[0] = array[--currentSize];
    percolateDown(0);
}

template<typename Comparable>
void BinaryHeap<Comparable>::makeEmpty() {
    currentSize = 0;
    array.clear();
}

template<typename Comparable>
void BinaryHeap<Comparable>::buildHeap() {
    for(int i = (currentSize-2)/2; i >= 0; --i) {
        percolateDown(i);
    }
}

template<typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole) {
    Comparable tmp = array[hole];
    int child;
    for(; 2*hole+1 < currentSize; hole = child) {
        child = 2 * hole + 1;
        if(child != currentSize-1 && array[child+1] < array[child]) {
            ++child;
        }
        if(tmp > array[child]) {
            array[hole] = array[child];
        } else {
            break;
        }
    }
    array[hole] = tmp;
}
#endif  // BINARYHEAP_H_

