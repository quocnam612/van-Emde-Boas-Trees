#pragma once
#include <map>

class HashTable {
private:
    std::map<int, bool> table;
public:
    HashTable(int size); // size unused
    ~HashTable();

    int min();
    int max();
    bool isEmpty();
    void insert(int x);
    void remove(int x);
    bool isMember(int x);
    int successor(int x);
    int predecessor(int x);
};
