#include "H-HashTable.h"
using namespace std;

HierarchicalHashTable::HierarchicalHashTable(int size) {
    universe_size = size;
    for (int i = 0; i <= MAX_LEVEL; ++i) {
        levels[i].prefixCount.clear();
        levels[i].data.clear();
    }
}

HierarchicalHashTable::~HierarchicalHashTable() {
    for (int i = 0; i <= MAX_LEVEL; ++i) {
        levels[i].data.clear();
        levels[i].prefixCount.clear();
    }
    universe_size = 0;
}

int HierarchicalHashTable::min() {
    if (isEmpty()) return -1;
    return *levels[MAX_LEVEL].data.begin();
}

int HierarchicalHashTable::max() {
    if (isEmpty()) return -1;
    return *levels[MAX_LEVEL].data.rbegin();
}

bool HierarchicalHashTable::isEmpty() {
    return universe_size == 0;
}

void HierarchicalHashTable::insert(int x) {
    for (int i = 0; i <= MAX_LEVEL; i++) {
        int prefix = x >> (MAX_LEVEL - i);
        levels[i].prefixCount[prefix]++;
    }
    levels[MAX_LEVEL].data.insert(x);
    universe_size++;
}

void HierarchicalHashTable::remove(int x) {
    for (int i = 0; i <= MAX_LEVEL; i++) {
        int prefix = x >> (MAX_LEVEL - i);
        auto& count = levels[i].prefixCount[prefix];
        if (--count == 0) {
            levels[i].prefixCount.erase(prefix);
        }
    }
    levels[MAX_LEVEL].data.erase(x);
    universe_size--;
}

bool HierarchicalHashTable::isMember(int x) {
    return levels[MAX_LEVEL].data.count(x);
}

int HierarchicalHashTable::successor(int x) {
    auto it = levels[MAX_LEVEL].data.upper_bound(x);
    if (it == levels[MAX_LEVEL].data.end()) return -1;
    return *it;
}

int HierarchicalHashTable::predecessor(int x) {
    if (isEmpty()) return -1;

    auto& s = levels[MAX_LEVEL].data;
    auto it = s.lower_bound(x);

    if (it == s.begin()) return -1; // No smaller element

    if (it == s.end() || *it >= x) --it; // Go to previous if x doesn't exist or x itself
    else if (*it == x) {
        // Already at x, so move back to strictly smaller
        if (it == s.begin()) return -1;
        it--;
    }

    return *it;
}

string HierarchicalHashTable::getPrefix(int x, int len) {
    return bitset<MAX_LEVEL>(x).to_string().substr(0, len);
}