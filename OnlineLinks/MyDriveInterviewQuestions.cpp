#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>        // std::fill_n, std::reverse, std::swap
#include <queue>            // Priority Queue
#include <typeinfo>         // typeid
#include <vector>
#include <cmath>            // ciel
#include <cstring>          // memset
#include <functional>       // std::function
#define __STDC_LIMIT_MACROS
#include <cstdint>
using namespace std;

// Used to print out additionals log messages
// #define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

/*
 * PROBLEM 1. Given two strings, find the first non matching character
 * bool     findFirstNonMatchingChar(string s1, string s2, char& result)
 *
 * PROBLEM 2: Find the unique character present in a string
 * char     findUniqueChar(string str)
 *
 * PROBLEM 3: Count the number of islands in a 2D matrix
 * uint32_t countConnectedIslands(int** twoDmat, uint32_t rows, uint32_t cols)
 *
 * PROBLEM 4: Given a input stream of numbers, compute the median after each entry
 * int      medianOfStreams(int number, maxHeap, minHeap)
 *
 * PROBLEM 5. Find the max sub array sum
 * int      maxSumSubArray(int arr[], int num)
 * void     maxSumSubSequence(int arr[], int num)
 *
 * PROBLEM 5b. Find the max sub array product
 * int maxProduct(vector<int>& nums)
 * 
 * PROBLEM 5c. Find the SUB ARRAY that will give you a sum
 * bool subArrayWithSum(int arr[], uint32_t num, int sum)
 *
 * PROBLEM 5d. Find ALL SUB ARRAYS that will give you a sum
 * bool allSubArraysWithSum(int arr[], uint32_t num, int sum)
 *
 * PROBLEM 5e. Find the max sum such that no two elements are adjacent
 * int maxLengthSubArraySum(vector<int> nums)
 *
 * PROBLEM 6. Finding greatest sum of elements of array which is divisible by a given number
 * int greatestSumOfSubarrayDivisibleByK(vector<int> nums, int divNum)
 *
 * PROBLEM 7. Print Matrix Diagonally
 * void printMatrixDiagonally(int** twoDMatrix, uint32_t rows, uint32_t cols)
 *
 * PROBLEM 7b. Print Matrix in Spiral Order
 * void printMatrixSpiralOrder(vector< vector <int> > twoDMatrix)
 *
 * PROBLEM 8. Given a string of 1s and 0s with '?' in between. A '?' can be either one or zero.
 * void printCombinationOnesZeros(string str, uint32_t stIdx, uint32_t lastQMarkPos)
 *
 * PROBLEM 9. Given an integer x, find ONE digit who is equal to its adjacent digits,
 * int largestNumByRemovingDup(int number)
 *
 * PROBLEM 10. Find Equilibrium Index of an array. Sum of left elements = Sum of Right elements
 * unint32_t equilibriumIndex(vector<int> nums)
 *
 * PROBLEM 11. Generalized Abbrevation
 * void generalizedAbbrevation(string word)
 *
 * PROBLEM 12. Find if two rectangles overlap
 * bool isRectanglesOverlap(Point a1, Point a2, Point b1, Point b2)
 *
 * PROBLEM 13. Find Largest Subarray with equal number of 0s and 1s
 * void printLargestSubArrayZeroOne(int arr[], uint32_t num)
 *
 * PROBLEM 14. 3 number sum AND closest sum
 * void printThreeNumSum(int arr[], uint32_t num, int sum)
 * void printThreeNumClosestSum(int arr[], uint32_t num, int sum)
 *
 * PROBLEM 15. 1 Missing and 1 Duplicate
 * void findMissingAndDuplicate(vector<int> nums)
 *
 * PROBLEM 16. 2 missing numbers
 * void findTwoMissing(vector<int> nums, uint32_t totalNums)
 
 * PROBLEM 17. Find minimum number of conference room required
 * uint32_t minConfRoomRequired(vector<struct MeetingTime> meetingsList)
 *
 * PROBLEM 18. Find median of two sorted arrays of same size
 * int medianTwoSortedSameSizeArrays(int arr1[], uint32_t num1, int arr2[], uint32_t num2);
 *
 * PROBLEM 19. Find median of two sorted arrays of different size
 * int medianTwoSortedDiffSizeArrays(int arr1[], uint32_t num1, int arr2[], uint32_t num2);
 *
 * PROBLEM 20. Find Kth smallest element in Union of two sorted arrays
 * int kthSmallestElement(int arr1[], uint32_t num1, int arr2[], uint32_t num2);
 *
 * PROBLEM 21. Kth Smallest Element in Unsorted Array
 * int kthSmalledInUnsorted(int arr[], uint32_t num, uint32_t k)
 *
 * PROBLEM 21b. Kth Smallest Element in Unsorted Array using QuickSelect
 * PROBLEM 21c. Simple Quick Sort and Three way Quick Sort
 * int kthSmallQuickSelect(vector<int> nums, uint32_t k)
 * pair<int32_t, int32_t> threeWayQuickSortPartition(vector<int>& nums, int32_t stIdx, int32_t endIdx)
 * int32_t quickSortPartition(vector<int>& nums, int32_t stIdx, int32_t endIdx)
 * void quickSortRec(vector<int>& nums, int32_t stIdx, int32_t endIdx)
 * void quickSortThreeWayRec(vector<int>& nums, int32_t stIdx, int32_t endIdx)
 *
 * PROBLEM 22. Find if an element is present in a row column sorted matrix
 * int findFirstSmallerIndex(vector< vector< int > > twoD, int elmt)
 * bool isElementPresentInRowColMatrix(vector<vector<int> > twoD, int elmt)
 * bool isElementPresentInRowColMatrixModified(vector<vector<int> > twoD, int elmt)
 *
 * PROBLEM 23. Multiplication of two very large numbers
 * int largeNumberMultiplication(int arr[], uint32_t num, uint32_t k)
 *
 * PROBLEM 23b. Binary Decimal Conversions
 * void convertDecimalNumToBinaryStrRec(uint32_t num, string strBin)
 * string convertDecimalNumToBinaryStr(uint32_t num)
 * string convertDecimalStrToBinaryStr(string strDec)
 * string convertBinaryStrToDecimalStr(string strBin)
 * uint32_t convertBinaryStrToDecimalNum(string strBin)
 *
 * PROBLEM 24. Finding the Minimum Window in S which Contains All Elements from T
 * uint32_t minWindowContainingString(string str1, string str2)
 *
 * PROBLEM 25. Find if an element is present in a rotated sorted array
 * bool binarySearchRecursion(vector<int> nums, int low, int high, int elmt)
 * bool binarySearch(vector<int> nums, int elmt)
 * int findInSortedRotatedArray(vector<int> nums, int elmt)
 *
 * PROBLEM 26. Find Award Budget Cuts Problem
 * uint32_t findGrantsCap(vector<int> grants, uint32_t budget)
 *
 * PROBLEM 27. Find if a Bit Stream is divisible by 3
 * uint32_t (int arr[], uint32_t num, uint32_t k)
 *
 * PROBLEM 28. Sort an array of 0s, 1s and 2s
 * void sortZeroOneTwoDutchFlag(vector<int> &nums)
 *
 * PROBLEM 29. Find majority element in an array
 * bool isMajorityElementPresent(vector<int> nums)
 *
 * PROBLEM 30. Sorting almost sorted array misplaced by k elements
 * void sortKsortedArray(vector<int>& nums, uint32_t k)
 *
 * PROBLEM 31. Given N points, find k points closest to 0,0
 * vector<point> findKclosestPoints(vector<point> pointsList, uint32_t k)
 *
 * PROBLEM 32. Move even numbers to front and odd numbers to back with Order preserved
 * void moveEvenNosOddNosWithOrder(vector<int> nums)
 *
 * PROBLEM 33. Given list of software dependencies. Find order of software installation
 * vector<char> findSoftwareInstallationOrder(vector<softwawre> dependencyList)
 *
 * PROBLEM 34. Find angle between hour and minute hand of clock
 * uint32_t findAngleBtwnHourMinute(uint32_t hour, uint32_t min)
 *
 * PROBLEM 35. Find all pairs of numbers that add to a sum
 * void findPairsAddingToSum(const vector<int>& nums, int sum)
 *
 * PROBLEM 36. A function with inclusion times and exclusion times
 * pair<uint32_t, uint32_t> findInclusiveExclusiveTimeOfFunction(const vector<functionDetails>& funcTimes, string funcName)
 *
 * PROBLEM 37. 
 */

// Structure to define a x-axis y-axis point
struct Point
{
    int x;
    int y;
};

void printVectorInt(vector<int> nums)
{
    for (int num : nums)
    {
        cout << num << ", ";
    }
    cout << endl;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 1. Given two strings, find the first non matching character
//            hello
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------
bool findFirstNonMatchingChar(string s1, string s2, char& result)
{
    uint32_t shortLen = (s1.length() < s2.length() ? s1.length() : s2.length());
    uint32_t i = 0;

    if (s1.empty() && s2.empty())
    {
        return false;
    }

    if (s1.empty())
    {
        result = s2[0];
        return true;
    }

    if (s2.empty())
    {
        result = s1[0];
        return true;
    }

    for (; i < shortLen; i++)
    {
        if (s1[i] != s2[i])
        {
            // Found a mismatch. Either s1[i] or s2[i]
            uint32_t x = i + 1;
            uint32_t y = i + 1;

            // Find first occurence of s2[i] in s1
            for (; x < shortLen; x++)
            {
                if (s1[x] == s2[i])
                {
                    break;
                }
            }    

            // Find first occurence of s1[i] in s2
            for (; y < shortLen; y++)
            {
                if (s2[y] == s1[i])
                {
                    break;
                }
            }

            if (x < y)
            {
                result = s1[i];
                return true;
            }
            if ( x > y)
            {
                result = s2[i];
                return true;
            }
        }
    }

    // If string 1 is bigger then return s1[i]
    if (i < s1.length())
    {
        result = s1[i];
        return true;
    }

    // If string 2 is bigger then return s2[i]
    if (i < s2.length())
    {
        result = s2[i];
        return true;
    }

    return false;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 2: Find the unique character present in a string
//            hlllhabcdedcba
//            Ans: e
// ------------------------------------------------------------------------------------------------
struct uniqChar
{
    bool isPresent;
    uint32_t index;
};

char findUniqueChar(string str)
{
    if (str.empty())
    {
        return str[0];
    }

    uint32_t minIndex = std::numeric_limits<std::int32_t>::max();
    unordered_map<char, uniqChar> charMap;

    for (uint32_t i = 0; i < str.length(); i++)
    {
        auto itr = charMap.find(str[i]);
        if (itr != charMap.end())
        {
            itr->second.isPresent = true;
        }
        else
        {
            charMap[str[i]] = {false, i};
        }
    }

    //for (unordered_map<char, uniqChar>::iterator itr = charMap.begin(); itr != charMap.end(); itr++)
    for (auto it = charMap.begin(); it != charMap.end(); it++)
    {

        if (!(it->second).isPresent)
        {
            if ((it->second).index < minIndex)
            {
                minIndex = it->second.index;
            }
        }
    }

    // VERY IMP: What if we don't have a Unique Char. Min index could be infinity.
    if (minIndex < str.length())
    {
        return str[minIndex];
    }
    else
    {
        // Return NULL if nothing is present.
        return 0;
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 3: Count the number of islands in a 2D matrix
// ------------------------------------------------------------------------------------------------
template <size_t rows, size_t cols>
void printTwoDMatrix(int (&twoDmat)[rows][cols])
{
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            cout << twoDmat[i][j] << ", ";
        }
        cout << endl;
    }
}

template <typename T>
void printTwoDPtrToPtr(T** array, uint32_t rows, uint32_t cols)
{
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            cout << array[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

int rowDirection[8] = {-1, -1, -1, 0 , 0, 1 , 1, 1};
int colDirection[8] = {-1, 0 , 1 , -1, 1, -1, 0, 1};

bool isValid(int** twoDmat, int row, int col, bool** visited, uint32_t maxRows, uint32_t maxCols)
{
    if (row < 0 || col < 0 || row >= maxRows || col >= maxCols)
    {
        return false;
    }

    // VERY IMP:
    // If we have already seen this, then we shouldn't go further deep. So return false;
    if (visited[row][col])
    {
        return false;
    }

    return (twoDmat[row][col] == 1);
}

void dfs(int** twoDmat, uint32_t row, uint32_t col, bool** visited, uint32_t maxRows, uint32_t maxCols)
{
    visited[row][col] = true;
    
    for (uint32_t i = 0; i < 8; i++)
    {
        int newRow = row + rowDirection[i];
        int newCol = col + colDirection[i];

        // We need maxRows and maxCols to find the size of the matrix.
        if (isValid(twoDmat, newRow, newCol, visited, maxRows, maxCols))
        {
            // newRow and newCol will be a positive number and within the range
            dfs(twoDmat, newRow, newCol, visited, maxRows, maxCols);
        }
    }
}

uint32_t countConnectedIslands(int** twoDmat, uint32_t rows, uint32_t cols)
{
    uint32_t numIslands = 0;
    bool **visited = new bool*[rows];

    // Can use a 2D Vector instead
    // vector< vector<int> > myTwoDVec(rows, vector<int> (cols, 5));

    // Initialize a Visited bool array
    for (uint32_t i = 0; i < rows; i++)
    {
        // VERY IMP: Use "()" to set default value to 0
        visited[i] = new bool[cols]();
    }

    // Set all values of bool array to false;
    //std::fill_n(visited, rows * cols, false);
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            visited[i][j] = false;
        }
    }

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            // IMP: go DFS only when we have a 1.
            if (visited[x][y] == false && twoDmat[x][y] == 1)
            {
                dfs(twoDmat, x, y, visited, rows, cols);
                numIslands++;
            }
        }
    }

    // Free up visited array
    for (uint32_t i = 0; i < rows; i++)
    {
        delete visited[i];
    }
    delete[] visited;
    return numIslands;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 4: Given a input stream of numbers, compute the median after each entry
//
// HEAPS can be used only if everything can be fit in memory
// Another approach is to use Counting sort
// http://www.geeksforgeeks.org/counting-sort/
// http://stackoverflow.com/questions/10657503/find-running-median-from-a-stream-of-integers
// ------------------------------------------------------------------------------------------------
template <typename T>
void printHeap(T myHeap)
{
    while (!myHeap.empty())
    {
        cout << myHeap.top() << " ";
        myHeap.pop();
    }
    cout << endl;
}

void medianOfStreamsHeap(int element, priority_queue<int>& desHeap, priority_queue<int, std::vector<int>, std::greater<int> >& ascHeap)
{
    int topDesHeap = desHeap.top();
    int topAscHeap = ascHeap.top();

    // If the next element is bigger than the first element in Descending heap then it should
    // go to the ascending heap.
    if (element > desHeap.top())
    {
        ascHeap.push(element);

        // Heapify
        if (ascHeap.size() - desHeap.size() > 1)
        {
            desHeap.push(ascHeap.top());
            ascHeap.pop();
        }
    }
    else
    {
        desHeap.push(element);

        // Heapify if desHeap get more elements
        if (desHeap.size() - ascHeap.size() > 1)
        {
            ascHeap.push(desHeap.top());
            desHeap.pop();
        }
    }
}

int medianOfStreams(int numbers[], uint32_t size)
{
    priority_queue<int, std::vector<int>, std::greater<int> > ascHeap;
    priority_queue<int> desHeap;

    if (size < 2)
    {
        return numbers[0];
    }

    if (numbers[0] > numbers[1])
    {
        ascHeap.push(numbers[0]);
        desHeap.push(numbers[1]);
    }
    else
    {
        desHeap.push(numbers[0]);
        ascHeap.push(numbers[1]);
    }

    // Put each new number into the heap as we get
    for (uint32_t i = 2; i < size; i++)
    {
        medianOfStreamsHeap(numbers[i], desHeap, ascHeap);
    }

    cout << endl << "Descending Heap: ";
    printHeap(desHeap);

    cout << endl << "Ascending Heap : ";
    printHeap(ascHeap);

    // To calculate the median get the top from both the heaps and find the median of them
    // If both heaps are of same size, Median will be the average.
    // Else median element will be the element of the larger heap
    if (ascHeap.size() == desHeap.size())
    {
        return ((ascHeap.top() + desHeap.top()) / 2);
    }
    else if (ascHeap.size() > desHeap.size())
    {
        return ascHeap.top();
    }
    else
    {
        return desHeap.top();
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 5. Find the maximum sum that you can get from a contiguous sub array
//            -2 -3 4 -1 -2 1 5 -3
//            Ans: 7
// ------------------------------------------------------------------------------------------------
int maxSumSubArray(int arr[], int num)
{
    // This can be Zero as we always do curSum + arr[i] Before comparing with max
    int curSum = 0;

    // VERY IMP. Else it will fail when just {-1} is passed.
    int maxSum = std::numeric_limits<std::int32_t>::min();

    for (uint32_t i = 0; i < num; i++)
    {
        curSum = max(arr[i], arr[i] + curSum);
        maxSum = max(curSum, maxSum);
    }

    return maxSum;
}

void maxSumSubSequence(int arr[], int num)
{
    // This can be Zero as we always do curSum + arr[i] Before comparing with max
    int curSum = 0;
    int stIdx = 0;
    int stIdx2 = 0;
    int endIdx = 0;

    // VERY IMP. Else it will fail when just {-1} is passed.
    int maxSum = std::numeric_limits<std::int32_t>::min();

    for (uint32_t i = 0; i < num; i++)
    {
        if (arr[i] > (arr[i] + curSum))
        {
            stIdx = i;
            curSum = arr[i];
        }
        else
        {
            curSum = arr[i] + curSum;
        }
                
        if (maxSum < curSum)
        {
            stIdx2 = stIdx;
            endIdx = i;
            maxSum = curSum;
        }
    }
    cout << "StIdx: " << stIdx2 << "; EndIdx: " << endIdx << endl;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 5b. Find the maximum product that you can get from a sub array
//            -2 -3 4 -1 -2 1 5 -3
//            Ans: 360
// ------------------------------------------------------------------------------------------------
int maxProduct(vector<int> nums)
{
    // Array can have a single negative number
    int maxPosProd = nums[0];
    int minNegProd = nums[0];
    int finalProd = nums[0];

    for (int i = 1; i < nums.size(); i++)
    {
        int tmpMax = maxPosProd;
        int tmpMin = minNegProd;

        // Case 1: 5, 4
        // Case 2: 5, -4
        // Case 3: -5, 4
        // Case 4: -5, -4
        // For each new number the max product till now can be either
        //      a. Max till now     * a[i] - If result gives a positive value
        //      b. Min Neg till now * a[i] - If current number is negative
        //      c. a[i]                    - If 
        maxPosProd = max(max(tmpMax * nums[i], tmpMin * nums[i]), nums[i]);
        minNegProd = min(min(tmpMax * nums[i], tmpMin * nums[i]), nums[i]);
        finalProd = max(maxPosProd, finalProd);
    }

    return finalProd;

}

// ------------------------------------------------------------------------------------------------
// PROBLEM 5c. Find the SUB ARRAY that will give you a sum
// http://www.geeksforgeeks.org/find-subarray-with-given-sum/
//             IMP:
//             a. ALL NUMBERS ARE POSITIVE.
//                IF we have +ve and -ve then can't find all subarray without using extra space
//             a. This does not give the maximum length sub array. This just gives first
//                such sub array
//
//             Returns false if no such array is present
// ------------------------------------------------------------------------------------------------
bool subArrayWithSum(int arr[], uint32_t num, int sum)
{
    uint32_t startIdx = 0;
    int curSum = 0;
    bool isSubArrayPresent = false;

    for (uint32_t i = 0; i < num; i++)
    {
        curSum += arr[i];

        // Say Sum = 25, Arr = 5, 5, 5, 25.
        // when i has 25, we have to remove all the previous entries. 
        while (curSum > sum && startIdx < i)
        {
            curSum -= arr[startIdx];
            startIdx++;
        }

        if (curSum == sum)
        {
            cout << "Elmt1: " << arr[startIdx] << "; Idx2 : " << arr[i] << endl;
            isSubArrayPresent = true;

            // Commenting the below line will print all sub arrays
            //return true;
        }
    }

    return isSubArrayPresent;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 5d. Find ALL SUB ARRAYS that will give you a sum
// http://stackoverflow.com/questions/14948258/given-an-input-array-find-all-subarrays-with-given-sum-k
// http://stackoverflow.com/questions/30480506/find-widest-subarray-with-given-sum-array-slicing
// http://www.geeksforgeeks.org/find-the-largest-subarray-with-0-sum/
//             IMP: This does not give the maximum length sub array.
//             This just gives all the such sub array
//
//             Returns false if no such array is present
//             Sum      : 3
//             Index    : 0, 1,  2, 3, 4,  5
//             Arr      : 4, 1, -3, 2, 6 , -5
//             Map      : 4, 5,  2, 4, 10,  5
//             Map Find : 1, 2, -1, 1,  7,  2
//             Check if each element in Map Find is present in the MAP.
//             We can see that "2" is present in the map at index 2. 
//             Now we are at Index 5, with a Sum of 5. This denotes that after Index 2 where
//             our Sum was 2. We have gotnumber in the middle which would contribute to a
//             Sum of 3.
//
//              
//             Sum      : 4
//             Index    : 0, 1,  2, 3, 4,  5
//             Arr      : 4, 1, -3, 2, 6 , -5
//             Map    :0, 4, 5,  2, 4, 10,  5 // VERY IMP: Map should start from 0.
//             Map Find : 0, 1, -2, 0,  6,  1
// ------------------------------------------------------------------------------------------------
bool allSubArraysWithSum(int arr[], uint32_t num, int sum)
{
    // Map will have Sums and Indices where the SUM has occurred.
    unordered_map<int, vector<int> > sumMap;
    int curSum = 0;
    bool isSubArrayPresent = false;

    // Add 0 to the map. This will help in finding if EXACT_SUM is present in the
    // array. 
    // Let the Value of 0 be -1. If the first element is Sum, we can find it.
    sumMap[0] = vector<int> {-1};

    for (int i = 0; i < num; i++)
    {
        curSum += arr[i];

        auto itr = sumMap.find(curSum - sum);

        if (itr != sumMap.end())
        {
            // We could have list of indices where SUM - curSum is present.
            for (int x : itr->second)
            {
                // Very IMP: Start Index will be x + 1
                cout << "Elmt1 Idx: " << x + 1 << "; Elmt2 Idx: " << i << endl;
            }
        }

        // Even if we have found, we should still go ahead and insert this sum to our Map
        auto itr2 = sumMap.find(curSum);
        
        if (itr2 != sumMap.end())
        {
            itr2->second.push_back(i);
        }
        else
        {
            sumMap[curSum] = vector<int> {i};
        }
    }

    return isSubArrayPresent;
}

void maxSubArraysWithLessOrEqualSumWrapper(const vector<int>& nums,
                                           uint32_t stIdx,
                                           const int sum,
                                           int curSum,
                                           uint32_t curLen,
                                           uint32_t& maxLen)
{
    if (curSum > sum || stIdx == nums.size())
    {
        if (maxLen < curLen)
        {
            maxLen = curLen;
        }

        return ;
    }

    for (uint32_t i = stIdx; i < nums.size(); i++)
    {
        if (curSum + nums[i] <= sum)
        {
            maxSubArraysWithLessOrEqualSumWrapper(nums, i + 1, sum, curSum + nums[i], curLen + 1, maxLen);
        }
    }

    return ;
}

uint32_t maxSubArraysWithLessOrEqualSumWrapperOptimized(const vector<int>& nums,
                                                        const int sum)
{
    uint32_t curSum = 0;
    uint32_t i = 0;

    for (; i < nums.size(); i++)
    {
        curSum += nums[i];

        if (curSum > sum)
        {
            break;
        }
    }

    return i;
}

uint32_t maxSubArraysWithLessOrEqualSum(const vector<int>& nums, const int sum)
{
    uint32_t maxLen = 0;
    // maxSubArraysWithLessOrEqualSumWrapper(nums, 0, sum, 0, 0, maxLen);

    vector<int> numsCopy = nums;
    sort(numsCopy.begin(), numsCopy.end());
    maxLen = maxSubArraysWithLessOrEqualSumWrapperOptimized(numsCopy, sum);

    return maxLen;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 5e. Find the max sum such that no two elements are adjacent
// http://stackoverflow.com/questions/4487438/maximum-sum-of-non-consecutive-elements
// http://www.geeksforgeeks.org/maximum-sum-such-that-no-two-elements-are-adjacent/
//
//            5,  5, 10, 40, 50, 35
//            Ans: 80; 5, 40, 35
//            Returns false if no such array is present
// ------------------------------------------------------------------------------------------------
int maxLengthSubArraySum(vector<int> nums)
{
    if (nums.size() == 0)
    {
        return false;
    }

    int a = nums[0];
    int b = nums[1];
    int maxVal = max(a, b);

    for (uint32_t i = 2; i < nums.size(); i++)
    {
        maxVal = max(b, a + nums[i]);
        a = b;
        b = maxVal;
    }

    return maxVal;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 6. Finding greatest sum of elements of array which is divisible by a given number
// http://stackoverflow.com/questions/13511885/finding-greatest-sum-of-elements-of-array-which-is-divisible-by-a-given-number
//
//            1,  6, 2, 9, 5; 4
//            Ans: 16
//
//            Arr 1:        Arr 2:
//            0: 0   0+1    0: 0
//            1: 0   0+1    1: 1
//            2: 0   0+1    2: 0
//            3: 0   0+1    3: 0
//
//            Arr 1:        Arr 2:
//            0: 0   0+6    0: 0
//            1: 1   1+6    1: 1
//            2: 0   0+6    2: 6
//            3: 0   0+6    3: 7
//
//            Arr 1:        Arr 2:
//            0: 0   0+2    0: 8
//            1: 1   1+2    1: 9
//            2: 6   6+2    2: 6
//            3: 7   7+2    3: 7
//
//            Arr 1:        Arr 2:
//            0: 8   8+9    0: 16
//            1: 9   9+9    1: 17
//            2: 6   6+9    2: 18
//            3: 7   7+9    3: 15
//
//            To implement this algorithm, the basic skeleton is as follows.
//
//            for (j = 0; j < k; j++) f[0][j] = 0;
//            for (i = 1; i <= n; i++)
//              for (j = 0; j < k; j++) {
//                x = (j + k - a[i]%k) % k;
//                f[i][j] = max(f[i-1][x] + a[i], f[i-1][j]);
//              }
// ------------------------------------------------------------------------------------------------
int greatestSumOfSubarrayDivisibleByK(vector<int> nums, uint32_t divNum)
{
    vector<int32_t> sumArr1(divNum, 0);
    vector<int32_t> sumArr2(divNum, 0);

    for (uint32_t i = 0; i < nums.size(); i++)
    {
        for (uint32_t j = 0; j < sumArr1.size(); j++)
        {
            int tmp = (sumArr1[j] + nums[i]);
            sumArr2[tmp % divNum] = max(tmp, sumArr2[tmp % divNum]);
        }

        sumArr1 = sumArr2;
    }

    return sumArr1[0];
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 7. Print Matrix Diagonally
// http://stackoverflow.com/questions/28433572/print-2d-array-diagonally-from-bottom-to-top
// http://stackoverflow.com/questions/20420065/loop-diagonally-through-two-dimensional-array
//
//      0,0
//      1,0     0,1
//      2,0     1,1     0,2
//      2,1     1,2     0,3
//      2,2     1,3
//      2,3
//
//      One should be increasing and other should be decreasing
//
//  i: 0    1       2           3               4
//  j: 0    0, 1    0, 1, 2     0, 1, 2, 3      0, 1, 2, 3, 4
//  k: 0    1, 0    2, 1, 0     3, 2, 1, 0      4, 3, 2, 1, 0
//Inv:                          x               x, x // Invalid numbers based on Row and Col
// ------------------------------------------------------------------------------------------------
template <int rows, int cols>
void printMatrixDiagonally(int (&twoDMatrix)[rows][cols])
//void printMatrixDiagonally(int (&twoDMatrix)[rows][cols])
//void printMatrixDiagonally(int twoDMatrix[3][3], int rows, int cols)
{
    for(uint32_t k = 0 ; k < rows + cols ; k++ )
    {
        for(uint32_t j = 0 ; j <= k ; j++ )
        {
            int i = k - j;

            if(i < rows && j < cols)
            {
                cout << twoDMatrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 7b. Print Matrix Spirally
// http://www.geeksforgeeks.org/print-a-given-matrix-in-spiral-form/
// http://stackoverflow.com/questions/726756/print-two-dimensional-array-in-spiral-order
// M  =  1   2   3   4   5
//       6   7   8   9  10
//      11  12  13  14  15
//      16  17  18  19  20
//
// The clockwise spiral print is:  1 2 3 4 5 10 15 20 19 18 17 16 11 6 7 8 9 14 13 12
// ------------------------------------------------------------------------------------------------
void printMatrixSpiralOrder(vector< vector <int> > twoDMatrix)
{
    int curRow = 0;
    int curCol = 0;
    int maxRow = twoDMatrix.size() - 1;
    int maxCol = twoDMatrix[0].size() - 1;

    while (curRow <= maxRow && curCol <= maxCol)
    {
        for (int i = curCol; i <= maxCol; i++)
        {
            cout << twoDMatrix[curRow][i] << ", ";
        }
        curRow++;

        for (int i = curRow; i <= maxRow; i++)
        {
            cout << twoDMatrix[i][maxCol] << ", ";
        }
        maxCol--;

        for (int i = maxCol; i >= curCol; i--)
        {
            cout << twoDMatrix[maxRow][i] << ", ";
        }
        maxRow--;

        for (int i = maxRow; i >= curRow; i--)
        {
            cout << twoDMatrix[i][curCol] << ", ";
        }
        curCol++;
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 8. Given a string of 1s and 0s with '?' in between. A '?' can be either one or zero.
//            Print All combinations of the string.
//
//            10?0
//            Ans: 1010
//                 1000
// ------------------------------------------------------------------------------------------------

void printCombinationOnesZeros(string str, uint32_t stIdx, uint32_t lastQMarkPos)
{
    if (stIdx == lastQMarkPos)
    {
        cout << str << endl;
        return;
    }

    for (uint32_t i = stIdx; i < str.size(); i++)
    {
        if (str[i] == '?')
        {
            str[i] = '0';
            printCombinationOnesZeros(str, i, lastQMarkPos);

            str[i] = '1';
            printCombinationOnesZeros(str, i, lastQMarkPos);
        }
    }
}

void findLastQMark(string str)
{
    uint32_t lastQMarkPos = str.size();
    for (int i = str.size()-1; i >=0; i--)
    {
        if (str[i] == '?')
        {
            lastQMarkPos = i;
        }
    }

    if (lastQMarkPos < str.size())
    {
        printCombinationOnesZeros(str, 0, lastQMarkPos);
    }
    else
    {
        cout << str << endl;
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 9. Given an integer x, find ONE digit who is equal to its adjacent digits,
//            and remove it. If there are multiple outcomes, return the largest number.
//
//            2234256623
//            Ans: 234256623 > 223425623
// ------------------------------------------------------------------------------------------------
int largestNumByRemovingDup(int number)
{
    string strNum = to_string(number);

    if (strNum.size() < 2)
    {
        return number;
    }

    // From FRONT try to find,
    //      num[i] == num[i+1] &&
    //      num[i+1] < num[i+2]
    // If NO SUCH number is present, then remove from the last
    //      num[l] == num[l-1]
    for (uint32_t i = 0; i < strNum.size() - 1; i++)
    {
        if (strNum[i] == strNum[i+1])
        {
            if (i+2 < strNum.size())
            {
                if (strNum[i+1] < strNum[i+2])
                {
                    strNum.erase(i+1, 1);
                    return atoi(strNum.c_str());
                }
            }
            // Reached end of string and last digit is  repeated. Just remove it
            else
            {
                strNum.erase(i+1, 1);
                return atoi(strNum.c_str());
            }
        }
    }

    for (int32_t i = strNum.size()-1; i > 0; i--)
    {
        if (strNum[i] == strNum[i-1])
        {
            if (i-2 >= 0)
            {
                if (strNum[i-1] < strNum[i-2])
                {

                    strNum.erase(i-1, 1);
                    return atoi(strNum.c_str());
                }
            }
            // Reached end of string and first digit is  repeated. Just remove it
            else
            {
                strNum.erase(i-1, 1);
                return atoi(strNum.c_str());
            }
        }
    }

    // Control should not reach here
    return 0;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 10. Find Equilibrium Index of an array. Sum of left elements = Sum of Right elements
//            -7, 1, 5, 2, -4, 3, 0
//
//            Ans: 3
// ------------------------------------------------------------------------------------------------
int32_t equilibriumIndex(vector<int> nums)
{
    int totalSum = 0;
    int leftSum = 0;
    int rightSum = 0;
    for (int a: nums)
    {
        totalSum += a;
    }

    for (uint32_t i = 0; i < nums.size(); i++)
    {
        // IMP: First thing to do is add element to Left sum
        // For Right Sum, we should exclude the current element as well.
        rightSum = totalSum - (leftSum + nums[i]);
        if (rightSum == leftSum)
        {
            return i;
        }

        leftSum += nums[i];
    }

    return -1;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 11. Generalized Abbrevation
//            word
//
//            Ans: word, 1ord, w1rd, wo1d, wor1, 2rd, w2d, wo2, 1o1d, 1or1, w1r1, 1o2, 2r1, 3d, w3, 4
// ------------------------------------------------------------------------------------------------
void generalizedAbbrevation(string word)
{
    for (uint32_t i = 1; i <= word.length(); i++)
    {
        // Check j + i-1 steps after each iteration
        for (uint32_t j = 0; (j + (i-1)) < word.length(); j++)
        {
            // Replace first char by j
            string temp = word;
            temp[j] = i + '0';

            // Should erase from the next character
            temp.erase(j+1, i-1);
            cout << temp << " ";
        }

        cout << endl;
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 12. Find if two rectangles overlap
// http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
// ------------------------------------------------------------------------------------------------
// Points should be such that
//      a1.x < a2.x &&
//      a1.y > a2.y &&
//      Left Top and Right bottom
bool isRectanglesOverlap(Point a1, Point a2, Point b1, Point b2)
{
    return (a1.x < b2.x &&
            a2.x > b1.x &&
            a1.y > b2.y &&
            a2.y < b1.y);
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 13. Find Largest Subarray with equal number of 0s and 1s
// http://stackoverflow.com/questions/31201245/finding-the-largest-subarray-with-equal-number-of-0s-and-1s
//             Complexity: O(N)
//             {0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12}
//             {0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  1,  0,  0};
//         {0, -1, -2, -3, -4, -5, -6, -7, -6, -5, -6, -5, -6, -7}
// ------------------------------------------------------------------------------------------------
struct oneZeroData
{
    int32_t startIdx;
    int32_t endIdx;
};

void printLargestSubArrayZeroOne(int arr[], uint32_t num)
{
    // Store SUM and START and END INDEX
    unordered_map<int, oneZeroData> oneZeroDiffMap;

    if (num == 0)
    {
        return;
    }

    uint32_t count = 0;
    uint32_t stIdx = 0;
    uint32_t endIdx = 0;
    uint32_t maxSubArrLen = 0;

    // Insert Zero into the map to start with
    oneZeroDiffMap[0] = {-1, -1};

    for(uint32_t i = 0; i < num; i++)
    {
        if (arr[i] == 1)
        {
            count++;
        }
        else if (arr[i] == 0)
        {
            count--;
        }

        auto itr = oneZeroDiffMap.find(count);
        if (itr != oneZeroDiffMap.end())
        {
            itr->second.endIdx = i;

            if (i - (itr->second.startIdx) > maxSubArrLen)
            {
                stIdx = itr->second.startIdx + 1;
                endIdx = itr->second.endIdx;
                maxSubArrLen = i - (itr->second.startIdx);
            }
        }
        else
        {
            oneZeroDiffMap[count] = {(int)i, -1};
        }
    }

    cout << "Start Index: " << stIdx << "; End Index: " << endIdx << endl;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 14. 3 number sum closest
// http://www.geeksforgeeks.org/find-a-triplet-that-sum-to-a-given-value/
// http://stackoverflow.com/questions/2070359/finding-three-elements-in-an-array-whose-sum-is-closest-to-a-given-number
//             This problem can be solved only by sorting the array. So consider  the array
//             is sorted.
// ------------------------------------------------------------------------------------------------
void printThreeNumSum(int arr[], uint32_t num, int sum)
{
    if (num < 3)
    {
        return;
    }

    uint32_t i = 0;

    // Keep three pointers.
    // i - goes from 0 to n
    // j - starts at i + 1
    // k - starts at n-1
    //
    // For each 'i', move j & k such that we converge towards the sum
    for (; i < num; i++)
    {
        uint32_t j = i + 1;
        uint32_t k = num - 1;

        while (j < k)
        {
            if (arr[i] + arr[j] + arr[k] == sum)
            {
                cout << arr[i] << " " << arr[j] << " " << arr[k] << endl;
                return;
            }
            else if (arr[i] + arr[j] + arr[k] > sum)
            {
                k--;
            }
            else
            {
                j++;
            }
        }
    }
}

void printThreeNumClosestSum(int arr[], uint32_t num, int sum)
{
    if (num < 3)
    {
        return;
    }

    uint32_t i = 0;

    int closestSum = std::numeric_limits<std::int32_t>::max();
    int tmpClosest = std::numeric_limits<std::int32_t>::max();
    uint32_t x, y, z;

    for (; i < num; i++)
    {
        uint32_t j = i + 1;
        uint32_t k = num - 1;

        while (j < k)
        {
            tmpClosest = abs(sum - (arr[i] + arr[j] + arr[k]));
            if (tmpClosest < closestSum)
            {
                closestSum = tmpClosest;
                x = i;
                y = j;
                z = k;
            }

            if (arr[i] + arr[j] + arr[k] == sum)
            {
                cout << arr[i] << " " << arr[j] << " " << arr[k] << endl;
                return;
            }

            else if (arr[i] + arr[j] + arr[k] > sum)
            {
                k--;
            }
            else
            {
                j++;
            }
        }
    }

    cout << "Closest Sum: " << arr[x] << " " << arr[y] << " " << arr[z] << endl;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 15. 1 Missing and 1 Duplicate
// http://www.geeksforgeeks.org/find-a-repeating-and-a-missing-number/
//             Given an unsorted array of size n.
//             One number from set {1, 2, n} is missing and one number occurs twice in array
// ------------------------------------------------------------------------------------------------
void findMissingAndDuplicate(vector<int> nums)
{
    int fullXor = 0;
    int numsWithRightSetBit = 0;
    int numsWithoutRightSetBit = 0;
    int rightSetBit;

    // XOR will all numbers from 1 to n
    for (int i = 1; i <= nums.size(); i++)
    {
        fullXor ^= i;
    }

    // XOR with all array elements
    // After this fullXor will be having just the XOR of missing and duplicate number
    for (int n : nums)
    {
        fullXor ^= n;
    }
    
    // Find the right most set bit in fullXor
    rightSetBit = fullXor & ~(fullXor - 1);

    // Now divide the numbers into two sets. Set one will have rightSetBit ON and Set two
    // will have rightSetBit OFF
    
    for (int n : nums)
    {
        if (rightSetBit & n)
        {
            numsWithRightSetBit ^= n;
        }
        else
        {
            numsWithoutRightSetBit ^= n;
        }
    }

    // Both sets should be XORed with the BOTH arrays to get the numbers.
    // Right set bit is just used to Partition into two arrays
    // Eg 1, 2, 2, 3
    //    1, 2, 3, 4
    //    XOR: 2 ^ 4 = 110
    //    Set1: 1       ; 1, 4 - XOR will give 4
    //    Set2: 2, 2, 3 ; 2, 3 - XOR will give 2
    for (int i = 1; i <= nums.size(); i++)
    {
        if (rightSetBit & i)
        {
            numsWithRightSetBit ^= i;
        }
        else
        {
            numsWithoutRightSetBit ^= i;
        }
    }

    cout << "Num1: " << numsWithRightSetBit << "; Num2: " << numsWithoutRightSetBit << endl;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 16. 2 missing numbers
// http://stackoverflow.com/questions/20026243/find-2-missing-numbers-in-an-array-of-integers-with-two-missing-values
//
//             {3,1,2,5,7,8}
//             Ans: 4, 6
// ------------------------------------------------------------------------------------------------
void findTwoMissing(vector<int> nums, uint32_t totalNums)
{
    int fullXor = 0;
    int numsWithRightSetBit = 0;
    int numsWithoutRightSetBit = 0;
    int rightSetBit;

    // XOR will all numbers from 1 to n
    for (int i = 1; i <= totalNums; i++)
    {
        fullXor ^= i;
    }

    // XOR with all array elements
    // After this fullXor will be having just the XOR of missing and duplicate number
    for (int n : nums)
    {
        fullXor ^= n;
    }
    
    // Find the right most set bit in fullXor
    // IMP: if fullXor = 010, then rightSetBit will be 0.
    if ((fullXor & (fullXor - 1)) != 0)
    {
        rightSetBit = fullXor & (fullXor - 1);
    }
    else
    {
        rightSetBit = fullXor;
    }

    // Now divide the numbers into two sets. Set one will have rightSetBit ON and Set two
    // will have rightSetBit OFF
    
    // 100 & 011 will result in 0. So we have use 100 itself
    for (int n : nums)
    {
        if (rightSetBit & n)
        {
            numsWithRightSetBit ^= n;
        }
        else
        {
            numsWithoutRightSetBit ^= n;
        }
    }

    // Both sets should be XORed with the BOTH arrays to get the numbers.
    // Right set bit is just used to Partition into two arrays
    // Eg 1, 2, 3, 5, 7, 8
    //    1, 2, 3, 5, 7, 8, 4, 6
    //    
    //    XOR: 6 ^ 4 = 010
    //    Set1: 2, 3, 7 ; 2, 3, 7, 6- XOR will give 6
    //    Set2: 1, 5, 8 ; 1, 5, 8, 4- XOR will give 4
    for (int i = 1; i <= totalNums; i++)
    {
        if (rightSetBit & i)
        {
            numsWithRightSetBit ^= i;
        }
        else
        {
            numsWithoutRightSetBit ^= i;
        }
    }

    cout << "Num1: " << numsWithRightSetBit << "; Num2: " << numsWithoutRightSetBit << endl;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 17. Find minimum number of conference room required
// http://stackoverflow.com/questions/12283559/find-overlapping-appointments-in-on-time
// http://stackoverflow.com/questions/24657695/optimal-room-count-and-sizes-for-n-overlapping-meeting-schedules
// ------------------------------------------------------------------------------------------------
static const double EPSILON = 0.000001;

bool areDoubleSame(double a, double b)
{
    return fabs(a - b) < EPSILON;
}

bool areDoubleGreater(double a, double b)
{
    if ((a - b) > EPSILON)
    {
        return true;
    }
    else
    {
        return false;
    }
}

struct MeetingTime
{
    int startTime;
    int endTime;

    MeetingTime(double sT, double eT) : startTime(sT),
                                        endTime(eT) { }

    bool operator < (const MeetingTime& meetTime) const
    {
        return (startTime < meetTime.startTime);
    }

    bool operator > (const MeetingTime& meetTime) const
    {
        return (endTime > meetTime.endTime);
    }
};

void printMeetingVector(vector<MeetingTime> meetings)
{
    cout << "List of Meetings: " << endl;
    for (auto meeting : meetings)
    {
        cout << meeting.startTime << "-" << meeting.endTime << endl;
    }
    cout << endl;
}

/*
struct MyMeetStrtEndComp
{
    bool operator()( const MeetingTime& lx, const MeetingTime& rx ) const {
        return lx.startTime < rx.endTime;
    }
};
*/

uint32_t minConfRoomRequired(vector<struct MeetingTime> meetingsList)
{
    uint32_t minRoomReqd = 0;
    // Sort by ascending order of start Time
    sort(meetingsList.begin(), meetingsList.end());

    vector<struct MeetingTime> meetingsEndTimeSort;

    for (auto meeting : meetingsList)
    {
        // If vector is empty OR first element's End time is greater than your start time,
        // push into it.
        if (meetingsEndTimeSort.empty() ||
            meetingsEndTimeSort[meetingsEndTimeSort.size()-1].endTime > meeting.startTime)
        {
            meetingsEndTimeSort.push_back(meeting);
            sort(meetingsEndTimeSort.begin(), meetingsEndTimeSort.end(), greater<MeetingTime>());
        }
        else
        {
            uint32_t i = 0;
            // Find first element with end time greater than current start time.
            // Come one step back and make sure the end time if before the current start time
            // Remove the entry and push the new entry
            // 
            // Lineraly traverse END TIME VECTOR to find the first one which has end time
            // greater than current start time
            for (i = 0; i < meetingsEndTimeSort.size(); i++)
            {
                // Eg: Start Time: 11am
                //     End Times : 8, 9, 10, 11, 12.
                //     Remove the meeting that ends and 11 and insert this new entry.
                if (meeting.startTime >= meetingsEndTimeSort[i].endTime)
                {
                    break;
                }
            }

            if (i < meetingsEndTimeSort.size())
            {
                meetingsEndTimeSort.erase(meetingsEndTimeSort.begin() + i);
            }

            meetingsEndTimeSort.push_back(meeting);
            sort(meetingsEndTimeSort.begin(), meetingsEndTimeSort.end(), greater<MeetingTime>());
        }
    }

    return meetingsEndTimeSort.size();
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 18. Find median of two sorted arrays of same size
// http://www.geeksforgeeks.org/median-of-two-sorted-arrays/
//
//             {1, 12, 15, 26, 38} 
//             {2, 13, 17, 30, 45}
//
//             Ans: 
// ------------------------------------------------------------------------------------------------
double medianTwoSortedSameSizeArrays(int arr1[], int arr2[], uint32_t num)
{
    double medArr1;
    double medArr2;
    if (num <= 0)
    {
        cout << "Invalid" << endl;
        return 0;
    }

    if (num == 1)
    {
        // Return the average of the two numbers
        return (arr1[num] + arr2[num]) / 2.0;
    }

    if (num == 2)
    {
        return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1])) / 2.0;
    }

    if (num % 2 == 0)
    {
        medArr1 = (arr1[num/2] + arr1[num/2 - 1]) / 2.0;
        medArr2 = (arr2[num/2] + arr2[num/2 - 1]) / 2.0;
    }
    else
    {
        medArr1 = arr1[num/2];
        medArr2 = arr2[num/2];
    }

    if (medArr1 == medArr2)
    {
        return medArr1;
    }
    else if (medArr1 > medArr2)
    {
        return medianTwoSortedSameSizeArrays(arr1,
                                             arr2 + (int)ceil(num/2),
                                             num - (ceil(num/2)));
    }
    else
    {
        return medianTwoSortedSameSizeArrays(arr1 + (int)ceil(num/2),
                                             arr2,
                                             num - (ceil(num/2)));
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 19. Find median of two sorted arrays of different size
// http://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/
// http://articles.leetcode.com/median-of-two-sorted-arrays
//
//             {900} and {5, 8, 10, 20}
//             {1, 2, 4, 8, 9, 10} and { 3, 5, 6, 7 }
//
//             Ans: 
// ------------------------------------------------------------------------------------------------
double findMedian( int A[], int B[], int l, int r, int nA, int nB )
{
    if (l > r)
    {
        return findMedian(B, A, max(0, (nA+nB)/2-nA), min(nB, (nA+nB)/2), nB, nA);
    }

    int i = (l + r) / 2;
    int j = (nA+nB)/2 - i - 1;

    if (j >= 0 && A[i] < B[j]) 
    {
        return findMedian(A, B, i+1, r, nA, nB);
    }
    else if (j < nB-1 && A[i] > B[j+1])
    {
        return findMedian(A, B, l, i-1, nA, nB);
    }
    else
    {
        if ((nA + nB) % 2 == 1) 
        {
            return A[i];
        }
        else if (i > 0)
        {
            return (A[i]+max(B[j], A[i-1]))/2.0;
        }
        else 
        {
            return (A[i]+B[j])/2.0;
        }
    }
}

double medianTwoSortedDiffSizeArrays(int A[], int n, int B[], int m)
{
    if (n<m)
    {
        return findMedian(A, B, 0, n-1, n, m);
    }
    else
    {
        return findMedian(B, A, 0, m-1, m, n);
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 20. Find Kth smallest element in Union of two sorted arrays
// http://stackoverflow.com/questions/4607945/how-to-find-the-kth-smallest-element-in-the-union-of-two-sorted-arrays
//
//             int A[] = {1, 2, 6, 8};
//             int B[] = {3, 5};
//
//             Ans: 4th Smallest is 5
//
// IMP: First array should be bigger than the second array
// ------------------------------------------------------------------------------------------------
int kthSmallestElement(int arr1[], uint32_t num1, int arr2[], uint32_t num2, uint32_t k)
{
    if (k > num1 + num2)
    {
        cout << "Error" << endl;
        return -1;
    }

    uint32_t index1 = 0;
    uint32_t index2 = 0;
    uint32_t step = 0;

    while (index1 + index2 < k - 1)
    {
        step = (k - index1 - index2) / 2;    
        uint32_t step1 = index1 + step;
        uint32_t step2 = index2 + step;

        if (num1 > step1 - 1 &&
            (num2 <= step2 - 1 ||
             arr1[step1 - 1] < arr2[step2 - 1]))
        {
            index1 = step1;
        }
        else
        {
            index2 = step2;
        }
    }

    // Now idx1 + idx2 will be k-1
    cout << "Idx 1: " << index1 << "; Index 2: " << index2 << endl;
    if (num1 > index1 &&
        (num2 <= index2 || arr1[index1] < arr2[index2]))
    {
        return arr1[index1];
    }
    else
    {
        return arr2[index2];
    }
}

// Kth Smallest Element Iterative method 2
// We maintain i + j = k, and find such i and j so that a[i-1] < b[j-1] < a[i] (or the other way round).
// Now since there are i elements in 'a' smaller than b[j-1], and j-1 elements in 'b' smaller than b[j-1], b[j-1] is the i + j-1 + 1 = kth smallest element.
// I'll assume that N and M are > k, so the complexity here is O(log k), which is O(log N + log M)
int kthSmallestElementIterativeTwo(int arr1[], uint32_t num1, int arr2[], uint32_t num2, uint32_t k)
{
    if (k > num1 + num2)
    {
        cout << "Error" << endl;
        return -1;
    }

    // Index 1 + Index 2 will always be k
    // IMP ASSUMPTION: Both ARRAYS have ATLEAST k/2 elements
    uint32_t idx1 = k/2;
    uint32_t idx2 = k - idx1;

    // VERY IMP: SIGNED INT
    int32_t step = k/4;

    while (step > 0)
    {
        if (arr1[idx1 - 1] > arr2[idx2 - 1])
        {
            idx1 -= step;
            idx2 += step;
        }
        else
        {
            idx1 += step;
            idx2 -= step;
        }
        step = step / 2;
    }

    cout << "1. Idx 1: " << idx1 << "; Idx 2: " << idx2 << endl;

    // Idx1 and Idx2 will give the k+1th and k+2th elements.
    // So Greatest of Idx-1 and Idx2-1 is the answer which will be k'th element
    if (arr1[idx1 - 1] > arr2[idx2 - 1])
    {
        return arr1[idx1 - 1];
    }
    else
    {
        return arr2[idx2 - 1];
    }
}

// Recurisve Algorithm to find the k'th smallest
int kthSmallestElementRec(int arr1[], uint32_t index1, uint32_t num1,
                          int arr2[], uint32_t index2, uint32_t num2,
                          uint32_t k)
{
    if (index1 + index2  == k - 1)
    {
        if (num1 > index1 &&
            (num2 <= index2 || arr1[index1] < arr2[index2]))
        {
            return arr1[index1];
        }
        else
        {
            return arr2[index2];
        }
    }

    uint32_t step = (k - index1  - index2) / 2;

    uint32_t step1 = index1 + step;
    uint32_t step2 = index2 + step;

    if (num1 > step1 - 1 &&
        (num2 <= step2 - 1 ||
         arr1[step1 - 1] < arr2[step2 - 1]))
    {
        index1 = step1; // commit to element at index = step1 - 1
    }
    else
    {
        index2 = step2;
    }

    return kthSmallestElementRec(arr1, index1, num1, arr2, index2, num2, k);
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 21. Find Kth smallest element in an Unsorted array
//
//             int A[] = {3,5,2,1,8,4,6};
//
//             Ans: 4th Smallest is 4
//             Complexity: O(N log K)
// http://stackoverflow.com/questions/2974470/efficiency-of-the-stl-priority-queue
// http://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/
// ------------------------------------------------------------------------------------------------
int kthSmalledInUnsorted(int arr[], uint32_t num, uint32_t k)
{
    if (k > num)
    {
        cout << "Invalid k" << endl;
        return -1;
    }

    // Default sorting is in descending order
    priority_queue<int> kSmallNos;

    // Now the heap will contain the first k numbers
    // Complexity O(K log K)
    // One push is (Log k)
    for(uint32_t i = 0; i < k; i++)
    {
        kSmallNos.push(arr[i]);
    }

    // Complexity (num - k)log K
    // So Total Complexity: O(K log K + (num-k)log K)
    for(uint32_t i = k; i < num; i++)
    {
        if (arr[i] < kSmallNos.top())
        {
            kSmallNos.pop();
            kSmallNos.push(arr[i]);
        }
    }

    return kSmallNos.top();
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 21b. Find Kth smallest element in an Unsorted array using QuickSelect
//
//              int A[] = {3,5,2,1,8,4,6};
//
//              Ans: 4th Smallest is 4
//              Complexity: O(N)
//
// http://stackoverflow.com/questions/251781/how-to-find-the-kth-largest-element-in-an-unsorted-array-of-length-n-in-on
// ------------------------------------------------------------------------------------------------
void mySwap(int& a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

pair<int32_t, int32_t> threeWayQuickSortPartition(vector<int>& nums, int32_t stIdx, int32_t endIdx)
{
    DEBUG_MSG("Pivot: " << nums[stIdx] << "; stIdx: " << stIdx << "; endIdx: " << endIdx << endl);
    int pivot = nums[stIdx];
    int32_t low = stIdx;
    int32_t mid = stIdx;
    int32_t high = endIdx;
    pair<int32_t, int32_t> pivotPos;

    while (mid < high)
    {
        // As long as mid is same as pivot, increment it.
        // Finally mid can either be greater than pivot or lesser than pivot.
        // If it is lesser, swap with low. If it is greater, swap with high
        while (nums[mid] == pivot)
        {
            mid++;
        }

        while (nums[high] > pivot)
        {
            high--;
        }

        // IMP: If we have a mid that is more than high then break and do not do any swapping
        if (mid > high)
        {
            break;
        }

        if (nums[mid] < pivot)
        {
            // Low will be having an element EQUAL to pivot.
            mySwap(nums[low], nums[mid]);
            low++;
        }
        else if (nums[mid] > pivot)
        {
            mySwap(nums[high], nums[mid]);
            high--;
        }
    }

    // If partition has happened then we would be at a HIGH which will be the actual pivot's
    // position. So num[high] will be < pivot.
    if (nums[high] < pivot)
    {
        mySwap(nums[stIdx], nums[high]);
    }

    // Start Pivot is at Low + 1 and End Pivot is at high
    pivotPos = make_pair(low, high);
    return pivotPos;

}

int32_t quickSortPartition(vector<int>& nums, int32_t stIdx, int32_t endIdx)
{
    // Pivot can be a number not present in the array. So start low from 0
    //cout << "0. StIdx: " << stIdx << "; EndIdx: " << endIdx << endl;
    int pivot = nums[stIdx];
    int32_t low = stIdx;
    int32_t high = endIdx;

    DEBUG_MSG("1. Pivot: " << pivot << "; Low: " << low << "; High: " << high << endl);
    while (low < high)
    {
        while (nums[low] <= pivot)
        {
            low++;
        }
        DEBUG_MSG("2. Pivot: " << pivot << "; Low: " << low << "; High: " << high << endl);

        while (nums[high] > pivot)
        {
            high--;
        }
        DEBUG_MSG("3. Pivot: " << pivot << "; Low: " << low << "; High: " << high << endl);

        if (low < high)
        {
            mySwap(nums[low], nums[high]);
        }
    }

    // If partition has happened then we would be at a HIGH which will be the actual pivot's
    // position. So num[high] will be < pivot.
    DEBUG_MSG("4. Pivot: " << pivot << "; Low: " << low << "; High: " << high << endl);
    if (nums[high] < pivot)
    {
        mySwap(nums[stIdx], nums[high]);
    }

    // Pivot is at high
    return high;
}

// VERY IMP: Everything should be SIGNED INT
void quickSortRec(vector<int>& nums, int32_t stIdx, int32_t endIdx)
{
    if (stIdx < endIdx)
    {
        int32_t pivot = quickSortPartition(nums, stIdx, endIdx);
        DEBUG_MSG("PivotPos: " << pivot << endl << endl);
        quickSortRec(nums, stIdx, pivot - 1);
        quickSortRec(nums, pivot + 1, endIdx);
    }
    else
    {
        return;
    }
}

void quickSortThreeWayRec(vector<int>& nums, int32_t stIdx, int32_t endIdx)
{
    if (stIdx < endIdx)
    {
        pair<int32_t, int32_t> pivot = threeWayQuickSortPartition(nums, stIdx, endIdx);
        DEBUG_MSG("Pivot Start: " << pivot.first  << "; Pivot End: " << pivot.second << endl << endl);
        quickSortThreeWayRec(nums, stIdx, pivot.first - 1);
        quickSortThreeWayRec(nums, pivot.second + 1, endIdx);
    }
    else
    {
        return;
    }
}

int kthSmallQuickSelect(vector<int>& nums, uint32_t k)
{
    // Make sure 'k' is less than the list of elements
    uint32_t pivotPos = 0;

    if (k < nums.size())
    {
        pivotPos = quickSortPartition(nums, 0, nums.size() - 1);

        while (k != pivotPos)
        {
            if (k > pivotPos)
            {
                pivotPos = quickSortPartition(nums, pivotPos + 1, nums.size() - 1);
            }
            else if (k < pivotPos)
            {
                pivotPos = quickSortPartition(nums, 0, pivotPos - 1);
            }
        }
    }

    return nums[pivotPos];    
}

// ----------------------------------------------------------------------------------------
// PROBLEM 22. Find if an element is present in a row column sorted matrix
// http://articles.leetcode.com/searching-2d-sorted-matrix-part-ii/
//
//             Last element of a row is lesser than the first element of the next row
// ----------------------------------------------------------------------------------------
int findFirstSmallerIndex(vector< vector< int > > twoD, int elmt)
{
    int low = 0;
    int high = twoD.size() - 1;
    uint32_t rows = twoD.size();
    uint32_t cols = twoD[0].size();

    if (elmt < twoD[0][0] || elmt > twoD[rows-1][cols-1])
    {
        return -1;
    }

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (twoD[mid][0] > elmt)
        {
            if (twoD[mid-1][0] <= elmt)
            {
                return mid - 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        else
        {
            low = mid + 1;
        }
    }

    if (low - 1 == high)
    {
        return low - 1;
    }

    return -1;
}

// Forward Declaration
bool binarySearch(vector<int> nums, int elmt);

// Complexity is O(log(N)). Using Binary Search for both Row and Col
bool isElementPresentInRowColMatrixModified(vector<vector<int> > twoD, int elmt)
{
    int32_t r = findFirstSmallerIndex(twoD, elmt);

    if (r < 0 || r > twoD.size())
    {
        return false;
    }

    return binarySearch(twoD[r], elmt);
}

// Complexity is O(N) where N is either N or M based on where it is found.
bool isElementPresentInRowColMatrix(vector<vector<int> > twoD, int elmt)
{
    uint32_t rows = twoD.size();
    uint32_t cols = twoD[0].size();

    for (int i = 0, j = cols - 1; i <= rows && j >=0;)
    {
        if (twoD[i][j] > elmt)
        {
            j--;
        }
        else if (twoD[i][j] < elmt)
        {
            i++;
        }
        else
        {
            // twoD[i][j] == elmt
            return true;
        }
    }

    return false;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 23. Multiplication of two very large numbers
//             Using Bit shift operation
// ------------------------------------------------------------------------------------------------
string largeNumberMultiplication(string str1, string str2)
{
    uint64_t num1 = stoi(str1);
    uint64_t num2 = stoi(str2);
    uint64_t result = 0;

    while (num1)
    {
        if ((num1 % 2) != 0)
        {
            result += num2;
        }
        num2 = num2 << 1;
        num1 = num1 >> 1;
    }

    return to_string(result);
}

// Do Multiplication without using "UINT"
// Utility function to add two numbers represented as string
string addStringNumbers(string s1, string s2)
{
    string result;
    uint32_t carry = 0;
    int32_t i = s1.length() - 1;
    int32_t j = s2.length() - 1;
    for (; i >= 0 && j >= 0; i--, j--)
    {
        uint32_t temp = (s1[i] - '0') + (s2[j] - '0');
        result += (carry + (temp % 10)) + '0';
        carry = temp / 10;
    }

    while (i >= 0)
    {
        result += (carry + (s1[i] - '0')) + '0';
        i--;
        carry = 0;
    }

    while (j >= 0)
    {
        result += (carry + (s2[j] - '0')) + '0';
        j--;
        carry = 0;
    }

    reverse(result.begin(), result.end());
    cout << result << endl;
    return result;
}

// Add two strings in binary form
// http://www.geeksforgeeks.org/add-two-bit-strings/
// sum = a xor b xor c
// carry = ab+bc+ca

// Assuming str1 and str2 in binary. Do the multiplication
string largeNumberBinaryMultStr(string str1, string str2)
{
    string result;

    /*
    while (str1)
    {
        if ((str1[str1.length() - 1]) != '0')
        {
            result = addStringNumbers(str2, result);
        }
        num2 = num2 << 1;
        num1 = num1 >> 1;
    }
    */

    return result;
}

string largeNumberMultiplicationString(string str1, string str2)
{
    //string binStr1 = convertStrNumToBin(str1);
    //string binStr2 = convertStrNumToBin(str2);

    //cout << largeNumberBinaryMultStr(binStr1, binStr2);
    return "";
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 23b. PROBLEM 23b. Binary Decimal Conversions
// ------------------------------------------------------------------------------------------------
// Recursion: Decimal Number to Binary String
void convertDecimalNumToBinaryStrRec(uint32_t num, string& strBin)
{
    if (num / 2 != 0)
    {
        convertDecimalNumToBinaryStrRec(num / 2, strBin);
    }

    strBin += (num % 2) + '0';
}

// Decimal Number to Binary String
string convertDecimalNumToBinaryStr(uint32_t num)
{
    string strBin;

    while (num / 2 != 0)
    {
        strBin += (num % 2) + '0';
        num = num / 2;
    }
    strBin += num % 2 + '0';

    std::reverse(strBin.begin(), strBin.end());
    return strBin;
}

// Decimal String to Binary String
string convertDecimalStrToBinaryStr(string strDec)
{
    return "";
}

// Binary String to Decimal String
string convertBinaryStrToDecimalStr(string strBin)
{
    return "";
}

// Binary String to Decimal Number
uint32_t convertBinaryStrToDecimalNum(string strBin)
{
    return 0;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 24. Finding the Minimum Window in S which Contains All Elements from T
//             http://articles.leetcode.com/finding-minimum-window-in-s-which
//             http://stackoverflow.com/questions/3592079/minimum-window-width-in-string-x-that-contains-all-characters-in-string-y
//             Complexity: O(n). Actually it is O(2n)
// ------------------------------------------------------------------------------------------------
void printUnorderedMap(unordered_map<char, uint32_t> myMap)
{
    for (auto mm : myMap)
    {
        cout << mm.first << ": " << mm.second << " , ";
    }
    cout << endl;
}

uint32_t minWindowContainingString(string str1, string str2)
{
    unordered_map<char, uint32_t> hasToFindMap;
    unordered_map<char, uint32_t> foundMap;
    uint32_t countFoundChars = 0;
    uint32_t minWindowSize = std::numeric_limits<std::int32_t>::max();
    uint32_t windowBegIdx = 0;
    uint32_t windowEndIdx = 0;
    uint32_t startPos = 0;

    // Update Count of each character in a HasToFindMap
    for (char c : str2)
    {
        // The below line takes care of the entire block
        // ++hasToFindMap[c];
        auto itr = hasToFindMap.find(c);
        if (itr != hasToFindMap.end())
        {
            (itr->second)++;
        }
        else
        {
            hasToFindMap[c] = 1;
        }
    }

    // Go over each character and find if it is present in HasToFindMap
    // If it is not present, then continue to the next character
    // If it is present, then
    //     Increase Count only when necessary
    //     Check if Count has reached to Total Number of Characters 
    for (uint32_t i = 0; i < str1.length(); i++)
    {
        auto itrToFind = hasToFindMap.find(str1[i]);

        // If the character is not present in Has to find map then proceed to the next
        // character.
        if (itrToFind != hasToFindMap.end())
        {
            auto itrFound = foundMap.find(str1[i]);

            if (itrFound != foundMap.end())
            {
                // If Count on Found Map is EQUAL or GREATER, don't increase COUNT
                // Increase COUNT only if CHAR on Found map is LESS than ToFindMap
                // IMP: We can use [] operator as the element is preset for sure
                if (itrFound->second < hasToFindMap[str1[i]])
                {
                    countFoundChars++;
                }
                (itrFound->second)++;
            }
            else
            {
                // Should increase found characters in this case too. It should not be
                // increased only when the CHARs Found are more than chars present
                foundMap[str1[i]] = 1;
                countFoundChars++;
            }

            // If we have found characters same as the number of characters in str2 then
            // we have found a WINDOW
            if (countFoundChars == str2.length())
            {
                // While we have more characters in hand, increment begin.
                // This is to reduce the size of the window
                //
                // If the character is NOT present in HAS to find map, then go to next char
                // VERY IMP to check foundMap[i] > hasToFindMap[i]
                auto itrToFind = hasToFindMap.find(str1[startPos]);
                while (itrToFind == hasToFindMap.end() ||
                        foundMap.at(str1[startPos]) > hasToFindMap.at(str1[startPos]))
                {
                    // IMP: Do .at() only if the element is present. Else we will get
                    // out_of_range exception
                    if (itrToFind != hasToFindMap.end() &&
                        foundMap.at(str1[startPos]) > hasToFindMap.at(str1[startPos]))
                    {
                        foundMap.at(str1[startPos])--;
                    }

                    startPos++;
                    itrToFind = hasToFindMap.find(str1[startPos]);
                }

                // Compute the minimum Window length
                if (minWindowSize > (i - startPos + 1))
                {
                    minWindowSize = (i - startPos + 1);
                    windowBegIdx = startPos;
                    windowEndIdx = i;
                }
            }
        }
    }
    cout << "Win Beg: " << windowBegIdx << "; Win End: " << windowEndIdx << "; Win Len: " << minWindowSize << endl;

    return minWindowSize;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 25. Find if an element is present in a rotated sorted array
//             http://stackoverflow.com/questions/4773807/searching-in-an-sorted-and-rotated-array
//             Complexity: O(log(n)).
// ------------------------------------------------------------------------------------------------
bool binarySearchRecursion(vector<int> nums, int low, int high, int elmt)
{
    if (low > high)
    {
        return false;
    }

    // IMP: should be SIGNED. Imagine a CASE with just ONE element
    int32_t mid = low + (high - low) / 2;

    if (nums[mid] == elmt)
    {
        return true;
    }
    else if (elmt < nums[mid])
    {
        return binarySearchRecursion(nums, low, mid - 1, elmt);
    }
    else
    {
        return binarySearchRecursion(nums, mid + 1, high, elmt);
    }

}

bool binarySearch(vector<int> nums, int elmt)
{
    uint32_t low = 0;
    uint32_t high = nums.size() - 1;

    while (low <= high)
    {
        int32_t mid = low + (high - low) / 2;

        if (nums[mid] == elmt)
        {
            return true;
        }
        else if (elmt < nums[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return false;
}

bool findInSortedRotatedArray(vector<int> nums, int elmt)
{
    uint32_t low = 0;
    uint32_t high = nums.size() - 1;

    while (low <= high)
    {
        uint32_t mid = low + (high - low) / 2;

        // First part is sorted
        if (nums[low] <= nums[mid])
        {
            // Element present in Sorted first half
            if (elmt >= nums[low] && elmt <= nums[mid])
            {
                // Do a binary search for the element here
                return binarySearchRecursion(nums, low, mid, elmt);
            }
            else
            {
                // Element present in 2nd half which is not sorted
                low = mid + 1;
            }
        }
        else
        {
            // Element present in Sorted Second Half
            if (elmt >= nums[mid] && elmt <= nums[high])
            {
                // Do a binary search for the element here
                return binarySearchRecursion(nums, mid, high, elmt);
            }
            else
            {
                // Element present in 1st half which is not sorted
                high = mid - 1;
            }
        }
    }

    return false;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 25b. Find Index where array is rotated
//              http://stackoverflow.com/questions/11855709/how-to-determine-at-which-index-has-a-sorted-array-been-rotated-around
//              Complexity: O(log(n)).
// ------------------------------------------------------------------------------------------------
bool IsArrayRotatedSorted(vector<int> nums)
{
    bool foundDip = false;

    for (uint32_t i = 1; i < nums.size() - 1; i++)
    {
        if (!foundDip && nums[i] < nums[i - 1])
        {
            foundDip = true;
        }
    }

    return foundDip;
}

int IndexOfRotatedSortedArray(vector<int> nums)
{
    if (!IsArrayRotatedSorted(nums))
    {
        return -1;
    }

    uint32_t low = 0;
    uint32_t high = nums.size() - 1;

    uint32_t mid = low + (high - low) / 2;

    while (mid != low && mid != high)
    {
        // Check if 1st half is sorted
        if (nums[low] < nums[mid])
        {
            low = mid;
        }
        else
        {
            high = mid;
        }

        mid = low + (high - low) / 2;
    }

    return high;

    /*
    while (low < high)
    {
        uint32_t mid = low + (high - low) / 2;

        // Check if 1st half is sorted
        if (nums[low] < nums[mid])
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    */
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 26. Find Award Budget Cuts Problem
//             
// 40,    50,      50,      100,       160,       200,       325,       500,       1075,        1500
// 400,   490,     490,     840,       1200,      1400,      1900,      2425,      3575,        4000
// 40*10, 40+50*9, 90+50*8, 140+100*7, 240+160*6, 400+200*5, 600+325*4, 925+500*3, 1425+1075*2, 2500+1500 
// ------------------------------------------------------------------------------------------------
double findGrantsCap(vector<uint32_t> grants, uint32_t budget)
{
    uint32_t curSum = 0;
    uint32_t tmpSum = 0;
    uint32_t i = 0;

    //Find the first entry where we exceed the budget if we give the amount that is requested
    for (; i < grants.size(); i++)
    {
        tmpSum = curSum + grants[i] * (grants.size() - i);

        if (tmpSum == budget)
        {
            return grants[i];
        }
        else if(tmpSum > budget)
        {
            break;
        }

        curSum += grants[i];
    }

    if (i == grants.size())
    {
        // Returning the max value
        return grants[i-1];
    }
    else
    {
        return (double)(budget - curSum) / (grants.size() - i);
    }
}

double findGrantsCapModified(vector<uint32_t> grants, uint32_t budget)
{
    uint32_t i = 0;
    double cap = budget / grants.size();

    // Find the minimum Cap that can be given and start incrementing the cap if we have a 
    // grant that is less than the cap
    for (; i < grants.size(); i++)
    {
        cout << cap << ", ";
        if (grants[i] <= cap)
        {
            cap += (double)(cap - grants[i]) / (grants.size() - i - 1);
        }
        else
        {
            break;
        }
    }
    cout << endl;

    return cap;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 27. Find if a Bit Stream is divisible by 3
//
// http://www.geeksforgeeks.org/dfa-based-division/
// https://www.careercup.com/question?id=11903257
//             Complexity: O(n).
// ------------------------------------------------------------------------------------------------
void isDivisible(uint32_t i, uint32_t num, uint32_t& rem)
{
    rem = (rem * 2 + i) % num;
}

bool isBitStreamDivsible(string bitStream, uint32_t num)
{
    uint32_t rem = 0;

    for (char c : bitStream)
    {
        isDivisible(c - '0', num, rem);
    }

    return rem;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 28. Sort an array of 0s, 1s and 2s
//
// http://www.geeksforgeeks.org/sort-an-array-of-0s-1s-and-2s/
//             Complexity: O(n).
// ------------------------------------------------------------------------------------------------
void sortZeroOneTwoDutchFlag(vector<int> &nums)
{
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = nums.size() - 1;
    
    while (y < z)
    {
        if (nums[y] == 0)
        {
            swap(nums[x++], nums[y++]);
        }
        else if (nums[y] == 1)
        {
            y++;
        }
        else
        {
            swap(nums[y], nums[z--]);
        }
    }
}

void sortZeroOneTwos(vector<int>& nums)
{
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = nums.size() - 1;

    while (x < z && y < z)
    {
        while (nums[x] == 0)
        {
            x++;
        }

        while (nums[z] == 2)
        {
            z--;
        }

        if (nums[x] == 1)
        {
            y = x;
            while (nums[y] == 1)
            {
                y++;
            }
        }

        if (y < x)
        {
            y = x;
        }

        if (x >= z || y >= z)
        {
            break;
        }

        if (nums[z] == 1)
        {
            swap(nums[z], nums[y]);
        }
        if (nums[z] == 0)
        {
            swap(nums[z], nums[x]);
            x++;
        }
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 29. Find majority element in an array
//
//             http://stackoverflow.com/questions/4325200/find-the-majority-element-in-array
//             Complexity: O(n).
// ------------------------------------------------------------------------------------------------
bool isMajorityElementPresent(vector<int> nums)
{
    uint32_t count = 0;
    uint32_t majorityElement = 0;

    for (uint32_t i = 0; i < nums.size(); i++)
    {
        if (count == 0)
        {
            majorityElement = nums[i];
        }

        if (nums[i] == majorityElement)
        {
            count++;
        }
        else
        {
            count--;
        }
    }

    // Got the majority element. find if it has occurs more than n/2 time
    count = 0;
    for (uint32_t i = 0; i < nums.size(); i++)
    {
        if (nums[i] == majorityElement)
        {
            count++;
        }
    }

    return count > (nums.size()/2) ? true : false;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 30. Sorting almost sorted array misplaced by k elements
//      
//      {2, 6, 3, 12, 56, 8}
//
// http://stackoverflow.com/questions/2726785/sorting-an-almost-sorted-array-elements-misplaced-by-no-more-than-k
// ------------------------------------------------------------------------------------------------
void sortKsortedArray(vector<int>& nums, uint32_t k)
{
    priority_queue<int, vector<int>, std::greater<int> > kNumPriQ;

    for (uint32_t i = 0; i < k; i++)
    {
        kNumPriQ.push(nums[i]);
    }

    uint32_t j = 0;
    for (uint32_t i = k; i < nums.size(); i++, j++)
    {
        kNumPriQ.push(nums[i]);
        nums[j] = kNumPriQ.top();
        kNumPriQ.pop();
    }

    for (; j < nums.size(); j++)
    {
        nums[j] = kNumPriQ.top();
        kNumPriQ.pop();
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 31. Given N points, find k points closest to 0,0
//
// http://stackoverflow.com/questions/9202315/algorithm-to-find-100-closest-stars-to-the-origin
// http://stackoverflow.com/questions/20398799/find-k-nearest-points-to-point-p-in-2-dimensional-plane
// http://www.geeksforgeeks.org/closest-pair-of-points-onlogn-implementation/
// ------------------------------------------------------------------------------------------------
double computeDistanceFromOrigin(pair<int, int> point)
{
    return sqrt(((double)point.first * point.first) + ((double)point.second * point.second));
}

bool compGreater(pair<int, int> x, pair<int, int> y)
{
    return computeDistanceFromOrigin(x) < computeDistanceFromOrigin(y);
}

void findKclosestPoints(vector<pair<int, int> >& pointsList, uint32_t k)
{
    uint32_t i = 0;
    priority_queue< pair<int, int>, vector<pair<int, int> >, std::function<bool(pair<int, int>, pair<int, int>)> > kClosest(compGreater);

    for (; i < k; i++)
    {
        kClosest.push(pointsList[i]);
    }

    for (; i < pointsList.size(); i++)
    {
        if (computeDistanceFromOrigin(pointsList[i]) < computeDistanceFromOrigin(kClosest.top()))
        {
            kClosest.pop();
            kClosest.push(pointsList[i]);
        }
    }

    // Will be printed in descending order
    for (uint32_t j = 0; j < k; j++)
    {
        cout << kClosest.top().first << ":" << kClosest.top().second << ", ";
        kClosest.pop();
    }
    cout << endl;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 32. Move even numbers to front and odd numbers to back with Order preserved
//
// https://www.quora.com/What-are-the-ways-to-segregate-even-and-odd-numbers-in-an-array-while-maintaining-the-order-of-even-and-odd-numbers
// http://stackoverflow.com/questions/10284123/arrays-puzzle-segregate-even-and-odd-numbers
// ------------------------------------------------------------------------------------------------
void moveEvenNosOddNosWithOrder(vector<int>& nums)
{
    vector<int> orderedNums;

    for (uint32_t i = 0; i < nums.size(); i++)
    {
        if (nums[i] % 2 == 0)
        {
            orderedNums.push_back(nums[i]);
        }
    }

    for (uint32_t i = 0; i < nums.size(); i++)
    {
        if (nums[i] % 2 != 0)
        {
            orderedNums.push_back(nums[i]);
        }
    }

    nums = orderedNums;

}

// ------------------------------------------------------------------------------------------------
// PROBLEM 33. Given list of software dependencies. Find order of software installation
//      {{'A', 'E'}, {'B', 'D'}, {'D', 'E'}, {'A', 'B'}, {'C', 'B'}, {'C', 'D'}}
//      Ans: A -> C -> B -> D -> E
//
//      https://www.careercup.com/question?id=5717669093310464
// ------------------------------------------------------------------------------------------------
void printDependencyMap(unordered_map <char, vector<char> > depMap)
{
    for (auto itr = depMap.begin(); itr != depMap.end(); itr++)
    {
        cout << itr->first << ": ";
        for (uint32_t i = 0; i < itr->second.size(); i++)
        {
            cout << itr->second[i] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void findSoftwareInstallationOrder(vector<pair<char, char> >& dependencyList)
{
    unordered_map <char, vector<char> > startMap;
    unordered_map <char, vector<char> > endMap;
    unordered_set <char> softwareSet;
    vector<char> result;

    for (uint32_t i = 0; i < dependencyList.size(); i++)
    {
        auto itr1 = startMap.find(dependencyList[i].first);
        if (itr1 != startMap.end())
        {
            itr1->second.push_back(dependencyList[i].second);
        }
        else
        {
            startMap[dependencyList[i].first] = vector<char> {dependencyList[i].second};
        }

        auto itr2 = endMap.find(dependencyList[i].second);
        if (itr2 != endMap.end())
        {
            itr2->second.push_back(dependencyList[i].first);
        }
        else
        {
            endMap[dependencyList[i].second] = vector<char> {dependencyList[i].first};
        }

        softwareSet.insert(dependencyList[i].first);
        softwareSet.insert(dependencyList[i].second);
    }

    for (auto endElmt : endMap)
    {
        cout << "Start Map: " << endl;
        printDependencyMap(startMap);
        cout  << "End Map: " << endl;
        printDependencyMap(endMap);
        auto itr = startMap.find(endElmt.first);

        // There should be at least one element that is NOT present in startMap
        if (itr == startMap.end())
        {
            result.push_back(endElmt.first);

            // For each element in Vector find if it is present in startMap
            for (char c : endElmt.second)
            {
                auto i2 = startMap.find(c);
                if (i2 != startMap.end())
                {
                    i2->second.erase(std::remove(i2->second.begin(), i2->second.end(), endElmt.first), i2->second.end());
                }

                if (i2->second.size() == 0)
                {
                    startMap.erase(endElmt.first);
                }
            }

            endMap.erase(endElmt.first);
            softwareSet.erase(endElmt.first);
            break;
        }
    }

    cout << "Start Map: " << endl;
    printDependencyMap(startMap);
    cout  << "End Map: " << endl;
    printDependencyMap(endMap);

}

// ------------------------------------------------------------------------------------------------
// PROBLEM 34. Find angle between hour and minute hand of clock
//
//     http://www.geeksforgeeks.org/calculate-angle-hour-hand-minute-hand/
//
//     Hour hand makes 360deg in 12 hours. 
//     i.e In 1 hour, 30 deg
//     So  In 1 min, 0.5 deg
//
//     Minute hand makes 360 deg in 60 minutes.
//     So In 1 min, 6 deg
// ------------------------------------------------------------------------------------------------
uint32_t findAngleBtwnHourMinute(uint32_t hour, uint32_t min)
{
    // VERY IMP: SHOULD be INT32_T and NOT UINT
    // Find Degree made by hour hand w.r.t handle 12
    int32_t hourDegree = hour * 30 + min * 0.5;

    // Find Degree made by minute hand w.r.t handle 12
    int32_t minDegree = min * 6;

    return abs(hourDegree - minDegree);
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 35. Find all pairs of numbers that add to a sum
//                    Idx:  0, 1,  2, 3, 4, 5, 6, 7,  8, 9, 10, 11
//      vector<int> nums = {5, 3, -2, 4, 3, 6, 5, 5, -1, 3, 10, 2};
// ------------------------------------------------------------------------------------------------
void findPairsAddingToSum(const vector<int>& nums, int sum)
{
    // Key: Array Element, Value: Index
    unordered_map<int, vector<int>> mapDiff;
    
    for(int i = 0; i < nums.size(); i++)
    {
        auto itr = mapDiff.find(nums[i]);
        if (itr != mapDiff.end())
        {
            //cout << nums[itr->second] << ", " << nums[i] << endl;
            for (uint32_t m = 0; m < itr->second.size(); m++)
            {
                cout << itr->second[m] << " - " << i << "; " << nums[itr->second[m]] \
                     << " - " << nums[i] << endl;
            }
            mapDiff[sum - nums[i]].push_back(i);     
        }
        
        // Store the difference in the map and Value will be the index
        else
        {
            mapDiff[sum - nums[i]].push_back(i);     
        }
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 36. 
//      A function with inclusion times and exclusion times
//      ab()            de()        hi()
//      {               {           {
//          de();           fg();       lo();
//          hi();       }               qw();
//      }                           }
//
//      Logic:
//          Get A's start time ---> (0)
//          For each entry after A() start,
//              Take next function's(X) start time ---> (1)
//              Till you get next function's(X) end time
//                  Skip all inbetween entries
//              Store next function's(X) end time ---> (2)
//              Result += (2) - (1)
//          Get A's end time ---> (3)
//          Inclusive time = (3) - (0)
//          Exclusive time = (3) - (0) - (Result)
//
//      ab  start   10
//      de  start   15
//      fg  start   17
//      fg  end     19
//      de  end     19  --> 19 - 15 = 4
//
//      hi  start   22 
//      lo  start   27
//      qw  start   31
//      qw  end     37
//      lo  end     38
//      hi  end     43  --> 43 - 22 = 21
//      ab  end     45  --> Inc Time: 45 - 10 = 35; Exc Time: 35 - (4 + 21) = 10
// ------------------------------------------------------------------------------------------------
struct functionDetails
{
    string name;
    string timeTag;
    uint32_t startEndTime;
};

// This is a utility function
pair<uint32_t, uint32_t> computeIncExcTime(const vector<functionDetails>& funcDetails, uint32_t i)
{
    string funcName = funcDetails[i].name;
    uint32_t funcStart = funcDetails[i].startEndTime;
    uint32_t funcOthersTime = 0;
    pair<uint32_t, uint32_t> result = {0, 0};
    uint32_t x = i + 1;
    
    // Go on till the end of list or until you get the END of funcName
    // ASSUMPTION: All entries are valid. You don't get same funcName with another START
    // tag again
    for (; x < funcDetails.size() && funcDetails[x].name != funcName; x++)
    {
        if (funcDetails[x].timeTag == "start")
        {
            string tmpFuncName = funcDetails[x].name;
            uint32_t tmpFuncStartTime = funcDetails[x].startEndTime;

            x++;
            while (funcDetails[x].name != tmpFuncName && x < funcDetails.size())
            {
                x++;
            }

            // Assumption: There is NOT another entry with tmpFuncName and START tag.
            uint32_t tmpFuncEndTime = funcDetails[x].startEndTime;
            funcOthersTime += tmpFuncEndTime - tmpFuncStartTime;
        }
    }

    uint32_t funcEnd = funcDetails[x].startEndTime;
    result = make_pair((funcEnd - funcStart), (funcEnd - funcStart - (funcOthersTime)));

    return result;
}

pair<uint32_t, uint32_t> findInclusiveExclusiveTimeOfFunction(const vector<functionDetails>& funcDetails, string funcName)
{
    pair<uint32_t, uint32_t> result = {0, 0};
    result.first = funcDetails[funcDetails.size() - 1].startEndTime - funcDetails[0].startEndTime;

    for (uint32_t i = 0; i < funcDetails.size(); i++)
    {
        if (funcDetails[i].name == funcName && "start" == funcDetails[i].timeTag)
        {
            return computeIncExcTime(funcDetails, i);
        }
    }

    return result;
}

// ------------------------------------------------------------------------------------------------
// Main Function
// ------------------------------------------------------------------------------------------------
int main()
{
    // Problem 1.
    {
        cout << endl << "Problem 1" << endl;
        string s1 = "hexlloahao";
        string s2 = "hexlloab";
        char result;
        if (findFirstNonMatchingChar(s1, s2, result))
        {
            cout << "First Non Match Char: " << result << endl;
        }
        else
        {
            cout << "No non Match Char" << endl;
        }
    }

    // Problem 2.
    {
        cout << endl << "Problem 2" << endl;
        string s1 = "hlllhabcdedcba";
        cout << "Unique Char: " << findUniqueChar(s1) << endl;
    }

    // Problem 3.
    {
        cout << endl << "Problem 3" << endl;
        uint32_t rows = 5;
        uint32_t cols = 5;
        /*
        int twoD[rows][cols] = {{1, 1, 0},
                                {0, 1, 0},
                                {1, 0, 0} };
                                */
        vector< vector<int> > twoD = {{1, 1, 0, 0, 0},
                                      {0, 1, 0, 0, 1},
                                      {1, 0, 0, 1, 1},
                                      {0, 0, 0, 0, 0},
                                      {1, 0, 1, 0, 1}};

        int **arrayTwoD = new int *[rows];
        for (uint32_t i = 0; i < rows; i++)
        {
            arrayTwoD[i] = new int[cols];
        }

        for (uint32_t i = 0; i < rows; i++)
        {
            for (uint32_t j = 0; j < cols; j++)
            {
                arrayTwoD[i][j] = twoD[i][j];
            }
        }

        printTwoDPtrToPtr(arrayTwoD, rows, cols);
        cout << "Num Islands: " << countConnectedIslands(arrayTwoD, rows, cols) << endl;
    }
        
    // Problem 4. Median of Streams
    {
        cout << endl << "Problem 4" << endl;
        int a[] = {5, 2, 4, 7, 2, 9, 1, 15, -3, 8, 13, -1, 3, 1, 6};
        //int a[] = {5, 2, 4, 7};
        cout << "Median of Stream: ";
        cout << medianOfStreams(a, sizeof(a) / sizeof(int)) << endl;
    }

    // Problem 5. Subarrays and Sum
    {
        cout << endl << "Problem 5" << endl;
        int arr1[] = {-2,-3,4,-1,-2,1,5,-3};
        //int arr1[] = {-2,-3,-4,-1,-2,-1,-5,-3};
        int arr2[] = {15, 2, 4, 8, 9, 5, 10, 13, 23};
        int arr3[] = {5, 6, 1, -2, -4, 3, 1, 5};
        int arr4[] = {4, 1, -3, 2, 6 , -5};
        vector<int> arr5 = {6, 5, 10, 40, 50, 35};

        cout << "Max Sum: " << maxSumSubArray(arr1, sizeof(arr1) / sizeof(arr1[0])) << endl;
        cout << "Max Sum SubSeq:: " << endl;
        maxSumSubSequence(arr1, sizeof(arr1) / sizeof(arr1[0]));
        cout << "Max Prod: " << maxProduct(std::vector<int> (arr1, arr1 + sizeof arr1 / sizeof arr1[0])) << endl;

        subArrayWithSum(arr2, sizeof(arr2) / sizeof(arr2[0]), 23);

        allSubArraysWithSum(arr4, sizeof(arr4) / sizeof(arr4[0]), 5);

        vector <int> nums = {74, 659, 931, 273, 545, 879, 924, 710, 441, 166, 493, 43, 988, 504, 328, 730, 841, 613, 304, 170, 710, 158, 561, 934, 100, 279, 817, 336, 98, 827, 513, 268, 811, 634, 980, 150, 580, 822, 968, 673, 394, 337, 486, 746, 229, 92, 195, 358, 2, 154, 709, 945, 669, 491, 125, 197, 531, 904, 723, 667, 550};
        cout << endl << endl;
        cout << "Max Len Sub Array For Sum: " << maxSubArraysWithLessOrEqualSum(nums, 22337) << endl;

        cout << "Max Sum Not Adjacent: " << maxLengthSubArraySum(arr5) << endl;
    }

    // Problem 6. Find greatest sum divisble by a number
    {
        cout << endl << "Problem 6" << endl;
        vector<int> nums = {1, 6, 2, 9};
        cout << "Greatest Sum Divisble by a number: " << greatestSumOfSubarrayDivisibleByK(nums, 9) << endl;
    }

    // Problem 7. Print Matrix Diagonally
    {
        cout << endl << "Problem 7" << endl;
        cout << "Print Matrix Diagonally" << endl;
        int twoD[5][4] = {{1, 2, 3, 4},
                          {5, 6, 7, 8},
                          {9, 10, 11, 12},
                          {13, 14, 15, 16},
                          {17, 18, 19, 20}};
        //int twoD[3][3] = {{1, 2, 3},
        //                  {4, 5, 6},
        //                  {7, 8, 9}};

        printMatrixDiagonally(twoD);
        cout << endl;
        //printMatrixDiagonally(twoD, 3, 3);
    }

    // Problem 7. Print Matrix Spirally
    {
        cout << endl << "Problem 7" << endl;
        cout << "Print Matrix Spirally" << endl;
        vector< vector <int> > twoDMatrix = {{1, 2, 3, 4},
                                             {5, 6, 7, 8},
                                             {9, 10, 11, 12},
                                             {13, 14, 15, 16},
                                             {17, 18, 19, 20}};

        printMatrixSpiralOrder(twoDMatrix);
        cout << endl;
    }

    // Problem 8. Combination of 1s and 0s
    {
        cout << endl << "Problem 8" << endl;
        string str = "10?0";
        findLastQMark(str);
    }

    // Problem 9. Remove duplicate int from a number
    {
        cout << endl << "Problem 9" << endl;
        cout << largestNumByRemovingDup(122334) << endl;
        //cout << largestNumByRemovingDup(433221) << endl << endl;
        //cout << largestNumByRemovingDup(122334) << endl;
        //cout << largestNumByRemovingDup(43332221) << endl << endl;
        //cout << largestNumByRemovingDup(122334) << endl;
        //cout << largestNumByRemovingDup(4333222) << endl;
    }

    // Problem 10. Find equilibrium Index
    {
        cout << endl << "Problem 10" << endl;
        vector<int> nums = {-7, 1, 5, 2, -4, 3, 0};
        cout << "Eq Idx: " << equilibriumIndex(nums) << endl;
    }

    // Problem 11. Generalized abbreviation
    {
        cout << endl << "Problem 11" << endl;
        string word = "word";
        generalizedAbbrevation(word);
    }

    // Problem 12. If two rectangles overlap
    {
        cout << endl << "Problem 12" << endl;
        Point a1 = {0, 10};
        Point a2 = {10, 0};
        Point b1 = {15, 5};
        Point b2 = {25, 0};

        cout << isRectanglesOverlap(a1, a2, b1, b2) << endl;
    }

    // Problem 13. Largest Subarray with equal number of 0s and 1s
    {
        cout << endl << "Problem 13" << endl;
        cout << "Largest Subarray with equal 0s and 1s" << endl;
        int arr[] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0};
        printLargestSubArrayZeroOne(arr, sizeof(arr) / sizeof(arr[0]));
        cout << endl;
    }

    // Problem 14. 3 number sum closest
    {
        cout << endl << "Problem 14" << endl;
        int arr[] = {1, 4, 6, 8, 10, 45};
        printThreeNumSum(arr, sizeof(arr)/sizeof(arr[0]), 22);
        printThreeNumClosestSum(arr, sizeof(arr)/sizeof(arr[0]), 21);
    }

    // Problem 15. 1 Element Missing and 1 element Duplicate
    {
        cout << endl << "Problem 15" << endl;
        vector<int> v1 = {1, 2, 2, 3};
        findMissingAndDuplicate(v1);
    }

    // Problem 16. Two numbers missing
    {
        cout << endl << "Problem 16" << endl;
        vector<int> v1 = {3,1,2,5,7,8};
        findTwoMissing(v1, v1.size() + 2);
    }

    // Problem 17. Minimum number of conference rooms
    {
        cout << endl << "Problem 17" << endl;
        vector<struct MeetingTime> meetings = {{9, 10}, {14, 16}, {8, 12},  {12, 16},  {10, 12}};
        cout << "Min Meetings Rooms: " << minConfRoomRequired(meetings) << endl;
    }

    // Problem 18. Median of two equal size sorted arrays
    {
        cout << endl << "Problem 18" << endl;
        int arr1[] = {1, 2, 3};
        int arr2[] = {4, 6, 8};
        cout << "Median 1: " << medianTwoSortedSameSizeArrays(arr1, arr2, sizeof(arr1) / sizeof(arr1[0])) << endl;
    }

    // Problem 19. Median of two sorted UNEQUAL arrays
    {
        cout << endl << "Problem 19" << endl;
        //int A[] = {900};
        //int B[] = {5, 8, 10, 20};
	
        //int A[] = {1, 2, 4, 8, 9, 10};
        //int B[] = {3, 5, 6, 7};
        int A[] = {1, 2, 4, 8};
        int B[] = {3, 5, 6};

        int N = sizeof(A) / sizeof(A[0]);
        int M = sizeof(B) / sizeof(B[0]);

        cout << "Median 2: " << medianTwoSortedDiffSizeArrays(A, N, B, M) << endl;
    }

    // Problem 20. Kth smallest Element
    {
        cout << endl << "Problem 20" << endl;
        //int A[] = {1, 2, 6, 8};
        //int B[] = {3, 5};
        int A[] = {1, 2, 6, 8, 9, 15, 20};
        int B[] = {3, 7, 10, 11, 12};

        int N = sizeof(A) / sizeof(A[0]);
        int M = sizeof(B) / sizeof(B[0]);

        cout << "Kth Smallest: " << kthSmallestElement(A, N, B, M, 8) << endl;

        uint32_t index1 = 0;
        uint32_t index2 = 0;
        cout << "Kth Smallest Rec: " << kthSmallestElementRec(A, index1, N, B, index2, M, 4) << endl;

        cout << "Kth Smallest Two: " << kthSmallestElementIterativeTwo(A, N, B, M, 4) << endl;

    }

    // Problem 21. Kth Smallest Element in Unsorted Array
    {
        cout << endl << "Problem 21" << endl;
        int arr[] = {3, 5, 2, 1, 8, 4, 6};
        cout << "Kth Smallest Unsorted: " << kthSmalledInUnsorted(arr, sizeof(arr) / sizeof(arr[0]), 4) << endl;
    }

    // Problem 21b. Kth Smallest Element in Unsorted Array using QuickSelect
    {
        cout << endl << "Problem 21b" << endl;
        vector<int> nums = {3, 5, 2, 1, 8, 4, 6};
        vector<int> nums2 = {3, 3, 5, 1, 3, 2, 3, 1, 3, 8, 0, 3, 4, 3, 6};
        printVectorInt(nums2);
        //quickSortPartition(nums2, 0, nums2.size() - 1);
        //threeWayQuickSortPartition(nums2, 0, nums2.size() - 1);

        //quickSortRec(nums2, 0, nums2.size() - 1);
        quickSortThreeWayRec(nums2, 0, nums2.size() - 1);
        printVectorInt(nums2);

        cout << "Kth Smallest Unsorted Quick Select: " << kthSmallQuickSelect(nums, 0) << endl;
        cout << "Kth Smallest Unsorted Quick Select: " << kthSmallQuickSelect(nums, 1) << endl;
        cout << "Kth Smallest Unsorted Quick Select: " << kthSmallQuickSelect(nums, 2) << endl;
        cout << "Kth Smallest Unsorted Quick Select: " << kthSmallQuickSelect(nums, 3) << endl;
        cout << "Kth Smallest Unsorted Quick Select: " << kthSmallQuickSelect(nums, 4) << endl;
        cout << "Kth Smallest Unsorted Quick Select: " << kthSmallQuickSelect(nums, 5) << endl;
        cout << "Kth Smallest Unsorted Quick Select: " << kthSmallQuickSelect(nums, 6) << endl;
    }

    // Problem 22. Find if an element is present in a row column sorted matrix
    {
        cout << endl << "Problem 22" << endl;
        cout << "Is element present in row column matrix" << ": ";
        vector< vector <int> > twoD = {{1,  4,  7, 11, 15},
                                       {2,  5,  8, 12, 19},
                                       {3,  6,  9, 16, 22},
                                       {10, 13, 14, 17, 24},
                                       {18, 21, 23, 26, 30}};

        vector< vector <int> > twoD2 = {{1, 2, 3, 4},
                                        {5, 6, 7, 8},
                                        {9, 10, 11, 12},
                                        {13, 14, 15, 16},
                                        {17, 18, 19, 20}};

        cout << isElementPresentInRowColMatrix(twoD, 19) << endl;
        cout << isElementPresentInRowColMatrixModified(twoD2, 0) << " ";
        cout << isElementPresentInRowColMatrixModified(twoD2, 2) << " ";
        cout << isElementPresentInRowColMatrixModified(twoD2, 7) << " ";
        cout << isElementPresentInRowColMatrixModified(twoD2, 11) << " ";
        cout << isElementPresentInRowColMatrixModified(twoD2, 15) << " ";
        cout << isElementPresentInRowColMatrixModified(twoD2, 19) << " ";
        cout << isElementPresentInRowColMatrixModified(twoD2, 21) << endl;
    }

    // Problem 23. Multiplication of two very large numbers
    {
        cout << endl << "Problem 23" << endl;
        cout << "Multiplication of large numbers using Bit operation" << endl;
        string s1 = "5830";
        string s2 = "23958233";
        cout << largeNumberMultiplication(s1, s2) << endl;

        addStringNumbers(s1, s2);
    }

    // PROBLEM 23b. PROBLEM 23b. Binary Decimal Conversions
    {
        cout << endl << "PROBLEM 23b" << endl;
        cout << "Binary Decimal Conversions" << endl;
        string strBin;
        uint32_t num = 110;
        convertDecimalNumToBinaryStrRec(num, strBin);
        cout << num << " in binary: " << strBin << endl;
        cout << num << " in binary: " << convertDecimalNumToBinaryStr(num) << endl;
        /*
        convertDecimalStrToBinaryStr();
        convertBinaryStrToDecimalStr();
        convertBinaryStrToDecimalStr();
        */
    }

    // PROBLEM 24. Finding the Minimum Window in S which Contains All Elements from T
    {
        cout << endl << "PROBLEM 24" << endl;
        cout << "Minimum Window containing characters" << endl;
        string str1 = "ADOBECOEBANCD";
        string str2 = "ABC";
        string str3 = "acbbaca";
        string str4 = "aba";
        minWindowContainingString(str1, str2);
        minWindowContainingString(str3, str4);
    }

    // Problem 25. Find if an element is present in a rotated sorted array
    {
        cout << endl << "Problem 25" << endl;
        cout << "Binary Search and Rotated Sorted Array" << endl;
        vector<int> nums = {2, 3, 17, 19, 22, 46, 82};
        cout << binarySearch(nums, 2) << " ";
        cout << binarySearch(nums, 3) << " ";
        cout << binarySearch(nums, 17) << " ";
        cout << binarySearch(nums, 19) << " ";
        cout << binarySearch(nums, 22) << " ";
        cout << binarySearch(nums, 46) << " ";
        cout << binarySearch(nums, 82) << " ";
        cout << binarySearch(nums, 83) << endl;
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 2) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 3) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 17) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 19) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 22) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 46) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 82) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 83) << endl;

        vector<int> nums2 = {17, 19, 22, 46, 82, 2, 3};
        cout << findInSortedRotatedArray(nums, 2) << " ";
        cout << findInSortedRotatedArray(nums, 3) << " ";
        cout << findInSortedRotatedArray(nums, 17) << " ";
        cout << findInSortedRotatedArray(nums, 19) << " ";
        cout << findInSortedRotatedArray(nums, 22) << " ";
        cout << findInSortedRotatedArray(nums, 46) << " ";
        cout << findInSortedRotatedArray(nums, 82) << " ";
        cout << findInSortedRotatedArray(nums, 20) << endl;
    }

    // PROBLEM 25b. Find Index where array is rotated
    {
        cout << endl << "PROBLEM 25b" << endl;
        cout << "Find Index where array is rotated" << endl;
        vector<int> nums = {17, 19, 22, 46, 82, 2, 3};
        cout << IndexOfRotatedSortedArray(nums) << endl;
    }

    // PROBLEM 26. Find Award Budget Cuts Problem
    {
        cout << endl << "PROBLEM 26" << endl;
        cout << "Award Cuts Problem" << endl;
        vector<uint32_t> grants = {40, 50, 50, 100, 160, 200, 325, 500, 1075, 1500};
        cout << findGrantsCap(grants, 2000) << endl;
        cout << findGrantsCapModified(grants, 2000) << endl;
    }

    // PROBLEM 27. Find if a Bit Stream is divisible by 3
    {
        cout << endl << "PROBLEM 27" << endl;
        cout << "Is Bit Stream Divisble by 3" << endl;
        string stream = "111";
        cout << isBitStreamDivsible(stream, 3) << endl;
    }

    // PROBLEM 28. Sort an array of 0s, 1s and 2s{
    {
        cout << endl << "PROBLEM 28" << endl;
        cout << "Sort an array of 0s 1s and 2s" << endl;
        vector <int> nums = {0, 0, 1, 0, 2, 0, 0, 1, 2, 1, 0, 1};
        printVectorInt(nums);
        sortZeroOneTwoDutchFlag(nums);
        printVectorInt(nums);
    }

    // PROBLEM 29. Find majority element in an array
    {
        cout << endl << "PROBLEM 29" << endl;
        cout << "Find Majority Element"<< endl;
        vector <int> nums = {0, 0, 1, 0, 2, 0, 0, 1, 2, 1, 0, 1};
        cout << isMajorityElementPresent(nums) << endl;
    }

    // PROBLEM 30. Sorting almost sorted array misplaced by k elements
    {
        cout << endl << "PROBLEM 30" << endl;
        cout << "Sorting almost sorted array misplaced by k elements" << endl;
        vector <int> nums = {2, 6, 3, 12, 56, 8};
        printVectorInt(nums);
        sortKsortedArray(nums, 3);
        printVectorInt(nums);
    }

    // PROBLEM 31. Given N points, find k points closest to 0,0
    {
        cout << endl << "PROBLEM 31" << endl;
        cout << "Given N points, find k points closest to Origin: " << endl;
        vector<std::pair<int, int> > pointsList = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}}; 
        findKclosestPoints(pointsList, 3);
    }

    // PROBLEM 32. Move even numbers to front and odd numbers to back with Order preserved
    {
        cout << endl << "PROBLEM 32" << endl;
        cout << "Move even numbers to front and odd numbers to back with Order preserved" << endl;
        vector <int> nums = {5, 6, 8, 3, 7, 1, 2, 9};
        printVectorInt(nums);
        moveEvenNosOddNosWithOrder(nums);
        printVectorInt(nums);
    }

    // PROBLEM 33. Given list of software dependencies. Find order of software installation
    {
        cout << endl << "PROBLEM 33" << endl;
        //cout << "Find order of software installation" << endl;
        vector<std::pair<char, char> > softwareList = {{'A', 'E'}, {'B', 'D'}, {'D', 'E'}, {'A', 'B'}, {'C', 'B'}, {'C', 'D'}}; 
        //findSoftwareInstallationOrder(softwareList);
    }

    // PROBLEM 34. Find angle between hour and minute hand of clock
    {
        cout << endl << "PROBLEM 34" << endl;
        cout << "Find angle between hour and minute hand of clock" << endl;
        cout << findAngleBtwnHourMinute(3, 30) << endl;
        cout << findAngleBtwnHourMinute(7, 40) << endl;
        cout << findAngleBtwnHourMinute(7, 20) << endl;
    }

    // PROBLEM 35. Find all pairs of numbers that add to a sum
    {
        cout << endl << "PROBLEM 35" << endl;
        cout << "Find all pairs that add to a sum" << endl;
        vector<int> nums = {5, 3, -2, 4, 3, 6, 5, 5, -1, 3, 10, 2};
        findPairsAddingToSum(nums, 8);
    }
            

    {
        cout << endl << "PROBLEM 36" << endl;
        cout << "Find inclusive and exclusive times of a function" << endl;
        vector<functionDetails> funcTimes = {{"ab", "start", 10}, {"de", "start", 15}, \
                                          {"fg", "start", 17}, {"fg", "end", 19}, \
                                          {"hi", "start", 19}, {"hi", "end", 22}, \
                                          {"de", "end", 25}, {"ab", "end", 28}};

        vector<functionDetails> funcTimes2 = {{"ab", "start", 10}, {"de", "start", 15}, \
                                           {"fg", "start", 17}, {"fg", "end", 19}, \
                                           {"de", "end", 19}, {"hi", "start", 22}, \
                                           {"lo", "start", 27}, {"qw", "start", 31}, \
                                           {"qw", "end", 37}, {"lo", "end", 38}, \
                                           {"hi", "end", 43}, {"ab", "end", 45}};
        string funcName = "ab";

        pair<uint32_t, uint32_t> res = findInclusiveExclusiveTimeOfFunction(funcTimes2, funcName);
        cout << "Inclusive Time: " << res.first << "; ExclusiveTime: " << res.second << endl;
    }

    cout << endl;
    return 0;
}
