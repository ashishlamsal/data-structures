#include <iostream>
#include <algorithm> 
#include <vector> 
#include <cmath>

class BucketSort
{
private:
    int n;
    int* arr;
public:
    BucketSort(int* arr, int n);
    ~BucketSort();
    
    void sort();
    void display();
};

BucketSort::BucketSort(int* arr, int n) :arr(arr), n(n) {}

BucketSort::~BucketSort() {}

void BucketSort::sort() {
    const int bucket_size = 5;
    
    // buckets: array of vectors
    std::vector<int> buckets[bucket_size];

    // find max value in arr
    int max = arr[0];
    for (int i = 0; i < n; i++) {
        if (max < arr[i])
            max = arr[i];
    }

    //CreateBuckets: push values at appropriate bucket.
    for (int i = 0; i < n; i++) {
        int index = std::floor((bucket_size - 1) * arr[i] / max);
        buckets[index].push_back(arr[i]);
    }
    
    // sort each bucket and append to arr
    int k = 0;
    for (auto&& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
        for (auto&& item : bucket)
            arr[k++] = item;
    }
}

void BucketSort::display() {
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

    BucketSort b(arr, n);
    std::cout << "Before Sorting : ";
    b.display();
    b.sort();
    std::cout << "After Sorting  : ";
    b.display();

    return 0;
}