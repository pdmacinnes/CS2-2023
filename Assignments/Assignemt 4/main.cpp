#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "bSearchTree.h"

using namespace std;
using namespace chrono;

// Function to generate random numbers
int generateRandomNumber(int lower, int upper, int seed) 
{
    mt19937 rng(seed);
    uniform_int_distribution<int> distribution(lower, upper);
    return distribution(rng);
}

int main(int argc, char **argv) 
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <output_file_name>" << endl;
        return 1;
    }

    ofstream outFile(argv[1]);

    if (!outFile) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    const int lowerBound = 1000001;
    const int upperBound = 9000000;
    const int dataSize = 100000;

    int seed = 6642; // Use the last 4 digits of your 700 number as seed
    bSearchTreeType<int> myTree;

    // Load tree with data
    for (int i = 0; i < dataSize; ++i) 
    {
        int randNum = generateRandomNumber(lowerBound, upperBound, seed);
        myTree.insert(randNum);
    }

    // Output data in order to a data file
    outFile << "Data in order:" << endl;
    myTree.inorderTraversal();
    outFile << endl;

    // Test all 11 functions
    auto start = high_resolution_clock::now();

    // Test operations and output results to outFile

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    // Output runtime to the file
    outFile << "Runtime: " << duration.count() << " nanoseconds" << endl;

    outFile.close();

    return 0;
}
