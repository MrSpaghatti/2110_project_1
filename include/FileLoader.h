#ifndef FILELOADER_H
#define FILELOADER_H

#include "Resource.h"
#include <string>
#include <vector>

// This is stateless, so the loading functions are static.
// Call them directly as FileLoader::loadResources(...)
// instead of creating an object first.
//
// loadReservations() WIP
class FileLoader {
public:
    // reads every non-empty line from resources record
    // and returns them as Resource objects. expects 4
    // fields that have been separated by pipes (id|name|type|availability)
    static std::vector<Resource> loadResources(const std::string &path);
};

#endif
