#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string date;
    const std::regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
    
    std::cout << "Enter a date: ";
    std::getline(std::cin, date);
    
    std::cout << "You entered: '" << date << "'" << std::endl;
    std::cout << "Length: " << date.length() << std::endl;
    
    // Print each character and its ASCII value
    for (size_t i = 0; i < date.length(); ++i) {
        std::cout << "Char " << i << ": '" << date[i] << "' (ASCII: " << (int)date[i] << ")" << std::endl;
    }
    
    bool matches = std::regex_match(date, datePattern);
    std::cout << "Regex match: " << (matches ? "YES" : "NO") << std::endl;
    
    return 0;
} 