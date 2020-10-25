#include <iostream>

void display(int arr[], int n) {
    std::cout << " Array : [ ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "]\n";
}

void merge(int left[], int right[], int result[], int l1, int l2) {
    int i = 0, j = 0, k = 0;

    while (i < l1 && j < l2) {
        if (left[i] <= right[j])
            result[k++] = left[i++];
        else
            result[k++] = right[j++];
    }

    while (i < l1)
        result[k++] = left[i++];

    while (j < l2)
        result[k++] = right[j++];
}

void merge_sort(int arr[], int n) {
    if (n < 2) return;

    // divide
    int middle = n / 2;
    int* left = new int[middle];
    for (int i = 0; i < middle; i++)
        left[i] = arr[i];

    int* right = new int[n - middle];
    for (int i = middle; i < n; i++)
        right[i - middle] = arr[i];

    // sort
    merge_sort(left, middle);
    merge_sort(right, n - middle);

    // conquer
    merge(left, right, arr, middle, n - middle);
    
    delete[] left;
    delete[] right;
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
    merge_sort(arr, n);
    std::cout << "After Sorting  : ";
    display(arr, n);

    return 0;
}