#include "HashTable.h"

HashTable::HashTable(int size) {
    // size ignored
}

HashTable::~HashTable() {}

bool HashTable::isEmpty() {
    return table.empty();
}

void HashTable::insert(int x) {
    table[x] = true;
}

void HashTable::remove(int x) {
    table.erase(x);
}

bool HashTable::isMember(int x) {
    return table.count(x) > 0;
}

int HashTable::min() {
    if (table.empty()) return -1;
    return table.begin()->first;
}

int HashTable::max() {
    if (table.empty()) return -1;
    return table.rbegin()->first;
}

int HashTable::successor(int x) {
    auto it = table.upper_bound(x);
    if (it == table.end()) return -1;
    return it->first;
}

int HashTable::predecessor(int x) {
    auto it = table.lower_bound(x);
    if (it == table.begin()) return -1;
    if (it == table.end() || it->first != x) it--;
    else if (it != table.begin()) it--;
    return it->first;
}
