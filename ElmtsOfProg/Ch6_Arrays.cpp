#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>      // For ostringstream
#include <unordered_map>
using namespace std;

// 6.1 Dutch National Flag Proble / 3 way quick sort
//void threeWayQuickSort(int arr[], int num)

// 6.2 Max Difference in Array
//int maxDifference(int arr[], int num)

// Helper function
// Given a number, find the number of bits required to represent the number.
//int numBitsPresent(int num)

// 6.3 Find all subsets of an array
//void printAllSubset(int arr[], int num)

// Helper function to convert Int array to string.
//string convertIntArrToString(int arr[], int num)

// 6.3b Find all substrings of an array using SUBSTING function.
//void printAllSubSring(int arr[], int num)

// 6.3c Recrusive way to find all substrings
//void printAllSubsetRec(int arr[], int num)

// 6.4 Find all permutations of an array
//void printAllPermutations(int arr[], int num)

// 6.4b Recrusive way to find all permutations
//void printAllPermutationsRec(int arr[], int num)

// 6.5 Print all anagrams of a string
//void printAllAnagrams(string str)

// 6.6 Print all possible strings of length k that can be formed from a set of n characters
//void printAllKLengthStrings(string str, uint32_t k)

void printArray(int arr[], int num)
{
    for (int i = 0; i < num; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void printArrayEndIdx(int arr[], uint32_t endIdx)
{
    for (int i = 0; i <= endIdx; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void printVectorInt(vector<int> nums, uint32_t eI)
{
    for (uint32_t i = 0; i <= eI; i++)
    {
        cout << nums[i] << " ";
    }

    cout << endl;
}

void printVectorChar(vector<char> vecChar)
{
    for (char c : vecChar)
    {
        cout << c << " ";
    }

    cout << endl;
}

// 6.1 Dutch National Flag Proble / 3 way quick sort
void threeWayQuickSort(int arr[], int num)
{
    int pivot = 4;
    int endIdx = num-1;
    int eqIdx = 0;
    bool endFlag = false;

    for (int i = 0; i <= endIdx; i++)
    {
        // Traverse from End till you find an element that
        // is less than or equal to pivot.
        while (endIdx > i &&
               arr[endIdx] > pivot &&
               endFlag)
        {
            endIdx--;
        }

        if (arr[i] > pivot)
        {
            int temp = arr[i];
            arr[i] = arr[endIdx];
            arr[endIdx] = temp;
            // We don't know if element at 'i' is less or equal to pivot.
            // So we have to process it.
            i--;
            endIdx--;
            endFlag = true;
        }
        else if (arr[i] < pivot)
        {
            endFlag = false;
            int temp = arr[i];
            arr[i] = arr[eqIdx];
            arr[eqIdx] = temp;
            eqIdx++;
        }
        else
        {
            endFlag = false;
        }
    }
}

// 6.2 Max Difference in Array
int maxDifference(int arr[], int num)
{
    int tmpDiff = INT_MIN; 
    int maxDiff = tmpDiff;
    int tmpSmall = arr[0];
    int finalSmall = arr[0];
    int tmpLarge = arr[0];
    int finalLarge = arr[0];

    for (int i = 1; i < num; i++)
    {
        if (arr[i] > tmpLarge)
        {
            tmpLarge = arr[i];
        }
        else if (arr[i] < tmpSmall)
        {
            tmpSmall = arr[i];
            tmpLarge = arr[i];
        }

        tmpDiff = tmpLarge - tmpSmall;
        if (tmpDiff > maxDiff)
        {
            maxDiff = tmpDiff;
            finalSmall = tmpSmall;
            finalLarge = tmpLarge;
        }
    }

    cout << endl << "Num 1: " << finalSmall << "; Num 2: " << finalLarge << "; Diff: " << maxDiff << endl;
}


//-----------------------------------------------------------------------------------------
// Helper function
// Given a number, find the number of bits required to represent the number.
int numBitsPresent(int num)
{
    return (log2(num) + 1);
}

// 6.3 Find all subsets of an array
void printAllSubset(int arr[], int num)
{
    int powerSetSize = pow(2, num);

    for (int i = 0; i < powerSetSize; i++)
    {
        int temp = i;
        int idx = 0;
        while (idx < numBitsPresent(temp))
        {
            if ((temp & (1 << idx)) != 0)
            {
                cout << arr[idx] << ",";
            }
            idx++;
        }
        cout << endl;
    }
}

// Helper function to convert Int array to string.
string convertIntArrToString(int arr[], int num)
{
    //ostringstream oss;
    std::ostringstream foo;
    foo.str("");

    for (int i = 0; i < num; i++)
    {
        foo << (arr[i]);
    }

    return foo.str();

}

// 6.3b Find all substrings of an array using SUBSTING function.
// http://stackoverflow.com/questions/15726641/find-all-possible-substring-in-fastest-way
void printAllSubSring(int arr[], int num)
{
    string tmpStr = convertIntArrToString(arr, num);
    
    for (int i = 0; i < num; i++)
    {
        // VERY IMP "num-i+1"
        // This gives the NUMBER of elements for each i
        for (int j = 1; j < num-i+1; j++)
        {
            cout << tmpStr.substr(i, j) << " ";
        }
    }
}

void copyVectorToItself(vector < vector <int> >& subsetVec)
{
    int vecSize = subsetVec.size();
    for (int i = 0; i < vecSize; i++)
    {
        subsetVec.push_back(subsetVec[i]);
    }
}

void printVectorOfVectors(vector < vector <int> > subsetVec)
{
    for (int i = 0; i < subsetVec.size(); i++)
    {
        for (int j = 0; j < subsetVec[i].size(); j++)
        {
            cout << subsetVec[i][j] << " ";
        }
        cout << " , ";
    }
}

// http://stackoverflow.com/questions/728972/finding-all-the-subsets-of-a-set
// 6.3c Recrusive way to find all substrings
void printAllSubsetRec(int arr[], int sI, int eI, vector < vector <int> >& subsetVec)
{

    if (eI == sI)
    {
        vector<int> temp{arr[eI]};
        subsetVec.push_back(temp);
    }
    else
    {
        printAllSubsetRec(arr, sI, eI - 1, subsetVec);

        int prevSize = subsetVec.size();
        copyVectorToItself(subsetVec);

        for (int i = prevSize; i < subsetVec.size(); i++)
        {
            subsetVec[i].push_back(arr[eI]);
        }

        vector<int> tempVec = {arr[eI]};    
        subsetVec.push_back(tempVec);
    }
}

// 6.3c2 Recrusive way to find all substrings
// VERY IMP:
//      1. USe separate index for result
//      2. sI can go bigger than eI
void printAllSubSetRecVer2(int arr[], uint32_t sI, uint32_t eI, int result[], uint32_t resIdx)
{
    if (sI > eI)
    {
        return;
    }

    if (sI == eI)
    {
        result[resIdx] = arr[sI];
        printArrayEndIdx(result, resIdx);
        return;
    }

    for (uint32_t i = sI; i <= eI; i++)
    {
        result[resIdx] = arr[i];
        printArrayEndIdx(result, resIdx);

        printAllSubSetRecVer2(arr, i+1, eI, result, resIdx + 1);
    }
}

void printAllSubSetVer2(int arr[], uint32_t num)
{
    int* result = new int[num];
    printAllSubSetRecVer2(arr, 0, num - 1, result, 0);
    delete[] result;
}

// 6.4 Find all permutations of an array
// Replace start index with Current index. All other elements except current index should be added.
void printAllPermutationsRecUtil(int arr[], uint32_t cI, uint32_t eI, int result[], uint32_t resIdx)
{
    if (cI > eI)
    {
        return;
    }

    if (cI == eI)
    {
        result[resIdx] = arr[cI];
        printArrayEndIdx(result, resIdx);
        return;
    }

    for (uint32_t i = 0; i <= eI; i++)
    {
        result[resIdx] = arr[i];
        printArrayEndIdx(result, resIdx);

        printAllPermutationsRecUtil(arr, i+1, eI, result, resIdx + 1);
    }
}



void printAllPermutationsRec(int arr[], int num)
{
    int* result = new int[num];
    printAllPermutationsRecUtil(arr, 0, num - 1, result, 0);
    delete[] result;

}

// 6.5 Print all anagrams of a string
void printAnagramsUtils(vector<char> vecStr, char result[], uint32_t curLen, uint32_t tarLen)
{
    if (curLen == tarLen)
    {
        result[curLen] = 0;
        cout << result << endl;
        return;
    }

    for (uint32_t i = 0; i < vecStr.size(); i++)
    {
        // VERY IMP: Use temp array. It is needed to re insert the element back to the vector
        char temp = vecStr[i];
        result[curLen] = temp;
        vecStr.erase(find(vecStr.begin(), vecStr.end(), temp));
        printAnagramsUtils(vecStr, result, curLen + 1, tarLen);
        vecStr.insert(vecStr.begin(), temp);
    }
}

void printAllAnagrams(string str)
{
    char result[str.size() + 1];

    vector<char> vecStr(str.begin(), str.end());

    printVectorChar(vecStr);
    printAnagramsUtils(vecStr, result, 0, str.size());
}

void printAnagramsUtilsStr(vector<char> vecStr, string result, uint32_t curLen, uint32_t tarLen)
{
    if (curLen == tarLen)
    {
        cout << result << endl;
        return;
    }

    for (uint32_t i = 0; i < vecStr.size(); i++)
    {
        // VERY IMP: Use temp array. It is needed to re insert the element back to the vector
        char temp = vecStr[i];
        result += temp;
        vecStr.erase(find(vecStr.begin(), vecStr.end(), temp));
        printAnagramsUtilsStr(vecStr, result, curLen + 1, tarLen);
        vecStr.insert(vecStr.begin(), temp);
        result.erase(result.find(temp));
    }
}

void printAllAnagramsStr(string str)
{
    string result = "";
    vector<char> vecStr(str.begin(), str.end());

    printVectorChar(vecStr);
    printAnagramsUtilsStr(vecStr, result, 0, str.size());
}

// Problem 6.7
// http://stackoverflow.com/questions/12477339/finding-anagrams-for-a-given-word
void printAllAnagramsUsingDict(string str)
{
    // Part 1. Update the dictionary contents into a hash table
    vector<string> dict = {"hello", "world"};
    unordered_map<string, vector<string> > dictHash;

    for (uint32_t i = 0; i < dict.size(); ++i)
    {
        string temp = dict[i];
        sort(temp.begin(), temp.end());

        auto itr = dictHash.find(temp);
        if (itr != dictHash.end())
        {
            itr->second.push_back(dict[i]);
        }
        else
        {
            // VERY IMP: '{' and '}'
            dictHash[temp] = vector<string> {dict[i]};
        }
    }

    // Part 2: For a given string print all the anagrams
    string sortStr = str;
    sort(sortStr.begin(), sortStr.end());
    auto it2 = dictHash.find(sortStr);
    if (it2 != dictHash.end())
    {
        vector<string> vecAnagram = it2->second;
        for (string s : vecAnagram)
        {
            cout << s << ", ";
        }
        cout << endl;
    }
    else
    {
        cout << "Dictionary doesn't contain the word" << endl;
    }
}

// 6.4b Recrusive way to find all permutations
// Using Char array
void printAllKLengthStringsRec(string str, uint32_t tarNum, uint32_t curNum, char res[])
{
    if (curNum == tarNum)
    {
        res[curNum] = 0;
        cout << res << endl;
        return;
    }

    for (char c : str)
    {
        // VERY IMP: ONE FOR LOOP IS ENOUGH
        //for (uint32_t i = curNum; i < tarNum; i++)
        if (curNum < tarNum)
        {
            res[curNum] = c;
            printAllKLengthStringsRec(str, tarNum, curNum + 1, res);
        }
        //res.pop_back();
    }

}

// Using Strings
void printAllKLengthStringsRec(string str, uint32_t tarNum, uint32_t curNum, string res)
{
    if (curNum == tarNum)
    {
        cout << res << endl;
        return;
    }

    for (char c : str)
    {
        res += c;
        printAllKLengthStringsRec(str, tarNum, curNum + 1, res);
        res.pop_back();
    }

}

void printAllKLengthStrings(string str, uint32_t k)
{
    string result;
   // char res[3];
    char c;
    printAllKLengthStringsRec(str, k, 0,  result);
    //printAllKLengthStringsRec(str, k, 0,  res);
}


int main()
{
    // 3 way quick sort
    {
        int arr[] = {4, 1, 6, 4, 4, 7, 8, 2, 3, 1, 4, 4};

        printArray(arr, sizeof(arr) / sizeof(int));

        cout << "Three Way Quick Sort" << endl;
        threeWayQuickSort(arr, sizeof(arr) / sizeof(int));
        printArray(arr, sizeof(arr) / sizeof(int));
    }

    // Max difference in an array
    {
        //int arr2[] = {7, 9, 5, 6, 3, 2}; 
        //int arr2[] =  { 3, 2, 6, 9, 5 }; 
        int arr2[] =  { 10, 1, 12, 3, 4, 28, 1 }; 
        
        //maxDifference(arr2, sizeof(arr2) / sizeof(int));
    }

    // Print all subsets
    {
        int arr3[] = {1, 2, 3, 4};
        printAllSubset(arr3, sizeof(arr3) / sizeof(int));
        cout << endl;
        cout << "Print All Substring" << endl;
        printAllSubSring(arr3, sizeof(arr3) / sizeof(int));
        cout << endl;

        // Version 2
        cout << "Print All Subsets Version 2" << endl;
        vector<int> nums(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));
        printAllSubSetVer2(arr3, sizeof(arr3) / sizeof(arr3[0]));
    }

    // Print all Subsets using recursion
    {
        int arr4[] = {1, 2, 3, 4};
        cout << "Print All Subsets Using Recursion" << endl;
        vector < vector <int> > subsetVec;
        printAllSubsetRec(arr4, 0, sizeof(arr4) / sizeof(int) - 1, subsetVec);
        printVectorOfVectors(subsetVec);
        cout << endl;
    }

    // Print All Permutation of an array
    {
        int arr[] = {1, 2, 3};
        // Goes on infinite loop
        //printAllPermutationsRec(arr, sizeof(arr)/sizeof(arr[0]));
    }

    // Print all permutations of a String
    // Print all anagrams of a string
    {
        cout << "Print All Anagrams Recursion" << endl;
        string str = "abc";
        printAllAnagrams(str);

        cout << "Print All Anagrams Recursion" << endl;
        string str2 = "abc";
        printAllAnagramsStr(str2);
    }

    // Print all possible strings of length k that can be formed from a set of n characters 
    {
        cout << "All Possible strings of Length k" << endl;
        string s = "abc";
        printAllKLengthStrings(s, 2);
    }
}
