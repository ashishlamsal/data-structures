// first repeated character

// find the character that occurs more than once 
// and whose index of second occurrence is smallest

#include <iostream>
#include <string>
#include <unordered_set>

char first_repeating_char(const std::string& str) {
    std::unordered_set<char> set;
    for (auto&& ch : str) {
        if (set.find(ch) == set.end()) // if ch not in set, add to set
            set.insert(ch);
        else
            return ch;
    }
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