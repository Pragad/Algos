// Pragadheesh Thiru
// Implementation of Dequeue

// Dequeue should be able to,
//  1. Push at the front as well as rear.
//  2. Pop from the front as well as rear.
//
// I have implemented this using linked lists, so that it can grow as long as we have enough
// memory.
//
// Also I have created it using template so we can use this for any data types.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
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
};

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
void DeQueue<T>::enqueueFront(T data)
{
    Node* temp = new Node(data);
    temp->_next = _head;

    // Check if it is the first node
    if (_head == nullptr)
    {
        _tail = temp;
    }
    else
    {
        _head->_prev = temp;

        // If there is just one node, then adjust the tail pointer as well.
        // IS THIS REQUIRED AS HEAD IS SAME AS TAIL.
        if (_head == _tail)
        {
            _tail->_prev = temp;
        }
    }

    _head = temp;
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
void DeQueue<T>::enqueueRear(T data)
{
    Node* temp = new Node(data);
    temp->_prev = _tail;

    // Check if it is the first node
    if (_tail == nullptr)
    {
        _head = temp;
        _tail = temp;
    }
    else
    {
        _tail->_next = temp;
        _tail = _tail->_next;

        // If there is just one node, then adjust the head pointer as well.
        // IS THIS REQUIRED AS HEAD IS SAME AS TAIL.
        if (_head == _tail)
        {
            _head->_next = temp;
        }
    }
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
T DeQueue<T>::dequeueFront()
{
    // TODO: Handle proper returning when _tail is null
    // This can be handled by using a wrapper function
    // Right now the caller should call this function my making sure the dequeue is not empty.
    // Else a garbage value will be returned.
    Node* tmp = _head;
    T tmpData = tmp->getData();

    if (_head != nullptr)
    {
        // Set the prev pointer of next node to null
        // Check if we have at least two nodes. Else, delete the single node
        if (_head->_next != nullptr)
        {
            _head = _head->_next;
            _head->_prev = nullptr;
        }

        // Delete the first node
        delete tmp;
    }
    else
    {
        cout << "Dequeue Front: List is empty" << endl;
    }
    return tmpData;
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
T DeQueue<T>::dequeueRear()
{
    // TODO: Handle proper returning when _tail is null
    // This can be handled by using a wrapper function
    // Right now the caller should call this function my making sure the dequeue is not empty.
    // Else a garbage value will be returned.
    Node* tmp = _tail;
    T tmpData = tmp->getData();

    if (_tail != nullptr)
    {
        // Set the next pointer of prev node to null
        // Check if we have at least two nodes. Else, delete the single node
        if (_tail->_prev != nullptr)
        {
            _tail = _tail->_prev;
            _tail->_next = nullptr;
        }

        // Delete the last node
        delete tmp;
    }
    else
    {
        cout << "Dequeue Rear: List is empty" << endl;
    }

    return tmpData;
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
void DeQueue<T>::printDeQueue()
{
    cout << endl << "Dequeue: ";
    Node* temp = _head;
    while(temp != _tail)
    {
        cout << temp->getData() << " ";
        temp = temp->_next;
    }

    // Print the last element;
    cout << temp->getData() << endl;
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
bool DeQueue<T>::isEmpty()
{
    return (_head == NULL && _tail == NULL);

}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
int main()
{
    DeQueue<int> *myIntDeque = new DeQueue<int>();

    myIntDeque->enqueueFront(5);
    myIntDeque->enqueueFront(6);
    myIntDeque->enqueueFront(7);
    myIntDeque->enqueueRear(4);
    myIntDeque->enqueueRear(3);
    myIntDeque->printDeQueue();
    cout << "Deque Rear: " << myIntDeque->dequeueRear() << endl;
    cout << "Deque Rear: " << myIntDeque->dequeueRear() << endl;
    myIntDeque->printDeQueue();
    cout << "Deque Front: " << myIntDeque->dequeueFront() << endl;
    cout << "Deque Front: " << myIntDeque->dequeueFront() << endl;
    cout << "Is Deque Empty: " << myIntDeque->isEmpty() << endl;
    myIntDeque->printDeQueue();

    cout << endl;
    return 0;
}
