#include <iostream>

const int MAXNODES =10;

template <class T>
class ArrayList
{
private:
    T* list;
    int count;
    int pos;
public:
    ArrayList();
    ~ArrayList();
    void insert(const T&);
    void insert(const T&, int pos);
    T remove();
    T remove(int pos);
    bool isFull();
    bool isEmpty();
    void display();
};

template <class T> ArrayList<T>::ArrayList()
{
    count = 0;
    pos = 0;
    list = new T[MAXNODES];
}

template <class T> ArrayList<T>::~ArrayList()
{
    delete[] list;
}

template <class T> bool ArrayList<T>::isEmpty() {
    return count == 0;
}

template <class T> bool ArrayList<T>::isFull() {
    return count == MAXNODES;
}

template <class T> void ArrayList<T>::insert(const T& data, int pos) {
    if (isFull())
        throw "Overflow";
    if (pos < 0 || pos > count)
        throw "Index out of Range";

    for (int i = count; i > pos; i--)
        list[i] = list[i-1];

    list[pos] = data;
    count++;
}

template <class T> void ArrayList<T>::insert(const T& data) {
    if (isFull())
        throw "Overflow";

    list[count++] = data;
}

template <class T> T ArrayList<T>::remove(int pos) {
    if (isEmpty())
        throw "Underflow";
    if (pos < 0 || pos >= count)
        throw "Index out of Range";

    T item = list[pos];
    for (int i = pos; i < count - 1; i++)
        list[i] = list[i+1];

    list[count - 1] = 0;
    count--;
    return item;
}

template <class T> T ArrayList<T>::remove() {
    if (isEmpty())
        throw "Void Deletion";

    T item = list[count - 1];
    list[count -1] = 0;
    count--;
    return item;
}

template <class T> void ArrayList<T>::display() {
    std::cout << "[ ";
	for (int i =0; i < count; i++)
	{
		std::cout << list[i] << " ";
	}
	std::cout << "]" << std::endl;
}


int main() {
    try
    {
        ArrayList<int> l1;
        l1.insert(1);
        l1.insert(2);
        l1.insert(3);
        l1.insert(4);
        std::cout << "Removing from last: " <<l1.remove()<< std::endl;
        l1.insert(8,2);
        l1.insert(80,4);
        l1.insert(90,5);
        std::cout << "Removing: " << l1.remove(4) << std::endl;
        std::cout << "Removing: " << l1.remove(2) << std::endl;
        l1.display();
    }
    
    catch(const char* e)
    {
        std::cerr << e << '\n';
    }
    return 0;
}