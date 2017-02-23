#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// http://codereview.stackexchange.com/questions/61671/binary-search-tree-c-implementation
// http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
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
        BST() : _root(nullptr),
                _length(0) { }

        ~BST() { delete _root; }

        bool isPresent(const int data);
        void insert(const int data);
        void balancedInsert(const int data);
        void balancedInsertRec(Node*& node, const int data);
        bool remove(const int data);
        int height(const Node* node);
        void printInorderIterative();
        void printLevelOrder();
        void rightRotate(Node*& node);
        void leftRotate(Node*& node);

        size_t getLength() { return _length; }
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

int
BST::height(const Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int lh = 1 + height(node->_left);
    int rh = 1 + height(node->_right);

    return max(lh, rh);
}

/*
a) Left Left Case
T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2

b) Left Right Case
     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2

c) Right Right Case

  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4

d) Right Left Case

   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3   

        x
    y
z   
 */
void
BST::rightRotate(Node*& node)
{
    Node* a = node->_left;
    Node* b = a->_right;

    a->_right = node;
    node->_left = b;

    node = a;
}

void
BST::leftRotate(Node*& node)
{
    Node* a = node->_right;
    Node* b = a->_left;

    a->_left = node;
    node->_right = b;

    node = a;
}

void
BST::balancedInsertRec(Node*& node, int data)
{
    // If ROOT is null, insert and give back the root
    if (node == nullptr)
    {
        node = new Node(data);
        ++_length;
        return;
    }

    // If data is greater, then it should be inserted on the right
    if (data > node->_data)
    {
        if (node->_right == nullptr)
        {
            node->_right = new Node(data);
            ++_length;
        }
        else
        {
            balancedInsertRec(node->_right, data);
        }

    }
    // If data is lesser, then it should be inserted on the left
    else
    {
        if (node->_left == nullptr)
        {
            node->_left = new Node(data);
            ++_length;
        }
        else
        {
            balancedInsertRec(node->_left, data);
        }
    }

    // Now a node would have been inserted either as left child or as right child
    int lh = height(node->_left);
    int rh = height(node->_right);
    cout << data << "; H: " << 1 + max(lh, rh) << "; H->L: " << lh << "; H->R: " << rh << endl;

    if (abs(lh - rh)  > 1)
    {
        // Tree in unbalanced. So balance it
        if (lh > rh) 
        {
            // Because Equal elements will get inserted to the left child
            // data: x, node: z
            if (data <= node->_left->_data)
            {
                // Do a right rotate
                rightRotate(node);
            }
            else
            {
                // Do a left rotate and then a right rotate
                leftRotate(node->_left);
                rightRotate(node);
            }

            return;
        }
        else if (lh < rh)
        {
            // data: x, node: z
            if(data <= node->_right->_data)
            {
                // Do a right rotate and then a left rotate
                rightRotate(node->_right);
                leftRotate(node);
            }
            else
            {
                // Do a left rotate
                leftRotate(node);
            }
        }
    }
}

void
BST::balancedInsert(const int data)
{
    balancedInsertRec(_root, data);
}

bool
BST::remove(const int data)
{
    return false;
}

void
BST::printLevelOrder()
{
    uint32_t level = 0;
    uint32_t nextLevel = 0;
    queue<Node*> levelQueue;
    
    if (_root == nullptr)
    {
        return;
    }

    levelQueue.push(_root);
    level++;

    cout << "Level Order Traversal" << endl;
    while(!levelQueue.empty())
    {
        Node* tmp = levelQueue.front();
        levelQueue.pop();
        level--;
        cout << tmp->_data << ", ";

        if (tmp->_left != nullptr)
        {
            levelQueue.push(tmp->_left);
            nextLevel++;
        }

        if (tmp->_right != nullptr)
        {
            levelQueue.push(tmp->_right);
            nextLevel++;
        }

        if (level == 0)
        {
            cout << endl;
            level = nextLevel;
            nextLevel = 0;
        }
    }

    cout << endl;
}

void
BST::printInorderIterative()
{
    Node* tmpRoot = _root;

    cout << "Inorder Traversal" << endl;
    stack<Node*> recStack;

    if (tmpRoot == nullptr)
    {
        return;
    }

    do
    {
        if (tmpRoot != nullptr)
        {
            recStack.push(tmpRoot);

            while (tmpRoot->_left != nullptr)
            {
                recStack.push(tmpRoot->_left);
                tmpRoot = tmpRoot->_left;
            }
        }

        tmpRoot = recStack.top();
        recStack.pop();
        cout << tmpRoot->getData() << ", ";

        tmpRoot = tmpRoot->_right;
    } while (!recStack.empty() || tmpRoot != nullptr);

    cout << endl;
}

int main()
{
    {
        cout << "Binary Search Tree" << endl;

        BST* root = new BST();
        root->balancedInsert(10);

        // Level 1
        root->balancedInsert(5);

        // Level 2
        root->balancedInsert(2);
        root->balancedInsert(7);
        root->balancedInsert(6);
        root->balancedInsert(3);
        root->balancedInsert(4);

        root->balancedInsert(30);
        root->balancedInsert(20);
        root->balancedInsert(25);
        root->balancedInsert(27);
        /*
        root->balancedInsert(3);
        root->balancedInsert(6);
        root->balancedInsert(8);
        root->balancedInsert(11);
        root->balancedInsert(13);
        root->balancedInsert(16);
        root->balancedInsert(18);
        */

        cout<< "Len: " << root->getLength() << endl;
        root->printInorderIterative();
        root->printLevelOrder();
    }

    cout << endl;
    return 0;
}
