#include <iostream>
using namespace std;

/*
The "Smallest Substring of All Characters" Problem

Given an array with unique characters arr and a string str, find the smallest substring of str containing all characters of arr.

Example:
arr: [x,y,z], str: xyyzyzyx
result: zyx

Implement your solution and analyze the runtime complexity
*/
string smallestSubStringWithAllChars(string str, vector<char> arr)
{
   unordered_map<char, uint32_t> uniqCharMap;
   unordered_map<char, uint32_t> uniqStrMap;
   uint32_t count = 0;
   uint32_t startIndex = 0;
   uint32_t subStringSize = 0;
   uint32_t stIdx = 0;
   uint32_t endIdx = 0;
   uint32_t minSubStringSize = INT_MAX;
  
   for (uint32_t i = 0; i < arr.size(); i++)
   {
       uniqCharMap[arr[i]] = 1;
   }
  
   // str: xyyzyzyx; arr = [x, y, z]
   // Count should be increased only for the first occurences of x, y and z.
   for (uint32_t i = 0; i < str.length(); i++)
   {
      auto itr = uniqCharMap.find(str[i]);
      if (itr != NULL)
      {
         auto itr2 = uniqStrMap.find(str[i]);
         if (itr2 == NULL || itr2->second == 0) // Will become zero in Line 56
         {
            count++;
            uniqStrMap[str[i]] = 1;
         }
         else
         {
            uniqStrMap[str[i]] = ++(itr2->second);
         }
      }
     
      // Will enter this loop only when str is "xyyz". My start index will become 1 which will make the count less than
      // arr.size(). So break out of while loop.
      while (count == arr.size()) // I have found a substring
      {
         subStringSize = i - startIndex + 1;//
        
         if (subStringSize < minSubStringSize)
         {
            stIdx = startIndex;
            endIdx = i;
            minSubStringSize = subStringSize;
          
         }
        
         auto itr3 =  uniqStrMap.find(str[startIndex])
         {
            uniqStrMap[str[startIndex]] = --(itr3->second); // IF this count becomes 0,, then I no longer have a substring
            if (itr3->second == 0)
            {
               count--;
            } 
         }
         startIndex++;

      }
   }
  
   return str.substring(stIdx, endIdx - stIdx + 1);
}

// 2, 6, 3, 12, 56, 8

//Implement  heap.replace and heap.findMin()
// That is fine. You don't have to implement that.
// What would be the time and space complexity of this logic ?
// first , for the creating minheap, it should be O(k)....

// for replacing the minheap, it should be O(logk);

// then the over all should be O(K)+O(logk*(n-k)) // since j // very good
// heap.findMin()

// but 
// I forgot to say the time complexity for my code.  that's fine 

// but I have to say, I still do not know how to write the minheap exactly
// I need to check or search it online
// That's fine for now. After the interview you can see how to use "priority_queue" in C++. It is data structure for Heap
// Very simple to use it.

// thanks a lot !
// could you please paste the answers of this question here ? I want to implement it after our talk
// Sure. Is this your first interview ? yes   i am a undergraduate student ... junior 
// After the interview, if you go to your Dashboard in pramp, you will be able to see the detailed solution with code and all the hints.
// I will paste it anyway here. // thanks a lot !!!

// If you don't mind where are you located ? Now, in Boston
// Nice. It is pretty late for you. I am in California. Cool, I Love California, 
// Glad to hear that. Where are you studying ? Even I am studying here. in Boston University , cs major . 
// Nice. All the best for your future interviews.  thanks ! same to you 
// Thanks. Shall we end the interview ? // ok , see you . you too
function kHeapSort(arr, k)
   h = new MinHeap()
   n = length(arr)
   for i from 0 to k:
      h.insert(arr[i])
   for i from k+1 to n-1:
      arr[i-(k+1)] = h.extractMin()
     h.insert(arr[i])
   for i from 0 to k:
     arr[n-k-1 + i] = h.extractMin()
   return arr
        

vector<int> sortArray(vector<int>&arr,int k,int n){ // arr.size() == n;
   int *tempArray = new int[k+1];
   for(int i=0;i<=k&&i<n;k++){
      tempArray[i] = arr[i];
}
   Minheap heap = (tempArray,k+1);
   
   for(int i=k+1,j=0;j<n;i++,j++){ /// O(n-k)
      if(i<n) arr[j] = heap.replace(tempArray[i]); // repalce with the new one , return the old root 
      else arr[j] = heap.findMin();// return the minimum (root)
   }
   
 
}

// k = 2
// Where can the first element be in arr ?
// first, second , third 
// Look at Index 0, 1, 2 and put the smallest in Index 0.
// 
// Look at Index  1, 2 ,3 and put the smallest in Index 1.
//
// for i = 0: look at index 0, 1, 2 and swap the minimum element with the element at index 0
// for i = 1: look at index 1, 2, 3 and swap the minimum element with the element at index 1
// for i = 2: look at index 2, 3, 4 and swap the minimum element with the element at index 2

int main() {
   cout << "Practice Makes Perfect";
   return 0;
}


