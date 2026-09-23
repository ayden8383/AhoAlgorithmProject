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
  
    //open file
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        std::cerr << "error: cannot open " << path << "\n";
        return 1;
    }

    //read file into one string
    std::ostringstream buffer;
    buffer << in.rdbuf();
    const std::string text = buffer.str();

    //show size of file
    std::cout << "Read " << path << " (" << text.size() << " characters)\n";

   

    std::cout << "Enter a word or multiple (if more than one word separate by spaces):\n> ";
    std::string line;
    std::getline(std::cin, line);

    std::vector<std::string> words;
    std::istringstream stream(line);
    std::string word;
    while (stream >> word) {
        words.push_back(word);
    }

    if (words.empty()) {
        std::cerr << "error: no words entered \n";
        return 1;
    }

    std::cout << "\nLooking for " << words.size() << " word(s):\n";
    for (std::size_t i = 0; i < words.size(); i++) {
        std::cout << "  [" << i << "] " << words.at(i) << "\n";
    }

    return 0;
}