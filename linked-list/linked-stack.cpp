// 1.	IMPLEMENT STACK AS LINKED LIST
#include <iostream>

template <class T>
class Stack {
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(const T& data) :data(data), next(NULL) {}
    };
    Node* top;

public:
    Stack();
    ~Stack();
    bool isEmpty();
    void push(const T&);
    T pop();
    void display();
};

template <class T>Stack<T>::Stack() :top(NULL) {}

template <class T>Stack<T>::~Stack() {
	Node* ptr = top;

	while (top != NULL) {
		ptr = top;
		top = top->next;
		delete ptr;
	}
}

template <class T> bool Stack<T>::isEmpty() {
    return top == NULL;
}

template <class T> void Stack<T>::push(const T& item) {
    Node* node = new Node(item);

    node->next = top;
    top = node;
}

template <class T> T Stack<T>::pop() {
    if (isEmpty()) {
        std::cout << "ERROR: Underflow" << std::endl;
        exit(1);
    }

    Node* ptr = top;
    T value = ptr->data;
    top = top->next;
    delete ptr;
    return value;
}

template <class T> void Stack<T>::display() {
	Node* ptr = top;

	std::cout << "STACK : [ ";
	while (ptr != NULL)
	{
		std::cout << ptr->data << " ";
		ptr = ptr->next;
	}
	std::cout << "]" << std::endl;
}

int main() {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.display();
    std::cout << "Popping : " << s.pop() << std::endl;
    std::cout << "Popping : " << s.pop() << std::endl;
    s.push(50);
    s.display();

    return 0;
}

