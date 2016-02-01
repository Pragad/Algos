#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <stdlib.h>
using namespace std;

template <class T>
class DeQueue
{
private:
    class Node
    {
    public:
        T       _data;
        Node*   _prev;
        Node*   _next;

        Node(T data) : _data(data),
                       _prev(nullptr),
                       _next(nullptr) { }

        T getData() { return _data; }
    };

private:
    Node* _head;
    Node* _tail;

public:
    DeQueue() : _head(nullptr),
                _tail(nullptr) { }

    void enqueueFront(T data);
    void enqueueRear(T data);
    T dequeueFront();
    T dequeueRear();
    bool isEmpty();
    void printDeQueue();
    //Node* getFirst() { return _head; }
    //Node* getLast() { return _tail; }
};

template <class T>
void DeQueue<T>::enqueueFront(T data)
{
    Node* temp = new Node(data);
    temp->next = _head;

    _head->prev = temp;
    _head = temp;
}

template <class T>
void DeQueue<T>::enqueueRear(T data)
{
    Node* temp = new Node(data);
    temp->prev = _tail;

    _tail->next = temp;
    _tail = _tail->next;
}

template <class T>
T DeQueue<T>::dequeueFront()
{
    return _head->getData();
}

template <class T>
T DeQueue<T>::dequeueRear()
{
    return _tail->getData();
}

template <class T>
void DeQueue<T>::printDeQueue()
{
    Node* temp = _head;
    while(temp != _tail)
    {
        cout << temp->getData() << " ";
        temp = temp->next;
    }

    // Print the last element;
    cout << _head->getData() << endl;
}

template <class T>
bool DeQueue<T>::isEmpty()
{
    return (_head == NULL && _tail == NULL);

}

int main()
{


    cout << endl;
    return 0;
}
