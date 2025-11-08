#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <iomanip>
#include <algorithm>
#include "json.hpp" // for loading and parsing json file
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"

using namespace std;         // avoids using std:: prefix every time
using json = nlohmann::json; // allows access to nlohmann by calling json

// accessing the variable counters declared in each sorting file
extern int numComparisonsInsertion;
extern int numMemAccessesInsertion;

extern int numComparisonsMergesort;
extern int numMemAccessesMergesort;

extern int numComparisonsQuicksort;
extern int numMemAccessesQuicksort;

int main(int argc, char **argv)
{
    // program outline:
    // 1. read json file input
    // 2. loop through all samples in the json file
    // 3. run insertion, merge, and quick sort on each sample
    // 4. record comparisons, memory accesses, and time for each sort

    if (argc != 2) // ensures exactly one file is provided
    {
        cerr << "Incorrect input. You either provided no file or more than one. Please provide one json file" << endl;
        return 1; // exits if incorrect number of arguments
    }

    string jsonFile = argv[1]; // stores json filename from command line

    ifstream inputFile(jsonFile); // open file for reading
    if (!inputFile.is_open())     // check if file opened successfully
    {
        cout << "File did not open"; // print error message
        return 1; // exit program
    }

    json data; // variable to store parsed json data

    try
    {
        inputFile >> data; // read and parse json contents into 'data'
    }
    catch (const json::parse_error &e) // catch invalid json format
    {
        cerr << "There is a problem with your JSON parsing: " << e.what() << endl;
        return 1; // exit if invalid json format
    }

    inputFile.close(); // close file after reading

    cout.precision(6); // set decimal precision for time values

    // print csv header exactly as autograder expects
    cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,"
         << "MergeSortTime,MergeSortCompares,MergeSortMemaccess,"
         << "QuickSortTime,QuickSortCompares,QuickSortMemaccess\n";

    // loop through every sample in json file
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        string sampleName = it.key(); // get current sample key

        if (sampleName == "metadata") // skip metadata section
            continue;

        vector<int> jsonArrays = it.value().get<vector<int>>(); // extracting sample array

        //Saving arrays for each sorting algorithm in there variables
        vector<int> insertionArray = jsonArrays;
        vector<int> mergesortArray = jsonArrays;
        vector<int> quicksortArray = jsonArrays;

        // Insertion Sort
        numComparisonsInsertion = 0; // reset comparison counter
        numMemAccessesInsertion = 0; //reset mem access counter
        clock_t start = clock(); // start timer
        InsertionSort(&insertionArray);
        clock_t end = clock();                                       // end timer
        double insertionTime = double(end - start) / CLOCKS_PER_SEC; // calculate time in seconds

        // Merge Sort
        numComparisonsMergesort = 0;                             // reset comparison counter
        numMemAccessesMergesort = 0;                             // resetting memory accesss counter
        start = clock();                                         // start timer
        MergeSort(&mergesortArray);                              // run merge sort
        end = clock();                                           // end timer
        double mergeTime = double(end - start) / CLOCKS_PER_SEC; // time in seconds

        //  Quick Sort
        numComparisonsQuicksort = 0;                             // resetting comparison counter
        numMemAccessesQuicksort = 0;                             // resetting memory access counter
        start = clock();                                         // start timer
        QuickSort(&quicksortArray);                              // run quick sort
        end = clock();                                           // end timer
        double quickTime = double(end - start) / CLOCKS_PER_SEC; // time in seconds

        // print sample results in CSV format
        cout << sampleName << ","
             << insertionTime << "," << numComparisonsInsertion << "," << numMemAccessesInsertion << ","
             << mergeTime << "," << numComparisonsMergesort << "," << numMemAccessesMergesort << ","
             << quickTime << "," << numComparisonsQuicksort << "," << numMemAccessesQuicksort << '\n';
    }

    return 0; // end of program
}
