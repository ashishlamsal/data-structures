#include <iostream>
#include <exception>

template <typename T>
class LinkedList
{
private:
	class Node {
	public:
		T value;
		Node* next;
		Node(const T& value) :value(value), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	int count;

private:
	bool isEmpty(){
		return head == nullptr;
	}

public:
	LinkedList();
	~LinkedList();
	void addLast(const T&);
	void addFirst(const T&);
	void addAfter(const T&, const T&);
	void addBefore(const T&, const T&);
	void deleteFirst();
	void deleteLast();
	void deleteAfter(const T&);
	int indexOf(const T&);
	bool contains(const T&);
	int size();
	T* toArray();
	void reversed();
	void display();
};

template <typename T> LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T> LinkedList<T>::~LinkedList() {
	Node* current = start;
	while (head != nullptr)
	{
		current = head->next;
		delete head;
		head = current;
	}
	tail = nullptr;
}

template <typename T> void LinkedList<T>::addLast(const T& item) {
	Node* node = new Node(item);

	if (isEmpty())
		head = tail = node;
	else {						// at least one element
		tail->next = node;
		tail = node;
	}
	count++;
}

template <typename T> void LinkedList<T>::addFirst(const T& item) {
	Node* node = new Node(item);

	if (isEmpty())
		head = tail = node;
	else {						// at least one element
		node->next = head;
		head = node;
	}
	count++;
}

template <typename T> void LinkedList<T>::addAfter(const T& item1, const T& item2) {
	Node* previous = head;
	Node* current = previous->next;

	while (previous->value != item1)
	{
		if (current == nullptr) {
			std::cout << item1 << " not found in the list" << std::endl;
			return;
		}
		previous = current;
		current = current->next;
	}

	Node* node = new Node(item2);

	if (previous == tail) {			// after last node
		previous->next = node;
		tail = node;
	}
	else {
		node->next = current;
		previous->next = node;
	}

	count++;
}

template <typename T> void LinkedList<T>::addBefore(const T& item1, const T& item2) {
	Node* previous = head;
	Node* current = previous;

	while (current->value != item1)
	{
		previous = current;
		current = current->next;
		if (current == nullptr) {
			std::cout << item1 << " not found in the list" << std::endl;
			return;
		}
	}

	Node* node = new Node(item2);

	node->next = current;
	if (current == head)			// add before first node
		head = node;
	else 
		previous->next = node;

	count++;
}

template <typename T> void LinkedList<T>::deleteFirst() {
	if (isEmpty())
		throw std::runtime_error("UnderFlow");
	
	Node* ptr = head;
	if (head == tail)
		head = tail = nullptr;
	else 
		head = head->next;
	delete ptr;
	count--;
}

template <typename T> void LinkedList<T>::deleteLast() {
	if (isEmpty())
		throw std::runtime_error("UnderFlow");

	Node* ptr = head;
	if (head == tail)
		head = tail = nullptr;

	else {
		while (ptr->next != tail)
			ptr = ptr->next;
		tail = ptr;
		ptr = ptr->next;
		tail->next = nullptr;
	}
	delete ptr;
	count--;
}

template <typename T> void LinkedList<T>::deleteAfter(const T& item1) {
	if (isEmpty())
		throw std::runtime_error("UnderFlow");

	Node* previous = head;
	Node* current = previous->next;

	while (previous->value != item1)
	{
		if (current == nullptr) {
			std::cout << item1 << " not found in the list" << std::endl;
			return;
		}
		previous = current;
		current = current->next;
	}

	if (previous == tail) {		// error : delete after last element
		std::cout << "Nothing to delete after " << item1 << std::endl;
		return;
	}
	if (current == tail)		// delete last element
		tail = previous;

	previous->next = current->next;
	delete current;

	count--;
}

template <typename T> int LinkedList<T>::indexOf(const T& item) {
	int index = 0;
	Node* ptr = head;
	while (ptr != nullptr)
	{
		if (ptr->value == item) return index;
		ptr = ptr->next;
		index++;
	}
	return -1;
}

template <typename T> bool LinkedList<T>::contains(const T& item) {
	return indexOf(item) != -1;
}

template <typename T> int LinkedList<T>::size() {
	return count;
}

template <typename T> T* LinkedList<T>::toArray() {
	T* array = new T[count + 1];

	Node* ptr = head;
	int index = 0;
	while (ptr != nullptr)
	{
		array[index++] = ptr->value;
		ptr = ptr->next;
	}
	array[index] = '\0';
	return array;
}

template <class T> void LinkedList<T>::reversed() {
	Node* previous = head;
	Node* current = previous->next;
	
	tail = head;
	tail->next = nullptr;

	while (current != nullptr)
	{
		Node* after = current->next;
		current->next = previous;
		previous = current;
		current = after;
	}

	head = previous;
}

template <class T> void LinkedList<T>::display() {
	Node* ptr = head;
	std::cout << "[ ";
	while (ptr != nullptr)
	{
		std::cout << ptr->value << " ";
		ptr = ptr->next;
	}
	std::cout << "]" << std::endl;
}

int main() {
	try	{
		LinkedList<int> l1;
		l1.addLast(4);
		l1.addLast(5);
		l1.addFirst(1);
		l1.addFirst(0);
		//l1.deleteFirst();
		l1.addFirst(2);
		//l1.deleteLast();
		l1.addAfter(2, 8);
		l1.deleteAfter(4);
		l1.addLast(80);
		//l1.addBefore(2,70);
		//l1.addFirst(-1);
		l1.display();
		std::cout << "Size = " << l1.size() << std::endl;
		//std::cout << "Reversed List = ";
		//l1.reversed();
		//l1.display();

		// linked list to array
		/*int* arr = l1.toArray();
		for (size_t i = 0; i < l1.size(); i++)
		{
			std::cout << arr[i] << std::endl;
		};
		delete arr;*/
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR : " << e.what() << '\n';
	}
	return 0;
}