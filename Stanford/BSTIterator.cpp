#include <iostream>
#include <stack>
using namespace std;

// http://www2.lawrence.edu/fast/GREGGJ/CMSC270/tree_iterators.html
// http://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec3/lec3.pdf
// http://codereview.stackexchange.com/questions/61671/binary-search-tree-c-implementation
class Node
{
    public:
        int _data;
        Node* _left;
        Node* _right;
        Node* _parent;

        Node() : _left(nullptr),
                 _right(nullptr),
                 _parent(nullptr),
                 _data(0) { }
                 
        Node(int data) : _left(nullptr),
                         _right(nullptr),
                         _parent(nullptr),
                         _data(data) { }

        int getData() { return _data; }
        int getParentData()
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
};

class BSTIterator
{
    private:
        Node* _cur;

    public:
        BSTIterator(Node* root) : _cur(root) { }

        BSTIterator operator++();
        int operator*();
        bool operator!=(const BSTIterator& comp);

        // IMP: Return by reference
        Node*& getCurrent()
        {
            return _cur;
        } 
};

int
BSTIterator::operator*()
{
    return _cur->getData();
}

bool
BSTIterator::operator!=(const BSTIterator& comp)
{
    return _cur == comp._cur;
}

BSTIterator
BSTIterator::operator++ ()
{
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
        while (tmp->_right == node)
        {
            node = tmp;
            tmp = tmp->_parent;
        }

        if (tmp->_left == node)
        {
            node = tmp;
        }
    }
    else
    {
        cout << "8. " << node->getData() << endl;
        //return nullptr;
    }

    //return node;    
    return *this;
}

class BST
{
    private:
        Node* _root;
        size_t _length;

    public:
        bool isPresent(const int data);
        void insert(const int data);
        bool remove(const int data);
        void printInorderIterative();
        BSTIterator begin();
        BSTIterator end();

        size_t getLength() { return _length; }

        BST() : _root(nullptr),
                _length(0) { }

        ~BST() { delete _root; }

        Node* getRoot()
        {
            cout << "0. " << _root->getData() << endl;
            return _root;
        }
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
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;
        ++bsi;
        cout << "ITER: " << *bsi << endl;

        BSTIterator bse = root->end();
        cout << "End ITER: " << *bse << endl;
    }

    cout << endl;
    return 0;
}
