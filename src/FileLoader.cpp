#include "FileLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

vector<Resource> FileLoader::loadResources(const string &path) {
    ifstream in(path);

    if (!in){
        cerr << "Error: Could not open the file." << endl;
        return vector<Resource>();
    }

    vector<Resource> resources;
    string line;
    char delim = '|';
    string field;
    while (getline(in, line)){
        if (line.empty()){
            continue;
        }

        // split each line on every '|' into each of the 4 expected fields.
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, delim)){
            fields.push_back(field);
        }

        // a resource should only ever have 4 fields.
        if (fields.size() != 4){
            cerr << "Error: Incorrect resource data provided" << endl;
            continue;
        }

        // Last field in resources.txt determines whether a resource is available for reservation.
        bool avail = (fields[3] == "Available");

        // build the resource and addd it to the results.
        resources.push_back(Resource(fields[0], fields[1], fields[2], avail));
    }
    return resources;
}
