#include <iostream>
#include <cassert>  // assert
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

/**
 * https://discuss.leetcode.com/topic/6604/ideal-solution-using-stack-java
 *
 * Your iterator will be initialized with the root node of a BST.
 *
 * Calling next() will return the next smallest number in the BST.
 *
 * Note: next() and hasNext() should run in average O(1) time and uses O(h) memory,
 * where h is the height of the tree.
 *
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// ----------------------------------------------------------------------------------------------
// Class TreeNode
// ----------------------------------------------------------------------------------------------
class TreeNode
{
    // Everything is private as User should not have access to TreeNode
    private:
        int val;
        TreeNode* left;
        TreeNode* right;
        friend class BSTIterator;
        friend class BST;

        TreeNode();
        TreeNode(int val);

        int getVal();
};

TreeNode::TreeNode() : left(nullptr),
               right(nullptr),
               val(0) { }
                 
TreeNode::TreeNode(int val) : left(nullptr),
                       right(nullptr),
                       val(val) { }

int
TreeNode::getVal()
{
    return val;
}

// ----------------------------------------------------------------------------------------------
// Class BSTIterator
// ----------------------------------------------------------------------------------------------
class BSTIterator
{
private:
    TreeNode* _cur;
    TreeNode* _root;
    unordered_map<TreeNode*, TreeNode*> _nextSmallestMap;

public:
    BSTIterator(TreeNode *root)
    {
        _cur = root;
        _root = root;
        if (root != NULL)
        {
            cout << "0. rootData: " << root->val << endl;
        }
        else
        {
            cout << "0. Root is null" << endl;
        }
        buildMap();
    }

    // Find a node that is greater than curNode's value.
    // Then keep going left
    TreeNode* inOrderSuccessor(TreeNode* root, TreeNode* curNode)
    {
        TreeNode* curSucc = NULL;
        while (root != NULL)
        {
            if (curNode->val < root->val)
            {
                curSucc = root;
                root = root->left;
            }
            else
            {
                root = root->right;
            }
        }

        return curSucc;
    }

    void printBSTIterMap()
    {
        for (auto i : _nextSmallestMap)
        {
            if (i.second != NULL)
            {
                cout << (i.first)->val << " - " << (i.second)->val << endl;
            }
            else
            {
                cout << (i.first)->val << " - NULL" << endl;
            }
        }
        cout << endl;
    }

    // https://www.geeksforgeeks.org/populate-inorder-successor-for-all-nodes/
    void buildMap()
    {
        // Traverse the tree iteratively and find inorder success for each node
        cout << "1. " << endl;
        queue<TreeNode*> nodeQ;
        if (_root == NULL)
        {
            cout << "2. " << endl;
            return;
        }

        cout << "3. rootData: " << _root->val << endl;
        nodeQ.push(_root);
        while (!nodeQ.empty())
        {
            TreeNode* tmp = nodeQ.front();
            nodeQ.pop();
            TreeNode* tmpSucc = inOrderSuccessor(_root, tmp);
            _nextSmallestMap[tmp] = tmpSucc;

            if (tmp->left != NULL)
            {
                nodeQ.push(tmp->left);
            }
            if (tmp->right != NULL)
            {
                nodeQ.push(tmp->right);
            }
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext()
    {
        auto itr = _nextSmallestMap.find(_cur);
        if (itr != _nextSmallestMap.end())
        {
            if (itr->second != NULL)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        
    }

    /** @return the next smallest number */
    int next()
    {
        auto itr = _nextSmallestMap.find(_cur);
        _cur = itr->second;
        return _cur->val;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

// ----------------------------------------------------------------------------------------------
// Class BST:
//      This is the Binary Search Tree data structure
// https://discuss.leetcode.com/topic/6575/my-solutions-in-3-languages-with-stack
// ----------------------------------------------------------------------------------------------
class BST
{
    private:
        TreeNode* _root;
        size_t _length;

    public:
        BST() : _root(nullptr),
                _length(0) { }

        ~BST() { delete _root; }

        bool isPresent(const int val);
        void insert(const int val);
        void printInorderIterative();

        size_t getLength() { return _length; }
        TreeNode* getRoot() { return _root; }
};

bool
BST::isPresent(const int val)
{
    TreeNode* itr = _root;
    while(itr != nullptr)
    {
        if (itr->getVal() > val)
        {
            itr = itr->left;
        }
        else if (itr->getVal() < val)
        {
            itr = itr->right;
        }
        else
        {
            return true;
        }
    }

    return false;
}

void
BST::insert(const int val)
{
    TreeNode* tmp = new TreeNode(val);

    if (_root == nullptr)
    {
        _root = tmp;
        ++_length;

        return;
    }
    else
    {
        TreeNode* curNode = _root;

        while (curNode)
        {
            if (curNode->getVal() < val)
            {
                if (curNode->right == nullptr)
                {
                    curNode->right = tmp;
                    ++_length;
                    return;
                }
                curNode = curNode->right;
            }
            else if (curNode->getVal() >= val)
            {
                if (curNode->left == nullptr)
                {
                    curNode->left = tmp;
                    ++_length;
                    return;
                }
                curNode = curNode->left;
            }
        }
    }
}

void
BST::printInorderIterative()
{
    stack<TreeNode*> recStack;

    if (_root == nullptr)
    {
        return;
    }

    do
    {
        if (_root != nullptr)
        {
            recStack.push(_root);

            while (_root->left != nullptr)
            {
                recStack.push(_root->left);
                _root = _root->left;
            }
        }

        _root = recStack.top();
        recStack.pop();
        cout << _root->getVal() << " : ";

        _root = _root->right;
    } while (!recStack.empty() || _root != nullptr);

    cout << endl;
}

// ----------------------------------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------------------------------
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

        BSTIterator bsi = BSTIterator(root->getRoot());

        bsi.printBSTIterMap();
        while (bsi.hasNext())
        {
            cout << bsi.next() << ", ";
        }
        cout << endl;
    }

    cout << endl;
    return 0;
}
