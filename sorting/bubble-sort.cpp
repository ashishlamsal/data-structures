#include <iostream>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// swap two successive items i.e 0,1 | 1,2 | 2,3 and so on in each pass
void bubble_sort(int arr[], int n) {
    bool isSorted;
    for (int i = 0; i < n - 1; i++) {
        isSorted = true;
        for (int j = 0; j < (n - 1 - i); j++)
        {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                isSorted = false;
            }
        }
        if (isSorted)
            return;
    }
}

void display(int arr[], int n) {
    std::cout << " Array : [ ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
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

    std::cout << "Before Sorting : ";
    display(arr, n);
    bubble_sort(arr, n);
    std::cout << "After Sorting  : ";
    display(arr, n);

    return 0;
}