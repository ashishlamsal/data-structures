#include <iostream>
#include <exception>

template <typename T>
class LinkedList
{
private:
	class Node
	{
	public:
		T value;
		Node *next;
		Node *prev;
		Node(const T &value) : value(value), next(nullptr), prev(nullptr) {}
	};

	Node *head;
	Node *tail;

private:
	bool isEmpty()
	{
		return head == nullptr;
	}

public:
	LinkedList();
	~LinkedList();
	void addLast(const T &);
	void addFirst(const T &);
	void addAfter(const T &, const T &);
	void addBefore(const T &, const T &);
	void addAt(int, const T &);
	void deleteFirst();
	void deleteLast();
	void deleteAfter(const T &);
	void deleteBefore(const T &);
	void deleteAt(int);
	void replace(const T &, const T &);
	void display();
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
LinkedList<T>::~LinkedList()
{
	Node *current = head;
	while (head != nullptr)
	{
		current = head;
		head = head->next;
		delete current;
	}
	tail = nullptr;
}

template <typename T>
void LinkedList<T>::addLast(const T &item)
{
	Node *node = new Node(item);

	if (isEmpty())
		head = tail = node;
	else
	{ // at least one element
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
}

template <typename T>
void LinkedList<T>::addFirst(const T &item)
{
	Node *node = new Node(item);

	if (isEmpty())
		head = tail = node;
	else
	{ // at least one element
		node->next = head;
		head->prev = node;
		head = node;
	}
}

template <typename T>
void LinkedList<T>::addAfter(const T &item1, const T &item2)
{
	Node *current = head;

	while (current->value != item1)
	{
		current = current->next;
		if (current == nullptr)
		{
			std::cout << item1 << " not found in the list" << std::endl;
			return;
		}
	}

	Node *node = new Node(item2);

	if (current == tail)
	{ // after last node
		current->next = node;
		node->prev = current;
		tail = node;
	}
	else
	{
		node->next = current->next;
		current->next->prev = node;

		node->prev = current;
		current->next = node;
	}
}

template <typename T>
void LinkedList<T>::addBefore(const T &item1, const T &item2)
{
	Node *current = head;

	while (current->value != item1)
	{
		current = current->next;
		if (current == nullptr)
		{
			std::cout << item1 << " not found in the list" << std::endl;
			return;
		}
	}

	Node *node = new Node(item2);

	if (current == head)
	{
		node->next = current;
		current->prev = node;
		head = node;
	}
	else
	{
		node->prev = current->prev;
		current->prev->next = node;

		node->next = current;
		current->prev = node;
	}
}

template <typename T>
void LinkedList<T>::addAt(int pos, const T &item)
{
	if (isEmpty() || pos < 1)
		throw std::runtime_error("UnderFlow");

	Node *current = head;

	for (int i = 1; i < pos; i++)
	{
		current = current->next;
		if (current == nullptr)
		{
			std::cout << "size of list is less than " << pos << std::endl;
			return;
		}
	}

	Node *node = new Node(item);

	if (current == head)
	{
		node->next = current;
		current->prev = node;
		head = node;
	}
	else
	{
		node->prev = current->prev;
		current->prev->next = node;

		node->next = current;
		current->prev = node;
	}
}

template <typename T>
void LinkedList<T>::deleteFirst()
{
	if (isEmpty())
		throw std::runtime_error("UnderFlow");

	Node *ptr = head;
	if (head == tail)
		head = tail = nullptr;
	else
	{
		head = head->next;
		head->prev = nullptr;
	}
	delete ptr;
}

template <typename T>
void LinkedList<T>::deleteLast()
{
	if (isEmpty())
		throw std::runtime_error("UnderFlow");

	Node *ptr = tail;
	if (head == tail)
		head = tail = nullptr;
	else
	{
		tail = tail->prev;
		tail->next = nullptr;
	}
	delete ptr;
}

template <typename T>
void LinkedList<T>::deleteAfter(const T &item1)
{
	if (isEmpty())
		throw std::runtime_error("UnderFlow");

	Node *current = head;

	while (current->value != item1)
	{
		current = current->next;
		if (current == nullptr)
		{
			std::cout << item1 << " not found in the list" << std::endl;
			return;
		}
	}

	if (current == tail)
	{ // error : delete after last element
		std::cout << "Nothing to delete after " << item1 << std::endl;
		return;
	}

	current = current->next;
	if (current == tail)
	{ // delete last element
		tail = current->prev;
		tail->next = nullptr;
	}
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	delete current;
}

template <typename T>
void LinkedList<T>::deleteBefore(const T &item1)
{
	if (isEmpty())
		throw std::runtime_error("UnderFlow");

	Node *current = head;

	while (current->value != item1)
	{
		current = current->next;
		if (current == nullptr)
		{
			std::cout << item1 << " not found in the list" << std::endl;
			return;
		}
	}

	if (current == head)
	{ // error : delete before first element
		std::cout << "Nothing to delete before " << item1 << std::endl;
		return;
	}

	current = current->prev;
	if (current == head)
	{ // delete first element
		head = current->next;
		head->prev = nullptr;
	}
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	delete current;
}

template <typename T>
void LinkedList<T>::deleteAt(int pos)
{
	if (isEmpty() || pos < 1)
		throw std::runtime_error("UnderFlow");

	Node *current = head;

	for (int i = 1; i < pos; i++)
	{
		current = current->next;
		if (current == nullptr)
		{
			std::cout << "size of list is less than " << pos << std::endl;
			return;
		}
	}
	if (current == head)
	{ // delete first element
	
		head = current->next;
		head->prev = nullptr;
	}
	else if (current == tail)
	{ // delete last element
		tail = current->prev;
		tail->next = nullptr;
	}
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	delete current;
}

template <typename T>
void LinkedList<T>::replace(const T &item1, const T &item2)
{
	Node *current = head;

	while (current->value != item1)
	{
		current = current->next;
		if (current == nullptr)
		{
			std::cout << item1 << " not found in the list" << std::endl;
			return;
		}
	}

	Node *node = new Node(item2);

	if (current == head)
	{ 
		node->next = current->next;
		current->next->prev = node;
		head = node;
	}
	else if (current == tail)
	{ 
		node->prev = current->prev;
		current->prev->next = node;
		tail = node;
	}
	else
	{
		node->next = current->next;
		node->prev = current->prev;

		current->next->prev = node;
		current->prev->next = node;
	}
	delete current;
}

template <class T>
void LinkedList<T>::display()
{
	Node *ptr = head;
	std::cout << "[ ";
	while (ptr != nullptr)
	{
		std::cout << ptr->value << " ";
		ptr = ptr->next;
	}
	std::cout << "]" << std::endl;
}

int main()
{
	try
	{
		LinkedList<int> l1;
		l1.addLast(4);
		l1.addLast(5);
		l1.addFirst(1);
		l1.addFirst(0);
		l1.display();
		l1.deleteFirst();
		l1.addFirst(2);
		l1.deleteLast();
		l1.addLast(80);
		l1.addAfter(80, 8);
		l1.display();
		l1.deleteAfter(80);
		l1.addBefore(80, 70);
		l1.addFirst(-1);
		l1.deleteBefore(1);
		l1.addAt(4, -40);
		l1.deleteAt(1);
		l1.replace(80, 50);
		l1.display();
	}
	catch (const std::exception &e)
	{
		std::cerr << "ERROR : " << e.what() << '\n';
	}
	return 0;
}