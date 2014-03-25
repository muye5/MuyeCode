// Copyright (c) 2014
// Author: Muye (muyepiaozhou@gmail.com)

//         1
//       /  \
//      2    3
//     / \    \
//    4   5    7
//
// After calling your function, the tree should look like:
//
//         1 -> NULL
//       /  \
//      2 -> 3 -> NULL
//     / \    \
//    4-> 5 -> 7 -> NULL
//
// Definition for binary tree with next pointer.
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

// solution: while iterating in a line, get the next node based on the upper line's information
// at this time, the upper line has been done well.
class Solution {
public:
    void connect(TreeLinkNode *root) {
        while(root) {
            TreeLinkNode *cur = root;
            while(cur) {
                TreeLinkNode *next = cur->next;
                while(next && !next->left && !next->right) next = next->next;
                if(next) next = next->left ? next->left : next->right;
                if(cur->left) cur->left->next = cur->right ? cur->right : next;
                if(cur->right) cur->right->next = next;
                cur = cur->next;
            }
            while(root && !root->left && !root->right) root = root->next;
            if(root) root = root->left ? root->left : root->right;
        }
    }
};

