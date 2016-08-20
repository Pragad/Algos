#include <iostream>
using namespace std;

struct node
{
      int data;
      node* left;
      node* right;
      node* parent;
};
 /*
 if node->right != NULL then successor could be in RST
 Traverse right and go to the LEFT MOST CHILD in the right sub tree
 Find minimum in RST
 
 if NODE is child of node->parent then
 keep going up to find a parent (p1) whose parent (p2) such that p1 is Left Child of P2
 */

node* findLeftMostNode(node* n)
{
   while (n->left != NULL)
   {
      n = n->left;
   }
  
   return n;
}

node* findSuccessor(node* n)
{
   if (n == NULL)
   {
      return NULL;
   }
  
   node* t1 = NULL;

   if (n->right != NULL)
   {
      t1 = findLeftMost(n->right);
   }
   else
   {
      while(n->parent != NULL)
      {
         // IF node is left child
         if (n->parent->left == n)
         {
            t1 = n->parent;
            break;
         }
         else
         {
            n = n->parent;
         }
      }
   }
  
   return t1;
}

int main() {
   cout << "Practice Makes Perfect";
   return 0;
}


/*
n  = 3;
   5    // result = 5
 4    6 // result = 4
3        7
     
     
               15 // result = 15
       7              25
   2      10       20       30  // result = 10
 1   3   8  12   16  22   27   35
     
      35
        36
          37
            38
 
 *
 if node->right != NULL then successor could be in RST
 Traverse right and go to the LEFT MOST CHILD in the right sub tree
 Find minimum in RST
 
 if NODE is child of node->parent then
 keep going up to find a parent (p1) whose parent (p2) such that p1 is Left Child of P2
 
 Complexity: O(log n) if BST is balanced
 Worst case: O(n) where n is number of nodes
 */


class Pramp {
// 40, 50, 50, 100, 160, 200, 325, 500, 1075, 1500 ; Say b = 2000. Find c;
// 160, 150,150, 100, 40 = 600
  
// 325, 500, 1075, 1500 ; Say b = 2000. Find c;
// 600 + (200 * remaing budgets)
// 600 + 800 => 1400

// 25, 0, 0, 0,
  
// 500, 1075, 1500 ; Say b = 2000. Find c;
// 25 + 350 * 3 => 1075
// 1075 / 3 = 358
// 575, 0,
  
   // take 25 and 25/n = 10 => 350 + x = c
// 1400 / 4 = 350

// Sum till 325 in g[40...325] + (358 * 3) = 1999
  
   // n research grants
   // reduction of budget to b dollars
   // cap on grants is c
   // choose right value of c --> sum(grants) = new budget
  
  
   // b / n => 2000 / 10 => 200 (c)
   // if g[i] <= c then
      // let it go
      // also add c - g[i] to pool of money
  
   // at the end of the above process we have
   // pool of money which we can repeat the above process for again
   public static void main(String[] args) {
     
   }
  
   public static int findGrantCap(int[] grants, int budget) {
      if (grants == null || grants.length == 0) {
         return budget;
      }
     
      if (budget <= 0) {
         return budget;
      }
     
      int i = 0;
      int cap = budget / grants.length;
      while (i < grants.length) {
         if (grants[i] <= cap) {
            if (i + 1 >= grants.length) {
               cap += cap - grants[i];
            } else {
               cap += ((cap - grants[i]) / grants.length - i - 1);
               i += 1;
            }
         } else {
            break;
         }
      }
     
      return cap;
   }
}
