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
  
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        std::cerr << "error: cannot open " << path << "\n";
        return 1;
    }

    std::ostringstream buffer;
    buffer << in.rdbuf();
    const std::string text = buffer.str();

    std::cout << "Read " << path << " (" << text.size() << " characters)\n";

   

    std::cout << "Enter a word or multiple (if more than one word seperate by spaces:)\n>) ";
    std::string line;
    std::getline(std::cin, line);

    return 0;
}