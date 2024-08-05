#include <iostream>
#include <string>
#include <cstring>
#include <regex>

bool match_pattern(const std::string& input, const std::string& pattern) {
    std::regex exp;

    try {
        exp = std::regex(pattern);
    } catch(std::exception &e) {
        throw std::runtime_error("Unhandled pattern \"" + pattern + "\" is not a valid regular expression");
    }

    return std::regex_search(input, exp);
}

int main(int argc, char* argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc != 3 || std::strcmp("-E", argv[1])) {
        std::cerr << "Usage: " << argv[0] << " -E PATTERN" << std::endl;
        return 1;
    }

    std::string pattern;

    if (std::strlen(argv[2]) > pattern.max_size()) {
        std::cerr << "Pattern is too long. Must be under " << pattern.max_size() << " bytes." << std::endl;
        return 1;
    }

    pattern = argv[2];

    std::string input;

    // overruns are prevented automatically here with an internal call of input.max_size()
    std::getline(std::cin, input);

    try {
        return !match_pattern(input, pattern); // exit code 0 if true, else 1
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
