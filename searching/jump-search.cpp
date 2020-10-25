#include <iostream>
#include <cmath>

// linear search on appropriate block
int jump_search(int arr[], int n, int item) {
    int block_size = static_cast<int>(sqrt(n));
    int start = 0;          // start of a block
    int next = block_size;  // start of next block

    // find block whose last item is greater than or equal to item
    while (start < n && arr[next - 1] < item) {
        start = next;
        next += block_size;
        if (next > n)
            next = n;
    }
    
    // linear search
    for (int i = start; i < next; i++) {
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
    // const int n = 9;
    // int arr[n] = { 8,6,10,5,9,3,2,6,4 };

    const int n = 9;
    int arr[n] = { 6,8,10,15,19,30,200,600,4000 }; //sorted

    int item;
    std::cout << "Enter item for search : ";
    std::cin >> item;
    std::cout << "Searching : ";
    display(arr, n);
    int index = jump_search(arr, n, item);
    if (index == -1)
        std::cout << item << " not found in the array." << std::endl;
    else
        std::cout << item << " is at index " << index << " in the array. " << std::endl;

    return 0;
}