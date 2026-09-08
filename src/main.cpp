#include <iostream>
#include "FileLoader.h"
using namespace std;

int main() {
    vector<Resource> resources = FileLoader::loadResources("data/resources.txt");
    for (size_t i = 0; i < resources.size(); ++i){
        resources[i].print();
    }
    return 0;
}
