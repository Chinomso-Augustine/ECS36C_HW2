// Declaring the necessary libraries we will be using in this second executable
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json; // Created a name for efficiency for the json file we will be using.

// Making sure that the user provided the correct number of file names (2)

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cerr << "Incorrect usage, provide exactly two JSON files to work with." << std::endl;
        return 1;
    }
    // Storing both of these json files into variables to easily use later on
    string firstFile = argv[1];
    string secondFile = argv[2];

    // Reading the first json file and making sure that it exists.
    ifstream file1(firstFile);
    ifstream file2(secondFile);

    if (!file1.is_open() || !file2.is_open())
    {
        cerr << " File cannot be opened" << endl;
        return 1;
    }
        json file1Contents, file2Contents; // Holding the parsed json file from file1Contents
        file1 >> file1Contents;            // Parsing through the first json file into file1
        file2 >> file2Contents;            // Parsing through the second json file2

        file1.close(); // Closing the first file
        file2.close(); // Closing the second file.

        json outputs_to_json;    // Storing all of the outputs of both files together in one json.
        int totalmismatches = 0; // Keeping count of the total number of mismatches between both json files

        // Gathering metadata from both of the json files
        // json metadatagroup1 = file1Contents["metadata"];
        // json metadatagroup2 = file2Contents["metadata"];

        // Creating the metadata section for both of the json files

        outputs_to_json["metadata"]["File1"]["name"] = firstFile;                                     // Storing the first filename
        outputs_to_json["metadata"]["File1"]["arraySize"] = file1Contents["metadata"]["arraySize"];   // Storing the array size for the first file
        outputs_to_json["metadata"]["File1"]["numSamples"] = file1Contents["metadata"]["numSamples"]; // Storing the number of samples for the first file

        outputs_to_json["metadata"]["File2"]["name"] = secondFile;                                    // Storing the second filename
        outputs_to_json["metadata"]["File2"]["arraySize"] = file2Contents["metadata"]["arraySize"];   // Storing the array size for the second file
        outputs_to_json["metadata"]["File2"]["numSamples"] = file2Contents["metadata"]["numSamples"]; // Storing the number of samples for the second file

        // Gathering the total number of samples in both files
        int totalNumSamples = file1Contents["metadata"]["numSamples"].get<int>();
        // int newArraySize = metadatagroup1["arraySize"]; // Figuring out total number of values in the array

        for (int sampVal = 1; sampVal <= totalNumSamples; sampVal++)
        { // Loops through each sample in both Json files.

            ostringstream ss;
            ss << "Sample" << setw(2) << setfill('0') << sampVal;
            string SampName = ss.str();

            if (!file1Contents.count(SampName) || !file2Contents.count(SampName))
            {
                cerr << "Warning: " << SampName << " missing in one of the files." << endl;
                continue;
            }

            json firstFileArray = file1Contents[SampName];  // Creating array for first file/accessing data from first file.
            json secondFileArray = file2Contents[SampName]; // Creating array for second file/accessing data from second file.

            bool anyMismatch = false; // Tells us if there are any mismatches between the output samples in each of the json files.
            json mismatchList;        // Storing the positions of the mismatches between the output samples

            size_t minSize = min(firstFileArray.size(), secondFileArray.size());

            for (size_t pos = 0; pos < minSize; pos++)
            { // Comparing each number in the arrays
                // int numFirstFile = firstFileArray[pos].get<int>();   // Getting value at position from first json file
                // int numSecondFile = secondFileArray[pos].get<int>(); // Getting value at position from second json file

                if (firstFileArray[pos] != secondFileArray[pos])
                {
                    mismatchList[to_string(pos)] = {firstFileArray[pos], secondFileArray[pos]};
                    anyMismatch = true;
                }
            }

            if (firstFileArray.size() != secondFileArray.size())
            {
                anyMismatch = true;
            }

            if (anyMismatch)
            { // Looping through the key/value pairs to see the mismatches between the samples in each of the files
                totalmismatches++;
                outputs_to_json[SampName]["File1"] = firstFileArray;    // Updates the new section of the JSON file in the "Sample1" - adds another key under file1.json
                outputs_to_json[SampName]["File2"] = secondFileArray;   // Updates the new sectioction of the JSON file in the "Sample2" - adds another key under file2.json
                outputs_to_json[SampName]["Mismatches"] = mismatchList; // Collecting all of the possible mismatches between both of the samples of data from both files
            }
        }

        outputs_to_json["metadata"]["samplesWithConflictingResults"] = totalmismatches;
        cout << outputs_to_json.dump(4) << endl; // Printing the format of the new updated JSON in an easy to read format. .dump() is from the nlohmann json library
        return 0;
    }
    
