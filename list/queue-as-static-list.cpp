//2.	WAP TO REPRESENT QUEUE AS A LIST.
#include <iostream>

using namespace std;

const int NUMNODES = 10;
int avail = 0;

struct Node
{
    int data;
    int next;
} node[NUMNODES];

class Queue
{
private:
    int front;
    int rear;

public:
    Queue()
    {
        rear = front = -1;
    }

    bool isEmpty()
    {
        return front == -1;
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

    void insert(int item)
    {
        int q = getnode();
        node[q].data = item;
        node[q].next = -1;

        if (isEmpty())
            front = rear = q;
        else
        {
            node[rear].next = q;
            rear = q;
        }
    }

    void remove()
    {
        if (isEmpty())
        {
            cout << "Underflow" << endl;
            exit(1);
        }
        int p = front;
        if (front == rear)
            front = rear = -1;
        else
            front = node[front].next;
        node[p].data = 0; // for visualization only
        freenode(p);
    }

    void display()
    {
        int ptr = front;
        cout << "FRONT=" << front << " | "
             << "REAR=" << rear;
        cout << " [ ";
        while (ptr != -1)
        {
            cout << node[ptr].data << " ";
            ptr = node[ptr].next;
        }
        cout << "]" << endl;
    }
};

int main()
{
    for (int i = 0; i < NUMNODES - 1; i++)
        node[i].next = i + 1;
    node[NUMNODES - 1].next = -1;

    Queue q1, q2;
    q1.insert(100);
    q1.insert(200);
    q1.insert(300);
    q1.remove();
    q1.insert(600);
    q1.insert(700);
    q1.remove();

    q2.insert(150);
    q2.insert(250);
    q2.insert(350);
    q2.remove();
    q2.insert(450);

    for (int i = 0; i < NUMNODES; i++)
    {
        cout << "i= " << i << " | " << node[i].data << " next=" << node[i].next << endl;
    }

    cout << "Queue 1 : ";
    q1.display();
    cout << "Queue 2 : ";
    q2.display();

    return 0;
}