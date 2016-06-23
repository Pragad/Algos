// Learning: If TWO FOR LOOPS with i = 0 to n-1 AND j = i+1 to n-1; then
// IMP: "i" CAN'T GO TILL n-1 as it will cause j to overflow

#include <iostream>
using namespace std;
/*
I/p:
   arr[] = {10, 20, 30, 40, 1, 2};
   int SUM=91
   MAP:
   key------val
   (sum)----(i,j)
    30-------(0,1)
    (10+30)--(0,2)------> while storing this SUM-currSum
  
okay. got it. let me try coding in 5mins and se what I ca get to
  
*/
// pair is struct that takes two int// sorry gave refresh shortcut
struct pair
{
   int x;
   int y;
};
vector<int> findQuadSum(vector<int> nums, int S)
{
   unordered_map<int, pair<int,int>> sumMap;
  
   for (int i = 0; i < nums.size(); i++)
   {
      for (int j = i+1; j < nums.size(); j++)
      {
         auto itr = sumMap.find(S - (nums[i] + num[j]));
         if (itr != sumMap.end())
         {
            // We have to check if all indices are different.
            // I am not sure how pair STL works. IF it is a struct of int then
            // cool
            if ((itr->second).first != i &&
                (itr->second).second != j &&
                (itr->second).first != j &&
                (itr->second).second != i)
            {
               vector<int> temp = {i, j, (itr->second).first, (itr->second).second};
               return temp;
            }
         }
         else
         {
            // thinking if it would S-num[i] o
            // i can try just a min
            sumMap[nums[i] + nums[j]] = make_pair(i,j); // okay.
            sumMap(nums[i] + nums[j]).push_back(make_pair(i,j));
         }
      }
   // can i return an empty vector or just return NULL?
   // got it
   }
  
   return vector<int> {-1, -1, -1, -1};
   // this should work or I can put in a temp vector and return the temp vector
}
