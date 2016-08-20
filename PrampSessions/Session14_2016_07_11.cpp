#include <iostream>
using namespace std;

int main() {
   
   for(int i  )
   
   cout << "Practice Makes Perfect";
   return 0;
}

// Logic:
// Go through arr1 and put all elements in a hash table (will store only the unique elements)
// Go through arr2 and put all elements in the same hash table (will store only the unique elements)
// Complexity arr1: n element; arr2: m elements. 
// Time complexity: O(n + m)
// Space Complexity: O(x) where x is the number of unique elements in arr1 and arr2

// Assumption: arr1 and arr2 are sorted in ascending order
// arr1: 5, 8, 10, 20, 30, 40, 50, 60
// arr2: 8, 15, 20
// op: 8, 20
// time Complexity: O(n+m)
vector<int> findDuplicates(vector<int> arr1, vector<int> arr2)
{
   int i = 0; 
   int j = 0;
   vector<int> uniqPersons;
   while (i < arr1.size() && j < arr2.size())
   {
      if (arr1[i] == arr2[j])
      {
         uniqPersons.push_back(arr[i]);
         i++; 
         j++;
      }
      else if (arr1[i] < arr2[j])
      {  
         i++;
      }
      else
      {
         j++;
      }
   }

   return uniqPersons;
}

// Complexity n log M where n is the number of elements in second array and m is the number of elements in the first array
vector<int> findDuplicatesOptimized(vector<int> arr1, vector<int> arr2)
{
   int i = 0; 
   int j = 0;
   vector<int> uniqPersons;
   
   vector<int> tmp;
   if (arr2.size() > arr1.size())
   {
      tmp = arr2;
      arr2 = arr1; 
      arr1 = tmp;
   }
   
   for (; j < arr2.size(); j++)
   {
      if (arr1.find(arr2[j]))  // Assuming find is doing a binary search on the array
      {
         uniqPersons.push_back(arr2[j]);
      }
   }
   
   return uniqPersons;
}
