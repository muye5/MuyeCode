// Copyright (c) 2014
// Author: Yanshi.WYS ()

#include <iostream>
#include <stack>
using namespace std;

class TreeNode {
public:
    TreeNode() : value(0), left(NULL), right(NULL) {}
public:
    int value;
    TreeNode *left, *right;
};

class BinaryTreeTravel {
public:
    static void preOrder(TreeNode *root);
    static void inOrder(TreeNode *root);
    static void postOrder(TreeNode *root);
};

void BinaryTreeTravel::preOrder(TreeNode *root) {
    stack<TreeNode *> S;
    if(root) S.push(root);
    while(!S.empty()) {
        root = S.top();
        S.pop();
        cout << root->value << endl;
        if(root->right) S.push(root->right);
        if(root->left) S.push(root->left);
    }
}

void BinaryTreeTravel::inOrder(TreeNode *root) {
    stack<TreeNode *> S;
    while(root || !S.empty()) {
        while(root) {
            S.push(root);
            root = root->left;
        }
        root = S.top();
        S.pop();
        cout << root->value << endl;
        root = root->right;
    }
}

void BinaryTreeTravel::postOrder(TreeNode *root) {
    TreeNode *pre = NULL;
    stack<TreeNode *> S;
    if(root) S.push(root);
    while(!S.empty()) {
        root = S.top();
        if((!root->left && !root->right) || (pre && (pre == root->left || pre == root->right))) {
            cout << root->value << endl;
            pre = root;
            S.pop();
        } else {
            if(root->right) S.push(root->right);
            if(root->left) S.push(root->left);
        }
    }
}

