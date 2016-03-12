#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>      // For ostringstream
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

// 6.3a Find all substrings of an array using SUBSTING function.
//void printAllSubSring(int arr[], int num)

// 6.3b Recrusive way to find all substrings
//void printAllSubsetRec(int arr[], int num)

// 6.4 Find all permutations of an array
//void printAllPermutations(int arr[], int num)

// 6.4b Recrusive way to find all permutations
//void printAllPermutationsRec(int arr[], int num)

// Helper function to convert Int array to string.
//string convertIntArrToString(int arr[], int num)

// 6.3a Find all substrings of an array using SUBSTING function.
//void printAllSubset2(int arr[], int num)

void printArray(int arr[], int num)
{
    for (int i = 0; i < num; i++)
    {
        cout << arr[i] << " ";
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

// 6.10 Find all substrings of an array using SUBSTING function.
// http://stackoverflow.com/questions/15726641/find-all-possible-substring-in-fastest-way
void printAllSubSring(int arr[], int num)
{
    string tmpStr = convertIntArrToString(arr, num);
    cout << endl << "TmpStr: " << tmpStr << endl;
    
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
// 6.10b Recrusive way to find all substrings
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

// 6.11 Find all permutations of an array
void printAllPermutations(int arr[], int num)
{

}

// 6.11b Recrusive way to find all permutations
void printAllPermutationsRec(int arr[], int num)
{

}


int main()
{
    int arr[] = {4, 1, 6, 4, 4, 7, 8, 2, 3, 1, 4, 4};

    printArray(arr, sizeof(arr) / sizeof(int));

    cout << "Three Way Quick Sort" << endl;
    threeWayQuickSort(arr, sizeof(arr) / sizeof(int));
    printArray(arr, sizeof(arr) / sizeof(int));


    //int arr2[] = {7, 9, 5, 6, 3, 2}; 
    //int arr2[] =  { 3, 2, 6, 9, 5 }; 
    int arr2[] =  { 10, 1, 12, 3, 4, 28, 1 }; 
    
    //maxDifference(arr2, sizeof(arr2) / sizeof(int));

    int arr3[] = {1, 2, 3, 4};
    printAllSubset(arr3, sizeof(arr3) / sizeof(int));
    cout << endl;
    cout << "Print All Substring" << endl;
    printAllSubSring(arr3, sizeof(arr3) / sizeof(int));
    cout << endl;

    int arr4[] = {1, 2, 3, 4};
    cout << "Print All Subsets Using Recursion" << endl;
    vector < vector <int> > subsetVec;
    printAllSubsetRec(arr4, 0, sizeof(arr4) / sizeof(int) - 1, subsetVec);
    printVectorOfVectors(subsetVec);
    cout << endl;
}
