#include <iostream>

void display(int arr[], int n) {
    std::cout << " Array : [ ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "]\n";
}

//shift larger values from left of current towards right and insert current
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int current = arr[i];

        int j = i - 1;                          // prev of currrent
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];                // shift j to right
            j--;
        }
        arr[j + 1] = current;
    }
}

int main() {
    const int n = 9;
    int arr[n] = { 8,6,10,5,9,3,2,6,4 };

    std::cout << "Before Sorting : ";
    display(arr, n);
    insertion_sort(arr, n);
    std::cout << "After Sorting  : ";
    display(arr, n);

    return 0;
}