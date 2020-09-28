// 1. Perform enqueue and dequeue operations in Linear Queue 

#include <iostream>

const int MAXQUEUE = 5;

template <class T>
class LinearQueue
{
private:
	int front;
	int rear;
	T* item;

public:
	LinearQueue();
	bool isEmpty();
	bool isFull();
	void enqueue(const T&);
	T dequeue();
	~LinearQueue();
};

template <class T> LinearQueue<T>::LinearQueue()
{
	rear = -1;
	front = 0;
	item = new T[MAXQUEUE];
}

template <class T> bool LinearQueue<T>::isEmpty() {
	return rear < front;
}

template <class T> bool LinearQueue<T>::isFull() {
	return rear == MAXQUEUE - 1;
}

template <class T> void LinearQueue<T>::enqueue(const T& j) {
	if (isFull()) {
		std::cout << "Queue is full" << std::endl;
		exit(1);
	}
	item[++rear] = j;
}

template <class T> T LinearQueue<T>::dequeue() {
	if (isEmpty()) {
		std::cout << "Queue is empty" << std::endl;
		exit(1);
	}
	return item[front++];
}

template <class T> LinearQueue<T>::~LinearQueue()
{
	delete[] item;
}


int main() 
{
	LinearQueue<int> q1;
	q1.enqueue(2);
	q1.enqueue(3);
	q1.enqueue(4);
	q1.enqueue(5);

	std::cout << q1.dequeue() << std::endl;
	std::cout << q1.dequeue() << std::endl;

	q1.enqueue(6);
	//q1.enqueue(7);
	//q1.enqueue(8);
	return 0;
}