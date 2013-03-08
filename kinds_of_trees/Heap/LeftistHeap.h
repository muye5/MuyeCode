// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#ifndef LEFTISTHEAP_H_
#define LEFTISTHEAP_H_
template<typename Comparable>
class LeftistHeap {
public:
    LististHeap();
    LeftistHeap(const LeftistHeap& rhs);
    ~LeftistHeap();

    bool isEmpty() const;
    const Comparable& findMin() const;

    void insert(const Comparable& x);
    void deleteMin();
    void deleteMin(Comparable& minItem);
    void makeEmpty();
    void merge(LeftistHeap& rhs);

    const LeftistHeap& operator=(const LeftistHeap& rhs);

private:
    struct LeftistNode {
        Comparable element;
        LeftistNode* left;
        LeftistNode* right;
        int npl; // null path lenght

        LeftistNode(const Comparable& e, LeftistNode* lt = NULL, LeftistNode* rt = NULL, int np = 0)
            : element(e), left(lt), right(rt), npl(np) {}
    };

    LeftistNode* root;
    LeftistNode* merge(LeftistNode* h1, LeftistNode* h2);
    LeftistNode* merge1(LeftistNode* h1, LeftistNode* h2);

    void swapChildren(LeftistNode* t);
    void reclaimMemory(LeftistNode* t);
    LeftistNode* clone(LeftistNode* t) const;
};
#endif  // LEFTISTHEAP_H_

