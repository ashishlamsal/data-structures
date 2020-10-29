#include <iostream>
#include <unordered_set>
#include <cstring>

void display(std::unordered_set<int>& set) {
    std::cout << "Set : { ";
    for (auto&& i : set)
        std::cout << i << ", ";
    std::cout << "\b\b }\n";
}

// put array emements in a set 
void remove_duplicates(int arr[], int n) {
    std::unordered_set<int> set;
    for (int i = 0; i < n; i++)
        set.insert(arr[i]);
    display(set);
}

int main() {
    int arr[] = { 2,3,4,3,4,2,4,5,7 };
    int n = sizeof(arr) / sizeof(arr[0]);
    remove_duplicates(arr, n);
    return 0;
}