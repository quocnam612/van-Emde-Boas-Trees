#include "DMCache.h"

DirectMappedCache::DirectMappedCache(int size) : size(size), cache(size, -1) {}

DirectMappedCache::~DirectMappedCache() {}

bool DirectMappedCache::isEmpty() {
    for (int val : cache) if (val != -1) return false;
    return true;
}

void DirectMappedCache::insert(int x) {
    int index = x % size;
    cache[index] = x;
}

void DirectMappedCache::remove(int x) {
    int index = x % size;
    if (cache[index] == x) cache[index] = -1;
}

bool DirectMappedCache::isMember(int x) {
    int index = x % size;
    return cache[index] == x;
}

int DirectMappedCache::min() {
    int result = INT_MAX;
    for (int val : cache) if (val != -1 && val < result) result = val;
    return isEmpty() ? -1 : result;
}

int DirectMappedCache::max() {
    int result = INT_MIN;
    for (int val : cache) if (val != -1 && val > result) result = val;
    return isEmpty() ? -1 : result;
}

int DirectMappedCache::successor(int x) {
    int succ = INT_MAX;
    for (int val : cache) if (val != -1 && val > x && val < succ) succ = val;
    return succ == INT_MAX ? -1 : succ;
}

int DirectMappedCache::predecessor(int x) {
    int pred = INT_MIN;
    for (int val : cache) if (val != -1 && val < x && val > pred) pred = val;
    return pred == INT_MIN ? -1 : pred;
}
