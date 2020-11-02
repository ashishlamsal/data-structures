#include <iostream>

const int MAXSIZE = 10;

template <class T>
class MinHeap {
private:
    T* items;
    int size;

private:
    // returns indexes of array (not item)
    int parent(int);
    int leftChild(int);
    int rightChild(int);
    int smallerChild(int);

    bool isValidParent(int);
    bool hasLeftChild(int);
    bool hasRightChild(int);

    void bubbleUp();
    void bubbleDown();
    void swap(int, int); // @param indexes

public:
    MinHeap();
    ~MinHeap();
    
    bool isEmpty();
    bool isFull();
    
    T min();
    void insert(const T&);
    T remove();      // removes root node (default)

    void display();
};

template <class T>
MinHeap<T>::MinHeap() {
    items = new T[MAXSIZE];
    size = 0;
}

template <class T>
MinHeap<T>::~MinHeap() {
    delete[] items;
}

template <class T>
bool MinHeap<T>::isEmpty() {
    return size == 0;
}

template <class T>
bool MinHeap<T>::isFull() {
    return size == MAXSIZE;
}

template <class T>
int MinHeap<T>::parent(int index) {
    return (index - 1) / 2;
}

template <class T>
int MinHeap<T>::leftChild(int index) {
    return (index * 2) + 1;
}

template <class T>
int MinHeap<T>::rightChild(int index) {
    return (index * 2) + 2;
}

template <class T>
void MinHeap<T>::swap(int first, int second) {
    T temp = items[first];
    items[first] = items[second];
    items[second] = temp;
}

template <class T>
T MinHeap<T>::min() {
    if (isEmpty()) {
        std::cout << "ERROR: MinHeap Underflow" << std::endl;
        exit(1);
    }

    return items[0];
}

template <class T>
void MinHeap<T>::insert(const T& value) {
    if (isFull()) {
        std::cout << "ERROR: MinHeap Overflow" << std::endl;
        return;
    }
    items[size++] = value;

    bubbleUp();
}

template <class T>
void MinHeap<T>::bubbleUp() {
    int index = size - 1;
    while (index > 0 && items[index] < items[parent(index)]) {
        swap(index, parent(index));
        index = parent(index);
    }
}

template <class T>
T MinHeap<T>::remove() {
    if (isEmpty()) {
        std::cout << "ERROR: MinHeap Underflow" << std::endl;
        exit(1);
    }

    // move last item in heap to root and bubble down
    T root = items[0];
    items[0] = items[--size];
    bubbleDown();
    
    items[size] = 0;
    return root;
}

template <class T>
void MinHeap<T>::bubbleDown() {
    int index = 0;
    while (index <= size && !isValidParent(index)) {
        int smallerIndex = smallerChild(index);
        swap(index, smallerIndex);
        index = smallerIndex;
    }
}

// any index must be < size (<= because size is already decreased in remove() method)
template <class T>
bool MinHeap<T>::hasLeftChild(int index) {
    return leftChild(index) <= size;
}

template <class T>
bool MinHeap<T>::hasRightChild(int index) {
    return rightChild(index) <= size;
}

template <class T>
bool MinHeap<T>::isValidParent(int index) {
    if (!hasLeftChild(index))
        return true;
    if (!hasRightChild(index))
        return items[index] <= items[leftChild(index)];

    return items[index] <= items[leftChild(index)] && items[index] <= items[rightChild(index)];
}

template <class T>
int MinHeap<T>::smallerChild(int index) {
    if (!hasLeftChild(index))
        return index;
    if (!hasRightChild(index))
        return leftChild(index);

    return (items[leftChild(index)] < items[rightChild(index)]) ?
        leftChild(index) : rightChild(index);
}

template <class T>
void MinHeap<T>::display()
{
    std::cout << "Min Heap : [  ";
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
    MinHeap<T> heap;
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
    MinHeap<int> heap;
    heap.insert(5);
    heap.insert(10);
    heap.insert(17);
    heap.insert(4);
    heap.insert(22);
    heap.insert(30);
    heap.insert(15);
    heap.display();
    std::cout << heap.remove() << " is removed" << std::endl;
    std::cout << heap.remove() << " is removed" << std::endl;
    heap.display();
    std::cout << heap.remove() << " is removed" << std::endl;
    heap.display();

    // priority pqueue
    PriorityQueue<float> pqueue;
    pqueue.enqueue(30.5);
    pqueue.enqueue(20.2);
    pqueue.enqueue(40.6);
    pqueue.enqueue(10.6);
    pqueue.display();
    std::cout << pqueue.dequeue() << " is removed" << std::endl;
    pqueue.display();
    return 0;
}
