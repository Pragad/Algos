/*
The "Merging 2 Packages" Problem

Given a package with a weight limit and an array arr of item weights, how can you most efficiently find two items with sum of weights that equals the weight limit?

Your function should return 2 such indices of item weights or -1 if such pair doesn't exist.
What is the runtime and space complexity of your solution?

limit = 100
Find two numbers that sum to a given number.
arr: 20, 30, 40, 50, 60, 65, 75, 85

map: 80:0, 70:1, 60:2, 50:3, 
*/
// for each element find if it is in the map

#include <iostream>
#include <vector>
using namespace std;

// Assumption: All item in weights are positive number;
pair<int, int> mergeTwoPackages(vector<int> weights, int limit)
{
   pair<int, int> result = {1, 2}; 
   return result;

   unordered_set
   for (int i = 0; i < weights.size(); i++)
   {

   }
}

int main()
{
    vector<int> weights = {20, 30, 40, 50, 60, 65, 75, 85};
    pair<int, int> tmp = mergeTwoPackages(weights, 100);
    cout << tmp.first << ", " << tmp.second << endl;
    cout << endl;
}
