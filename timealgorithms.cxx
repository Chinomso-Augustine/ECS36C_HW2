#include <iostream> // Used for the input and output stream 
#include <fstream> // This is used for the input and output files
#include <vector> // This is here so we can use the vector data structure
#include <ctime> // Used to gather the time where use case is getting the time in seconds
#include <string> // Allows us to use the string library
#include <algorithm> // Gives access to already pre-written general algorithms

#include "json.hpp" //For loading json file
#include "insertionsort.h" // Loading the insertion sort header file
#include "mergesort.h" // Loading the mergesort header file
#include "quicksort.h" // Loading the quicksort header file

using namespace std;  // Avoids using std everytime and uses standard namespace
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
    // Assuming json files are not provided, we send an error
    if (argc != 2)
    {
        cerr << "Incorrect input. You either provided no file or more than one. Please provide one json file" << endl;
        return 1;
    }

    string jsonFile = argv[1]; // getting jsonFile from command line and storing it into a string variable

    ifstream inputFile(jsonFile); // Reading the input jsonFile
    if (!inputFile.is_open()) // Checking if the input file is not open
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
        cerr << "There is a problem with your JSON parsing: " << e.what() << endl; // throwing an error for any possibe invalid json format there could be.
        return 1;
    }
    inputFile.close(); // Closing the file once we are done reading it

    // Printing CSV header exactly as the autograder expects
    cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,"
         << "MergeSortTime,MergeSortCompares,MergeSortMemaccess,"
         << "QuickSortTime,QuickSortCompares,QuickSortMemaccess\n"; 

    for (auto it = data.begin(); it != data.end(); ++it) // Same logic as the sortedverification.cxx: start from the beginning and don't stop until we reach the end of data
    {
        string sampleName = it.key(); // Getting the string key value from the sample Name

        if (sampleName == "metadata") // Skipping if the sample data ends up being metadata
            continue;

        vector<int> jsonArrays; // Making the json array a vector that stores integers
        try
        {
            jsonArrays = it.value().get<vector<int>>(); // Iterates over the top level json object which is the JSON value current key 
        }
        catch (const json::exception &e) // Catches the error if the JSON isn't the expected type
        {
            cerr << "There was an error reading the sample " << sampleName << ": " << e.what() << " (Expected array of numbers)." << endl; // Throws an error
            continue;
        }

        // Making sure that all 3 of these sorting algorithms are sorting the exact same data and are dynamically allocated as arrays of integers.
        vector<int> insertionArray = jsonArrays;
        vector<int> mergesortArray = jsonArrays;
        vector<int> quicksortArray = jsonArrays;

        // Insertion Sort
        numComparisonsInsertion = 0; // Resetting the count for the number of comparisons in the insertion sort algorithm
        numMemAccessesInsertion = 0; // Resetting the count for the number of memory accesses in the insertion sort algorithm 
        clock_t start = clock(); // starts the clock
        InsertionSort(&insertionArray); // Calls and runs the Insertion Sort Function on the data
        clock_t end = clock(); // Ends the timing
        double insertionTime = double(end - start) / CLOCKS_PER_SEC; // Gets the time in seconds

        // Merge Sort
        numComparisonsMergesort = 0; // Resetting the count for the number of comparisons in the merge sort algorithm
        numMemAccessesMergesort = 0; // Resetting the count for the number of memory accesses in the merge sort algorithm
        start = clock(); // Starting the timer
        MergeSort(&mergesortArray); // Running merge sort
        end = clock(); // Ending the timer
        double mergeTime = double(end - start) / CLOCKS_PER_SEC; // Getting the time in seconds

        // Quick Sort
        numComparisonsQuicksort = 0; // Resetting the count for the number of Comparisons in the quick sort algorithm
        numMemAccessesQuicksort = 0; // Resetting the count for the number of memoryAccesses in the quicksort algorithm
        start = clock(); // Starting the timer
        QuickSort(&quicksortArray); // Running Quick sort
        end = clock(); // Ending the timer
        double quickTime = double(end - start) / CLOCKS_PER_SEC; // Getting the time per second

        cout << sampleName << ","
             << insertionTime << "," << numComparisonsInsertion << "," << numMemAccessesInsertion << ","
             << mergeTime << "," << numComparisonsMergesort << "," << numMemAccessesMergesort << ","
             << quickTime << "," << numComparisonsQuicksort << "," << numMemAccessesQuicksort << '\n'; // For each test sample it is printing onr row of results in CSV format
    }
    return 0;
}
