// 1. Perform enqueue and dequeue operations in Circular Queue 

#include <iostream>

const int MAXQUEUE = 5;

template <class T>
class CircularQueue
{
private:
	int front;
	int rear;
	int count;
	T* items;

public:
	CircularQueue();
	bool isEmpty();
	bool isFull();
	void enqueue(const T&);
	T dequeue();
	void display();
	~CircularQueue();
};

template <class T> CircularQueue<T>::CircularQueue()
{
	rear = -1;
	front = count = 0;
	items = new T[MAXQUEUE];
}

template <class T> bool CircularQueue<T>::isEmpty() {
	return count == 0;
}

template <class T> bool CircularQueue<T>::isFull() {
	return count == MAXQUEUE;
}

template <class T> void CircularQueue<T>::enqueue(const T& j) {
	if (isFull()) {
		std::cout << "Queue is full " << std::endl;
		exit(1);
	}
	rear = (rear + 1) % MAXQUEUE;
	items[rear] = j;
	display();
	count++;
}

template <class T> T CircularQueue<T>::dequeue() {
	if (isEmpty()) {
		std::cout << "Queue is empty" << std::endl;
		exit(1);
	}
	T item = items[front];
	items[front] = 0;
	front = (front + 1) % MAXQUEUE;
	count--;
	display();
	return item;
}

template <class T> void CircularQueue<T>::display() {
	std::cout << "Queue: [ ";
	for (size_t i = 0; i < MAXQUEUE; i++)
	{
		std::cout << items[i] << " ";
	}
	std::cout << "]\t";
	std::cout << "rear: " <<rear << " front : " << front;
	std::cout << std::endl;
}

template <class T> CircularQueue<T>::~CircularQueue()
{
	delete[] items;
}


int main()
{
	CircularQueue<int> q1;
	q1.enqueue(2);
	q1.enqueue(3);
	q1.enqueue(4);
	q1.enqueue(5);
	std::cout << q1.dequeue() << " ... Dequeued" << std::endl;
	std::cout << q1.dequeue() << " ... Dequeued" << std::endl;

	q1.enqueue(6);
	q1.enqueue(7);
	q1.enqueue(8);
	q1.enqueue(9);
	return 0;
}