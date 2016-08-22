#include <iostream>
#include <stack>
using namespace std;

// http://codereview.stackexchange.com/questions/61671/binary-search-tree-c-implementation
class BST
{
    private:
        class Node; // Forward declaration
        Node* _root;
        size_t _length;

        class Node
        {
            public:
                int _data;
                Node* _left;
                Node* _right;

                Node() : _left(nullptr),
                         _right(nullptr),
                         _data(0) { }
                         
                Node(int data) : _left(nullptr),
                                 _right(nullptr),
                                 _data(data) { }

                int getData() { return _data; }
        };

    public:
        bool isPresent(const int data);
        void insert(const int data);
        bool remove(const int data);
        void printInorder();

        size_t getLength() { return _length; }

        BST() : _root(nullptr),
                _length(0) { }

        ~BST() { delete _root; }
};

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
BST::printInorder()
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
        cout << _root->getData() << ", ";

        _root = _root->_right;
    } while (!recStack.empty() || _root != nullptr);

    cout << endl;
}

int main()
{
    {
        cout << "Binary Search Tree" << endl;

        BST* root = new BST();
        root->insert(5);
        cout<< "Len: " << root->getLength() << endl;
        root->insert(6);
        root->insert(2);
        root->insert(8);
        cout<< "Len: " << root->getLength() << endl;
        root->printInorder();
    }

    cout << endl;
    return 0;
}
