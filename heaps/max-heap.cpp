#include <iostream>

const int MAXSIZE = 10;

template <class T>
class MaxHeap {
private:
    T* items;
    int size;

private:
    // returns indexes of array (not item)
    int parent(int);
    int leftChild(int);
    int rightChild(int);
    int largerChild(int);

    bool isValidParent(int);
    bool hasLeftChild(int);
    bool hasRightChild(int);

    void bubbleUp();
    void bubbleDown();
    void swap(int, int); // @param indexes

public:
    MaxHeap();
    ~MaxHeap();
    
    bool isEmpty();
    bool isFull();
    T max();
    void insert(const T&);
    T remove();      // removes root node (default)

    static int getKthLargest(int* arr, int, int);
    void display();
};

template <class T>
MaxHeap<T>::MaxHeap() {
    items = new T[MAXSIZE];
    size = 0;
}

template <class T>
MaxHeap<T>::~MaxHeap() {
    delete[] items;
}

template <class T>
bool MaxHeap<T>::isEmpty() {
    return size == 0;
}

template <class T>
bool MaxHeap<T>::isFull() {
    return size == MAXSIZE;
}

template <class T>
int MaxHeap<T>::parent(int index) {
    return (index - 1) / 2;
}

template <class T>
int MaxHeap<T>::leftChild(int index) {
    return (index * 2) + 1;
}

template <class T>
int MaxHeap<T>::rightChild(int index) {
    return (index * 2) + 2;
}

template <class T>
void MaxHeap<T>::swap(int first, int second) {
    T temp = items[first];
    items[first] = items[second];
    items[second] = temp;
}

template <class T>
T MaxHeap<T>::max() {
    if (isEmpty()) {
        std::cout << "ERROR: MaxHeap Underflow" << std::endl;
        exit(1);
    }

    return items[0];
}

template <class T>
void MaxHeap<T>::insert(const T& value) {
    if (isFull()) {
        std::cout << "ERROR: MaxHeap Overflow" << std::endl;
        return;
    }
    items[size++] = value;

    bubbleUp();
}

template <class T>
void MaxHeap<T>::bubbleUp() {
    int index = size - 1;
    while (index > 0 && items[index] > items[parent(index)]) {
        swap(index, parent(index));
        index = parent(index);
    }
}

template <class T>
T MaxHeap<T>::remove() {
    if (isEmpty()) {
        std::cout << "ERROR: MaxHeap Underflow" << std::endl;
        exit(1);
    }

    // move last item in heap to root and bubble down
    T root = items[0];
    items[0] = items[--size];
    items[size] = 0;

    bubbleDown();
    return root;
}

template <class T>
void MaxHeap<T>::bubbleDown() {
    int index = 0;
    while (index <= size && !isValidParent(index)) {
        int largerIndex = largerChild(index);
        swap(index, largerIndex);
        index = largerIndex;
    }
}

// any index must be < size (<= because size is already decreased in remove() method)
template <class T>
bool MaxHeap<T>::hasLeftChild(int index) {
    return leftChild(index) <= size;
}

template <class T>
bool MaxHeap<T>::hasRightChild(int index) {
    return rightChild(index) <= size;
}

template <class T>
bool MaxHeap<T>::isValidParent(int index) {
    if (!hasLeftChild(index))
        return true;
    if (!hasRightChild(index))
        return items[index] >= items[leftChild(index)];

    return items[index] >= items[leftChild(index)] && items[index] >= items[rightChild(index)];
}

template <class T>
int MaxHeap<T>::largerChild(int index) {
    if (!hasLeftChild(index))
        return index;
    if (!hasRightChild(index))
        return leftChild(index);

    return (items[leftChild(index)] > items[rightChild(index)]) ?
        leftChild(index) : rightChild(index);
}

template <class T>
int MaxHeap<T>::getKthLargest(int arr[], int n, int k) {
    if (k < 1 || k > n) {
        std::cout << "ERROR: Invalid Range" << std::endl;
        exit(1);
    }

    MaxHeap<int> h;
    for (int i = 0; i < n; i++)
        h.insert(arr[i]);

    for (int i = 0; i < k - 1; i++)
        h.remove();

    return h.max();
}

template <class T>
void MaxHeap<T>::display()
{
    std::cout << "Max Heap : [  ";
    for (int i = 0; i < size; i++)
    {
        std::cout << items[i] << ", ";
    }
    std::cout << "\b\b  ]\n";
}


template <class T>
class PriorityQueue
{
private:
    MaxHeap<T> heap;
public:
    void enqueue(const T&);
    T dequeue();
    bool isEmpty();
    void display();
};

template <class T>
bool PriorityQueue<T>::isEmpty() {
    return heap.isEmpty();
}

template <class T>
void PriorityQueue<T>::enqueue(const T& value) {
    heap.insert(value);
}

template <class T>
T PriorityQueue<T>::dequeue() {
    return heap.remove();
}

template <class T>
void PriorityQueue<T>::display() {
    std::cout << "Priority Queue ";
    heap.display();
}

int main() {
    MaxHeap<int> heap;
    heap.insert(5);
    heap.insert(10);
    heap.insert(17);
    heap.insert(4);
    heap.insert(22);
    heap.insert(30);
    heap.insert(15);
    heap.display();
    std::cout << heap.remove() << " is removed" << std::endl;
    heap.display();
    std::cout << heap.remove() << " is removed" << std::endl;
    heap.display();


    // heap sort
    MaxHeap<int> h1;
    int arr[] = { 10, 4,3, 50, 40, 5,8 };
    int n = sizeof(arr) / sizeof(arr[0]);

    for (auto&& item : arr)
        h1.insert(item);

    for (int i = n - 1; i >= 0; i--) // ascending order | [0 to n (descending)]
        arr[i] = h1.remove();

    std::cout << "\nSorted array : [  ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << ", ";
    std::cout << "\b\b  ]\n";

    int k = 3;
    std::cout << "Kth largest element (k=" << k << ") : "
        << MaxHeap<int>::getKthLargest(arr, n, k) << "\n\n";

    // priority queue
    PriorityQueue<float> queue;
    queue.enqueue(30.5);
    queue.enqueue(20.2);
    queue.enqueue(40.6);
    queue.enqueue(10.6);
    queue.display();
    std::cout << queue.dequeue() << " is removed" << std::endl;
    queue.display();
    return 0;
}
