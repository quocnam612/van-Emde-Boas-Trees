#pragma once
#include <set>
#include <unordered_map>
#include <cmath>
#include <algorithm>

class YFastTrie {
private:
    struct Chunk {
        std::set<int> bst; // Red-Black Tree
    };
    int universe_size;
    int minimum, maximum;
    int bucketSize;
    std::unordered_map<int, Chunk*> buckets; // Chain Hash Table
    std::set<int> representatives; // Red-Black Tree
public:
    YFastTrie(int size);
    ~YFastTrie();

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
    int getBucketId(int x);
    void ensureBucket(int x);
};
