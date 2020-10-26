/* 
    1. Perform enqueue and dequeue operations in Priority Queue 
    Assumptions:
    - insert items in ascending order and remove largest item
    - Larger number has higher priority and are dequeued first.
*/

#include <iostream>

const int MAXQUEUE = 5;

template <class T>
class PriorityQueue
{
private:
    T* items;
    int count;

public:
    PriorityQueue();
    bool isEmpty();
    bool isFull();
    void enqueue(const T&);
    T dequeue();
    void display();
    ~PriorityQueue();
};

template <class T> PriorityQueue<T>::PriorityQueue()
{
    items = new T[MAXQUEUE];
    count = 0;
}

template <class T> bool PriorityQueue<T>::isEmpty() {
    return count == 0;
}

template <class T> bool PriorityQueue<T>::isFull() {
    return count == MAXQUEUE;
}

// enqueue j such that items are in ascending order
template <class T> void PriorityQueue<T>::enqueue(const T& j) {
    if (isFull()) {
        std::cout << "Queue is full" << std::endl;
        exit(1);
    }
    
    // shift all items larger than j to right and insert j      
    int i = count - 1;
    while (i >= 0 && items[i] > j) {
        items[i + 1] = items[i];
        i--;
    };
    
    items[i + 1] = j;
    count++;
}

// dequeue largest items
template <class T> T PriorityQueue<T>::dequeue() {
    if (isEmpty()) {
        std::cout << "Queue is empty" << std::endl;
        exit(1);
    }
    int item = items[--count];
    items[count] = 0;
    return item;            // e.g. decrease count(5-1) and pop item at index(4)
}

template <class T> void PriorityQueue<T>::display() {
    std::cout << "Queue: [ ";
    for (size_t i = 0; i < MAXQUEUE; i++)
    {
        std::cout << items[i] << " ";
    }
    std::cout << "]\n";
}

template <class T> PriorityQueue<T>::~PriorityQueue()
{
    delete[] items;
}


int main()
{
    PriorityQueue<int> p1;
    p1.enqueue(8);
    p1.enqueue(4);
    p1.enqueue(2);
    p1.enqueue(5);
    p1.display();
    std::cout << p1.dequeue() << std::endl;
    std::cout << p1.dequeue() << std::endl;
    p1.display();
    p1.enqueue(3);
    p1.enqueue(7);
    p1.display();
    return 0;
}