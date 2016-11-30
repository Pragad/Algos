// Pragadheesh Thiru
// Implementation of Fifoqueue

// Fifoqueue should be able to,
//  1. Push at the rear
//  2. Pop from the front
//
// Due to "push rear" and "pop rear" we can do it with a Singly LinkedList
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

    std::mutex _mtxFifoQueue;
    std::condition_variable _cvFifoQueue;
// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
class FifoQueue
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
    uint32_t _maxQueueSize;
    uint32_t _curQueueSize;

public:
    FifoQueue(uint32_t maxSize = 5) : _head(nullptr),
                                      _tail(nullptr),
                                      _maxQueueSize(maxSize)  { }

    void enqueueRear(T data);
    T dequeueFront();
    bool isEmpty();
    bool isFull();
    uint32_t getSize();
    void printFifoQueue();
};

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
void FifoQueue<T>::enqueueRear(T data)
{
    if (isFull())
    {
        return;
    }

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
    _curQueueSize++;
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
T FifoQueue<T>::dequeueFront()
{
    // TODO: Handle proper returning when _tail is null
    // This can be handled by using a wrapper function
    // Right now the caller should call this function my making sure the dequeue is not empty.
    // Else a garbage value will be returned.
    if (isEmpty())
    {
        return 0;
    }

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
        cout << "Fifoqueue Front: List is empty" << endl;
    }

    _curQueueSize--;
    return tmpData;
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
void FifoQueue<T>::printFifoQueue()
{
    cout << endl << "Fifoqueue: ";
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
bool FifoQueue<T>::isEmpty()
{
    return (_head == NULL && _tail == NULL);
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
bool FifoQueue<T>::isFull()
{
    return (_maxQueueSize == _curQueueSize);
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <class T>
uint32_t FifoQueue<T>::getSize()
{
    return _curQueueSize;
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
int main()
{
    FifoQueue<int> *myIntFifoque = new FifoQueue<int>();

    myIntFifoque->enqueueRear(5);
    myIntFifoque->enqueueRear(6);
    myIntFifoque->enqueueRear(7);
    myIntFifoque->enqueueRear(4);
    myIntFifoque->enqueueRear(3);
    myIntFifoque->printFifoQueue();
    cout << "Is Fifoque Full: " << myIntFifoque->isFull() << endl;
    cout << "Fifoque Rear: " << myIntFifoque->dequeueFront() << endl;
    cout << "Fifoque Rear: " << myIntFifoque->dequeueFront() << endl;
    myIntFifoque->printFifoQueue();
    cout << "Fifoque Front: " << myIntFifoque->dequeueFront() << endl;
    cout << "Fifoque Front: " << myIntFifoque->dequeueFront() << endl;
    cout << "Is Fifoque Empty: " << myIntFifoque->isEmpty() << endl;
    cout << "Fifoque Size: " << myIntFifoque->getSize() << endl;
    myIntFifoque->printFifoQueue();

    cout << endl;
    return 0;
}
