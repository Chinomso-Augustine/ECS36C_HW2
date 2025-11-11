#include <iostream>
#include <fstream>
#include <algorithm>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// function that reads json file

json readMyJsonFile(const string &fileToRead)
{
    ifstream file(fileToRead); // reading fileToRead into file

    // Checking if file is openable. if it's not report that it could not be open
    if (!file.is_open())
    {
        cerr << "File could not open" << endl;
        exit(1);
    }

    json data;    // Declaring json variale to hold file data
    file >> data; // store or push file info into data variable
    return data;  // return data
}

int main(int argc, char *argv[])
{

    // Ensure user provided two file names
    if (argc != 3)
    {
        cerr << "Please use two files" << endl;
        return 1;
    }

    json result;             // stores results
    int conflictCounter = 0; // Keeps tracks of how many counter we have

    json file1 = readMyJsonFile(argv[1]); // passing file1 info as jason
    json file2 = readMyJsonFile(argv[2]); // passing file2 info as json

    // looping throw the files
    for (auto items = file1.begin(); items != file1.end(); ++items)
    {
        string sampleName = items.key();
        if (sampleName == "metadata")
        {
            continue;
        }

        if (!file2.count(sampleName))
        {
            cerr << "Warning: missing sample name from second file.\n";
            continue;
        }
        auto &array1 = items.value();     // Getting the array from file1
        auto &array2 = file2[sampleName]; // Getting the matching array from fil

        json mismatches;            // Json that will record mismatches
        bool hasMismatches = false; // Assume there are no mismatches rn

        int minSize = min(array1.size(), array2.size());

        for (int i = 0; i < minSize; i++)
        {
            // We know there is mismatch if i in array 1 is != i in array2
            if (array1[i] != array2[i])
            {
                hasMismatches = true; // confirm that we have a mismatch

                mismatches[to_string(i)] = {array1[i], array2[i]}; // storing mismatch indexs
            }
        }

        if (array1.size() != array2.size())
        {
            hasMismatches = true;
            mismatches["lengthMismatch"] = {array1.size(), array2.size()};
        }

        if (hasMismatches)
        {
            conflictCounter++;
            result[sampleName]["File1"] = array1;
            result[sampleName]["File2"] = array2;
            result[sampleName]["Mismatches"] = mismatches;
        }
    }
    // metadata block
    if (file1.count("metadata"))
    {
        result["metadata"]["File1"]["name"] = argv[1];
        result["metadata"]["File1"]["numSamples"] = file1["metadata"]["numSamples"];
        result["metadata"]["File1"]["arraySize"] = file1["metadata"]["arraySize"];
    }

    if (file2.count("metadata"))
    {
        result["metadata"]["File2"]["name"] = argv[2];
        result["metadata"]["File2"]["numSamples"] = file2["metadata"]["numSamples"];
        result["metadata"]["File2"]["arraySize"] = file2["metadata"]["arraySize"];
    }

    result["metadata"]["samplesWithConflictingResults"] = conflictCounter;
    cout << result.dump(4) << endl;

    return 0;
}