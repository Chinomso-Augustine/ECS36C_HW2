#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <iomanip>
#include <algorithm>

#include "json.hpp" //For loading json file
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"

using namespace std;         // Avoids using std everytime
using json = nlohmann::json; // allows access to nlohmann just by calling json

// Accessing the variable counters declared in each of the sorting
extern int numComparisonsInsertion;
extern int numMemAccessesInsertion;

extern int numComparisonsMergesort;
extern int numMemAccessesMergesort;

extern int numComparisonsQuicksort;
extern int numMemAccessesQuicksort;

int main(int argc, char **argv)
{
    // Program outline

    // 1 and 2: read json file and Looping though all sample in jason file

    // Assuming json file is not provided, we send an error
    if (argc != 2)
    {
        cerr << "Incorrect input. You either provided no file or more than one. Please provide one json file" << endl;
        return 1;
    }

    string jsonFile = argv[1]; // getting jsonFile from command line and storing it into a string variable

    ifstream inputFile(jsonFile); // Reading jsonFile
    if (!inputFile.is_open())
    { // If file is not open print not open and stop. This is for file validation
        cout << "File did not open";
        return 1;
    }

    json data; // Declaring a json data type that will store the file data
    try
    {
        inputFile >> data; // Pushing or reading file inputs into data
    }
    catch (const json::parse_error &e)
    {
        cerr << "There is a problem with your JSON parsing: " << e.what() << endl;
        return 1;
    }
    inputFile.close(); // Closing the file once we are done reading it

    cout.precision(6);
    // Print CSV header exactly as autograder expect
    cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,"
         << "MergeSortTime,MergeSortCompares,MergeSortMemaccess,"
         << "QuickSortTime,QuickSortCompares,QuickSortMemaccess\n"; // ✅ Added newline after header

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        string sampleName = it.key();

        if (sampleName == "metadata")
            continue;

        vector<int> jsonArrays;
        try
        {
            jsonArrays = it.value().get<vector<int>>();
        }
        catch (const json::exception &e)
        {
            cerr << "There was an error reading the sample " << sampleName << ": " << e.what() << " (Expected array of numbers)." << endl;
            continue;
        }

        // Making sure that all 3 of these sorting algorithms are sorting the exact same data
        vector<int> insertionArray = jsonArrays;
        vector<int> mergesortArray = jsonArrays;
        vector<int> quicksortArray = jsonArrays;

        // Insertion Sort
        numComparisonsInsertion = 0;
        numMemAccessesInsertion = 0;
        clock_t start = clock();
        InsertionSort(&insertionArray);
        clock_t end = clock();
        double insertionTime = double(end - start) / CLOCKS_PER_SEC;

        // Merge Sort
        numComparisonsMergesort = 0;
        numMemAccessesMergesort = 0;
        start = clock();                                         // Starting the timer
        MergeSort(&mergesortArray);                              // Running merge sort
        end = clock();                                           // Ending the timer
        double mergeTime = double(end - start) / CLOCKS_PER_SEC; // Getting the time in seconds

        // Quick Sort
        numComparisonsQuicksort = 0;
        numMemAccessesQuicksort = 0;
        start = clock();                                         // Starting the timer
        QuickSort(&quicksortArray);                              // Running Quick sort
        end = clock();                                           // Ending the timer
        double quickTime = double(end - start) / CLOCKS_PER_SEC; // Getting the time in seconds

        // ✅ Use '\n' instead of endl to avoid extra blank lines
        cout << sampleName << ","
             << insertionTime << "," << numComparisonsInsertion << "," << numMemAccessesInsertion << ","
             << mergeTime << "," << numComparisonsMergesort << "," << numMemAccessesMergesort << ","
             << quickTime << "," << numComparisonsQuicksort << "," << numMemAccessesQuicksort << '\n';
    }
    return 0;
}
