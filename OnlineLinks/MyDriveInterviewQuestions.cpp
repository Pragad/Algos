#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>        // std::fill_n
#include <queue>            // Priority Queue
#include <typeinfo>         // typeid
#include <vector>
#include <cmath>            // ciel
using namespace std;

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
 * int      maxSubArraySum(int arr[], int num)
 *
 * PROBLEM 5b. Find the max sub array product
 * int maxProduct(vector<int>& nums)
 * 
 * PROBLEM 6. Coin change problem
 * uint32_t minCoinChangeRec(uint32_t coins[], uint32_t num, uint32_t val)
 *
 * PROBLEM 7. Print Matrix Diagonally
 * void printMatrixDiagonally(int** twoDMatrix, uint32_t rows, uint32_t cols)
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
 *
 * PROBLEM 17. Find minimum number of conference room required
 * uint32_t minConfRoomRequired(vector<struct MeetingTime> meetingsList)
 *
 * PROBLEM 18. Find median of two sorted arrays of same size
 * int medianTwoSortedSameSizeArrays(int arr1[], uint32_t num1, int arr2[], uint32_t num2);
 *
 * PROBLEM 18b. Find median of two sorted arrays of same size
 * int medianTwoSortedDiffSizeArrays(int arr1[], uint32_t num1, int arr2[], uint32_t num2);
 *
 * PROBLEM 19. Find Kth smallest element in Union of two sorted arrays
 * int kthSmallestElement(int arr1[], uint32_t num1, int arr2[], uint32_t num2);
 */

// Structure to define a x-axis y-axis point
struct Point
{
    int x;
    int y;
};

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

    uint32_t minIndex = INT_MAX;
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
            uniqChar temp{false, i};
            charMap[str[i]] = temp;
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

    // Initialize a Visited bool array
    for (uint32_t i = 0; i < rows; i++)
    {
        visited[i] = new bool[cols];
    }

    // Set all values of bool array to false;
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
//            hlllhabcdedcba
//            Ans: e
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

int medianOfStreamsHeap(int element, priority_queue<int>& desHeap, priority_queue<int, std::vector<int>, std::greater<int> >& ascHeap)
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
        return 0;
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
    int maxSum = INT_MIN;

    for (uint32_t i = 0; i < num; i++)
    {
        curSum = max(arr[i], arr[i] + curSum);
        maxSum = max(curSum, maxSum);
    }

    return maxSum;
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
//             Map Find : -1, 0, -3, -1, 5 0
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

// ------------------------------------------------------------------------------------------------
// PROBLEM 5e. Find the max sum such that no two elements are adjacent
// http://stackoverflow.com/questions/4487438/maximum-sum-of-non-consecutive-elements
// http://www.geeksforgeeks.org/maximum-sum-such-that-no-two-elements-are-adjacent/
//
//            5,  5, 10, 40, 50, 35
//            Ans: 80; 5, 40, 35
//            Returns false if no such array is present
// ------------------------------------------------------------------------------------------------
bool maxLengthSubArraySum(vector<int> nums, int& maxNonConSum)
{
    /*
    if (nums.size() == 0)
    {
        return false;
    }

    vector<int> dpMaxSum;
    dpMaxSum[0] = 0;
    dpMaxSum[1] = nums[0];

    for (uint32_t i = 1; i < nums.size() - 1; i++)
    {
        dpMaxSum[i+1] = max(dpMaxSum[i], nums[i] + dpMaxSum[i-1]);
    }

    maxNonConSum = dpMaxSum[nums.length()-1];
    return true;
    */
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 6. Coin change problem
//            coins[] = {25, 10, 5}, V = 30
//            Ans: 2
// ------------------------------------------------------------------------------------------------
//uint32_t minCoinChangeRec(vector<int> coins)
// http://algorithms.tutorialhorizon.com/dynamic-programming-coin-change-problem/
// Time Complexity 2^n
uint32_t minCoinChangeRec(uint32_t coins[], uint32_t num, uint32_t val)
{
    if (val == 0)
    {
        return 0;
    }

    else
    {
        uint32_t minCoin = UINT_MAX;
        for (uint32_t i = 0; i < num; i++)
        {
            if (val >= coins[i])
            {
                // IMP: We have UNLIMITED supply of coins. So comment out the below line
                //int tempMinCoin = 1 + minCoinChangeRec(coins + 1 , num - 1, val - coins[i]);
                uint32_t tempMinCoin = minCoinChangeRec(coins + i , num - i, val - coins[i]);

                if (tempMinCoin != UINT_MAX)
                {
                    minCoin = min(1 + tempMinCoin, minCoin);
                }
            }
        }
        return minCoin;
    }
}

uint32_t minCoinChangeDP(uint32_t coins[], uint32_t num, uint32_t val)
{
    // We will store values till dpTable of VAL. So need space from 0 to Val + 1.
    // To store dpTable[5], we need an array of size 6.
    uint32_t dpTable[val+1];
    uint32_t tmpResult = UINT_MAX;
    std::fill_n(dpTable, val+1, UINT_MAX);

    dpTable[0] = 0;

    // Motto is to fill the DP table from 1 to Target Value
    // For each entry in the dp table, see if we can get that using an entry we have saved before.
    for(uint32_t i = 1; i <= val; i++)
    {
        for (uint32_t j = 0; j < num; j++)
        {
            // Only if the dp table entry is >= current coin proceed
            if (coins[j] <= i)
            {
                tmpResult = dpTable[i - coins[j]];
                if ((tmpResult != UINT_MAX) &&
                    (tmpResult + 1 < dpTable[i]))
                {
                    dpTable[i] = tmpResult + 1;
                }
            }
        }
    }

    return dpTable[val];
}

// Wrapper function to return -1 when we can't give out the Coin Change
int32_t minCoinChangeWrapper(uint32_t coins[], uint32_t num, uint32_t val)
{
    // Following is the recursive function
    //uint32_t minCoins = minCoinChangeRec(coins, num, val);

    // Following is the dynamic programming approach function
    uint32_t minCoins = minCoinChangeDP(coins, num, val);

    return (minCoins == UINT_MAX ? -1 : minCoins);
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 7. Print Matrix Diagonally
// http://stackoverflow.com/questions/28433572/print-2d-array-diagonally-from-bottom-to-top
// http://stackoverflow.com/questions/20420065/loop-diagonally-through-two-dimensional-array
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
                // Reached end of string and first digit is  repeated. Just remove it
                else
                {
                    strNum.erase(i-1, 1);
                    return atoi(strNum.c_str());
                }
            }
        }
    }
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
// http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
// ------------------------------------------------------------------------------------------------
void printLargestSubArrayZeroOne(int arr[], uint32_t num)
{
    if (num == 0)
    {
        return;
    }

    uint32_t countZero = 0;
    uint32_t countOne = 0;

    for(uint32_t i = 0; i < num; i++)
    {
        if (arr[i] == 1)
        {
            countOne++;
        }
        else if (arr[i] == 0)
        {
            countZero++;
        }
    }

    // If either is zero then no sub array
    if (countOne == 0 || countZero == 0)
    {
        cout << "None" << endl;
        return;
    }

    for(uint32_t i = 0, j = num-1; i < j;)
    {
        if (countOne == countZero)
        {
            cout << "Idx 1: " << i << "; Idx 2: " << j << endl;
            return;
        }
        else if (countOne > countZero)
        {
            // One count is more
            if (arr[i] == 1)
            {
                i++;
            }
            else if (arr[j] == 1)
            {
                j--;
            }
        }
        else
        {
            // ZeroCount is more
            if (arr[i] == 0)
            {
                i++;
            }
            else if (arr[j] == 0)
            {
                j--;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 14. 3 number sum closest
// http://www.geeksforgeeks.org/find-a-triplet-that-sum-to-a-given-value/
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

    int closestSum = INT_MAX;
    int tmpClosest = INT_MAX;
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
//             is sorted.
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
    rightSetBit = fullXor & (fullXor - 1);

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

    /*
    bool operator < (const MeetingTime& meetTime) const
    {
        return (startTime < meetTime.startTime);
    }

    bool operator > (const MeetingTime& meetTime) const
    {
        return (areDoubleGreater(endTime, meetTime.endTime));
    }
    */

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

    cout << "Med1: " << medArr1 << "; Med2: " << medArr2 << endl;
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
// PROBLEM 18b. Find median of two sorted arrays of same size
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
// PROBLEM 19. Find Kth smallest element in Union of two sorted arrays
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
int kthSmallestElementTwo(int arr1[], uint32_t num1, int arr2[], uint32_t num2, uint32_t k)
{
    if (k > num1 + num2)
    {
        cout << "Error" << endl;
        return -1;
    }

    // Index 1 + Index 2 will always be k
    uint32_t idx1 = k/2;
    uint32_t idx2 = k - idx1;

    // VERY IMP: SIGNED INT
    int32_t step = k/4;

    while (step > 0)
    {
        //cout << "0. Idx 1: " << idx1 << "; Idx 2: " << idx2 << endl;
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

    kthSmallestElementRec(arr1, index1, num1, arr2, index2, num2, k);
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 20. Find Kth smallest element in an Unsorted array
//
//             int A[] = {3,5,2,1,8,4,6};
//
//             Ans: 4th Smallest is 4
//
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
    for(uint32_t i = 0; i < k; i++)
    {
        kSmallNos.push(arr[i]);
    }

    cout << kSmallNos.top() << endl;

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
// Main Function
// ------------------------------------------------------------------------------------------------
int main()
{
    // Problem 1:
    {
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

    // Problem 2:
    {
        string s1 = "hlllhabcdedcba";
        cout << "Unique Char: " << findUniqueChar(s1) << endl;
    }

    // Problem 3:
    {
        uint32_t rows = 5;
        uint32_t cols = 5;
        /*
        int twoD[rows][cols] = {{1, 1, 0},
                                {0, 1, 0},
                                {1, 0, 0} };
                                */
        int twoD[rows][cols] = {{1, 1, 0, 0, 0},
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
        
    // Problem 4: Median of Streams
    {
        int a[] = {5, 2, 4, 7, 2, 9, 1, 15, -3, 8, 13, -1, 3, 1, 6};
        //int a[] = {5, 2, 4, 7};
        cout << "Median of Stream: ";
        cout << medianOfStreams(a, sizeof(a) / sizeof(int)) << endl;
    }

    // Problem 5: Subarrays and Sum
    {
        //int arr1[] = {-2,-3,4,-1,-2,1,5,-3};
        int arr1[] = {-2,-3,-4,-1,-2,-1,-5,-3};
        int arr2[] = {15, 2, 4, 8, 9, 5, 10, 13, 23};
        int arr3[] = {5, 6, 1, -2, -4, 3, 1, 5};
        int arr4[] = {4, 1, -3, 2, 6 , -5};


        cout << "Max Sum: " << maxSumSubArray(arr1, sizeof(arr1) / sizeof(arr1[0])) << endl;
        cout << "Max Prod: " << maxProduct(std::vector<int> (arr1, arr1 + sizeof arr1 / sizeof arr1[0])) << endl;

        subArrayWithSum(arr2, sizeof(arr2) / sizeof(arr2[0]), 23);

        allSubArraysWithSum(arr4, sizeof(arr4) / sizeof(arr4[0]), 5);
    }

    // Problem 6: Coin Change Problem
    {
        uint32_t coins[] = {10, 5};
        cout << "Min Coins: ";
        cout << minCoinChangeWrapper(coins, sizeof(coins)/sizeof(uint32_t), 20) << endl;
    }

    // Problem 7: Print Matrix Diagonally
    {
        int twoD[5][4] = {{1, 2, 3, 4},
                          {5, 6, 7, 8},
                          {9, 10, 11, 12},
                          {13, 14, 15, 16},
                          {17, 18, 19, 20}};
        /*
        int twoD[3][3] = {{1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9}};
                          */

        printMatrixDiagonally(twoD);
        //printMatrixDiagonally(twoD, 3, 3);
    }

    // Problem 8: Combination of 1s and 0s
    {
        string str = "10?0";
        findLastQMark(str);
    }

    // Problem 9: Remove duplicate int from a number
    {
        cout << largestNumByRemovingDup(122334) << endl;
        /*
        cout << largestNumByRemovingDup(433221) << endl << endl;
        cout << largestNumByRemovingDup(122334) << endl;
        cout << largestNumByRemovingDup(43332221) << endl << endl;
        cout << largestNumByRemovingDup(122334) << endl;
        cout << largestNumByRemovingDup(4333222) << endl;
        */
    }

    // Problem 10. Find equilibrium Index
    {
        vector<int> nums = {-7, 1, 5, 2, -4, 3, 0};
        cout << "Eq Idx: " << equilibriumIndex(nums) << endl;
    }

    // Problem 11. Generalized abbreviation
    {
        string word = "word";
        generalizedAbbrevation(word);
    }

    // Problem 12. If two rectangles overlap
    {
        Point a1 = {0, 10};
        Point a2 = {10, 0};
        Point b1 = {15, 5};
        Point b2 = {25, 0};

        cout << isRectanglesOverlap(a1, a2, b1, b2) << endl;
    }

    // Problem 13. Largest Subarray with equal number of 0s and 1s
    {

    }

    // Problem 14. 3 number sum closest
    {
        int arr[] = {1, 4, 6, 8, 10, 45};
        printThreeNumSum(arr, sizeof(arr)/sizeof(arr[0]), 22);
        printThreeNumClosestSum(arr, sizeof(arr)/sizeof(arr[0]), 21);
    }

    // Problem 15. 1 Element Missing and 1 element Duplicate
    {
        vector<int> v1 = {1, 2, 2, 3};
        findMissingAndDuplicate(v1);
    }

    // Problem 16. Two numbers missing
    {
        vector<int> v1 = {3,1,2,5,7,8};
        findTwoMissing(v1, v1.size() + 2);
    }

    // Minimum number of conference rooms
    {
        vector<struct MeetingTime> meetings = {{9, 10}, {14, 16}, {8, 12},  {12, 16},  {10, 12}};
        cout << "Min Meetings Rooms: " << minConfRoomRequired(meetings) << endl;
    }

    // Median of two equal size sorted arrays
    {
        int arr1[] = {1, 2, 3};
        int arr2[] = {4, 6, 8};
        cout << endl << "Median 1: " << medianTwoSortedSameSizeArrays(arr1, arr2, sizeof(arr1) / sizeof(arr1[0])) << endl;
    }

    // Median of two sorted UNEQUAL arrays
    {
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

    // Kth smallest Element
    {
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

        cout << "Kth Smallest Two: " << kthSmallestElementTwo(A, N, B, M, 4) << endl;

    }

    // Kth Smallest Element in Unsorted Array
    {
        int arr[] = {3, 5, 2, 1, 8, 4, 6};
        cout << "Kth Smallest Unsorted: " << kthSmalledInUnsorted(arr, sizeof(arr) / sizeof(arr[0]), 4) << endl;
    }

    cout << endl;
    return 0;
}
