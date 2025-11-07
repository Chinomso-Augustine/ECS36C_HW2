// Declaring the necessary libraries we will be using in this second executable
#include <iostream>// for input and output stream
#include <fstream> // this is for the file input and output
#include <vector> // this is so we can use the vector data structure
#include <string> // allows us to use the string library
#include <iomanip> // allows us to manipulate data that is displayed in the console
#include "json.hpp" // this allows us to use the JSON library

using namespace std; // using the standard namespace
using json = nlohmann::json; // Created a name for efficiency for the json file we will be using.

// Making sure that the user provided the correct number of file names (2)

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cerr << "Incorrect usage, provide exactly two JSON files to work with." << std::endl; // Spits out error message when incorrect number of JSON files are inputted
        return 1;
    }
    // Storing both of these json files into variables to easily use later on
    string firstFile = argv[1];
    string secondFile = argv[2];

    ifstream file1(firstFile); // Creates an input filestream for the first file
    ifstream file2(secondFile); // Creates an input filestream for the second file
    if (!file1.is_open() || !file2.is_open()) // Checking if either of the files are not open
    {
        cerr << "Error: Cannot open file " << firstFile << endl; // If neither the first file nor second file is open we spit out an error message
        return 1;
    }

    json file1Contents, file2Contents; // Declares two JSOn variables that will be used for the rest of the program
    file1 >> file1Contents; // Parsing through the first json file into file1
    file2 >> file2Contents; // Parsing through the second json file2
    file1.close();          // Closing the first file
    file2.close();          // Closing the second file.

    json outputs_to_json;    // Storing all of the outputs of both files together in one json.
    int totalmismatches = 0; // Keeping count of the total number of mismatches between both json files

    // Creating the metadata section for both of the json files

    outputs_to_json["metadata"]["File1"]["name"] = firstFile;                                     // Storing the first filename
    outputs_to_json["metadata"]["File1"]["arraySize"] = file1Contents["metadata"]["arraySize"];   // Storing the array size for the first file
    outputs_to_json["metadata"]["File1"]["numSamples"] = file1Contents["metadata"]["numSamples"]; // Storing the number of samples for the first file

    outputs_to_json["metadata"]["File2"]["name"] = secondFile;                                    // Storing the second filename
    outputs_to_json["metadata"]["File2"]["arraySize"] = file2Contents["metadata"]["arraySize"];   // Storing the array size for the second file
    outputs_to_json["metadata"]["File2"]["numSamples"] = file2Contents["metadata"]["numSamples"]; // Storing the number of samples for the second file

    // Gathering the total number of samples in both files
    int totalNumSamples = file1Contents["metadata"]["numSamples"];
    // int newArraySize = metadatagroup1["arraySize"]; // Figuring out total number of values in the array

    for (int sampVal = 1; sampVal <= totalNumSamples; sampVal++)
    { // Loops through each sample in both Json files.

        // These 3 lines below are makign sure the format of the Sample is Sample01 and not Sample1. 
        ostringstream ss;
        ss << "Sample" << setw(2) << setfill('0') << sampVal;
        string SampName = ss.str();

        if (!file1Contents.count(SampName) || !file2Contents.count(SampName)) // Checking to see if either of the file contents contain the sample name itself
        {
            cerr << "Warning: " << SampName << " missing in one of the files." << endl; // Spits out a warning if one of the files is missing
            continue;
        }

        json firstFileArray = file1Contents[SampName];  // Creating array for first file/accessing data from first file.
        json secondFileArray = file2Contents[SampName]; // Creating array for second file/accessing data from second file.

        if (!firstFileArray.is_array() || !secondFileArray.is_array()) // checks to see if either of the files are not in the array
        {
            continue;
        }

        bool anyMismatch = false; // Tells us if there are any mismatches between the output samples in each of the json files.
        json mismatchList;        // Storing the positions of the mismatches between the output samples

        int minSize = min(firstFileArray.size(), secondFileArray.size()); // Checking the minimum size of the arrays within the files and comparing the size of both files.

        for (int pos = 0; pos < minSize; pos++) // going through the positions of the values within the arrays
        {
            if (!firstFileArray[pos].is_number() || !secondFileArray[pos].is_number()) // Checks whether either element at position pos in the two arrays is not a number 
            {
                mismatchList[to_string(pos)] = json::array({firstFileArray[pos], secondFileArray[pos]}); // If one of the values isnt a number we record the mismatch. I assumed that some of the cases could be that there could be null in the arrays.
                anyMismatch = true; // Confirming that the mismatch is indeed correct.
                continue;
            }


            // Checking if both numbers from each of the files are integers
            int numFromFile1 = firstFileArray[pos].get<int>();
            int numFromFile2 = secondFileArray[pos].get<int>();

            if (numFromFile1 != numFromFile2) // Checking if the number from file 1 is not the same as the number from file 2
            {
                mismatchList[to_string(pos)] = json::array({numFromFile1, numFromFile2}); // Adding mismatch to the mismatch list if we detect one
                anyMismatch = true;
            }
        }

        // Checking to see if the file in the first array is not the same as the file in the second array
        if (firstFileArray.size() != secondFileArray.size())
        {
            anyMismatch = true;
        }

        if (anyMismatch)
        { // Looping through the key/value pairs to see the mismatches between the samples in each of the files
            totalmismatches++;
            outputs_to_json[SampName][firstFile] = firstFileArray;   // Updates the new section of the JSON file in the "Sample1" - adds another key under file1.json
            outputs_to_json[SampName][secondFile] = secondFileArray; // Updates the new sectioction of the JSON file in the "Sample2" - adds another key under file2.json
            outputs_to_json[SampName]["Mismatches"] = mismatchList;  // Collecting all of the possible mismatches between both of the samples of data from both files
        }
    }

    outputs_to_json["metadata"]["samplesWithConflictingResults"] = totalmismatches; // Outputs all of the mismatches to the samples with Conflicting Results and stores them
    cout << outputs_to_json.dump(4) << endl; // Printing the format of the new updated JSON in an easy to read format. .dump() is from the nlohmann json library
    return 0;
}
