/*
The "Flatten a Dictionary" Problem

Given a dictionary, write a function to flatten it. Consider the following input/output scenario for better understanding:

Input:

{
  'Key1': '1',
  'Key2': {
    'a' : '2',
    'b' : '3',
    'c' : {
      'd' : '3',
      'e' : '1'
      }
    }
}

Output:

{
  'Key1': '1',
  'Key2.a': '2',
  'Key2.b' : '3',
  'Key2.c.d' : '3',
  'Key2.c.e' : '1'
}
*/

#include <iostream>
using namespace std;

struct myObj
{
   bool isStringPresent;
   string val; // If val is ""
   unordered_map<string, struct myObj> valMap;
};

void flattenDict(unordered_map<string, myObj> myDict, string currentKey, unordered_map<string, myObj>& resultDict)
{

   for (int i = 0; i < myDict.size(); i++)
   {
      if (!myDict.getValue(i).isStringPresent)
      {
         if (!currentKey.isEmpty())
         {
            flattenDict(myDict.getValue(i), currentKey + "." + myDict.getKey(i), resultDict);
         }
         else
         {
            flattenDict(myDict.getValue(i), myDict.getKey(i), resultDict);
         }
      }
      else
      {
         string tmp;
         if (currentKey != "NULL")
         {
            tmp = currentKey + "." + myDict.getKey(i);
         }
         else
         {
            tmp = myDict.getKey(i);
         }
         resultDict[tmp] = myDict.getValue(i);    
      }
   }
}

unordered_map<string, myObj> flattenDictWrapper(unordered_map<string, myObj> myDict)
{
   // Assumption key cannot be "NULL"
   unordered_map<string, myObj> resultDict;
   flattenDict(myDict, "" ,resultDict);
  
   return resultDict;
}

int main() {
   cout << "Practice Makes Perfect";
   return 0;
}

