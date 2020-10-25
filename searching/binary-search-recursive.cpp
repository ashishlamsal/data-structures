#include <iostream>

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

void display(int arr[], int n) {
    std::cout << " Array : [ ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << "]\n";
}

int main() {
    // const int n = 9;
    // int arr[n] = { 8,6,10,5,9,3,2,6,4 };
    
    const int n = 9;
    int arr[n] = { 6,8,10,15,19,30,200,600,4000 }; // sorted
    
    int item;
    std::cout << "Enter item for search : ";
    std::cin >> item;
    std::cout << "Searching : ";
    display(arr, n);
    int index = binary_search(arr, item, 0, n - 1);
    if (index == -1)
        std::cout << item << " not found in the array." << std::endl;
    else
        std::cout << item << " is at index " << index << " in the array. " << std::endl;

    return 0;
}