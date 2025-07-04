#include <fstream>
#include <iostream>
#include <chrono>
#include <utility>
#include <vector>
#include <iomanip>
using namespace std;

template <typename Func, typename... Args>
double measureExecutionTime(Func func, Args&&... args) { // Measure the execution time of a function in ms
    auto start = chrono::high_resolution_clock::now();
    func(forward<Args>(args)...);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    return duration.count() / 1000.0;
}

template <typename T>
void benchMark(const string& pathInput, const string& pathOutput, vector<int> powers) {
    ifstream inputFile(pathInput);
    ofstream outputFile(pathOutput, ios::app);
    vector<int> inputData, operationData, sizes;
    double tmpTime = -1.0;
    int tmpInt;
    
    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error opening files!" << endl;
        return;
    }

    for (int power : powers) sizes.push_back(1 << power); // 2^power

    // Read input and operation data
    while (inputFile >> tmpInt) inputData.push_back(tmpInt);
    for (int i = 0; i < sizes.size(); i++) { // Generate random operation that meet the conditions
        int start = (i == 0) ? 0 : sizes[i - 1];
        for (int j = start; j < sizes[i]; j++) {
            int min = (i == 0) ? 0 : sizes[i - 1];
            int max = sizes[i] - 1;
            operationData.push_back(rand() % (max - min + 1) + min); // Random number in the range [min, max]
        }
    }

    outputFile << typeid(T).name() << "...\n" << left << setw(15) << "Size" << fixed << setprecision(0)
            << setw(15) << "insert()" << setw(15) << "remove()" << setw(15) << "isMember()" 
            << setw(15) << "min()" << setw(15) << "max()" << setw(15) << "successor()"
            << setw(15) << "predecessor()" << endl;

    // Test for each size
    for (int size : sizes) {
        // Insert initial data - not measured
        T structure(size);
        for (int i = 0; i < size / 2; i++) structure.insert(inputData[i]);
        outputFile << left << "2^" << setw(15) << log2(size);

        // Measure insert time
        tmpTime = measureExecutionTime([&structure, &operationData, size]() {
            for (int i = 0; i < size; i++) structure.insert(operationData[i]);
        });
        outputFile << setw(15) << tmpTime;

        // Measure remove time
        tmpTime = measureExecutionTime([&structure, &operationData, size]() {
            for (int i = 0; i < size; i++) structure.remove(operationData[i]);
        });
        outputFile << setw(15) << tmpTime;

        // Measure isMember time
        tmpTime = measureExecutionTime([&structure, &operationData, size]() {
            for (int i = 0; i < size; i++) structure.isMember(operationData[i]);
        });
        outputFile << setw(15) << tmpTime;

        // Measure min time
        tmpTime = measureExecutionTime([&structure]() {
            structure.min();
        });
        outputFile << setw(15) << tmpTime;

        // Measure max time
        tmpTime = measureExecutionTime([&structure]() {
            structure.max();
        });
        outputFile << setw(15) << tmpTime;

        // Measure successor time
        tmpTime = measureExecutionTime([&structure, &operationData, size]() {
            for (int i = 0; i < size; i++) structure.successor(operationData[i]);
        });
        outputFile << setw(15) << tmpTime;

        // Measure predecessor time
        tmpTime = measureExecutionTime([&structure, &operationData, size]() {
            for (int i = 0; i < size; i++) structure.predecessor(operationData[i]);
        });
        outputFile << setw(15) << tmpTime;

        outputFile << endl;
    }
    outputFile << endl;
}

template <typename T>
void debug() {
    vector<int> sizes = {3, 2, 6, 1, 7, 5, 10, 9, 8, 5}; // Example sizes for debugging
    T structure(16);
    
    cout << "Debugging " << typeid(T).name() << "..." << endl;
    for (int size : sizes) {
        structure.insert(size);
        cout << "Inserted: " << size << endl;
    }
    cout << "Min: " << structure.min() << endl;
    cout << "Max: " << structure.max() << endl;
    cout << "Is member 2? " << (structure.isMember(2) ? "Yes" : "No") << endl;
    structure.remove(2);
    cout << "Removed 2." << endl;
    cout << "Is member 2? " << (structure.isMember(2) ? "Yes" : "No") << endl;
    cout << "Successor of 5: " << structure.successor(5) << endl;
    cout << "Predecessor of 5: " << structure.predecessor(5) << endl;
}