#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "matcher.hpp"

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

    //lowercase both sides so matching ignors
    auto to_lower = [](std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
            });
        return s;
        };

    std::vector<std::string> patterns;
    for (const std::string& w : words) {
        patterns.push_back(to_lower(w));
    }

    const std::string haystack = to_lower(text);

    const aA::NaiveMatcher matcher(patterns);
    const std::vector<aA::Match> matches = matcher.scan(haystack);

    std::cout << "\nResults:\n";
    for (std::size_t i = 0; i < words.size(); i++) {
        std::cout << "  [" << i << "] " << words.at(i) << "  ";

        int count = 0;
        for (const aA::Match& m : matches) {
            if (m.pattern_index != i) continue;
            const std::size_t start = m.end_pos + 1 - patterns.at(i).size();
            std::cout << "[" << start << "," << m.end_pos << "] ";
            ++count;
        }

        if (count == 0) {
            std::cout << "not found";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
    return 0;
}