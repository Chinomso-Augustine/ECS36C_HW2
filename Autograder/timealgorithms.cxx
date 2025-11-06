#include <iostream>
#include <fstream>
#include "json.hpp" //For loading json file
#include <vector>
#include <ctime>

// Importing the three sorting files we will be running
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"

using namespace std;         // Avoids using std everytime
using json = nlohmann::json; // allows access to nlohmann just by calling json

// Accessing the variable counters declared in each of the sorting 
extern long long numComparisonsInsertion;
extern long long numMemAccessesInsertion;


extern long long numComparisonsMergesort;
extern long long numMemAccessesMergesort;


extern long long numComparisonsQuicksort;
extern long long numMemAccessesQuicksort;



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

    else
    {
        json data;         // Declaring a json data type that will store the file data
        inputFile >> data; // Pushing or reading file inputs into data
        inputFile.close(); // Closing the file once we are done reading it

        for (auto items = data.begin(); items != data.end(); ++items)
        { // start from the beginning and don't stop until we reach the end of data
                string key = items.key();   // holds json keys like sample1, sample2,...
                // skipping metadata because it is not a list of numbers 
                if (key == "metadata")
                {
                    continue; // move to the next key value pair
                }
                vector<int> jsonArrays = items.value().get<vector<int>>(); // stores values as a vector

                // Making sure that all 3 of these sorting algorithms are sorting the exact same data
                vector<int> inserstionArray = jsonArrays; 
                vector<int> mergeSortArray = jsonArrays;
                vector<int> quicksortArrays = jsonArrays;

                int totArraySize = jsonArrays.size(); // Gathering the total array size

                // 3: For each sample, run insertionSort, mergeSort, and quickSort
                
                // Insertion Sort
                numComparisonsInsertion = 0;
                numMemAccessesInsertion = 0; 
                clock_t start = clock(); // Starting the timer
                InsertionSort(&jsonArrays);  // Running insertion sort
                clock_t end = clock(); // Ending the timer
                double InsertTime = double(end - start) / CLOCKS_PER_SEC; // Getting the time in seconds

                long long insertCompares = numComparisonsInsertion;
                long long insertAccesses = numMemAccessesInsertion;

                cout << key << ",InsertionSort," << totArraySize << "," << InsertTime << endl; // Printing the insertion sort output in csv format.
                
             
                numComparisonsQuicksort = 0;
                numMemAccessesQuicksort = 0;

                start = clock(); // Starting the timer
                QuickSort(&jsonArrays);  // Running Quick sort
                end = clock(); // Ending the timer
                double QuickTime = double(end - start) / CLOCKS_PER_SEC; // Getting the time in seconds

                long long quickCompares = numComparisonsQuicksort;
                long long quickAccesses = numMemAccessesQuicksort;

                cout << key << ",QuickSort," << totArraySize << "," << QuickTime << endl; // Printing the quick sort output in csv format.
                
               

                numComparisonsMergesort = 0;
                numMemAccessesMergesort = 0;
                start = clock(); // Starting the timer
                MergeSort(&jsonArrays);  // Running merge sort
                end = clock(); // Ending the timer
                double MergeTime = double(end - start) / CLOCKS_PER_SEC; // Getting the time in seconds

                long long mergeCompares = numComparisonsMergesort;
                long long mergeAccesses = numMemAccessesMergesort;

            cout<<endl; 
            cout<< key << ",MergeSort," << totArraySize << "," << MergeTime << endl; // Printing the merge sort output in csv format.
                
            cout << key << ","; 
            cout<< InsertTime << "," << insertCompares << "," << insertAccesses <<","<<endl;
            cout<< MergeTime << "," << mergeCompares << "," << mergeAccesses << ","<<endl;
            cout<< QuickTime << "," << quickCompares << "," << quickAccesses <<endl; 
            cout<<endl; 
            
            }
            
        }
        return 0;
    }