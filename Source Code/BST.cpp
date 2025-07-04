#include "BST.h"

BinarySearchTree::BinarySearchTree(int size) {
    // size ignored
}

BinarySearchTree::~BinarySearchTree() {
    tree.clear();
}

bool BinarySearchTree::isEmpty() {
    return tree.empty();
}

void BinarySearchTree::insert(int x) {
    tree.insert(x);
}

void BinarySearchTree::remove(int x) {
    tree.erase(x);
}

bool BinarySearchTree::isMember(int x) {
    return tree.count(x) > 0;
}

int BinarySearchTree::min() {
    if (tree.empty()) return -1;
    return *tree.begin();
}

int BinarySearchTree::max() {
    if (tree.empty()) return -1;
    return *tree.rbegin();
}

int BinarySearchTree::successor(int x) {
    auto it = tree.upper_bound(x);
    if (it == tree.end()) return -1;
    return *it;
}

int BinarySearchTree::predecessor(int x) {
    auto it = tree.lower_bound(x);
    if (it == tree.begin()) return -1;
    if (it == tree.end() || *it != x) --it;
    else if (it != tree.begin()) --it;
    return *it;
}
