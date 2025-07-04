#pragma once
#include <vector>
#include <climits>

class DirectMappedCache {
private:
    int size;
    std::vector<int> cache;
public:
    DirectMappedCache(int size);
    ~DirectMappedCache();

    int min();
    int max();
    bool isEmpty();
    void insert(int x);
    void remove(int x);
    bool isMember(int x);
    int successor(int x);
    int predecessor(int x);
};
