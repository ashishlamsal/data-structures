#include <iostream>

int linear_search(int arr[], int item, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == item)
            return i;
    }
    return -1;
}

void display(int arr[], int n) {
    std::cout << " Array : [ ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << "]\n";
}

int main() {
    const int n = 9;
    int arr[n] = { 8,6,10,5,9,3,2,6,4 };

    // const int n = 100000;
    // int arr[n];
    // for (int i = 0; i < n; i++)
    // {
    //     arr[i] = n- i;
    // }
    
    int item;
    std::cout << "Enter item for search : ";
    std::cin >> item;
    std::cout << "Searching : ";
    display(arr, n);
    int index = linear_search(arr, item, n);
    if (index == -1)
        std::cout << item << " not found in the array." << std::endl;
    else
        std::cout << item << " is at index " << index << " in the array. " << std::endl;

    return 0;
}