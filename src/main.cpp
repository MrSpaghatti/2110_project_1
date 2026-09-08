#include <iostream>

int main() {
    std::cout << "Campus Resource Reservation System\n";
    std::cout << "===============================\n";
    std::cout << "Menu coming in a later milestone.\n";
    return 0;
}

// ============================================================================
//  When FileLoader::loadResources exists, replace the three cout lines and the
//  `return 0;` inside main() with:
//
//      std::vector<Resource> resources = FileLoader::loadResources("data/resources.txt");
//      for (std::size_t i = 0; i < resources.size(); ++i) {
//          resources[i].print();
//      }
//      return 0;
//
//  (add  #include "FileLoader.h"  at the top when you do)
// ============================================================================
