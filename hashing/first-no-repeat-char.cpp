#include <iostream>
#include <string>
#include <unordered_map>

char first_non_repeating_char(const std::string& str) {
    // map: key=ch and value='no of repeation of each ch'
    std::unordered_map<char, int> map;
    for (auto&& ch : str)
        map[ch]++;

    // display k:v of map
    for (auto&& ch : map)
        std::cout << ch.first << " = " << ch.second << std::endl;

    // traverse the string to check for ch=1
    for (auto&& ch : str)
        if (map[ch] == 1) return ch;

    return '\0';
    
    /*
    std::unordered_map<char, int> map;
    for (std::string::const_iterator ch = str.begin(); ch != str.end(); ch++)
        map[*ch]++;

    for (std::unordered_map<char, int> ::iterator itr = map.begin(); itr!= map.end(); itr++)
        std::cout << itr->first << " = " << itr->second << std::endl;

    for (std::string::const_iterator ch = str.begin(); ch != str.end(); ch++)
        if (map[*ch] == 1) return *ch;

    return '\0';
    */
}


int main() {
    std::string str = "a green apple";
    std::cout << "Given string is : " << str << std::endl;
    char ch = first_non_repeating_char(str);
    if (ch == '\0')
        std::cout << "No non-repeating character found in the string.\n";
    else
        std::cout << "First non-repeating character : " << ch << std::endl;
    return 0;
}