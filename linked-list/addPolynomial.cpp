// 3.	REPRESENT THE POLYNOMIAL EQUATION USING LINKED LIST TO PERFORM ADDITION OF TWO POLYNOMIALS
# include <iostream>

class Polynomial {
private:
	class Node {
	public:
		int coeff;
		int power;
		Node* next;

		Node(int coeff, int power) :coeff(coeff), power(power), next(NULL) {}
	};

	Node* head;
	Node* tail;
public:
	Polynomial();
	~Polynomial();
	void insertLast(const int&, const int&);
	void addPoly(Polynomial&, Polynomial&);
	void display();
};

Polynomial::Polynomial() :head(NULL), tail(NULL) {}

Polynomial::~Polynomial() {
	Node* ptr = head;

	while (head != NULL) {
		ptr = head;
		head = head->next;

		delete ptr;
	}
	tail = NULL;
}

void Polynomial::insertLast(const int& coeff, const int& power) {
	Node* node = new Node(coeff, power);

	if (head == NULL)
		head = tail = node;
	else {						// at least one element
		tail->next = node;
		tail = node;
	}
}

void Polynomial::addPoly(Polynomial& p1, Polynomial& p2) {
	Node* ptr1 = p1.head;
	Node* ptr2 = p2.head;

	while (ptr1 != NULL && ptr2 != NULL)
	{
		if (ptr1->power > ptr2->power) {
			this->insertLast(ptr1->coeff, ptr1->power);
			ptr1 = ptr1->next;
		}
		else if (ptr2->power > ptr1->power) {
			this->insertLast(ptr2->coeff, ptr2->power);
			ptr2 = ptr2->next;
		}
		else {
			this->insertLast(ptr1->coeff + ptr2->coeff, ptr1->power);
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
	}

	Node* ptrr = NULL;
	if (ptr1 != NULL) { ptrr = ptr1; }
	if (ptr2 != NULL) { ptrr = ptr2; }

	while (ptrr != NULL)
	{
		this->insertLast(ptrr->coeff, ptrr->power);
		ptrr = ptrr->next;
	}
}

void Polynomial::display() {
	Node* ptr = head;
	while (ptr != NULL)
	{
		std::cout << ptr->coeff << "x^" << ptr->power << " + ";
		ptr = ptr->next;
	}
	std::cout << "\b\b " << std::endl;
}

int main() {
	Polynomial p1, p2, p3;

	// insert coefficient and power for polynomial 1
	p1.insertLast(4, 6);
	p1.insertLast(3, 5);
	p1.insertLast(5, 0);

	// insert coefficient and power for polynomial 2
	p2.insertLast(2, 8);
	p2.insertLast(4, 5);
	p2.insertLast(8, 2);

	p3.addPoly(p1, p2);

	p1.display();
	p2.display();
	std::cout << "Sum: \n";
	p3.display();

	return 0;
}





