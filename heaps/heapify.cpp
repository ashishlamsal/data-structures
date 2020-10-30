#include <iostream>

class Heapify {
private:
    static void maxHeapify(int[], int, int);
    static void minHeapify(int[], int, int);
    static void swap(int&, int&);

public:
    static void maxHeapify(int[], int);
    static void minHeapify(int[], int);
    static void printHeap(int[], int);
};

void Heapify::maxHeapify(int arr[], int n) {
    // int lastParentIndex = (n / 2 - 1);
    for (int i = (n / 2 - 1); i >= 0; i--)
        maxHeapify(arr, n, i);
}

void Heapify::maxHeapify(int arr[], int n, int index) {
    int largerIndex = index;

    int leftIndex = 2 * index + 1;
    if (leftIndex < n && arr[leftIndex] > arr[largerIndex])
        largerIndex = leftIndex;

    int rightIndex = 2 * index + 2;
    if (rightIndex < n && arr[rightIndex] > arr[largerIndex])
        largerIndex = rightIndex;

    if (index == largerIndex)       // index is in correct position 
        return;

    swap(arr[index], arr[largerIndex]);

    maxHeapify(arr, n, largerIndex);
}

void Heapify::minHeapify(int arr[], int n) {
    for (int i = (n / 2 - 1); i >= 0; i--)
        minHeapify(arr, n, i);
}
void Heapify::minHeapify(int arr[], int n, int index) {
    int smallerIndex = index;

    int leftIndex = 2 * index + 1;
    if (leftIndex < n && arr[leftIndex] < arr[smallerIndex])
        smallerIndex = leftIndex;

    int rightIndex = 2 * index + 2;
    if (rightIndex < n && arr[rightIndex] < arr[smallerIndex])
        smallerIndex = rightIndex;

    if (index == smallerIndex)       // index is in correct position 
        return;

    swap(arr[index], arr[smallerIndex]);

    minHeapify(arr, n, smallerIndex);
}

void Heapify::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void Heapify::printHeap(int arr[], int n)
{
    std::cout << "[  ";

    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << ", ";
    std::cout << "\b\b  ]\n";
}


int main() {
    //maxHeapify
    int arr[] = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Array : " << std::endl;
    Heapify::printHeap(arr, n);

    std::cout << "Max Heapify : " << std::endl;
    Heapify::maxHeapify(arr, n);
    Heapify::printHeap(arr, n);

    std::cout << "Min Heapify : " << std::endl;
    Heapify::minHeapify(arr, n);
    Heapify::printHeap(arr, n);

    return 0;
}