#include <iostream> // Library for input and output stream
#include <fstream> // Library used for the file input and output stream 
#include "json.hpp" //For loading json file

using namespace std; // using the standard namespace
using json = nlohmann::json; // allows access to nlohmann just by calling json

int main(int argc, char **argv)
{

    // Assuming json file is not provided, we send an error
    if (argc != 2)
    {
        cerr << "Incorrect input. You either provided no file or more than one. Please provide one json file" << endl; // Error display if there is an incorrect input
        return 1;
    }

    string jsonFile = argv[1]; // getting jsonFile from command line

    ifstream inputFile(jsonFile); // Reading jsonFile
    if (!inputFile.is_open())
    { // If file is not open print not open and stop. This is for file validation
        cout << "File did not open";
        return 1;
    }

    // Storing json data
    else
    {
        json data;         // Declaring a json data type that will store the file data
        inputFile >> data; // Pushing or reading file inputs into data
        json result;       // json object to store result

        // Checking for consecutive inversion
        for (auto items = data.begin(); items != data.end(); ++items)
        { // start from the beginning and don't stop until we reach the end of data
            {

                string key = items.key(); // Getting the string key value from the data
                json value = items.value(); // Getting the value itself from the data

                // skipping metadata because it is not an array
                if (key == "metadata")
                {
                    continue; // move to the next key value pair
                }

                // Assume no inversion until we found one
                bool hasInversion = false;

                for (int i = 0; i < value.size() - 1; i++)
                { // looping though all key values pair starting at i = counter =0 to size of the value

                    // This is where we check inversion.
                    // Check if i > i +1, if true, we have consecutive inversion
                    if (value[i] > value[i + 1])
                    {

                        result[key]["ConsecutiveInversions"][to_string(i)] = { // store inversion to result with its index
                        value[i], value[i + 1]}; // inversion occurrs here
                        hasInversion = true;  // checks that we now have inversion
                    }
                }
                if (hasInversion) // checks if at least one inversion was founh
                {
                    result[key]["sample"] = value; // stores entire sample array in result
                }
            }
        }
        // metadata to add back to result when displaying
        result["metadata"]["arraySize"] = data["metadata"]["arraySize"];
        result["metadata"]["numSamples"] = data["metadata"]["numSamples"];
        result["metadata"]["file"] = jsonFile;
        result["metadata"]["samplesWithInversions"] = result.size() - 1;

        cout << result.dump(4) << endl; // display result in a readable way
    }

    return 0;
}