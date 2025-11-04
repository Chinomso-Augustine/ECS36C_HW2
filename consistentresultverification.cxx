// Declaring the necessary libraries we will be using in this second executable
#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using namespace std;
using json_file = nlohmann::json; // Created a name for efficiency for the json file we will be using. 

// Making sure that the user provided the correct number of file names (2)

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr <<"Usage: ./consistentresultverification file1.json, file2.json" <<std::endl;
        return 1;
    }
    // Storing both of these json files into variables to easily use later on
    std::string firstFile = argv[1];
    std::string secondFile = argv[2];

    // Reading the first json file
    ifstream file1(firstFile); 
    if(!file1.is_open()) {
        cerr <<" File 1 cannot be opened " << firstFile << endl;
        return 1;
    }

    json_file file1Contents; // Holding the parsed json file from file1Contents
    file1 >> file1Contents; // Parsing through the first json file into file1
    file1.close();

    // Opening and reading the second file
    ifstream file2(secondFile);
    if(!file2.is_open()) {
        cerr <<" File 2 cannot be opened " << secondFile << endl;
        return 1;
    }

    json_file file2Contents; //Holding the parsed json file from file2Contents
    file2 >> file2Contents; // Parsing through the second json file2
    file2.close();

    int mismatches = 0; // Keeping count of the total number of mismatches between both json files
    json_file outputs_to_json; 

    // Gathering metadata from both of the json files
    json_file metadatagroup1 = file1Contents["metadata"];
    json_file metadatagroup2 = file2Contents["metadata"];

    // Creating the metadata section for both of the json files

    output["metadata"]["File1"]["name"] = file1Contents; // Storing the first filename
    output["metadata"]["File1"]["arraySize"] = metadatagroup1["arraySize"]; // Storing the array size for the first file
    output["metadata"]["File1"]["numSamples"] = metadatagroup1["numSamples"]; // Storing the number of samples for the first file

    output["metadata"]["File2"]["name"] = file2Contents; // Storing the second filename
    output["metadata"]["File2"]["arraySize"] = metadatagroup2["arraySize"]; // Storing the array size for the second file
    output["metadata"]["File2"]["numSamples"] = metadatagroup2["numSamples"]; // Storing the number of samples for the second file

    // We are looping through each key in the first JSON file.
    for (auto& value: file1Contents) {
      
    }











    



}