#pragma once
#include <set>

class BinarySearchTree {
private:
    std::set<int> tree;
public:
    BinarySearchTree(int size);  // size unused
    ~BinarySearchTree();

    int min();
    int max();
    bool isEmpty();
    void insert(int x);
    void remove(int x);
    bool isMember(int x);
    int successor(int x);
    int predecessor(int x);
};
