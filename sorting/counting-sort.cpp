#include <iostream>

void display(int arr[], int n) {
    std::cout << " Array : [ ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << "]\n";
}

void counting_sort(int arr[], int n) {
    const int range = 10;
    int count[range] = { 0 };
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    int k = 0;
    for (int i = 0; i < range; i++)
        for (int j = 0; j < count[i]; j++)
            arr[k++] = i;
}

int main() {
    const int n = 9;
    int arr[n] = { 8,6,5,5,9,2,2,6,4 };

    // const int n = 100000;
    // int arr[n];
    // for (int i = 0; i < n; i++)
    // {
    //     arr[i] = n- i;
    // }

    std::cout << "Before Sorting : ";
    display(arr, n);
    counting_sort(arr, n);
    std::cout << "After Sorting  : ";
    display(arr, n);

    return 0;
}