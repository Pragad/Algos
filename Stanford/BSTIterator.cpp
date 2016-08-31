#include <iostream>
#include <cassert>  // assert
#include <stack>
using namespace std;

// http://www2.lawrence.edu/fast/GREGGJ/CMSC270/tree_iterators.html
// http://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec3/lec3.pdf
// http://codereview.stackexchange.com/questions/61671/binary-search-tree-c-implementation
// ----------------------------------------------------------------------------------------------
// Class Node
// ----------------------------------------------------------------------------------------------
class Node
{
    // Everything is private as User should not have access to Node
    private:
        int _data;
        Node* _left;
        Node* _right;
        Node* _parent;
        friend class BSTIterator;
        friend class BST;

        Node();
        Node(int data);

        int getData();
        int getParentData();
};

Node::Node() : _left(nullptr),
               _right(nullptr),
               _parent(nullptr),
               _data(0) { }
                 
Node::Node(int data) : _left(nullptr),
                       _right(nullptr),
                       _parent(nullptr),
                       _data(data) { }

int
Node::getData()
{
    return _data;
}

int
Node::getParentData()
{
    if (_parent != nullptr)
    {
        return _parent->_data;
    }
    else
    {
        return 0;
    }
}

// ----------------------------------------------------------------------------------------------
// Class BSTIterator:
//      This is the iterator for the BST
// ----------------------------------------------------------------------------------------------
class BSTIterator
{
    private:
        Node* _cur;

        // IMP: Return by reference
        Node*& getCurrent();

    public:
        BSTIterator(Node* root) : _cur(root) { }

        int operator * () const;
        int operator -> () const;
        bool operator != (const BSTIterator& rhs) const;
        bool operator == (const BSTIterator& rhs) const;
        BSTIterator operator ++ ();
        BSTIterator operator ++ (int); // Post Increment
};

int
BSTIterator::operator * () const
{
    assert(_cur != nullptr && "Dereferencing NULL Iterator");
    return _cur->getData();
}

int
BSTIterator::operator -> () const
{
    assert(_cur != nullptr && "Dereferencing NULL Iterator");
    return _cur->getData();
}

bool
BSTIterator::operator != (const BSTIterator& rhs) const
{
    return _cur != rhs._cur;
}

bool
BSTIterator::operator == (const BSTIterator& rhs) const
{
    return _cur == rhs._cur;
}

Node*&
BSTIterator::getCurrent()
{
    return _cur;
} 

BSTIterator
BSTIterator::operator ++ ()
{
    assert(_cur != nullptr && "Increment on NULL Iterator");
    Node*& node = getCurrent();

    if (node->_right != nullptr)
    {
        node = node->_right;

        while (node->_left != nullptr)
        {
            node = node->_left;
        }
    }
    else if(node->_parent != nullptr)
    {
        Node* tmp = node->_parent;

        // IMP: Make sure tmp is not NULL
        while (tmp != nullptr && tmp->_right == node)
        {
            node = tmp;
            tmp = tmp->_parent;
        }

        if (tmp != nullptr && tmp->_left == node)
        {
            node = tmp;
        }

        // IMP: Make the node point to NULL when we don't have SUCCESSOR
        else if (tmp == nullptr)
        {
            node = nullptr;
        }
    }
    else
    {
        node = nullptr;
    }

    return *this;
}

BSTIterator
BSTIterator::operator ++ (int)
{
    BSTIterator tmp(*this);
    operator++();   // Perform Prefix Increment
    return tmp;     // Return value before Increment
}

// ----------------------------------------------------------------------------------------------
// Class BST:
//      This is the Binary Search Tree data structure
// ----------------------------------------------------------------------------------------------
class BST
{
    private:
        Node* _root;
        size_t _length;

    public:
        BST() : _root(nullptr),
                _length(0) { }

        ~BST() { delete _root; }

        bool isPresent(const int data);
        void insert(const int data);
        bool remove(const int data);
        void printInorderIterative();
        BSTIterator begin();
        BSTIterator end();

        size_t getLength() { return _length; }
        Node* getRoot() { return _root; }
};

BSTIterator
BST::begin()
{
    Node* tmpRoot = _root;
    // Instead of returning root, we should returning the smallest element
    while (tmpRoot->_left != nullptr)
    {
        tmpRoot = tmpRoot->_left;
    }

    return BSTIterator(tmpRoot);
}

BSTIterator
BST::end()
{
    Node* tmpRoot = _root;
    while(tmpRoot->_right != nullptr)
    {
        tmpRoot = tmpRoot->_right;
    }

    return BSTIterator(tmpRoot);
}

bool
BST::isPresent(const int data)
{
    Node* itr = _root;
    while(itr != nullptr)
    {
        if (itr->getData() > data)
        {
            itr = itr->_left;
        }
        else if (itr->getData() < data)
        {
            itr = itr->_right;
        }
        else
        {
            return true;
        }
    }

    return false;
}

void
BST::insert(const int data)
{
    Node* tmp = new Node(data);

    if (_root == nullptr)
    {
        _root = tmp;
        ++_length;

        return;
    }
    else
    {
        Node* curNode = _root;

        while (curNode)
        {
            if (curNode->getData() < data)
            {
                if (curNode->_right == nullptr)
                {
                    curNode->_right = tmp;
                    tmp->_parent = curNode;
                    ++_length;
                    return;
                }
                curNode = curNode->_right;
            }
            else if (curNode->getData() >= data)
            {
                if (curNode->_left == nullptr)
                {
                    curNode->_left = tmp;
                    tmp->_parent = curNode;
                    ++_length;
                    return;
                }
                curNode = curNode->_left;
            }
        }
    }
}

bool
BST::remove(const int data)
{
    return false;
}

void
BST::printInorderIterative()
{
    stack<Node*> recStack;

    if (_root == nullptr)
    {
        return;
    }

    do
    {
        if (_root != nullptr)
        {
            recStack.push(_root);

            while (_root->_left != nullptr)
            {
                recStack.push(_root->_left);
                _root = _root->_left;
            }
        }

        _root = recStack.top();
        recStack.pop();
        cout << _root->getData() << " : " << _root->getParentData() << " , ";

        _root = _root->_right;
    } while (!recStack.empty() || _root != nullptr);

    cout << endl;
}

int main()
{
    {
        cout << "Binary Search Tree" << endl;

        BST* root = new BST();
        root->insert(10);

        // Level 1
        root->insert(5);
        root->insert(15);

        // Level 2
        root->insert(2);
        root->insert(7);
        root->insert(12);
        root->insert(17);

        // Level 3
        root->insert(1);
        root->insert(3);
        root->insert(6);
        root->insert(8);
        root->insert(11);
        root->insert(13);
        root->insert(16);
        root->insert(18);

        BSTIterator bsi = root->begin();

        //while (bsi != root->end())
        while (bsi != nullptr)
        {
            cout << "ITER: " << *bsi << endl;
            ++bsi;
        }

        /*
        cout << "ITER: " << *bsi << endl;
        bsi++;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        bsi++;
        cout << "ITER: " << *bsi << endl;
        bsi++;
        cout << "ITER: " << *bsi << endl;
        bsi++;
        cout << "ITER: " << *bsi << endl;
        */

        BSTIterator bse = root->end();
        cout << "End ITER: " << *bse << endl;
    }

    cout << endl;
    return 0;
}
