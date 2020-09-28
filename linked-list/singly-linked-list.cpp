//3. SINGLY LINEAR LINKED LIST

#include <iostream>
using namespace std;

template<class T>
class LinkedList
{
private:
	class Node {
	public:
		T data;
		Node* next;
		Node(const T& data) :data(data), next(NULL) {}
	};

	Node* start;

public:
	LinkedList();
	~LinkedList();
	bool isEmpty();
	void insertFirst(const T&);
	void insertLast(const T&);
	void insertAfter(const T&, const T&);
	void insertBefore(const T&, const T&);
	void deleteFirst();
	void deleteLast();
	void deleteAfter(const T&);
	void display();
};

template <class T> 
LinkedList<T>::LinkedList() :start(NULL) {}

template <class T> 
LinkedList<T>::~LinkedList()
{
	Node* ptr = start;
	while (start != NULL)
	{
		ptr = start->next;
		delete start;
		start = ptr;
	}
}

template <class T> 
bool LinkedList<T>::isEmpty() {
	return start == NULL;
}

template <class T> 
void LinkedList<T>::insertFirst(const T& item) {
	Node* node = new Node(item);

	node->next = start;
	start = node;
}

template <class T> 
void LinkedList<T>::insertLast(const T& item) {
	Node* node = new Node(item);

	Node* ptr = start;
	if (isEmpty())					// empty list
		start = node;
	else
	{
		while (ptr->next != NULL)	// traverse to end of list
			ptr = ptr->next;
		ptr->next = node;			
	}
}

template <class T> 
void LinkedList<T>::insertAfter(const T& value, const T& item) {
	if (isEmpty())
	{
		cout << "Error: Attempt to insert after " << value << " in a empty list" << endl;
		return;
	}

	Node* preptr = start;
	Node* ptr = preptr->next;
	while (preptr->data != value)
	{
		if (ptr == NULL) {
			cout << "Void insertion : " << value << " not found in the list" << endl;
			return;
		}
		preptr = ptr;
		ptr = ptr->next;
	}

	Node* node = new Node(item);
	node->next = ptr;
	preptr->next = node;
}

template <class T> 
void LinkedList<T>::insertBefore(const T& value,  const T& item) {
	if (isEmpty())
	{
		cout << "Error: Attempt to insert before " << value << " in a empty list" << endl;
		return;
	}

	Node* ptr = start;
	Node* preptr = ptr;
	while (ptr->data != value)
	{
		preptr = ptr;
		ptr = ptr->next;

		if (ptr == NULL) {
			cout << "Void insertion : " << value << " not found in the list" << endl;
			return;
		}
	}

	Node* node = new Node(item);
	node->next = ptr;
	if (preptr == ptr)		// insert before first node
		start = node;
	else
		preptr->next = node;
}

template <class T> 
void LinkedList<T>::deleteFirst() {
	if (isEmpty()) {
		cout << "Underflow" << endl;
		exit(1);
	}

	Node* ptr = start;
	start = start->next;
	delete ptr;
}

template <class T> 
void LinkedList<T>::deleteLast() {
	if (isEmpty()) {
		cout << "Underflow" << endl;
		exit(1);
	}

	Node* preptr = start;
	Node* ptr = preptr->next;
	if (ptr == NULL) {		// only one node in list
		start = NULL;
		delete preptr;
	}
	else {
		while (ptr->next != NULL) {
			preptr = ptr;
			ptr = ptr->next;
		}
		preptr->next = NULL;
		delete ptr;
	}
}

template <class T> 
void LinkedList<T>::deleteAfter(const T& value) {
	if (isEmpty()) {
		cout << "Underflow" << endl;
		exit(1);
	}
	Node* preptr = start;
	Node* ptr = preptr->next;
	while (preptr->data != value)
	{
		if (ptr == NULL) {
			cout << "Void deletion : " << value << " not found in the list" << endl;
			return;
		}
		preptr = ptr;
		ptr = ptr->next;
	}
	if (ptr == NULL) {
		cout << "Void deletion : " << "Nothing to delete after " << value << endl;
		return;
	}
	
	preptr->next = ptr->next;
	delete ptr;
}

template <class T> 
void LinkedList<T>::display() {
	Node* ptr = start;
	cout << "List : [ ";
	while (ptr != NULL)
	{
		cout << ptr->data << " ";
		ptr = ptr->next;
	}
	cout << "]" << endl;
}

int main() {
	LinkedList<int> l1;
	l1.insertLast(8);
	l1.insertLast(9);
	l1.insertFirst(3);
	l1.insertFirst(2);
	l1.display();
	l1.insertBefore(8, 5);
	l1.insertFirst(1);
	l1.insertAfter(3, 4);
	l1.insertLast(10);
	l1.display();
	l1.deleteFirst();
	l1.deleteAfter(3);
	l1.deleteLast();
	l1.display();
	return 0;
}