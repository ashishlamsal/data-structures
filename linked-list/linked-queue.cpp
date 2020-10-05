// 2.	IMPLEMENT QUEUE AS LINKED LIST
#include <iostream>

template <class T>
class Queue {
private:
	class Node {
	public:
		T data;
		Node* next;

		Node(const T& data) :data(data), next(NULL) {}
	};
	Node* front;
	Node* rear;

public:
	Queue();
	~Queue();
	bool isEmpty();
	void enqueue(const T&);
	T dequeue();
	void display();
};

template <class T>Queue<T>::Queue() :front(NULL), rear(NULL) {}

template <class T>Queue<T>::~Queue() {
	Node* ptr = front;

	while (front != NULL) {
		ptr = front;
		front = front->next;
		delete ptr;
	}
	rear = NULL;
}

template <class T> bool Queue<T>::isEmpty() {
	return front == NULL;
}

template <class T> void Queue<T>::enqueue(const T& item) {
	Node* node = new Node(item);

	if (isEmpty())
		front = rear = node;
	else {
		rear->next = node;
		rear = node;
	}
}

template <class T> T Queue<T>::dequeue() {
	if (isEmpty()) {
		std::cout << "ERROR: Underflow" << std::endl;
		exit(1);
	}

	Node* ptr = front;
	T value = ptr->data;
	
	if (front == rear)
		front = rear = NULL;
	else
		front = front->next;
	delete ptr;
	return value;
}

template <class T> void Queue<T>::display() {
	Node* ptr = front;

	std::cout << "QUEUE : [ ";
	while (ptr != NULL)
	{
		std::cout << ptr->data << " ";
		ptr = ptr->next;
	}
	std::cout << "]" << std::endl;
}

int main() {
	Queue<int> q;
	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	q.enqueue(40);
	q.display();
	std::cout << "Removing : " << q.dequeue() << std::endl;
	std::cout << "Removing : " << q.dequeue() << std::endl;
	q.enqueue(50);
	q.display();

	return 0;
}

