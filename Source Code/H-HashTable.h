#pragma once
#include <set>
#include <unordered_map>
#include <bitset>
#include <cmath>
#include <string>

class HierarchicalHashTable {
private:
    struct Level {
        std::unordered_map<int, int> prefixCount;
        std::set<int> data; // Red-Black Tree
    };
    static const int MAX_LEVEL = 32; // Maximum level for 32-bit integers
    Level levels[MAX_LEVEL + 1];
    int universe_size;
public:
    HierarchicalHashTable(int size);
    ~HierarchicalHashTable();
    
// All ordered dictionary operations    
    int min();
    int max();
    bool isEmpty();
    void insert(int x);
    void remove(int x);
    bool isMember(int x);
    int successor(int x);
    int predecessor(int x);
    
// Helper functions
    std::string getPrefix(int x, int len);
};