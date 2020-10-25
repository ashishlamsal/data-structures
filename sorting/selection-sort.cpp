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

// find min from i to n and swap (i, min) in each pass
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i; j < n; j++) {
            if (arr[min_index] > arr[j])
                min_index = j;
        }
        swap(arr[i], arr[min_index]);
    }
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

    std::cout << "Before Sorting : ";
    display(arr, n);
    selection_sort(arr, n);
    std::cout << "After Sorting  : ";
    display(arr, n);

    return 0;
}