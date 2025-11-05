#include <iostream>
#include <fstream>
#include "json.hpp" //For loading json file
#include <vector>

// Importing the three sorting files we will be running
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"

using namespace std;         // Avoids using std everytime
using json = nlohmann::json; // allows access to nlohmann just by calling json

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

    string jsonFile = argv[1]; // getting jsonFile from command line

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

        for (auto items = data.begin(); items != data.end(); ++items)
        { // start from the beginning and don't stop until we reach the end of data
            {
                string key = items.key();   // holds json keys like sample1, sample2,...
                vector<int> jsonArrays = items.value().get<vector<int>>(); // stores values as a vector

                // skipping metadata because it is not an array
                if (key == "metadata")
                {
                    continue; // move to the next key value pair
                }
                InsertionSort(&jsonArrays); 

                // 3: For each sample, run insertionSort, mergeSort, and quickSort

                // 4: store all result in a variable

                // 5: Print result in cvs format
            }
        }
    }
}