#include <list>
#include <unordered_map>
#include <iostream>
using namespace std;

// ------------------------------------------------------------------------------------------------
// Class Node
// ------------------------------------------------------------------------------------------------
class Node
{
private:
    int _data;
    Node* _next;
    Node* _prev;

public:
    Node(int data);
    int getData();
};

Node::Node(int data) :
      _data(data),
      _next(nullptr),
      _prev(nullptr)
{ }

int
Node::getData()
{
    return _data;
}

// ------------------------------------------------------------------------------------------------
// Class DoublyList
// ------------------------------------------------------------------------------------------------
class DoublyList
{
private:
    friend class Node;
    Node* _head;
    Node* _tail;
    size_t _length;

public:
    void pushFront();
    void pushBack();
    void popFront();
    void popBack();
    void insertAfter(Node*);
    void removeNode(Node*);

    size_t getlength() { return _length; };
};

// ------------------------------------------------------------------------------------------------
// Class LRUCache
// ------------------------------------------------------------------------------------------------
class LRUCache
{
private:
    friend class Node;
    int _capacity;
    DoublyList* _pDoublyList;
    unordered_map<int, Node* > _lruMap;

    void pushToFront(Node*);
    void deleteNode(Node*);
    Node* getNode(int data);

public:
    LRUCache(int capacity);
    int get(int key);
    void set(int key, int value);
};

LRUCache::LRUCache(int capacity) :
          _capacity(capacity)
{ }

int
LRUCache::get(int key)
{
    return 0;
}

void
LRUCache::set(int key, int value)
{
    
}

// ------------------------------------------------------------------------------------------------
// Main Function
// ------------------------------------------------------------------------------------------------
int main()
{
    LRUCache lruCache(5);

    std::cout << "\n";
    return 0;
}
