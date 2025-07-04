#pragma once
#include <vector>
#include <cmath>

class VanEmdeBoasTree {
private:
    int universe_size, minimum, maximum, cluster_size;
    VanEmdeBoasTree* summary;
    std::vector<VanEmdeBoasTree*> clusters;
public:
    VanEmdeBoasTree(int size);
    ~VanEmdeBoasTree(); 
    
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
    int high(int x);
    int low(int x);
    int generateIndex(int x, int y);
    void emptyInsert(int x);
};