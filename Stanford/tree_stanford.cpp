/* 
 * Problem 0. Print Tree Inorder
 * void printTreeInorderIterative(tree* root)
 *
 * Problem 1. Compute the Number of nodes in the tree
 * int size(tree* root)
 *
 * Problem 2. Compute the max depth in the tree
 * int maxDepth(tree* root)
 *
 * Problem 3. Compute the minimum value
 * int minValue(tree* root)
 *
 * Problem 4. Compute if there is path that matches the sum
 * bool hasPathSum(tree* root, int sum)
 *
 * Problem 5. Compute the Paths recursively
 * void printPathsRecur(tree* root, int path[], int pathLen)
 * vector<string> binaryTreePaths(tree* root)
 *
 * Problem 6. Compute the paths using vector
 * void printPathsVec(tree* root)
 *
 * Problem 7. Compute the mirror of a tree
 * void mirror(tree* root)
 *
 * Problem 8. Compute the double of a tree
 * void doubleTree(tree* root)
 *
 * Problem 9. Compute if two trees are same
 * bool sameTree(tree* a, tree* b)
 *
 * Problem 10. Count the number of possible trees
 * int countTree(int numNodes)
 *
 * Problem 11. Compute the max height of a tree
 * uint32_t computeHeight(tree* root)
 *
 * Problem 12. This tell if a binary tree is Balanced or not.
 * bool isTreeBalanced(tree* root)
 *
 * Problem 13. Compute the LCA of a tree
 * tree* findLCA(tree* root, tree* a, tree* b)
 *
 * Problem 13a. LCA in a Binary Search Tree
 * tree* lowestCommonAncestor(tree* root, tree* p, tree* q)
 *
 * Problem 13b. Find Distance Between Siblings in a Binary Tree
 * int distanceBetweenKeys(tree* root, int a, int b)
 *
 * Problem 14. Given a Binary Tree, find the maximum sum path from a leaf to root.
 * int maxSumLeafToRoot(tree* root)
 *
 * Problem 15. Given a Binary Tree, find the maximum sum path from a leaf to leaf.
 * int maxSumLeafToLeaf(tree* root)
 *
 * Problem 16. Given a Binary Tree, find the maximum sum path from a ANY NODE to ANY NODE
 * int maxSumNodeToNode(tree* root)
 *
 * Problem 17. print-the-longest-leaf-to-leaf-path-in-a-binary-tree-and-its-length
 * uint32_t longPathLength(tree* root)
 *
 * Problem 18. Print Tree in Level Order
 * void printTreeLevelOrder(tree* root)
 *
 * Problem 19. Print Tree in Spiral Order
 * void printSpiralOrder(tree* root)
 *
 * Problem 20. Print Tree in Vertical Order
 * void printVerticalOrder(tree* root)
 *
 * Problem 21. Find the nearest element that is lesser than the given key
 * int nearestLesserElmt(tree* root, int key, int& minElmt)
 *
 * Problem 22. Find largest element smaller than K in a BST
 * int findLargestNumSmallerThanKey(tree* root, int elmt)
 *
 * Problem 23. Find next larger number than K in a BST
 * int findSmallestNumLargerThanKey(tree* root, int elmt)
 *
 * Problem 24. Nth largest element in a binary search tree
 * int NthLargestInBST(tree* root, uint32_t n)
 *
 * Problem 25 In Order Successor in Binary Search Tree
 * tree* InorderSuccessorWithParent(treeWithParent* node)
 *
 * Problem 26. Iterative Inorder, Preorder, Postorder Traversal
 * void printTreeInorderIterative(tree* root)
 *
 * Problem 27. Iterative Inorder, Preorder, Postorder Traversal
 * void printTreePreorderIterative(tree* root)
 *
 * Problem 28. Iterative Inorder, Preorder, Postorder Traversal
 * void printTreePostorderIterative(tree* root)
 *
 */

// This contains solution to Stanford's Tree problems.
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#define __STDC_LIMIT_MACROS     // std::numeric_limits<std::int32_t>::max();
#include <cstdint>              // std::numeric_limits<std::int32_t>::max();
#include <limits> 
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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

struct treeWithParent
{
    int data;
    struct treeWithParent* left;
    struct treeWithParent* right;
    struct treeWithParent* parent;
};

treeWithParent* newNodeParent(int data)
{
    struct treeWithParent* node = new treeWithParent();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}

void printTreePreorder(tree* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        cout << root->data << "  ";
        printTreePreorder(root->left);
        printTreePreorder(root->right);
    }
}

void printTreeInorder(tree* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        printTreeInorder(root->left);
        cout << root->data << "  ";
        printTreeInorder(root->right);
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

    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 6);

    return root;
}

// ------------------------------------------------------------------------------------------------
// Problem 1.
//      Compute the Number of nodes in the tree
// ------------------------------------------------------------------------------------------------
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

// ------------------------------------------------------------------------------------------------
// Problem 2.
//      Compute the max depth in the tree
// ------------------------------------------------------------------------------------------------
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

// ------------------------------------------------------------------------------------------------
// Problem 3.
//      Compute the minimum value
// ------------------------------------------------------------------------------------------------
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

    return -1;
}

// ------------------------------------------------------------------------------------------------
// Problem 4.
//      Compute if there is path that matches the sum
// ------------------------------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------------------
// Problem 5.
//      Compute the Paths recursively
// -----------------------------------------------------------------------------------------

// From LeetCode
void binaryTreePathsRec(tree* root, vector<string>& paths, string path)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        path = path + to_string(root->data);
        paths.push_back(path);
    }

    binaryTreePathsRec(root->left, paths, path + to_string(root->data) + "->");
    binaryTreePathsRec(root->right, paths, path + to_string(root->data) + "->");
}

vector<string> binaryTreePaths(tree* root)
{
    vector<string> paths;
    string path = "";
    binaryTreePathsRec(root, paths, path);
    return paths;
}

// Using Arrays
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

// ------------------------------------------------------------------------------------------------
// Problem 6.
//      Compute the paths using vector
// ------------------------------------------------------------------------------------------------
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

// ------------------------------------------------------------------------------------------------
// Problem 7.
//      Compute the mirror of a tree
// ------------------------------------------------------------------------------------------------
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

// ------------------------------------------------------------------------------------------------
// Problem 8.
//      Compute the double of a tree
// ------------------------------------------------------------------------------------------------
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

// ------------------------------------------------------------------------------------------------
// Problem 9.
//      Compute if two trees are same
// ------------------------------------------------------------------------------------------------
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

// ------------------------------------------------------------------------------------------------
// Problem 10.
//      Count the number of possible trees
// ------------------------------------------------------------------------------------------------
int countTree(int numNodes)
{
    if (numNodes == 0 || numNodes == 1)
    {
        return numNodes;
    }
    return (countTree(numNodes-1) + countTree(numNodes-1));
    return (1 + countTree(numNodes-1));
}

// ------------------------------------------------------------------------------------------------
// Problem 11.
//      Compute the max height of a tree
// ------------------------------------------------------------------------------------------------
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

// ------------------------------------------------------------------------------------------------
// Problem 12.
// http://stackoverflow.com/questions/742844/how-to-determine-if-binary-tree-is-balanced
// This tell if a binary tree is Balanced or not.
// VERY IMP: What if the tree is highly unbalanced with million nodes on one side
// and very few nodes on other side.
// ------------------------------------------------------------------------------------------------
bool isTreeBalanced(tree* root)
{
    return ((root == NULL) ||
            ((isTreeBalanced(root->left)) &&
            (isTreeBalanced(root->right)) &&
            (std::abs((double)computeHeight(root->left) - (double)computeHeight(root->right)) <= 1)));
}

// ------------------------------------------------------------------------------------------------
// Problem 13.
//      Compute the LCA of a tree
// This function ASSUMES that node a and node b are present in the Tree
// ------------------------------------------------------------------------------------------------
tree* findLCA(tree* root, tree* a, tree* b)
{
    cout << "0. Root: " << root << " ; a: " << a << " ; b: " << b << endl;
    if (root == NULL)
    {
        return NULL;
    }

    // IMP: This doesnot cover the following edge case.
    // When either is the direct child of other. 
    /*
    if ((root->left == a && root->right == b) ||
        (root->left == b && root->right == a))
    {
        return root;
    }
    */

    // Fix for the above problem
    if (root == a || root == b)
    {
        return root;
    }

    tree* la = findLCA(root->left, a, b);
    tree* ra = findLCA(root->right, a, b);

    if (la != NULL && ra != NULL)
    {
        return root;
    }

    else if (la != NULL)
    {
        return la;
    }
    else
    {
        return ra;
    }
}

int findLCANum(tree* root)
{
    tree* result = new tree();

    result = findLCA(root, root, root);
    //result = findLCA(root, root->right->right->left, root->left);
    return result->data;
}

// -----------------------------------------------------------------------------------------
// Problem 13a. LCA in a Binary Search Tree
// -----------------------------------------------------------------------------------------
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if (root == NULL || p == NULL || q == NULL)
    {
        return NULL;
    }

    while (root != NULL)
    {
        if (root->val == p->val || root->val == q->val)
        {
            return root;
        }
        else if ((root->val > p->val && root->val < q->val) ||
            (root->val < p->val && root->val > q->val))
        {
            return root;
        }
        else if (root->val > p->val && root->val > q->val)
        {
            root = root->left;
        }
        else if (root->val < p->val && root->val < q->val)
        {
            root = root->right;
        }
    }

    return NULL;
}

// ------------------------------------------------------------------------------------------------
// Problem 13b. Find Distance Between Siblings/Key in a Binary Tree
//      http://www.geeksforgeeks.org/find-distance-two-given-nodes/
// ------------------------------------------------------------------------------------------------
int findLevel(const tree* root, int a, int lvl)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->data == a)
    {
        return lvl;
    }

    return findLevel(root->left, a, lvl + 1);
    return findLevel(root->right, a, lvl + 1);
}

tree* findLCAwithLevel(tree* root, int a, int b, int& lvlOfA, int& lvlOfB, int& totDist, int lvl)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->data == a)
    {
        lvlOfA = lvl;
        return root;
    }
    else if (root->data == b)
    {
        lvlOfB = lvl;
        return root;
    }

    tree* la = findLCAwithLevel(root->left, a, b, lvlOfA, lvlOfB, totDist, lvl + 1);
    tree* ra = findLCAwithLevel(root->right, a, b, lvlOfA, lvlOfB, totDist, lvl + 1);

    if (la != NULL && ra != NULL)
    {
        // Both lvlOfA and lvlOfB will have some values
        totDist = (lvlOfA - lvl) + (lvlOfB - lvl);
        return root;
    }
    else if (la != NULL)
    {
        return la;
    }
    else
    {
        return ra;
    }
}

int distanceBetweenKeys(tree* root, int a, int b)
{
    int lvlOfA = -1;
    int lvlOfB = -1;
    int totDist = -1;
    tree* lca = findLCAwithLevel(root, a, b, lvlOfA, lvlOfB, totDist, 0);

    if (lvlOfA != -1 && lvlOfB != -1)
    {
        return totDist;
    }
    else if (lvlOfA != -1)
    {
        // Now A is the ancestor. Find level of B located from A
        int bLvl = findLevel(lca, b, lvlOfA);

        return bLvl - lvlOfA;
    }
    else
    {
        // Now B is the ancestor. Find level of A from B
        int aLvl = findLevel(lca, a, lvlOfB);

        return aLvl - lvlOfB;
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 14
// http://www.geeksforgeeks.org/find-the-maximum-sum-path-in-a-binary-tree/
//
//  Given a Binary Tree, find the maximum sum path from a leaf to root.
//  For example, in the following tree, there are three leaf to root paths 8->-2->10, -4->-2->10 and 7->10.
//  The sums of these three paths are 16, 4 and 17 respectively.
//  The maximum of them is 17 and the path for maximum is 7->10.
// ------------------------------------------------------------------------------------------------
// VERY IMP: Don't have to pass curSum as a REFERENCE
void maxSumLeafToRootPath(tree* root, int curSum, int& maxSum)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        curSum += root->data;
        if (curSum > maxSum)
        {
            maxSum = curSum;
        }

        // VERY IMP: The below can be ignored as the values are not passed as reference
        // IMP: Reset Current sum to Previous value
        //curSum -= root->data;
        return;
    }

    // http://stackoverflow.com/questions/16767345/invalid-initialization-of-non-const-reference-of-type-int-from-a-temporary-of
    // VERY IMP: Can't pass a VALUE directly to a reference. It should be put in a 
    // variable before doing so.
    // curSum is being passed as value. So we can skip the temp variable
    int temp = root->data + curSum;

    maxSumLeafToRootPath(root->left, temp, maxSum);
    maxSumLeafToRootPath(root->right, temp, maxSum);
}

int maxSumLeafToRoot(tree* root)
{
    int maxSum = 0;
    int curSum = 0;
    maxSumLeafToRootPath(root, curSum, maxSum);

    return maxSum;
}

// ------------------------------------------------------------------------------------------------
// Problem 15
// http://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/
//
//  Given a Binary Tree, find the maximum sum path from a leaf to leaf.
//  maxLeafToLeaf - Store the max leaf to leaf value- Max Sum stored between two leaves.
//  returValue - Return the max value from that node to its leaves.
//
//  IMP:
//  We are interested in TWO MAIN thins.
//  1. Given a Root, what is the sum of ROOT + LEFT CHILD + RIGHT CHILD
//  2. ROOT + MAX (LEFT CHILD, RIGHT CHILD)
//  3. If ROOT is one sided return INTMIN
//
//  (1) Will give if root, left, right hold the MAX sum
//  (2) Will give if ROOT + (LEFT OR RIGHT) is a part of the MAX sum
// ------------------------------------------------------------------------------------------------
int maxSumLeafToLeafRec(tree* root, int& maxLeafToLeaf)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->left == NULL && root->right == NULL)
    {
        return root->data;
    }

    int leftMaxSum = maxSumLeafToLeafRec(root->left, maxLeafToLeaf);
    int rightMaxSum = maxSumLeafToLeafRec(root->right, maxLeafToLeaf);

    if (root->left != NULL && root->right != NULL)
    {
        // VERY IMP:
        // This should be the ONLY place where we update maxLeafToLeaf.
        // Two leaves should exist in the Binary Tree. For that there should be a NODE whose
        // left and right is NOT null
        maxLeafToLeaf = max(maxLeafToLeaf, leftMaxSum + rightMaxSum + root->data);

        // Return the max value from current node to its leaves
        return (max(leftMaxSum, rightMaxSum) + root->data);
    }

    // VERY IMP: This should be ELSE IF. Otherwise the above IF as well as the below IF will get executed
    else if (root->left != NULL)
    {
        // Don't update maxLeafToLeaf here
        // Consider the following tree
        //      10          10
        //     /               \
        //    5                 2
        // The above trees DON't have a leaf to leaf path
        return leftMaxSum + root->data;
    }
    else
    {
        return rightMaxSum + root->data;
    }
}

int maxSumLeafToLeaf(tree* root)
{
    int maxSum = numeric_limits<int>::min();

    // We don't need the return value here
    maxSumLeafToLeafRec(root, maxSum);
    return maxSum;
}

// ------------------------------------------------------------------------------------------------
// Problem 16
// http://www.geeksforgeeks.org/find-maximum-path-sum-in-a-binary-tree/
//
//  Given a Binary Tree, find the maximum sum path from a ANY NODE to ANY NODE
//  maxSum - Contains the max sum found till now
//  returValue - Return the max value from that node to its leaves.
//
//  MaxSum can either of the following
//      a. root->data
//      b. root->data + leftSum
//      c. root->data + rightSum
//      d. root->data + leftSum + rightSum
//
//  IMP:
//  We are interested in TWO MAIN things.
//  1. We should return MAX found along LEFT OR RIGHT side
//  2. MaxSum will store the actual Max got from LEFT OR RIGHT OR BOTH
// ------------------------------------------------------------------------------------------------
// MaxSum can be either of the following
// 1. Max of LeftSum, RightSum
// 2. Max of LeftSum, RightSum + Root->data
// 3. LeftSum + RightSum + Root->data
// 4. Current Max itself
//
// At each level you should return the maxSum you got including the root
// 1. Max of LeftSum, Right + Root->data
// 2. Or just Root->data
int maxPathSumRec(tree* root, int& maxSum)
{
    // We can't return 0. A tree can have all -ve numbers
    if (root == NULL)
    {
        return numeric_limits<int>::min();
    }

    if (root ->left == NULL && root->right == NULL)
    {
        return root->data;
    }

    int leftMaxSum = maxPathSumRec(root->left, maxSum);
    int rightMaxSum = maxPathSumRec(root->right, maxSum);

    int maxVal = max(leftMaxSum, rightMaxSum);

    // INT_MIN + -ve Number would become very big positive number.
    // So add conditions to avoid that
    if (leftMaxSum != numeric_limits<int>::min() && rightMaxSum != numeric_limits<int>::min())
    {
        maxSum = max(max(max(maxVal, maxVal + root->data), leftMaxSum + rightMaxSum + root->data), maxSum); 
    }
    else if (leftMaxSum == numeric_limits<int>::min())
    {
        maxSum = max(max(max(maxVal, maxVal + root->data), rightMaxSum + root->data), maxSum); 
    }
    else if (rightMaxSum == numeric_limits<int>::min())
    {
        maxSum = max(max(max(maxVal, maxVal + root->data), leftMaxSum + root->data), maxSum); 
    }
    
    return max(maxVal + root->data, root->data);
}


int maxSumNodeToNode(tree* root)
{
    if (root == NULL)
    {
        return numeric_limits<int>::min();
    }

    int maxSum = numeric_limits<int>::min();
    int retVal = maxPathSumRec(root, maxSum);
    return max(maxSum, retVal);
}

// ------------------------------------------------------------------------------------------------
// Problem 17
// http://stackoverflow.com/questions/17703952/print-the-longest-leaf-to-leaf-path-in-a-binary-tree-and-its-length
//
// Imagine a tree like below
//              a
//            b  
//          c   f
//        d       g
//      e          
//
// That is why there is another wrapper function to determine if the final max is 
// MaxPathLen OR the returned value which is MaxAlongOneSide
// ------------------------------------------------------------------------------------------------
uint32_t longestPathLengthRec(tree* root, uint32_t& maxPathLen)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }

    uint32_t leftPathLen = longestPathLengthRec(root->left, maxPathLen);
    uint32_t rightPathLen = longestPathLengthRec(root->right, maxPathLen);

    uint32_t maxAlongOneSide = 1 + max(leftPathLen, rightPathLen);

    // This is the total max path len by considering both sides as well
    maxPathLen = max(maxPathLen, max(maxAlongOneSide, 1 + leftPathLen + rightPathLen));

    return maxAlongOneSide;
}

uint32_t longPathLength(tree* root)
{
    if (root == NULL)
    {
        return 0;
    }

    uint32_t maxPathLen = 0;
    uint32_t maxAlongOneSide = longestPathLengthRec(root, maxPathLen);

    return max(maxPathLen, maxAlongOneSide);

}

// ------------------------------------------------------------------------------------------------
// Problem 18
//      Print Tree in Level Order
// ------------------------------------------------------------------------------------------------
void printTreeLevelOrder(tree* root)
{
    if (root == NULL)
    {
        return;
    }

    queue<tree*> lvlQueue;
    lvlQueue.push(root);
    uint32_t levelCount = 1;
    uint32_t nextLvlCnt = 0;

    while(!lvlQueue.empty())
    {
        tree* temp = lvlQueue.front();
        lvlQueue.pop();
        levelCount--;
        cout << temp->data << " ";

        if (temp->left != NULL)
        {
            lvlQueue.push(temp->left);
            nextLvlCnt++;
        }

        if (temp->right != NULL)
        {
            lvlQueue.push(temp->right);
            nextLvlCnt++;
        }

        if (levelCount == 0)
        {
            cout << endl;
            levelCount = nextLvlCnt;
            nextLvlCnt = 0;
        }
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 19
//      Print Tree in Spiral Order
// ------------------------------------------------------------------------------------------------
void printSpiralOrder(tree* root)
{
    if (root == NULL)
    {
        return;
    }

    if (root -> left == NULL && root -> right == NULL)
    {
        cout << root->data << endl;
        return;
    }

    vector<tree*> leftStack;
    vector<tree*> rightStack;

    // To Start with put the first level in the stack
    cout << root->data << endl;
    if (root->left != NULL)
    {
        rightStack.push_back(root->left);
    }

    if (root->right != NULL)
    {
        rightStack.push_back(root->right);
    }

    while (!leftStack.empty() || !rightStack.empty())
    {
        while (!rightStack.empty())
        {
            tree* temp = rightStack.back();
            cout << temp->data << " ";

            if (temp->right != NULL)
            {
                leftStack.push_back(temp->right);
            }

            if (temp->left != NULL)
            {
                leftStack.push_back(temp->left);
            }

            rightStack.pop_back();
        }
        cout << endl;

        while (!leftStack.empty())
        {
            tree* temp = leftStack.back();
            cout << temp->data << " ";

            if (temp->left != NULL)
            {
                rightStack.push_back(temp->left);
            }

            if (temp->right != NULL)
            {
                rightStack.push_back(temp->right);
            }
            leftStack.pop_back();
        }
        cout << endl;
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 20
//      Print Tree in Vertical Order
// http://stackoverflow.com/questions/14485255/vertical-sum-in-a-given-binary-tree?lq=1
// http://stackoverflow.com/questions/20521098/print-a-tree-vertically
// ------------------------------------------------------------------------------------------------
void fillHorizontalDistanceMap(tree* root, unordered_map<int, vector<int> >& horiDistMap, int horiDist)
{
    if (root == NULL)
    {
        return;
    }

    auto itr = horiDistMap.find(horiDist);
    if (itr != horiDistMap.end())
    {
        itr->second.push_back(root->data);
    }
    else
    {
        horiDistMap[horiDist] = vector<int> {root->data};
    }

    fillHorizontalDistanceMap(root->left, horiDistMap, horiDist - 1);
    fillHorizontalDistanceMap(root->right, horiDistMap, horiDist + 1);
}

void printVerticalOrder(tree* root)
{
    // This map should be finally sorted by KEYS and the printed
    unordered_map<int, vector<int> > horiDistMap;

    // Use a Map to store all Nodes's corresponding to a horizontal distance
    fillHorizontalDistanceMap(root, horiDistMap, 0);

    // Sort the Undered Map. This needs an extra data structure
    std::map<int, vector<int> > orderedDistMap(horiDistMap.begin(), horiDistMap.end());

    // Print the Map in Order
    // Get each element of the map
    // If we use for each, can't use itr->second. So using iterator to traverse.
    for (auto itr = orderedDistMap.begin(); itr != orderedDistMap.end(); itr++)
    {
        // Each element of the map is a vector of values corresponding to an horizontal
        // distance.
        cout << itr->first << ": ";
        for (auto data : itr->second)
        {
            cout << data << ", ";
        }
        cout << endl;
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 21
//      Find the nearest element that is lesser than the given key
//      A simpler approach
// ------------------------------------------------------------------------------------------------
void nearestLesserElmt(tree* root, int key, int& minElmt)
{
    if (root == NULL)
    {
        return;
    }

    if (root->data == key)
    {
        if (root->left != NULL)
        {
            minElmt = root->left->data;
        }

        return;
    }

    if (key > root->data)
    {
        minElmt = root->data;
        nearestLesserElmt(root->right, key, minElmt);
    }
    else
    {
        nearestLesserElmt(root->left, key, minElmt);
    }
}

/*
int nearestLesserElmt(tree* root, int key, int& minElmt)
{
    if (root == NULL)
    {
        return numeric_limits<int>::max();
    }

    if (root->data == key)
    {
        if (root->left != NULL)
        {
            // If both are present return the number that is JUST smaller than key.
            // So larger of the two minimum numbers
            return max(minElmt, root->left->data);
        }
        return minElmt;
    }

    if (key > root->data)
    {
        minElmt = root->data;
        return nearestLesserElmt(root->right, key, minElmt);
    }
    else
    {
        return nearestLesserElmt(root->left, key, minElmt);
    }
}
*/

// ------------------------------------------------------------------------------------------------
// Problem 22
//      Find largest element smaller than K in a BST
//      http://stackoverflow.com/questions/6334514/to-find-largest-element-smaller-than-k-in-a-bst
// ------------------------------------------------------------------------------------------------
int findLargestNumSmallerThanKey(tree* root, int elmt)
{
    int result = -1;

    while(root != NULL)
    {
        if (root->data >= elmt)
        {
            root = root->left;
        }
        else
        {
            result = root->data;
            root = root->right;
        }
    }

    return result;
}

int findLargestNumSmallerThanKeyRec(tree* root, int elmt)
{
    if (root == NULL)
    {
        return -1;
    }

    if (root->data >= elmt)
    {
        return findLargestNumSmallerThanKeyRec(root->left, elmt);
    }
    else
    {
        int result1 = root->data;

        // If root->right != NULL then result2 WILL Be > result1
        int result2 = findLargestNumSmallerThanKeyRec(root->right, elmt);
        return max(result1, result2);

        // Approach 2:
        /*
         int result1 = root->data;

         if (root->right != NULL)
         {
             result1 = findLargestNumSmallerThanKeyRec(root->right, elmt);
         }
         return result1;
         */
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 23
//      Find next larger number than K in a BST
//      http://stackoverflow.com/questions/6334514/to-find-largest-element-smaller-than-k-in-a-bst
// ------------------------------------------------------------------------------------------------
int findSmallestNumLargerThanKey(tree* root, int elmt)
{
    int result = -1;

    while(root != NULL)
    {
        if (root->data > elmt)
        {
            result = root->data;
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return result;
}

int findSmallestNumLargerThanKeyRec(tree* root, int elmt)
{
    if (root == NULL)
    {
        return numeric_limits<int>::max();
    }

    if (root->data > elmt)
    {
        int result1 = root->data;
        int result2 = findSmallestNumLargerThanKeyRec(root->left, elmt);
        return min(result1, result2);
    }
    else
    {
        return findSmallestNumLargerThanKeyRec(root->right, elmt);
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 24
//      Nth largest element in a binary search tree
//      http://stackoverflow.com/questions/2612362/nth-largest-element-in-a-binary-search-tree
// ------------------------------------------------------------------------------------------------
void NthLargestInBST(tree* root, uint32_t& n, int32_t& result)
{
    if (root == NULL)
    {
        return;
    }

    NthLargestInBST(root->right, n, result);

    n--;
    if (n == 0)
    {
        result = root->data;
        return;
    }

    NthLargestInBST(root->left, n, result);
}

// ------------------------------------------------------------------------------------------------
// Problem 25
//      In Order Successor in Binary Search Tree
//      http://stackoverflow.com/questions/5471731/in-order-successor-in-binary-search-tree
// ------------------------------------------------------------------------------------------------
treeWithParent* findLeftMostNode(treeWithParent* node)
{
    while(node->left != NULL)
    {
        node = node->left;
    }

    return node;
}

treeWithParent* InorderSuccessorWithParent(treeWithParent* node)
{
    if (node == NULL || 
        (node->left == NULL && node->right == NULL && node->parent == NULL))
    {
        return newNodeParent(-1);
    }

    // Find the left most element in the Right child of the node.
    if (node->right != NULL)
    {
        // IMP: Should call on the RIGHT child and NOT on the node itself
        return findLeftMostNode(node->right);
    }
    else
    {
        while (node->parent != NULL)
        {
            if (node->parent->left == node)
            {
                // IMP: Should return the PARENT and NOT the node itself
                return node->parent;
            }
            else
            {
                node = node->parent;
            }
        }

        // Where node is the Largest element and has no successor
        return newNodeParent(-1);
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 26. Iterative Inorder Traversal
//      Iterative Inorder Traversal of a Tree
//      http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
//
//      Without Stack:
//      Morris inorder tree traversal
//      http://stackoverflow.com/questions/5502916/explain-morris-inorder-tree-traversal-without-using-stacks-or-recursion
// ------------------------------------------------------------------------------------------------
void printTreeInorderIterative(tree* root)
{
    stack<tree*> recStack;

    if (root == NULL)
    {
        return;
    }

    do
    {
        if (root != NULL)
        {
            recStack.push(root);

            while (root->left != NULL)
            {
                recStack.push(root->left);
                root = root->left;
            }
        }

        root = recStack.top();
        recStack.pop();
        cout << root->data << ", ";

        root = root->right;
    } while (!recStack.empty() || root != NULL);

    cout << endl;
}

// ------------------------------------------------------------------------------------------------
// Problem 27. Iterative Preorder Traversal
//      Iterative Preorder Traversal of a Tree
//      http://www.geeksforgeeks.org/iterative-preorder-traversal/
// ------------------------------------------------------------------------------------------------
void printTreePreorderIterative(tree* root)
{
    stack<tree*> preRecStack;
    if (root == NULL)
    {
        return;
    }

    preRecStack.push(root);
    while (!preRecStack.empty())
    {
        root = preRecStack.top();
        preRecStack.pop();
        cout << root->data << ", ";

        if (root->right != NULL)
        {
            preRecStack.push(root->right);
        }
        if (root->left != NULL)
        {
            preRecStack.push(root->left);
        }
    }

    cout << endl;
}

// ------------------------------------------------------------------------------------------------
// Problem 28. Iterative Postorder Traversal
//      Iterative Postorder Traversal of a Tree
//      http://www.geeksforgeeks.org/iterative-postorder-traversal/
//      http://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/
// ------------------------------------------------------------------------------------------------
vector<int> postorderTraversal(tree* root)
{
    vector<int> postorderList;
    stack<tree*> postorderStackTmp;
    stack<tree*> postorderStackFinal;

    if (root == NULL)
    {
        return postorderList;
    }

    // Build the Final stack by pushing into a temporary stack
    postorderStackTmp.push(root);
    while (!postorderStackTmp.empty())
    {
        tree* tmp = postorderStackTmp.top();
        postorderStackTmp.pop();
        postorderStackFinal.push(tmp);

        if (tmp->left != NULL)
        {
            postorderStackTmp.push(tmp->left);
        }
        if (tmp->right != NULL)
        {
            postorderStackTmp.push(tmp->right);
        }
    }

    while (!postorderStackFinal.empty())
    {
        tree* tmp = postorderStackFinal.top();
        postorderStackFinal.pop();
        postorderList.push_back(tmp->data);
    }

    return postorderList;
}

void printTreePostorderIterative(tree* root)
{
    vector<int> postList = postorderTraversal(root);

    for (auto num : postList)
    {
        cout << num << ", ";
    }
    cout << endl;
}

// ------------------------------------------------------------------------------------------------
// Main Function
// ------------------------------------------------------------------------------------------------
int main()
{
    cout << "TREE" << endl;
    struct tree* root = NULL;
    root = build123();
    printTreePreorder(root);
    cout << endl;

    cout << "Probelm 1: Size: " << size(root) << endl;
    cout << "Probelm 2: Max Depth: " << maxDepth(root) << endl;
    cout << "Probelm 3: Min Value: " << minValue(root) << endl;

    cout << "Probelm 4: Has Path Sum: " << hasPathSum(root, 12) << endl;
    cout << "Probelm 4: Has Path Sum: " << hasPathSum(root, 18) << endl;
    cout << "Probelm 4: Has Path Sum: " << hasPathSum(root, 5) << endl;

    cout << "Probelm 5: Paths: ";
    printPaths(root);

    cout << "Probelm 6: Paths Using Vectors: ";
    printPathsVec(root);

    cout << "Probelm 7: Mirror of a Node" << endl;
    printTreePreorder(root);
    /*
    cout << endl;
    mirror(root);
    printTreePreorder(root);
    cout << endl;

    cout << "Probelm 8: Doubling a tree" << endl;
    doubleTree(root);
    printTreePreorder(root);
    */

    // Problem 13. Find LCA
    {
        cout << endl << "Probelm 13: LCA" << endl;
        cout << findLCANum(root) << endl;
    }

    // Problem 13b. Find Distance Between Siblings/Key in a Binary Tree
    {
        root = newNode(1);
        root->left = newNode(2);
        root->right = newNode(3);

        root->left->left = newNode(4);
        root->left->right = newNode(5);
        root->right->left = newNode(6);
        root->right->right = newNode(7);

        root->left->left->left = newNode(8);
        root->left->right->right = newNode(9);
        root->right->left->right = newNode(10);
        root->right->right->left = newNode(11);

        cout << endl << "Problem 13b. Dist : " << distanceBetweenKeys(root, 4, 5) << endl;
        cout << endl << "Problem 13b. Dist : " << distanceBetweenKeys(root, 4, 6) << endl;
        cout << endl << "Problem 13b. Dist : " << distanceBetweenKeys(root, 3, 4) << endl;
        cout << endl << "Problem 13b. Dist : " << distanceBetweenKeys(root, 2, 4) << endl;
        cout << endl << "Problem 13b. Dist : " << distanceBetweenKeys(root, 10, 5) << endl;
    }

    // Problem 14. Find Max root to leaf path
    {
        struct tree* root = newNode(-15);
        root->left = newNode(5);
        root->right = newNode(6);
        root->left->left = newNode(-8);
        root->left->right = newNode(1);
        root->left->left->left = newNode(2);
        root->left->left->right = newNode(6);
        root->right->left = newNode(3);
        root->right->right = newNode(9);
        root->right->right->right= newNode(0);
        root->right->right->right->left= newNode(4);
        root->right->right->right->right= newNode(-1);
        root->right->right->right->right->left= newNode(10);

        struct tree *root1 = newNode(10);
        root1->left	 = newNode(2);
        root1->right	 = newNode(10);
        root1->left->left = newNode(-20);
        root1->left->right = newNode(-1);
        root1->right->right = newNode(-25);
        root1->right->right->left = newNode(17);
        //root1->right->right->right = newNode(4);

        cout << endl << "Preorder Traversal" << endl;
        printTreePreorder(root);
        cout << endl;

        cout << endl << "Level Order Traversal" << endl;
        printTreeLevelOrder(root1);
        cout << endl;

        cout << "Probelm 14: Max Root to Leaf: " << maxSumLeafToRoot(root1) << endl;

        cout << "Probelm 15: Max Leaf to Leaf: " << maxSumLeafToLeaf(root1) << endl;

        cout << "Probelm 16: Max Node to Node: " << maxSumNodeToNode(root1) << endl;
    }

    // Max Length of Path
    {
        struct tree* root = newNode(1);
        root->left = newNode(2);
        root->left->left = newNode(3);
        root->left->right = newNode(4);
        root->left->left->left = newNode(5);
        root->left->right->right = newNode(6);
        root->left->left->left->left = newNode(7);

        cout << "Probelm 17: Max Length of Path: " << longPathLength(root) << endl;
    }

    // Problem 18,19 Print Tree in Level and Spiral Order
    {
        struct tree* root = newNode(1);
        root->left = newNode(10);
        root->right = newNode(11);

        root->left->left = newNode(100);
        root->left->right = newNode(101);
        root->right->left = newNode(102);
        root->right->right = newNode(103);

        root->left->left->left = newNode(200);
        root->left->left->right = newNode(201);
        root->left->right->left = newNode(202);
        root->left->right->right = newNode(203);
        root->right->left->left = newNode(204);
        root->right->left->right = newNode(205);
        root->right->right->left = newNode(206);
        root->right->right->right = newNode(207);

        root->left->left->left->left = newNode(300);
        root->left->left->left->right = newNode(301);
        root->left->left->right->left = newNode(302);
        root->left->left->right->right = newNode(303);

        cout << endl << "Probelm 18: Tree in Level Order" << endl;
        printTreeLevelOrder(root);

        cout << endl << "Probelm 19: Tree in Spiral Order" << endl;
        printSpiralOrder(root);
    }

    // Problem 20 Vertical Order of a Binary Tree
    {
        struct tree* root = newNode(1);
        root->left = newNode(10);
        root->right = newNode(11);

        root->left->left = newNode(100);
        root->left->right = newNode(101);
        root->right->left = newNode(102);
        root->right->right = newNode(103);

        cout << endl << "Probelm 20: Print Tree in Vertical Order" << endl;
        printVerticalOrder(root);
    }

    root = newNode(20);
    root->left = newNode(10);
    root->right = newNode(30);

    root->left->left = newNode(5);
    root->left->right = newNode(15);
    root->right->left = newNode(25);
    root->right->right = newNode(35);

    // Problem 21 Find element that is lesser and closest to a given key
    {
        int minElement = numeric_limits<int>::min();

        cout << endl << "Level Order Traversal" << endl;
        printTreeLevelOrder(root);
        cout << endl;

        nearestLesserElmt(root, 5, minElement);
        cout << "Problem 21: Nearest Lower Element: " << minElement << endl;
        nearestLesserElmt(root, 10, minElement);
        cout << "Problem 21: Nearest Lower Element: " << minElement << endl;
        nearestLesserElmt(root, 15, minElement);
        cout << "Problem 21: Nearest Lower Element: " << minElement << endl;
        nearestLesserElmt(root, 20, minElement);
        cout << "Problem 21: Nearest Lower Element: " << minElement << endl;
        nearestLesserElmt(root, 25, minElement);
        cout << "Problem 21: Nearest Lower Element: " << minElement << endl;
        nearestLesserElmt(root, 30, minElement);
        cout << "Problem 21: Nearest Lower Element: " << minElement << endl;
        nearestLesserElmt(root, 35, minElement);
        cout << "Problem 21: Nearest Lower Element: " << minElement << endl;

        /*
        cout << "Probelm 21: Nearest Lower Element: " << nearestLesserElmt(root, 5, minElement) << endl;
        cout << "Probelm 21: Nearest Lower Element: " << nearestLesserElmt(root, 10, minElement) << endl;
        cout << "Probelm 21: Nearest Lower Element: " << nearestLesserElmt(root, 15, minElement) << endl;
        cout << "Probelm 21: Nearest Lower Element: " << nearestLesserElmt(root, 20, minElement) << endl;
        cout << "Probelm 21: Nearest Lower Element: " << nearestLesserElmt(root, 25, minElement) << endl;
        cout << "Probelm 21: Nearest Lower Element: " << nearestLesserElmt(root, 30, minElement) << endl;
        cout << "Probelm 21: Nearest Lower Element: " << nearestLesserElmt(root, 35, minElement) << endl;
        */
    }

    // Problem 22,23 Find largest element smaller than K in a BST
    {
        cout << endl << "Probelm 22,23: Find largest element smaller than K in a BST" << endl;
        cout << "Normal: " << findLargestNumSmallerThanKey(root, 30) << endl;
        cout << "Recursion: " << findLargestNumSmallerThanKeyRec(root, 30) << endl;
        cout << "Normal: " << findLargestNumSmallerThanKey(root, 5) << endl;
        cout << "Recursion: " << findLargestNumSmallerThanKeyRec(root, 5) << endl;
        cout << "Normal: " << findLargestNumSmallerThanKey(root, 25) << endl;
        cout << "Recursion: " << findLargestNumSmallerThanKeyRec(root, 25) << endl;
        cout << "Normal: " << findLargestNumSmallerThanKey(root, 35) << endl;
        cout << "Recursion: " << findLargestNumSmallerThanKeyRec(root, 35) << endl << endl;

        cout << "Normal: " << findSmallestNumLargerThanKey(root, 30) << endl;
        cout << "Recursion: " << findSmallestNumLargerThanKeyRec(root, 30) << endl;
        cout << "Normal: " << findSmallestNumLargerThanKey(root, 5) << endl;
        cout << "Recursion: " << findSmallestNumLargerThanKeyRec(root, 5) << endl;
        cout << "Normal: " << findSmallestNumLargerThanKey(root, 25) << endl;
        cout << "Recursion: " << findSmallestNumLargerThanKeyRec(root, 25) << endl;
        cout << "Normal: " << findSmallestNumLargerThanKey(root, 35) << endl;
        cout << "Recursion: " << findSmallestNumLargerThanKeyRec(root, 35) << endl;
    }

    // Problem 24 Nth largest element in a binary search tree
    {
        cout << endl << "Probelm 24: Nth largest element in a binary search tree" << endl;
        uint32_t n = 1;
        int32_t result = 0;
        NthLargestInBST(root, n, result); cout << result << ", ";
        n = 2;
        NthLargestInBST(root, n, result); cout << result << ", ";
        n = 3;
        NthLargestInBST(root, n, result); cout << result << ", ";
        n = 4;
        NthLargestInBST(root, n, result); cout << result << ", ";
        n = 5;
        NthLargestInBST(root, n, result); cout << result << ", ";
        n = 6;
        NthLargestInBST(root, n, result); cout << result << ", ";
        n = 7;
        NthLargestInBST(root, n, result); cout << result << endl;
    }

    // Problem 25 In Order Successor in Binary Search Tree
    {
        struct treeWithParent* root = newNodeParent(20);
        root->left = newNodeParent(10);
        root->left->parent = root;
        root->right = newNodeParent(30);
        root->right->parent = root;

        root->left->left = newNodeParent(5);
        root->left->left->parent = root->left;
        root->left->right = newNodeParent(15);
        root->left->right->parent = root->left;

        root->right->left = newNodeParent(25);
        root->right->left->parent = root->right;
        root->right->right = newNodeParent(35);
        root->right->right->parent = root->right;

        cout << endl << "Probelm 25: In Order Successor in Binary Search Tree" << endl;
        treeWithParent* result = InorderSuccessorWithParent(root);
        cout << root->data << "**" << result->data << ", ";

        result = InorderSuccessorWithParent(root->left);
        cout << root->left->data << "**" << result->data << ", ";

        result = InorderSuccessorWithParent(root->right);
        cout << root->right->data << "**" << result->data << ", ";

        result = InorderSuccessorWithParent(root->left->left);
        cout << root->left->left->data << "**" << result->data << ", ";

        result = InorderSuccessorWithParent(root->left->right);
        cout << root->left->right->data << "**" << result->data << ", ";

        result = InorderSuccessorWithParent(root->right->left);
        cout << root->right->left->data << "**" << result->data << ", ";

        result = InorderSuccessorWithParent(root->right->right);
        cout << root->right->right->data << "**" << result->data << ", ";
    }

    root = newNode(20);
    root->left = newNode(10);
    root->right = newNode(30);

    root->left->left = newNode(5);
    root->left->right = newNode(15);
    root->right->left = newNode(25);
    root->right->right = newNode(35);

    /*
    root->left->left->left = newNode(1);
    root->left->right->right = newNode(17);
    root->right->left->right = newNode(28);
    root->right->right->left = newNode(33);
    */

    // Problem 26,27,28. Iterative Inorder, Preorder, Postorder Traversal
    {
        cout << endl << endl << "Probelm 26: Iterative Inorder Traversal" << endl;
        printTreeInorderIterative(root);

        cout << endl << "Probelm 27: Iterative Preorder Traversal" << endl;
        printTreePreorderIterative(root);

        cout << endl << "Probelm 28: Iterative Postorder Traversal" << endl;
        printTreePostorderIterative(root);
    }

    cout << endl;

    return 0;
}
