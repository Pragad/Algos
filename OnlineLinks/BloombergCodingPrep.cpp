#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <stdlib.h>
using namespace std;

struct node
{
    int data;
    struct node* next;
};

/*
1) You have a ladder n-steps in height. You can either take one step or two steps up the ladder at a
time. How can you find out all the different combinations up the ladder? Then figure out an
algorithm that will actually print out all the different ways up the ladder. ie: 1,1,2,1,2,2... etc...

2) Write an algorithm to calculate the square root of a number.

3) Given an array of integers, write a method that returns an array of the same size where each
index is the product of all integers except itself, ie given array {1,2,3,4} return {24,12,8,6}
explicitly {2*3*4,1*3*4,1*2*4,1*2*3}

4) Give an array of 100 random integers. Write an algorithm to find the the closest 2 integers
(closest by position) in the array that add up to 100.

5) Given the root node to a singly linked list, write an algorithm to detect if there is a loop in the
list.

6) Given the function: "bool numExists( int array[], int array_len, int num )" where "array" is a
sorted array of integers. Determine if "num" exists in the array.
*/

//----------------------------------------------------------------------------------------------
// Problem 1: Ladder Problem
// Algorithm: Used Dynamic Programming to get the result.
//
//            I store the "n-1" and "n-2" lader positions. Then I append
//            '1' to 'n-1' positions and '2' to all 'n-2' positions.

// Utility function to print a Vector of Vector
void printVecOfVec(vector< vector<unsigned int> > vecOfVec)
{
    cout << "Vector of Vectors" << endl;
    for (unsigned int i = 0; i < vecOfVec.size(); i++)
    {
        for (unsigned int j = 0; j < vecOfVec[i].size(); j++)
        {
            cout << vecOfVec[i][j] << " ";
        }
        cout <<  endl;
    }
    cout << endl;
}

// Given a source vector and a number, it appends the number to each source vectors
// and puts the final values in the destination vector
void appendElementToVector(vector< vector <unsigned int> > src,
                           unsigned int num,
                           vector< vector <unsigned int> > &dest)
{
    for (int i = 0; i < src.size(); i++)
    {
        src[i].push_back(num);
        dest.push_back(src[i]);
    }
}

// Ladder Problem
void ladderDynamic(int number)
{
    vector< vector<unsigned int> > vecNminusTwo = {{}};
    vector< vector<unsigned int> > vecNminusOne = {{1}};
    vector< vector<unsigned int> > vecResult;

    for (int i = 2; i <= number; i++)
    {
        // Empty the result vector to hold fresh set
        vecResult.clear();

        // Append '2' to all N-2 ladder positions
        appendElementToVector(vecNminusTwo, 2, vecResult);

        // Append '1' to all N-1 ladder positions
        appendElementToVector(vecNminusOne, 1, vecResult);

        vecNminusTwo = vecNminusOne;
        vecNminusOne = vecResult;
    }

    printVecOfVec(vecResult);
}


//----------------------------------------------------------------------------------------------
// Problem 2: Square root of a number
//
// Algorithm 1: My algorithm to return Square root to nearest whole number.
//      For a given number, go from 1 to n/2 and find the number for which n * n = Given number.
//      Return the answer.
//
// Algorithm 2: Learned this Algo from Geeksforgeeks
double squareRoot(double number)
{
    if (number == 0 || number == 1)
    {
        return number;
    }

    // Start x from number / 2 and y from 1.
    // The point where x and y meets is the approximate square root.
    double x = number / 2;
    double y = 1;

    // Loop will continue till we get an accuracy of 0.001
    while ((x - y) > 0.001)
    {
        x = (x + y) / 2;
        y = number / x;
    }

    return x;
}

//----------------------------------------------------------------------------------------------
// Problem 3: Product of all other numbers
//
// Algorithm 1:
//     Find the product of all the numbers. Traverse the array and for each Index
//     divide by the element at the index. This will give product of all other numbers.
//
//     But this algorithm won't work if your current element is 0. In which case we would get
//     "Divide by Zero" Issue. Also if we have a Zero in the array, then product will become 
//     Zero.
// 
// Algorithm 2: 
//     n^2 complexity. For each element, find product of every other element by looping over
//     twice.
//     This algorithm also requires a space complexity of N. We can't replace an item in the
//     array as we have to use the array's original item for calculating other products.
//
// Algorithm 3:
//     Check the number of elements of the Array that is 0.
//     If One element is Zero, then find the new value for that element by multiplying all
//     other elements.
//     If two or more elements are Zero, then the new array will have all 0's.
//     Else use Algorithm 2.

// Helper function to check if array has 0.
unsigned int checkNumZerosInArray(int array[], int num)
{
    unsigned int countZeros = 0;
    for (unsigned int i = 0; i < num; i++)
    {
        if (array[i] == 0)
        {
            countZeros++;
        }
    }

    return countZeros;
}

// Helper function to where 0 has occured in the array.
unsigned int findZeroIndexInArray(int array[], int num)
{
    unsigned int zeroIndex = 0;
    for (unsigned int i = 0; i < num; i++)
    {
        if (array[i] == 0)
        {
            return zeroIndex;
        }
    }
}

int findAllOtherProducts(int array[], int num)
{
    int prod = 1;
    for (unsigned int i = 0; i < num; i++)
    {
        if (array[i] != 0)
        {
            prod *= array[i];
        }
    }

    return prod;
}

/*
// O(N^2) algo, that loops over twice
void productAllOtherIndexAlg1(int array[], int num)
{
    // Allocate a temporary array to store the results.
    int *tmpArray = new int[num];

    for (unsigned int i = 0; i < num; i++)
    {
        int totalProd = 1;
        for (unsigned int j = 0; j < num; j++)
        {
            if (i != j)
            {
                totalProd *= array[j];
            }
        }

        tmpArray[i] = totalProd;
    }

    // Copy back the result to the original array.
    for (unsigned int i = 0; i < num; i++)
    {
        array[i] = tmpArray[i];
    }

}
*/

// O(N) algo. Will work if no element is 0.
void productAllOtherIndexAlg2(int array[], int num)
{
    int totalProd = 1;

    // Get the product of all the elements
    for (unsigned int i = 0; i < num; i++)
    {
        totalProd *= array[i];
    }

    for (unsigned int i = 0; i < num; i++)
    {
        array[i] = totalProd / array[i];
    }
}

void productAllOtherIndex(int array[], int num)
{
    // If there is just one or lesser elements in the array, return;
    if (num <= 1)
    {
        return;
    }

    // If Zero is present
    if (checkNumZerosInArray(array, num) == 1)
    {
        unsigned int zeroIndex = findZeroIndexInArray(array, num);

        // As we have two elements as zero, set all the values to 0.
        std::fill(array, array + num, 0);
        
        array[zeroIndex] = findAllOtherProducts(array, num);
    }
    else if (checkNumZerosInArray(array, num) == 2)
    {
        // As we have two elements as zero, set all the values to 0.
        std::fill(array, array + num, 0);
    }
    else
    {
        productAllOtherIndexAlg2(array, num);
    }
}

//----------------------------------------------------------------------------------------------
// Problem 4: Closest 2 numbers that add up to 100.
// Algorithm: Find list of all numbers that add up to 100
//            From the list, choose the numbers that are closest.
//
// Cons: Extra space complexity and Extra variables

void closestSumOld(int arr[], unsigned int num, int targSum)
{
    unordered_map<int, int> diffHash;
    vector<int> firstIndex;
    vector<int> secondIndex;
    int minIndexDiff = INT_MAX;
    int resIndex1;
    int resIndex2;

    for (unsigned int i = 0; i < num; i++)
    {
        auto itr = diffHash.find(arr[i]);
        if (itr != diffHash.end())
        {
            // We have found a pair that sums to TARGET SUM
            firstIndex.push_back(itr->second);
            secondIndex.push_back(i);
        }
        else
        {
            // Add the difference to Hash. So that next time if we find the number we will
            // have a pair
            diffHash[targSum - arr[i]] = i;
        }
    }

    for (unsigned int i = 0; i < firstIndex.size(); i++)
    {
        if (abs(firstIndex[i] - secondIndex[i]) < minIndexDiff)
        {
            minIndexDiff = firstIndex[i] - secondIndex[i];
            resIndex1 = firstIndex[i];
            resIndex2 = secondIndex[i];
        }
    }
    
    cout << resIndex1 << " : " << resIndex2 << endl;
}

//----------------------------------------------------------------------------------------------
// Problem 4b: Closest 2 numbers that add up to 100.
// Algorithm: Find list of all numbers that add up to 100
//            From the list, choose the numbers that are closest.
//
// Cons: Extra space complexity and Extra variables

void closestSum(int arr[], unsigned int num, int targSum)
{
    unordered_map<int, int> diffHash;
    int firstIndex;
    int secondIndex;
    int minIndexDiff = INT_MAX;

    for (int i = 0; i < num; i++)
    {
        auto itr = diffHash.find(arr[i]);
        if (itr != diffHash.end())
        {
            // We have found a pair that sums to TARGET SUM
            if (abs(i - itr->second) < minIndexDiff)
            {
                firstIndex = itr->second;
                secondIndex = i;
                minIndexDiff = abs(i - itr->second);

                // Update the Hash Table so that we can have another closest pair
                // in the numbers yet to be traversed.
                diffHash[targSum - arr[i]] = i;
            }
        }
        else
        {
            // Add the difference to Hash. So that next time if we find the number we will
            // have a pair
            diffHash[targSum - arr[i]] = i;
        }
    }

    cout << firstIndex << " : " << secondIndex << endl;
}

//----------------------------------------------------------------------------------------------
// Problem 5:
// Algorithm: Have a slow and fast pointers. If slow pointer meets fast pointer then loop is 
// present.

// Check if there is a loop in the list
bool isLoopPresent(struct node* head)
{
    // If the list is empty return NULL
    if (head == NULL)
    {
        return false;
    }

    // So we have at least one element in the list.
    struct node* fastPtr = head;

    // Move head by one position and move fastPtr by two positions.
    // If head and fastPtr meetss then we have a loop.
    while (head != NULL && fastPtr != NULL)
    {
        head = head->next;

        if (fastPtr->next != NULL)
        {
            fastPtr = fastPtr->next->next;
        }
        else
        {
            // FastPtr's next is NULL.
            return false;
        }

        // If head meets fastPtr, then we have a loop
        if (head == fastPtr)
        {
            return true;
        }
    }

    return false;
}

//----------------------------------------------------------------------------------------------
// Problem 6:
// Algorithm: Use recursive binary search to find if element is present.

// This is a helper function to find if an element exists in an array
// using binary search.
bool numExistsInArray(int array[], int startIdx, int endIdx, int num)
{
    // VERY IMP:
    // If we have just one element in the array, check if element is present
    if (startIdx == endIdx)
    {
        return (array[startIdx] == num);
    }

    int middle_pos = (startIdx + endIdx) / 2;

    if (array[middle_pos] == num)
    {
        return true;
    }
    else if (num < array[middle_pos])
    {
        return numExistsInArray(array, startIdx, middle_pos - 1, num);
    }
    else
    {
        return numExistsInArray(array, middle_pos + 1, endIdx, num);
    }

}

bool numExists(int array[], int array_len, int num)
{
    // Invalid Test Case when length of array is 0 or less.
    if (array_len <= 0)
    {
        return false;
    }
    else
    {
        return numExistsInArray(array, 0, array_len - 1, num);
    }
}

//----------------------------------------------------------------------------------------------
int main()
{
    cout << endl;
    int arr[] = {1, 3, 4, 2, 3, 8};
    closestSum(arr, sizeof(arr) / sizeof(int), 6);
    //ladderDynamic(6);
    return 0;
}
