#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {

    std::string path;
    if (argc >= 2) {
        path = argv[1];
    }
    else {
        std::cout << "Text file: ";
        std::getline(std::cin, path);
    }
  
    
}