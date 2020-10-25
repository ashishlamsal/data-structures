#include <iostream>

int ternary_search(int arr[], int item, int left, int right) {
    if (right < left) return -1;
    
    int partition = (right - left) / 3;
    int middle1 = left + partition;
    int middle2 = right - partition;
    
    if (item == arr[middle1])
        return middle1;
    else if (item == arr[middle2])
        return middle2;
    else if (item < arr[middle1])
        return ternary_search(arr, item, left, middle1 - 1);
    else if (item > arr[middle1] && item < arr[middle2])
        return ternary_search(arr, item, middle1 + 1, middle2 - 1);
    else
        return ternary_search(arr, item, middle2 + 1, right);
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
    int index = ternary_search(arr, item, 0, n - 1);
    if (index == -1)
        std::cout << item << " not found in the array." << std::endl;
    else
        std::cout << item << " is at index " << index << " in the array. " << std::endl;

    return 0;
}