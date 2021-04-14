#pragma once
#include <vector>
#include <stdexcept>

const int INITIAL_CAPACITY = 5;

template <typename ValueType>
class Queue {
private:
    std::vector<ValueType> ringBuffer;
    int front;
    int rear;

    int count;
    int capacity;

private:
    void expandRingBufferCapacity();

public:
    Queue();
    virtual ~Queue() = default;

    void clear();
    int size() const;
    bool isEmpty() const;

    void enqueue(const ValueType& value);
    ValueType dequeue();
    ValueType peek() const;

    ValueType& getFront();
    ValueType& getBack();
};

template <typename ValueType>
Queue<ValueType>::Queue() :front(0), rear(0), count(0), capacity(INITIAL_CAPACITY) {
    ringBuffer = std::vector<ValueType>(capacity);
}

template <typename ValueType>
int Queue<ValueType>::size() const {
    return count;
}

template <typename ValueType>
bool Queue<ValueType>::isEmpty() const {
    return count == 0;
}

template <typename ValueType>
void Queue<ValueType>::clear() {
    capacity = INITIAL_CAPACITY;
    ringBuffer = std::vector<ValueType>(capacity);
    front = 0;
    rear = 0;
    count = 0;
}

template <typename ValueType>
void Queue<ValueType>::enqueue(const ValueType& value) {
    if (count >= capacity - 1)
        expandRingBufferCapacity();

    ringBuffer[rear] = value;
    rear = (rear + 1) % capacity;
    count++;
}

template <typename ValueType>
ValueType Queue<ValueType>::dequeue() {
    if (isEmpty())
        throw std::runtime_error("dequeue: Attempting to dequeue an empty queue");

    ValueType result = ringBuffer[front];
    front = (front + 1) % capacity;
    count--;
    return result;
}

template <typename ValueType>
ValueType Queue<ValueType>::peek() const {
    if (isEmpty())
        throw std::runtime_error("peek: Attempting to peek at an empty queue");
    return ringBuffer.get(front);
}

template <typename ValueType>
ValueType& Queue<ValueType>::getFront() {
    if (isEmpty())
        throw std::runtime_error("front: Attempting to read front of an empty queue");
    return ringBuffer[front];
}

template <typename ValueType>
ValueType& Queue<ValueType>::getBack() {
    if (isEmpty())
        throw std::runtime_error("back: Attempting to read back of an empty queue");
    return ringBuffer[(rear + capacity - 1) % capacity];
}

template <typename ValueType>
void Queue<ValueType>::expandRingBufferCapacity() {
    std::cout << "R" << count << std::endl;
    std::vector<ValueType> copyBuffer = ringBuffer;
    ringBuffer = std::vector<ValueType>(2 * capacity);
    for (int i = 0; i < count; i++) {
        ringBuffer[i] = copyBuffer[(front + i) % capacity];
    }
    front = 0;
    rear = count;
    capacity *= 2;
}