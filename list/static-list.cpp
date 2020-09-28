// 1.	WAP TO INSERT AND DELETE IN A LIST.
#include <iostream>

using namespace std;

const int NUMNODES = 10;
int avail = 0;

struct Node
{
	int data;
	int next;
} node[NUMNODES];

class List
{
private:
	int start;

public:
	List() : start(-1) {}

	bool isEmpty()
	{
		return start == -1;
	}

	int getnode()
	{
		if (avail == -1)
		{
			cout << "Overflow" << endl;
			exit(1);
		}
		int p = avail;
		avail = node[avail].next;
		return p;
	}

	void freenode(int p)
	{
		node[p].next = avail;
		avail = p;
	}

	void insertFirst(int item)
	{
		int q = getnode();
		node[q].data = item;
		node[q].next = start;
		start = q;
	}

	void insertLast(int item)
	{
		int q = getnode();
		node[q].data = item;
		node[q].next = -1;

		int ptr = start;
		if (isEmpty())
			start = q;
		else
		{
			while (node[ptr].next != -1) // traverse to end of list
				ptr = node[ptr].next;
			node[ptr].next = q;
		}
	}

	void insertAfter(int value, int item)
	{
		if (isEmpty())
		{
			cout << "Error: Attempt to insert after " << value << " in a empty list" << endl;
			return;
		}

		int preptr = start;
		int ptr = node[preptr].next;
		while (node[preptr].data != value)
		{
			if (ptr == -1)
			{
				cout << "Void insertion : " << value << " not found in the list" << endl;
				return;
			}
			preptr = ptr;
			ptr = node[ptr].next;
		}
		int q = getnode();
		node[q].data = item;

		node[q].next = ptr;
		node[preptr].next = q;
	}

	void deleteFirst() {
		if (isEmpty()) {
			cout << "Underflow" << endl;
			exit(1);
		}

		int ptr = start;
		start = node[start].next;
		node[ptr].data =0;
		freenode(ptr);
	}

	void deleteLast() {
		if (isEmpty()) {
			cout << "Underflow" << endl;
			exit(1);
		}

		int preptr = start;
		int ptr = node[preptr].next;
		if (ptr == -1) {		// only one node in list
			start = -1;
			node[preptr].data = 0;
			freenode(preptr);
		}
		else {
			while (node[ptr].next != -1) {
				preptr = ptr;
				ptr = node[ptr].next;
			}
			node[preptr].next = -1;
			node[ptr].data = 0;
			freenode(ptr);
		}
	}	

	void deleteAfter(int value)
	{
		if (isEmpty())
		{
			cout << "Underflow" << endl;
			exit(1);
		}
		int preptr = start;
		int ptr = node[preptr].next;
		while (node[preptr].data != value)
		{
			if (ptr == -1)
			{
				cout << "Void deletion : " << value << " not found in the list" << endl;
				return;
			}
			preptr = ptr;
			ptr = node[ptr].next;
		}
		if (ptr == -1)
		{
			cout << "Void deletion : "
				 << "Nothing to delete after " << value << endl;
			return;
		}
		node[preptr].next = node[ptr].next;
		node[ptr].data = 0;
		freenode(ptr);
	}

	void display()
	{
		int ptr = start;
		cout << "START=" << start;
		std::cout << " [ ";
		while (ptr != -1)
		{
			std::cout << node[ptr].data << " ";
			ptr = node[ptr].next;
		}
		std::cout << "]" << std::endl;
	}
};

int main()
{
	for (int i = 0; i < NUMNODES - 1; i++)
		node[i].next = i + 1;
	node[NUMNODES - 1].next = -1;

	List l1;
	l1.insertFirst(100);
	l1.insertFirst(300);
	l1.insertFirst(200);
	l1.insertLast(400);
	l1.insertLast(500);
	l1.insertAfter(400, 800);
	l1.deleteAfter(100);
	l1.insertAfter(300, 50);
	l1.deleteFirst();
	l1.deleteLast();
	l1.insertLast(600);

	List l2;
	l2.insertFirst(100);
	l2.insertFirst(300);

	for (int i = 0; i < NUMNODES; i++)
	{
		cout << "i= " << i << " | " << node[i].data << " next=" << node[i].next << endl;
	}

	cout << "List 1 : ";
	l1.display();
	cout << "List 2 : ";
	l2.display();
	return 0;
}