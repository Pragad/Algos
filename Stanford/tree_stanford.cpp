/*
tree* findLCA(tree* root, tree* a, tree* b)
bool isTreeBalanced(tree* root)
uint32_t computeHeight(tree* root)
int countTree(int numNodes)
bool sameTree(tree* a, tree* b)
void doubleTree(tree* root)
void mirror(tree* root)
void printPathsVec(tree* root)
void printPathsRecurVec(tree* root, vector<int> path)
void printVector(vector<int> path)
void printPaths(tree* root)
void printPathsRecur(tree* root, int path[], int pathLen)
void printArray(int path[], int len)
bool hasPathSum(tree* root, int sum)
int minValue(tree* root)
int maxDepth(tree* root)
int size(tree* root)
tree* build123()
tree* insert(tree* root, int data)
void printTree(tree* root)
*/

// This contains solution to Stanford's Tree problems.
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct tree
{
    int data;
    struct tree* left;
    struct tree* right;
};

tree* newNode(int data)
{
    struct tree* node = new tree();
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void printTree(tree* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        cout << root->data << "  ";
        printTree(root->left);
        printTree(root->right);
    }
}

tree* insert(tree* root, int data)
{
    if (root == NULL)
    {
        return newNode(data);
    }
    else
    {
        if (data > root->data)
        {
            root->right = insert(root->right, data);
        }
        else
        {
            root->left = insert(root->left, data);
        }
    }

    return root;
}

tree* build123()
{
    struct tree* root = NULL;

    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 4);
    root = insert(root, 7);
    root = insert(root, 6);

    return root;
}

int size(tree* root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return (size(root->left) + 1 + size(root->right));
    }
}

int maxDepth(tree* root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int lDepth = 1 + maxDepth(root->left);
        int yDepth = 1 + maxDepth(root->right);
        return (lDepth > yDepth ? lDepth : yDepth);
    }
}

int minValue(tree* root)
{
    while (root != NULL)
    {
        if (root->left == NULL)
        {
            return root->data;
        }
        return minValue(root->left);
    }
}

bool hasPathSum(tree* root, int sum)
{
    if (root == NULL)
    {
        return false;
    }
    else if (root->left == NULL && root->right == NULL && sum == root->data)
    {
        return true;
    }
    else if (root->left != NULL || root->right != NULL)
    {
        return (hasPathSum(root->left, sum - root->data) ||
                hasPathSum(root->right, sum - root->data));
    }
    else
    {
        return false;
    }
}

void printArray(int path[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << path[i] << "  ";
    }
    cout << endl;
}

void printPathsRecur(tree* root, int path[], int pathLen)
{
    if (root == NULL)
    {
        cout << endl;
        return;
    }
    else if (root->left == NULL && root->right==NULL)
    {
        path[pathLen] = root->data;
        printArray(path, pathLen+1);
        return;
    }
    else
    {
        path[pathLen] = root->data;
        printPathsRecur(root->left, path, pathLen+1);
        printPathsRecur(root->right, path, pathLen+1);
    }
}

void printPaths(tree* root)
{
    int path[1000];
    printPathsRecur(root, path, 0);
}

// Using Vectors to print the path
void printVector(vector<int> path)
{
    for (vector<int>::iterator it = path.begin(); it != path.end(); it++)
    {
        cout << *it << "  ";
    }
    cout << endl;
}

void printPathsRecurVec(tree* root, vector<int> path)
{
    if (root == NULL)
    {
        cout << endl;
        return;
    }
    else if (root->left == NULL && root->right==NULL)
    {
        path.push_back(root->data);
        printVector(path);
        return;
    }
    else
    {
        path.push_back(root->data);
        printPathsRecurVec(root->left, path);
        printPathsRecurVec(root->right, path);
    }

}

void printPathsVec(tree* root)
{
    vector<int> vPath;
    printPathsRecurVec(root, vPath);
}

void mirror(tree* root)
{
    if (root == NULL)
    {
        return;
    }

    mirror(root->left);
    mirror(root->right);

    tree* temp = root->left;
    root->left = root->right;
    root->right = temp;
}

void doubleTree(tree* root)
{
    if (root == NULL)
    {
        return;
    }

    // Copy the left and right of current node
    tree* tmpL = root->left;
    tree* tmpR = root->right;

    tree* temp = new tree();
    temp->data = root->data;
    temp->left = root->left;
    temp->right = NULL;

    // Add the new node to the left of temp.
    root->left = temp;

    doubleTree(tmpL);
    doubleTree(tmpR);
}

bool sameTree(tree* a, tree* b)
{
    if (a == NULL && b == NULL)
    {
        return true;
    }
    else if (a == NULL && b != NULL)
    {
        return false;
    }
    else if (a != NULL && b == NULL)
    {
        return false;
    }
    else if (a->data != b->data)
    {
        return false;
    }
    else
    {
        // a's data is same as b's data. Procced to child trees
        return (sameTree(a->left, b->left) &&
                sameTree(a->right, b->right));
    }
}

int countTree(int numNodes)
{
    if (numNodes == 0 || numNodes == 1)
    {
        return numNodes;
    }
    return (countTree(numNodes-1) + countTree(numNodes-1));
    return (1 + countTree(numNodes-1));
}

// This functions computes the height of a tree.
uint32_t computeHeight(tree* root)
{
    if (root != NULL)
    {
        return 0;
    }

    uint32_t leftHeight = 1 + computeHeight(root->left);
    uint32_t rightHeight = 1 + computeHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// This tell if a binary tree is Balanced or not.
// VERY IMP: What if the tree is highly unbalanced with million nodes on one side
// and very few nodes on other side.
bool isTreeBalanced(tree* root)
{
    return ((root == NULL) ||
            ((isTreeBalanced(root->left)) &&
            (isTreeBalanced(root->right)) &&
            (abs(computeHeight(root->left) - computeHeight(root->right)) <= 1)));
}

// This function ASSUMES that node a and node b are present in the Tree
tree* findLCA(tree* root, tree* a, tree* b)
{
    if (root == NULL)
    {
        return NULL;
    }

    if ((root->left == a && root->right == b) ||
        (root->left == b && root->right == a))
    {
        return root;
    }

    if (root == a || root == b)
    {
        return root;
    }
}

int main()
{
    cout << "TREE" << endl;
    struct tree* root = NULL;
    root = build123();
    printTree(root);
    cout << endl;

    cout << "Size: " << size(root) << endl;
    cout << "Max Depth: " << maxDepth(root) << endl;
    cout << "Has Path Sum: " << hasPathSum(root, 12) << endl;
    cout << "Has Path Sum: " << hasPathSum(root, 18) << endl;
    cout << "Has Path Sum: " << hasPathSum(root, 5) << endl;

    cout << "Min Value: " << minValue(root) << endl;
    cout << "Paths: ";
    printPaths(root);

    cout << "Paths Using Vectors: ";
    printPathsVec(root);

    cout << "Mirror of a Node" << endl;
    printTree(root);
    cout << endl;
    mirror(root);
    printTree(root);
    cout << endl;

    cout << "Doubling a tree" << endl;
    doubleTree(root);
    printTree(root);
    cout << endl;
    return 0;
}
