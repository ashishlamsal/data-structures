// 3. Deque 

#include <iostream>

const int MAXQUEUE = 5;

template <class T>
class Deque
{
private:
	int front;
	int rear;
	int count;
	T* items;

public:
	Deque();
	bool isEmpty();
	bool isFull();
	void push_back(const T&);
	void push_front(const T&);
	T pop_front();
	T pop_back();
	void display();
	~Deque();
};

template <class T> Deque<T>::Deque()
{
	rear = -1;
	front = count = 0;
	items = new T[MAXQUEUE];
}

template <class T> bool Deque<T>::isEmpty() {
	return count == 0;
}

template <class T> bool Deque<T>::isFull() {
	return count == MAXQUEUE;
}

template <class T> void Deque<T>::push_back(const T& j) {
	if (isFull()) {
		std::cout << "Queue is full" << std::endl;
		exit(1);
	}
	//rear = (rear + 1) % MAXQUEUE;
	if (rear == MAXQUEUE - 1)
		rear = 0;
	else
		rear++;

	items[rear] = j;
	display();
	count++;
}

template <class T> void Deque<T>::push_front(const T& j) {
	if (isFull()) {
		std::cout << "Queue is full" << std::endl;
		exit(1);
	}
	// front = (front + MAXQUEUE -1) % MAXQUEUE
	if (front == 0)
		front = MAXQUEUE - 1;
	else
		front--;

	items[front] = j;
	display();
	count++;
}

template <class T> T Deque<T>::pop_front() {
	if (isEmpty()) {
		std::cout << "Queue is empty" << std::endl;
		exit(1);
	}
	T item = items[front];
	items[front] =0;
	//front = (front + 1) % MAXQUEUE;
	if (front == MAXQUEUE - 1)
		front = 0;
	else
		front++;
	count--;
	display();
	return item;
}

template <class T> T Deque<T>::pop_back() {
	if (isEmpty()) {
		std::cout << "Queue is empty" << std::endl;
		exit(1);
	}
	T item = items[rear];
	items[rear] = 0;
	// rear = (rear + MAXQUEUE -1) % MAXQUEUE
	if (rear == 0)
		rear = MAXQUEUE - 1;
	else
		rear--;
	count--;
	display();
	return item;
}

template <class T> void Deque<T>::display() {
	std::cout << "Queue: [ ";
	for (size_t i = 0; i < MAXQUEUE; i++)
	{
		std::cout << items[i] << " ";
	}
	std::cout << "]\t";
	std::cout << "rear: " <<rear << " front : " << front;
	std::cout << std::endl;
}

template <class T> Deque<T>::~Deque()
{
	delete[] items;
}


int main()
{
	Deque<int> q1;
	q1.push_back(2);
	q1.push_back(3);
	q1.push_front(5);
	q1.push_back(6);
	q1.push_front(4);
	std::cout << q1.pop_back() << std::endl;
	std::cout << q1.pop_front() << std::endl;

	q1.push_back(8);
	q1.push_back(7);
	//q1.push_back(9);
	std::cout << q1.pop_back() << std::endl;
	std::cout << q1.pop_front() << std::endl;
	std::cout << q1.pop_front() << std::endl;

	return 0;
}