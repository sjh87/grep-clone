#include <iostream>
#include <string>
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

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        std::cerr << "Expected first argument to be '-E' flag" << std::endl;
        return 1;
    }

    std::string input;
    std::getline(std::cin, input);

    try {
        if (match_pattern(input, pattern)) {
            return 0;
        }

        return 1;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
