#include "vEBTree.h"
using namespace std;

VanEmdeBoasTree::VanEmdeBoasTree(int size) {
    universe_size = size;
    minimum = maximum = -1;
    summary = nullptr;

    if (size <= 2) {
        cluster_size = 0;
        clusters = {};
    } 
    else {
        cluster_size = 1 << int(ceil(log2(size) / 2.0));
        clusters = vector<VanEmdeBoasTree*>(cluster_size, nullptr);
    }
}

VanEmdeBoasTree::~VanEmdeBoasTree() {
    for (auto ptr : clusters) delete ptr;
    delete summary;
}

/* All ordered dictionary operations */

int VanEmdeBoasTree::min() { return minimum; }

int VanEmdeBoasTree::max() { return maximum; }

bool VanEmdeBoasTree::isEmpty() { return minimum == -1; }

void VanEmdeBoasTree::insert(int x) {
    if (minimum == -1) emptyInsert(x);
    else {
        if (x < minimum) swap(x, minimum);
        if (universe_size > 2) {
            int h = high(x), l = low(x);

            if (clusters[h] == nullptr) clusters[h] = new VanEmdeBoasTree(cluster_size);

            if (clusters[h]->min() == -1) {
                if (!summary) summary = new VanEmdeBoasTree(cluster_size);
                summary->insert(h);
                clusters[h]->emptyInsert(l);
            } 
            else clusters[h]->insert(l);
        }
        if (x > maximum) maximum = x;
    }
}

void VanEmdeBoasTree::remove(int x) {
    if (minimum == maximum) minimum = maximum = -1;
    else if (universe_size == 2) minimum = maximum = (x == 0) ? 1 : 0;
    else {
        if (x == minimum) {
            int first_cluster = summary ? summary->min() : -1;
            if (first_cluster == -1) {
                minimum = maximum;
                return;
            }
            x = generateIndex(first_cluster, clusters[first_cluster]->min());
            minimum = x;
        }
        int h = high(x), l = low(x);
        if (clusters[h]) clusters[h]->remove(l);
        if (clusters[h] && clusters[h]->min() == -1) {
            summary->remove(h);
            if (x == maximum) {
                int summary_max = summary->max();
                if (summary_max == -1) maximum = minimum;
                else maximum = generateIndex(summary_max, clusters[summary_max]->max());
            }
        } 
        else if (x == maximum) maximum = generateIndex(h, clusters[h]->max());
    }
}

bool VanEmdeBoasTree::isMember(int x) {
    if (x == minimum || x == maximum) return true;
    if (universe_size <= 2) return false;
    int h = high(x), l = low(x);
    return clusters[h] && clusters[h]->isMember(l);
}

int VanEmdeBoasTree::successor(int x) {
    if (universe_size == 2) {
        if (x == 0 && maximum == 1) return 1;
        return -1;
    }
    if (minimum != -1 && x < minimum) return minimum;

    int h = high(x), l = low(x);
    int maxLow = clusters[h] ? clusters[h]->max() : -1;
    if (maxLow != -1 && l < maxLow) {
        int offset = clusters[h]->successor(l);
        return generateIndex(h, offset);
    }
    int succCluster = summary ? summary->successor(h) : -1;
    if (succCluster == -1) return -1;
    int offset = clusters[succCluster]->min();
    return generateIndex(succCluster, offset);
}

int VanEmdeBoasTree::predecessor(int x) {
    if (universe_size == 2) {
        if (x == 1 && minimum == 0) return 0;
        return -1;
    }
    if (maximum != -1 && x > maximum) return maximum;

    int h = high(x), l = low(x);
    int minLow = clusters[h] ? clusters[h]->min() : -1;
    if (minLow != -1 && l > minLow) {
        int offset = clusters[h]->predecessor(l);
        return generateIndex(h, offset);
    }
    int predCluster = summary ? summary->predecessor(h) : -1;
    if (predCluster == -1) return (minimum != -1 && x > minimum) ? minimum : -1;
    int offset = clusters[predCluster]->max();
    return generateIndex(predCluster, offset);
}

/* Helper functions */

int VanEmdeBoasTree::high(int x) {
    int half = log2(universe_size) / 2;
    return x >> half;
}

int VanEmdeBoasTree::low(int x) {
    int half = log2(universe_size) / 2;
    return x & ((1 << half) - 1);
}

int VanEmdeBoasTree::generateIndex(int x, int y) {
    int half = log2(universe_size) / 2;
    return (x << half) | y;
}

void VanEmdeBoasTree::emptyInsert(int x) {
    minimum = maximum = x;
}