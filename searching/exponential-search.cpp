#include <iostream>
#include <cmath>

int binary_search(int arr[], int item, int left, int right) {
    if (right < left) return -1;
    
    int middle = (left + right) / 2;
    
    if (item == arr[middle])
        return middle;
    
    if (item < arr[middle])
        return binary_search(arr, item, left, middle - 1);
    else
        return binary_search(arr, item, middle + 1, right);
}

// binary search on appropriate block
int exponential_search(int arr[], int n, int item) {
    int bound = 1;
    while (bound < n && arr[bound] < item)
        bound *= 2;

    int left = bound / 2;
    int right = (bound + n - 1 - abs(bound - (n - 1))) / 2; // min(bound, n-1)

    return binary_search(arr, item, left, right);
}

void display(int arr[], int n) {
    std::cout << " Array : [ ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << "]\n";
}

int main() {
    // const int n = 9;
    // int arr[n] = { 8,6,10,5,9,3,2,6,4 };

    const int n = 10;
    int arr[n] = { 6,8,10,15,19,30,200,600,4000,4200 }; //sorted

    int item;
    std::cout << "Enter item for search : ";
    std::cin >> item;
    std::cout << "Searching : ";
    display(arr, n);
    int index = exponential_search(arr, n, item);
    if (index == -1)
        std::cout << item << " not found in the array." << std::endl;
    else
        std::cout << item << " is at index " << index << " in the array. " << std::endl;

    return 0;
}