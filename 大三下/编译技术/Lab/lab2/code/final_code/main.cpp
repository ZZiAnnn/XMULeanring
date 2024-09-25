#include <iostream>
#include <fstream>
#include "grammatical.hpp"
int main()
{
    std::string filename = "test.txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    std::vector<token> tokens;
    std::string buffer;

    std::cout << "Input file: " << std::endl;
    while (std::getline(file, buffer)) {
        std::cout << buffer << std::endl;
        std::vector<token> res = scan(buffer);
        tokens.insert(tokens.end(), res.begin(), res.end());
    }

    file.close();

    std::cout << "\nToken size: " << tokens.size() << std::endl;
    std::cout << "\nTokens: ";
    for (const auto& tok : tokens) {
        std::cout << tok.data << " ";
    }
    std::cout << std::endl;
    parse(tokens);

    return 0;
}