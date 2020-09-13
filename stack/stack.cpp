#include <iostream>
using namespace std;

const int STACKSIZE = 20;

template <class T>
class stack
{
private:
	int top;
	T *nodes;

public:
	stack();
	bool empty();
	void push(T &);
	T pop();
	T peek();
	void display();
	int size();
	~stack();
};

template <class T>
stack<T>::stack()
{
	top = -1;
	nodes = new T[STACKSIZE];
}

template <class T>
bool stack<T>::empty()
{
	return top == -1;
}

template <class T>
void stack<T>::push(T &j)
{
	if (top == STACKSIZE - 1)
	{
		cout << "Stack overflow" << endl;
		exit(1);
	}
	nodes[++top] = j;
}

template <class T>
T stack<T>::pop()
{
	if (empty())
	{
		cout << "Stack underflow" << endl;
		exit(1);
	}
	return nodes[top--];
}

template <class T>
T stack<T>::peek()
{
	if (empty())
	{
		cout << "Stack is empty" << endl;
		exit(1);
	}
	return nodes[top];
}

template <class T>
void stack<T>::display()
{
	cout << "Stack : ";
	for (int i = 0; i <= top; i++)
	{
		cout << nodes[i] <<" ";
	}
	cout << endl;
}

template <class T>
int stack<T>::size() 
{
	return (top + 1);
}

template <class T>
stack<T>::~stack()
{
	delete[] nodes;
}

int main()
{
	stack<int> s1;
	int a = 2, b = 4;
	s1.push(a);
	s1.push(b);
	s1.display();
	cout << s1.peek() << endl;
	s1.pop();
	cout << "size of stack: " << s1.size()<< endl;
	s1.pop();
	cout << s1.peek() << endl;
	return 0;
}