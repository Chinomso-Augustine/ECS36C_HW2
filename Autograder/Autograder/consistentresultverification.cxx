// consistentresultverification.cxx
// Author: Chinomso Augustine
// Purpose: Compare two JSON files containing sorted samples and report any mismatches.
#include <iostream>
#include <fstream>
#include <algorithm>
#include "json.hpp"

using json = nlohmann::json; //Created a name for efficiency for the json file we will be using. 
using namespace std; //This avoids using std everytime 

// Function to read and parse a JSON file
json readMyJsonFile(const string &fileToRead)
{
    ifstream file(fileToRead); // Create an input file stream to open the JSON file for reading

    // Check if the file can be opened successfully
    if (!file.is_open())
    {
        cerr << "Error: Cannot open file " << fileToRead << endl; // Print error message if unable to open file
        exit(1); // Exit program with error code 1
    }

    json data; // Create a JSON object to store the parsed data
    
    try
    {
        file >> data; //push file contents into the JSON object
    }
    catch (const exception &e)
    {
        cerr << "Error: Invalid JSON format in " << fileToRead << endl; // Catch parsing errors
        exit(1); // Exit if file format is invalid
    }

    file.close(); // Close the file after reading
    return data;  // Return the parsed JSON data
}

int main(int argc, char *argv[])
{
    // checking that two JSON filenames are provided as command in the command line
    if (argc != 3)
    {
        cerr <<"Either file is more or less than 2. Please provide only 2 json files"<< endl;
        return 1; // Exit if the number of files are incorrect
    }

    string file1Name = argv[1]; // Store first filename
    string file2Name = argv[2]; // Store second filename

    json result; // JSON object to store the final comparison results
    int conflictCounter = 0;  // Counter to keep track of the number of mismatched samples we found

    // Reading both input JSON files using readMyJsonFile created. 
    json file1 = readMyJsonFile(file1Name); //file one 
    json file2 = readMyJsonFile(file2Name);//file 2

    // Loop through all key-value pairs in the first JSON file
    for (auto items = file1.begin(); items != file1.end(); ++items)
    {
        string sampleName = items.key(); // Extract the current sample's key name

        // Skipping metadata section since it's not part of the data comparison. But it will be use later
        if (sampleName == "metadata")
            continue; //Move on

        // checking If the second file does not contain the same sample
        if (!file2.count(sampleName))
        {
            conflictCounter++; // Increment conflict count
            result[sampleName]["Mismatches"]["missing"] = "Sample missing from second file"; // Record missing info
            continue; // Skip the rest of the checks
        }

        // Retrieving the array from both files
        auto &array1 = items.value(); //Obtains array1 values 
        auto &array2 = file2[sampleName]; //Array2 sample 

        json mismatches;  // JSON object to store mismatched indices and values
        bool hasMismatches = false; // Assuming we do not have a mismatches at the moment
        int minSize = min(array1.size(), array2.size()); // Use smaller size to avoid out-of-bounds errors which could cause segfault

        // Compare the elements from both arrays
        for (int i = 0; i < minSize; i++)
        {
            if (array1[i] != array2[i]) // This checks for mismatches 
            {
                hasMismatches = true; //Onces above condition is true, now we have a mismatch
                mismatches[to_string(i)] = {array1[i], array2[i]}; // Record mismatched elements with their indices
            }
        }

        // Recording size differences If one array is longer than the other.
        if (array1.size() != array2.size())
        {
            hasMismatches = true; //Another mistmatche detected
            mismatches["lengthMismatch"] = {array1.size(), array2.size()}; //Saves the differences of both array
        }

        // If mismatches were found, store the full arrays and mismatches under this sample
        if (hasMismatches)
        {
            conflictCounter++; // Increment conflict count
            result[sampleName][file1Name] = array1; // Storing sample data from first file
            result[sampleName][file2Name] = array2; // Storing sample data from second file
            result[sampleName]["Mismatches"] = mismatches; // Storing mismatch information
        }
    }

    // Include metadata information for the first file if there is one
    if (file1.count("metadata")) //checking for "metadata"
    {
        result["metadata"]["File1"]["name"] = file1Name; //Storing first file name
        result["metadata"]["File1"]["numSamples"] = file1["metadata"]["numSamples"]; //storing first file numSample
        result["metadata"]["File1"]["arraySize"] = file1["metadata"]["arraySize"]; //Storing first file arraysize
    }

    // metadata info for the second file 
    if (file2.count("metadata")) //checking for metadata
    {
        result["metadata"]["File2"]["name"] = file2Name; //Storing second file name
        result["metadata"]["File2"]["numSamples"] = file2["metadata"]["numSamples"]; //storing file 2 numSamples
        result["metadata"]["File2"]["arraySize"] = file2["metadata"]["arraySize"]; //storing file 2 arraysize 
    }

    // Adding total number of conflicting samples to the metadata section
    result["metadata"]["samplesWithConflictingResults"] = conflictCounter;

    // Printing the final result in easy and readable json format
    cout << result.dump(4) << endl;

    return 0; // indicates that program ran successfully
}