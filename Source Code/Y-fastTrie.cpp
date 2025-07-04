#include "Y-fastTrie.h"

YFastTrie::YFastTrie(int size) {
    universe_size = size;
    minimum = maximum = -1;
    bucketSize = std::max(1, int(std::log2(size)));
}

YFastTrie::~YFastTrie() {
    for (auto& [_, chunk] : buckets) delete chunk;
}

/* All ordered dictionary operations */
int YFastTrie::min() { 
    return minimum; 
}

int YFastTrie::max() { 
    return maximum; 
}

bool YFastTrie::isEmpty() { 
    return minimum == -1; 
}

void YFastTrie::insert(int x) {
    ensureBucket(x);
    int id = getBucketId(x);
    Chunk* c = buckets[id];
    c->bst.insert(x);
    if (minimum == -1 || x < minimum) minimum = x;
    if (maximum == -1 || x > maximum) maximum = x;
}

void YFastTrie::remove(int x) {
    int id = getBucketId(x);
    if (buckets.find(id) == buckets.end()) return;
    Chunk* c = buckets[id];
    c->bst.erase(x);
    if (c->bst.empty()) {
        delete c;
        buckets.erase(id);
        representatives.erase(id);
    }
    if (x == minimum || x == maximum) {
        minimum = maximum = -1;
        for (auto& [_, chunk] : buckets) {
            if (!chunk->bst.empty()) {
                int mini = *chunk->bst.begin();
                int maxi = *chunk->bst.rbegin();
                if (minimum == -1 || mini < minimum) minimum = mini;
                if (maximum == -1 || maxi > maximum) maximum = maxi;
            }
        }
    }
}

bool YFastTrie::isMember(int x) {
    int id = getBucketId(x);
    return buckets.find(id) != buckets.end() && buckets[id]->bst.count(x);
}

int YFastTrie::successor(int x) {
    int id = getBucketId(x);
    int result = INT_MAX;

    if (buckets.count(id)) {
        auto it = buckets[id]->bst.upper_bound(x);
        if (it != buckets[id]->bst.end()) result = std::min(result, *it);
    }

    auto it = representatives.upper_bound(id);
    if (it != representatives.end()) {
        Chunk* c = buckets[*it];
        if (!c->bst.empty()) result = std::min(result, *c->bst.begin());
    }

    return result == INT_MAX ? -1 : result;
}

int YFastTrie::predecessor(int x) {
    int id = getBucketId(x);
    int result = INT_MIN;

    if (buckets.count(id)) {
        auto it = buckets[id]->bst.lower_bound(x);
        if (it != buckets[id]->bst.begin()) {
            it--;
            result = std::max(result, *it);
        }
    }

    auto it = representatives.lower_bound(id);
    if (it != representatives.begin()) {
        it--;
        Chunk* c = buckets[*it];
        if (!c->bst.empty()) result = std::max(result, *c->bst.rbegin());
    }

    return result == INT_MIN ? -1 : result;
}

/* Helper functions */

int YFastTrie::getBucketId(int x) {
    return x / bucketSize;
}

void YFastTrie::ensureBucket(int x) {
    int id = getBucketId(x);
    if (buckets.find(id) == buckets.end()) {
        buckets[id] = new Chunk();
        representatives.insert(id);
    }
}