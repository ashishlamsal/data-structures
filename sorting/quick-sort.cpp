#include <iostream>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void display(int arr[], int n) {
    std::cout << " Array : [ ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "]\n";
}

int partition(int arr[], int start, int end) {
    int pivot = arr[end];
    int boundary = start - 1; // end of left partition
    for (int i = start; i <= end; i++) {
        if (arr[i] <= pivot)
            swap(arr[++boundary], arr[i]);
    }
    return boundary;
}

void sort(int arr[], int start, int end) {
    if (start >= end)
        return;

    int boundary = partition(arr, start, end);

    sort(arr, start, boundary - 1);
    sort(arr, boundary + 1, end);
}

void quick_sort(int arr[], int n) {
    sort(arr, 0, n - 1);
}

int main() {
    const int n = 9;
    int arr[n] = { 8,6,10,5,9,3,2,6,4 };

    // const int n = 100000;
    // int arr[n];
    // for (int i = 0; i < n; i++)
    // {
    //     arr[i] = n - i;
    // }

    std::cout << "Before Sorting : ";
    display(arr, n);
    quick_sort(arr, n);
    std::cout << "After Sorting  : ";
    display(arr, n);

    return 0;
}