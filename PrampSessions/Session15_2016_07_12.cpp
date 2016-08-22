/*
The "Getting a Different Number" Problem

Given an array arr of n unique non-negative integers, how can you most efficiently find a non-negative integer that is not in the array?

Your solution should return such an integer or null if arr contains all possible integers.
Analyze the runtime and space complexity of your solution.
*/

#include <iostream>
using namespace std;

// hello. same here. I am unable to hear you. Okay.
//*hi, nice to meet you. Same here, we can chat , take your time, i am reading it too

// I am looking at my problem. Give me about two -three minutes.
// Logic 1: Brute force approach
// Go through all elements of the array and put them in a hash table (key of the hash table will be the element)
// Now go from 1 to all possible numbers and see if it is in the hash table. 
// Complexity O(n + n); "n" to put all elements in the hash table and "n" to find a unique number.
//* this is a good idea. One thing about complexity: O(n+n) is O(n). Would you like to start coding? 
// Yeah that's right. I just called it out explicitly. Sure

int findDifferentNumber(vector<unsigned int> arr)
{
   unordered_map<unsigned int, unsigned int> uniqNumMap;
   for (auto num : arr)
   {
      auto itr = uniqNumMap.find(num); // Assumption is that the array has unique elements. So this is an extra check.
      if (itr != uniqNumMap.end())     // Ideally we should never go to If block and always go to Else block
      {
         continue;
      }
      else
      {
         uniqNumMap[num] = 1; // Just storing 1 for value. We are never going to use the value.
      }
   }
   
   // Once we have reached the last possible element that could fit in unsigned int stop the program
   for (unsigned int i = 0; i < pow(2, sizeof(unsigned int)); i++) 
   {
      auto itr = uniqNumMap.find(i)
      if (itr == uniqNumMap.end()) // If "i" is not present in the map then return it
      {
         return i;
      }
   }
   
   return -1; // -1 to indicate that we don't have such an element.
}

// I can think of another logic
// Logic 2:
// Go through all the elements in the array and find the maximum number that we have.
// Return 1 + max number that we have so far. 
// Complexity O(n): "n" to find the maximum in an array
// * I am here, reading , never mind I will type
// What browser are you using ? I will try to connect from Chrome. Last time it worked for me in chrome.
int main() {
   cout << "Practice Makes Perfect";
   return 0;
}
