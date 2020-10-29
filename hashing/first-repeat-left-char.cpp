// repeated character present first

// find the repeated character present first in the string
// i.e. repeated character whose first appearance is leftmost

#include <iostream>
#include <string>
#include <unordered_map>

char first_repeating_char(const std::string& str) {
    std::unordered_map<char, int> map;
    for (auto&& ch : str)
        map[ch]++;

    for (auto&& ch : map)
        std::cout << ch.first << " = " << ch.second << std::endl;

    for (auto&& ch : str)
        if (map[ch] != 1) return ch;
    
    return '\0';
}

int main() {
    std::string str = "geeks for geeks";
    std::cout << "Given string is : " << str << std::endl;
    char ch = first_repeating_char(str);
    if (ch == '\0')
        std::cout << "No repeating character found in the string.\n";
    else
        std::cout << "First repeating character : " << ch << std::endl;
    return 0;
}