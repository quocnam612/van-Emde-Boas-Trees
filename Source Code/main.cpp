#include "DMCache.h"
#include "BST.h"
#include "HashTable.h"
#include "vEBTree.h"
#include "H-HashTable.h"
#include "Y-fastTrie.h"
#include "HelperFunctions.h"

const string INPUT_PATH = "Data/input.txt"; // Input the initial data
const string OUTPUT_PATH = "Data/output.txt"; // Output the stats of the operations
const vector<int> SIZE_POWER = {9, 12, 14, 16, 20, 23}; // size will be 2^SIZE_POWER[i], compatible with input, DO NOT CHANGE THIS
const int SEED = 69; // Seed for random number generation in testing

int main() {
/*      All of the data struct avaiable in this project [Copy - Paste]:
    DirectMappedCache
    BinarySearchTree
    HashTable
    VanEmdeBoasTree
    HierarchicalHashTable
    YFastTrie
*/

    srand(SEED); // Seed the random number generator
    debug<HierarchicalHashTable>(); // Cout the specific operations of a data structure
    benchMark<HierarchicalHashTable>(INPUT_PATH, OUTPUT_PATH, SIZE_POWER);

    return 0;
}   