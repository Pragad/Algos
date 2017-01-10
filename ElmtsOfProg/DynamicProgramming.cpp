#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // fill_n
#include <cstring>
#include <climits>              // INT_MAX, INT_MIN, numeric_limits
using namespace std;

/*
 * Problem 1. Fibonacci
 * unsigned int fibonacci(int n)
 * unsigned int fibonacciDynamic2(int n)
 *
 * Problem 2. Ladder Problem
 * void ladderPathsRec(char* strPath, unsigned int num, unsigned int recLevel)
 * void ladderDynamic(int number)
 *
 * Problem 3. Longest Increasing Subsequence
 * uint32_t longestIncreasingSubSequenceVec(vector<int>& nums)
 * uint32_t longestIncreasingSubseq(vector<int> nums)
 *
 * Problem 4. Longest Common Subsequence
 * uint32_t longestCommonSubSequenceRec(string str1, string str2)
 * uint32_t longestCommonSubSequenceDP(string str1, string str2)
 *
 * PROBLEM 5. Coin change problem
 * uint32_t minCoinChangeRec(uint32_t coins[], uint32_t num, uint32_t val)
 * uint32_t minCoinChangeDP(uint32_t coins[], uint32_t num, uint32_t val)
 *
 * PROBLEM 6a. Longest Increasing Subsequence in a 2D Matrix considering Diagonals
 * uint32_t longestIncSubSeqTwoDMat(int** twoDMat, uint32_t rows, uint32_t cols)
 *
 * PROBLEM 6b. Longest Increasing Path in a 2D Matrix without Diagonals
 * int longestIncreasingPath(vector<vector<int>>& matrix)
 *
 * PROBLEM 7. Partition Equal Subset Sum
 * bool isSubsetSum(const vector<int>& nums)
 * void printAllSubsetSum(const vector<int>& nums)
 *
 * PROBLEM 8. Edit Distance between two Strings
 * int minEditDistance(const string& word1, const string& word2)
 *
 * PROBLEM 9. Longest Palindromic Substring
 * string longestPalindromicString(string s)
 */

// Utility function to print a Vector of Vector
template <typename T>
void printVecOfVec(vector< vector<T> > vecOfVec)
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

// Utility function to print a vector 
template<typename T>
void printVector(vector<T> nums)
{
    for (auto num : nums)
    {
        cout << num << ", ";
    }
    cout << endl;
}

// ---------------------------------------------------------------------------------------
// Problem 1: Fibonacci of a number
// http://php.bubble.ro/fibonacci/
// ---------------------------------------------------------------------------------------
unsigned int fibonacci(int n)
{
    // VERY IMP: // If N is less than 2, return n
    //if (n == 1 || n == 2)
    if (n <= 1)
    {
        return n;
        //return 1;
    }
    else
    {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

// O(N) space
// O(2^n) Time
unsigned int fibonacciDynamic(int n)
{
    vector<unsigned int> fibVec;

    fibVec.push_back(1);
    fibVec.push_back(1);

    for (unsigned int i = 2; i < n; i++)
    {
        fibVec.push_back(fibVec[i - 1] + fibVec[i - 2]);
    }

    for (int i = 0; i < fibVec.size(); i++)
    {
        cout << fibVec[i] << " ";
    }
    cout << endl;

    return fibVec[n - 1];
}

unsigned int fibonacciDynamic2(int n)
{
    if ( n <= 1)
    {
        return n;
    }

    int a = 1;
    int b = 0;
    int result;

    for (unsigned int i = 1; i < n; i++)
    {
        result = a + b;
        b = a;
        a = result;
    }

    return result;
}

// ---------------------------------------------------------------------------------------
// Problem 2: Ladder Problem
// Algorithm: Used Dynamic Programming to get the result.
// So Complexity is O(N).
// I store the "n-1" and "n-2" lader positions. Then I append
// '1' to 'n-1' positions and '2' to all 'n-2' positions.
// ---------------------------------------------------------------------------------------

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
    cout << "Ladder Dynamic" << endl;
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

// ---------------------------------------------------------------------------------------
// Problem 2: Print paths down a ladder
// Algorithm: Use recursion to print the paths
//            One call to the function is made for every single path entry.
// http://www.geeksforgeeks.org/count-ways-reach-nth-stair/
// ---------------------------------------------------------------------------------------
void ladderPathsStrRec(string strPath, unsigned int num, unsigned int recLevel)
{
    if (num == 0)
    {
        cout << strPath << endl;
        return;
    }

    if (num >= 1)
    {
        // Add '1' to our paths and go one step further
        strPath += '1';
        ladderPathsStrRec(strPath, num - 1, recLevel + 1);
    }

    if (num >= 2)
    {
        // As we have added '1' remove it
        // Add '2' to our paths and go two steps further
        strPath.pop_back();
        strPath += '2';
        ladderPathsStrRec(strPath, num - 2, recLevel + 1);
    }
}

void ladderPathsRec(char* strPath, unsigned int num, unsigned int recLevel)
{
    if (num == 0)
    {
        strPath[recLevel] = '\0';
        cout << strPath << endl;
    }

    if (num >= 1)
    {
        // Add '1' to our paths and go one step further
        strPath[recLevel] = '1';
        ladderPathsRec(strPath, num - 1, recLevel + 1);
    }

    if (num >= 2)
    {
        // Add '2' to our paths and go two steps further
        strPath[recLevel] = '2';
        ladderPathsRec(strPath, num - 2, recLevel + 1);
    }
}

void ladderRec(unsigned int number)
{
    // This array will hold one valid path to reach 'N' steps.
    // So the max memory required would be 'N + 1'
    // Using char array
    {
        cout << "Ladder Paths using Char Array" << endl;
        char* strPath = new char[number + 1];
        ladderPathsRec(strPath, number, 0);
        delete[] strPath;
    }

    // Using string
    {
        cout << "Ladder Paths using String" << endl;
        string strPath;
        ladderPathsStrRec(strPath, number, 0);
    }
}

// ---------------------------------------------------------------------------------------
// Problem 2b: Ladder Count Possibilities
// ---------------------------------------------------------------------------------------
uint32_t countPossibilitiesLadderRec(uint32_t num)
{
    if (num <= 2)
    {
        return num;
    }
    else
    {
        return countPossibilitiesLadderRec(num - 1) + countPossibilitiesLadderRec(num - 2);
    }
}

uint32_t countPossibilitiesLadderDynamic(uint32_t num)
{
    if (num <= 2)
    {
        return num;
    }

    uint32_t res = 0;
    uint32_t a = 2;
    uint32_t b = 1;
    for (uint32_t i = 2; i < num; i++)
    {
        res = a + b;

        // VERY IMP: First put a in b and the res in a
        b = a;
        a = res;
    }

    return res;
}

// ---------------------------------------------------------------------------------------
// Problem 3: Longest Increasing Subsequence
// http://stackoverflow.com/questions/2631726/how-to-determine-the-longest-increasing-subsequence-using-dynamic-programming
//
//      Let arr[0..n-1] be the input array and
//      L(i) be the length of the LIS till index i such that arr[i] is part of LIS and arr[i] is the last element in LIS, then L(i) can be recursively written as.
//      
//      L(i) = { 1 + Max ( L(j) ) }
//      where j < i and arr[j] < arr[i] and if there is no such j then L(i) = 1
//
//      Complexity Recursion: O(n!)
//      Complexity DP: O(n log(n))
//
//               lis(4)
//        /        |       \
//      lis(3)    lis(2)   lis(1)
//     /   \        /
//   lis(2) lis(1) lis(1)
//   /
// lis(1)
// ---------------------------------------------------------------------------------------
uint32_t longestIncreasingSubSequenceRecUtil(int arr[], uint32_t num, uint32_t& maxVal)
{
    if (num == 1)
    {
        return 1;
    }

    uint32_t tmpMax;
    uint32_t maxTillHere = 1;
    for (uint32_t i = 1; i < num; i++)
    {
        tmpMax = longestIncreasingSubSequenceRecUtil(arr, i, maxVal);
        if (arr[i - 1] < arr[num - 1] &&
            (tmpMax + 1) > maxTillHere)
        {
            maxTillHere = tmpMax + 1;
        }
    }

    maxVal = max(maxVal, maxTillHere);

    return maxTillHere;
}

uint32_t longestIncreasingSubSequenceRec(int arr[], uint32_t num)
{
    uint32_t maxVal = 1;
    (void) longestIncreasingSubSequenceRecUtil(arr, num, maxVal); 
    return maxVal;
}

// ---------------------------------------------------------------------------------------
// TIME COMPLEXITY: O(N^2)
// DP Logic: O(N*N)
//      
//      Arr: 3, 5, 6, 2, 5, 4, 19, 5, 6, 7, 12
//      DP : 1, 2, 3, 1, 2, 2,  4, 3, 4, 5,  6
//
//      1. Start i at 1 and j at 0
//      2. If num[i] > num[j], then DP[i] = 1 + DP[j]
//      3. Go till 'j' reaches 'i'
//      4. Once 'j' reaches 'i', move 'j' back to 0 and increment 'i'
//      5. Keep track of max values got so far
// ---------------------------------------------------------------------------------------
uint32_t longestIncreasingSubSequenceVec(vector<int>& nums)
{
    if (nums.size() < 2)
    {
        return nums.size();
    }

    // VERY IMP
    // maxSoFar should be initialized
    uint32_t maxSoFar = 0;
    uint32_t endIdx;

    // Make everything 1 to start with. Because LIS will be at least 1
    vector<uint32_t> DP(nums.size(), 1);
    
    for (uint32_t i = 1; i < nums.size(); i++)
    {
        for (int32_t j = i-1; j >=0; j--)
        {
            if ((nums[j] < nums[i]) && (DP[j] + 1 > DP[i]))
            {
                DP[i] = DP[j] + 1;
            }
        }

        if (DP[i] > maxSoFar)
        {
            maxSoFar = DP[i];
            endIdx = i;
        }
    }
    //printVector(DP);

    return maxSoFar;
}

// ---------------------------------------------------------------------------------------
// Dynamic Programming Approach: O(N log(N))
//
// Collection of integers: 2 6 3 4 1 2 9 5 8
// Steps:
// 0. S = {} - Initialize S to the empty set
// 1. S = {2} - New largest LIS
// 2. S = {2, 6} - New largest LIS
// 3. S = {2, 3} - Changed 6 to 3
// 4. S = {2, 3, 4} - New largest LIS
// 5. S = {1, 3, 4} - Changed 2 to 1
// 6. S = {1, 2, 4} - Changed 3 to 2
// 7. S = {1, 2, 4, 9} - New largest LIS
// 8. S = {1, 2, 4, 5} - Changed 9 to 5
// 9. S = {1, 2, 4, 5, 8} - New largest LIS

// Collection of integers: 10,9,2,5,3,7,101,18
// Steps:
// 0. S = {} - Initialize S to the empty set
// 1. S = {10} - New largest LIS
// 2. S = {9} - Change 10 to 9
// 3. S = {2} - Changed 9 to 2
// 4. S = {2, 5} - New largest LIS
// 5. S = {2, 3} - Changed 5 to 3
// 6. S = {2, 3, 7} - New largest LIS
// 7. S = {2, 3, 7, 101} - New largest LIS
// 8. S = {2, 3, 7, 18} - Changed 101 to 18
// ---------------------------------------------------------------------------------------
uint32_t findFirstLargerElement(vector<int> longIncSeq, int num)
{
    uint32_t low = 0;
    uint32_t high = longIncSeq.size()-1;

    if (longIncSeq.size() < 1)
    {
        return 0;
    }

    if (num < longIncSeq[0])
    {
        return 0;
    }

    if (num > longIncSeq[longIncSeq.size()-1])
    {
        return longIncSeq.size();
    }

    while (low < high)
    {
        uint32_t middle = (low + high) / 2;

        // VERY IMP ">=" NOT ">"
        if (longIncSeq[middle] >= num)
        {
            // Check if the previous element is lesser than the middle. That means
            // middle is the first element greater.
            if ((middle - 1) >= 0 && longIncSeq[middle - 1] <= num)
            {
                return middle;
            }
            high = middle - 1;
        }
        else
        {
            // Check if the next element is greater than the middle. That means
            // middle element is the last element smaller.
            if ((middle + 1) < longIncSeq.size() && longIncSeq[middle + 1] > num)
            {
                return middle + 1;
            }
            low = middle + 1;
        }
    }
}

uint32_t longestIncreasingSubseq(vector<int> nums)
{
    if (nums.size() < 2)
    {
        return nums.size();
    }
 
    vector<int> longIncSeq;
    uint32_t maxLisLen = 1;
    longIncSeq.push_back(nums[0]);

    for (uint32_t i = 1; i < nums.size(); i++)
    {
        // Check if the number is greater than the LAST number in the DP array
        // If so add it to our LIS list.
        if (nums[i] > longIncSeq[longIncSeq.size()-1])
        {
            longIncSeq.push_back(nums[i]);
            maxLisLen++;
        }

        // VERY IMP: Less OR EQUAL
        else if (nums[i] <= longIncSeq[0])
        {
            // If the new element is less than the first element, put in in the first
            // position and start from beginning
            longIncSeq[0] = nums[i];
        }

        else
        {
            // Find the First element that is greater than the current element
            // and replace the new element there
            uint32_t index = findFirstLargerElement(longIncSeq, nums[i]);
            longIncSeq[index] = nums[i];
        }
    }

    return maxLisLen;
}

// ---------------------------------------------------------------------------------------
// Problem 4: Longest Common Subsequence
//            Using Recursion
// ---------------------------------------------------------------------------------------
uint32_t longestCommonSubSequenceRec(string str1, string str2)
{
    // Even if one string is 0, then we don't have to go further
    if (str1.length() == 0 || str2.length() == 0)
    {
        return 0;
    }

    if (str1[str1.length()-1] == str2[str2.length()-1])
    {
        return 1 + longestCommonSubSequenceRec(str1.substr(0, str1.length()-1),
                                               str2.substr(0, str2.length()-1));
    }
    else
    {
        return max(longestCommonSubSequenceRec(str1.substr(0, str1.length()-1), str2),
                   longestCommonSubSequenceRec(str1, str2.substr(0, str2.length()-1)));
    }
}

// ---------------------------------------------------------------------------------------
// Problem 4: Longest Common Subsequence
//            Using DP
//
// Logic: 
//      1. If str[i] == str[j] then
//         DP[i][j] = 1 + DP[i-1][j-1]
//      2. Else
//         DP[i][j] = max(DP[i-1][j], DP[i][j-1])
//
//         X M J Y A U Z
//       0 0 0 0 0 0 0 0
//     M 0 0 1 1 1 1 1 1
//     Z 0 0 1 1 1 1 1 2
//     J 0 0 1 2 2 2 2 2
//     A 0 0 1 2 2 3 3 3
//     W 0 0 1 2 2 3 3 3
//     X 0 1 1 2 2 3 3 3
//     U 0 1 1 2 2 3 4 4
// ---------------------------------------------------------------------------------------
uint32_t longestCommonSubSequenceDP(string str1, string str2)
{
    // Even if one string is 0, then we don't have to go further
    if (str1.length() == 0 || str2.length() == 0)
    {
        return 0;
    }
    
    // VERY IMP. To initialize a 2D array to 0.
    //uint32_t subSeqDP[str1.length()+1][str2.length()+1] = {{0}};

    vector< vector<int> > subSeqDP(str1.length() + 1, vector<int> (str2.length() + 1, 0));
    
    // STD:FILL NOT WORKING
    //std::fill_n(subSeqDP, ((str1.length()+1) * (str2.length()+1)), 0);
    //std::fill_n(subSeqDP, (sizeof subSeqDP / sizeof **subSeqDP), 0);
    //memset(subSeqDP, 0, sizeof(subSeqDP));

    for(uint32_t i = 1; i <= str1.length(); i++)
    {
        for(uint32_t j = 1; j <= str2.length(); j++)
        {
            if (str1[i-1] == str2[j-1])
            {
                subSeqDP[i][j] = 1 + subSeqDP[i-1][j-1];
            }
            else
            {
                subSeqDP[i][j] = max(subSeqDP[i-1][j], subSeqDP[i][j-1]);
            }
        }
    }

    //printVecOfVec(subSeqDP);
    // To print out the LCS
    string strLcs;
    // VeRY IMP: Start from Length
    for (int i = str1.length(), j = str2.length(); i > 0 && j > 0;)
    {
        // VERY IMP: Should compare i-1 and j-1
        if (str1[i-1] == str2[j-1])
        {
            strLcs += str1[i-1];
            i--;
            j--;
        }
        else
        {
            if (subSeqDP[i-1][j] > subSeqDP[i][j-1])
            {
                i--;
            }
            else
            {
                j--;
            }
        }
    }

    reverse(strLcs.begin(), strLcs.end());
    cout << "LCS String: " << strLcs << endl;
    return subSeqDP[str1.length()][str2.length()];
}

// ---------------------------------------------------------------------------------------
// PROBLEM 5. Coin change problem
// http://algorithms.tutorialhorizon.com/dynamic-programming-coin-change-problem/
//            coins[] = {25, 10, 5}, V = 30
//            Ans: 2
// EVERY COIN EITHER GETS INCLUDED or EXCLUDED
// Time Complexity 2^n
// ---------------------------------------------------------------------------------------
//uint32_t minCoinChangeRec(vector<int> coins)
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
            if (val >= coins[i])        // IMP Here
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

// ---------------------------------------------------------------------------------------
// http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
// Coins:     2, 3, 4, 5
// DP   : 0, 1   , 2, 3, 4, 5, 6
// 6    : 0, -INF, 1, 1, 2, 2, 2
//                       1, 1, 1
//
// Logic: 
//      1. If coins[j] >  val, i.e. Coin '7' Val '2'
//         We can't form 2 from coin 7. So continue
//      2. Else DP[i] = min(1 + DP[i - coin[j]])
//      3. To get the coins we should use another array to store as and when we update
//      
//      Sum: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
//      DP : 0, 1, 2, 3, 4, 1, 1, 2, 1, 2,  2,  2,  2 
//
// Complexity: O(m.n)
// ---------------------------------------------------------------------------------------
uint32_t minCoinChangeDP(uint32_t coins[], uint32_t num, uint32_t val)
{
    // We will store values till dpTable of VAL. So need space from 0 to Val + 1.
    // To store dpTable[5], we need an array of size 6.
    vector<uint32_t> dpTable(val + 1, UINT_MAX);
    uint32_t tmpResult = UINT_MAX;

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

    // printVector(dpTable);
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

// ---------------------------------------------------------------------------------------
// PROBLEM 6a. Longest Increasing Subsequence in a 2D Matrix considering Diagonals 
// http://stackoverflow.com/questions/6558710/longest-increasing-sequence-2d-matrix-recursion
// Including Diagonal Paths as well
// {{97, 47, 56, 36, 60, 31, 57, 54, 12, 55},
// {35, 57, 41, 13, 82, 80, 71, 93, 31, 62},
// {89, 36, 98, 75, 91, 46, 95, 53, 37, 99},
// {25, 45, 26, 17, 15, 82, 80, 73, 96, 17},
// {75, 22, 63, 96, 96, 36, 64, 31, 99, 86},
// {12, 80, 42, 74, 54, 14, 93, 17, 14, 55},
// {14, 15, 20, 71, 34, 50, 22, 60, 32, 41},
// {90, 69, 44, 52, 54, 73, 20, 12, 55, 52},
// {39, 33, 25, 31, 76, 45, 44, 84, 90, 52},
// {94, 35, 55, 24, 41, 63, 87, 93, 79, 24}}
// ---------------------------------------------------------------------------------------
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

template <size_t rows, size_t cols>
uint32_t getLongestSeq(int32_t (&twoDMat)[rows][cols], uint32_t x, uint32_t y, uint32_t** &longestSeq)
{
    uint32_t maxVal = 0;
    if (longestSeq[x][y] == 0)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (!(i == 0 && j == 0) &&
                    (x + i >= 0 && x + i < rows) &&
                    (y + j >= 0 && y + j < cols) &&
                    (twoDMat[x+i][y+j] > twoDMat[x][y]))
                {
                    uint32_t longVal = getLongestSeq(twoDMat, x + i, y  + j, longestSeq);
                    maxVal = max(longVal, maxVal);
                }
            }
        }
        longestSeq[x][y] = 1 + maxVal;
    }

    return longestSeq[x][y];
}

template <uint32_t rows, uint32_t cols>
uint32_t longestIncSubSeqTwoDMat(int (&twoDMat)[rows][cols])
{
    uint32_t maxSeq = 0;
    uint32_t** longestSeq = new uint32_t*[rows];
    for (uint32_t i = 0; i < rows; i++)
    {
        longestSeq[i] = new uint32_t[cols];
        std::fill_n(longestSeq[i], cols, 0);
    }

    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            uint32_t tmpMax = getLongestSeq(twoDMat, i, j, longestSeq);
            if (tmpMax > maxSeq)
            {
                maxSeq = tmpMax;
            }
        }
    }

    for (uint32_t i = 0; i < rows; i++)
    {
        delete[] longestSeq[i];
    }
    delete[] longestSeq;
    return maxSeq;
}

// ---------------------------------------------------------------------------------------
// PROBLEM 6b. Longest Increasing Path in a 2D Matrix without Diagonals
// ---------------------------------------------------------------------------------------
bool isValidPositions(int i, int j, int rows, int cols)
{
    return (i >= 0 && i < rows && j >= 0 && j < cols);
}

int dfsIncreasingPath(int i,
                      int j,
                      const vector<vector<int>>& matrix,
                      vector<vector<int>>& incPathMatrix)
{
    // Have four variables to store the max path length got from four sides
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;
    int val4 = 0;
    bool dfsFlag = false;

    // Extra Check. Not necessary. Instead can directly make it to 0
    if (incPathMatrix[i][j] == -1)
    {
        incPathMatrix[i][j] = 0;
    }

    // 1. Check if the new 'i' and new 'j' are valid
    // 2. Only if the matrix[newI][newJ] > matrix[i][j] we get the new value
    // 3. Also do DFS only we haven't done it before
    if (isValidPositions(i - 1, j, matrix.size(), matrix[0].size()) &&
        matrix[i - 1][j] > matrix[i][j])
    {
        dfsFlag = true;

        // Go DFS only if we don't know the value of the incPathMatrix
        if (incPathMatrix[i - 1][j] == -1)
        {
            val1 = dfsIncreasingPath(i - 1, j, matrix, incPathMatrix);
        }
        else
        {
            val1 = incPathMatrix[i - 1][j];
        }
    }
    if (isValidPositions(i, j - 1, matrix.size(), matrix[0].size()) &&
        matrix[i][j - 1] > matrix[i][j])
    {
        dfsFlag = true;

        if (incPathMatrix[i][j - 1] == -1)
        {
            val2 = dfsIncreasingPath(i, j - 1, matrix, incPathMatrix);
        }
        else
        {
            val2 = incPathMatrix[i][j - 1];
        }
    }
    if (isValidPositions(i + 1, j, matrix.size(), matrix[0].size()) &&
        matrix[i + 1][j] > matrix[i][j])
    {
        dfsFlag = true;

        if (incPathMatrix[i + 1][j] == -1)
        {
            val3 = dfsIncreasingPath(i + 1, j, matrix, incPathMatrix);
        }
        else
        {
            val3 = incPathMatrix[i + 1][j];
        }
    }
    if (isValidPositions(i, j + 1, matrix.size(), matrix[0].size()) &&
        matrix[i][j + 1] > matrix[i][j])
    {
        dfsFlag = true;

        if (incPathMatrix[i][j + 1] == -1)
        {
            val4 = dfsIncreasingPath(i, j + 1, matrix, incPathMatrix);
        }
        else
        {
            val4 = incPathMatrix[i][j + 1];
        }
    }

    // If any of the previous DfsFlag has been set, it means that we have a Row Col
    // which has higher value than current 'i' 'j'
    if (!dfsFlag)
    {
        incPathMatrix[i][j] = 0;
        return 0;
    }
    else
    {
        int maxVal = (1 + max(max(max(val1, val2), val3), val4));
        incPathMatrix[i][j] = maxVal;
        return maxVal;
    }
}

int longestIncreasingPath(vector<vector<int>>& matrix)
{
    int longestIncPath = -1;

    if (matrix.size() == 0)
    {
        return 0;
    }

    vector<vector<int>> incPathMatrix (matrix.size(), vector<int>(matrix[0].size(), -1));

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (incPathMatrix[i][j] == -1)
            {
                int incPathLen = dfsIncreasingPath(i, j, matrix, incPathMatrix);
                if (incPathLen > longestIncPath)
                {
                    longestIncPath = incPathLen;
                }
            }
        }
    }
    // printVecOfVec(incPathMatrix);

    return 1 + longestIncPath;
}

// ---------------------------------------------------------------------------------------
// PROBLEM 7. Partition Equal Subset Sum
// Find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.
// 
// Logic:
//      0. We can get 0 total from a empty set. So Colum 0 will be all T
//      1. If nums[i] > curValue, nums[i] won't play any role. So just get from top
//         sumMap[i][j] = sumMap[i-1][j]
//      2. Also if sumMap[i-1][j] is True, then sumMap[i][j] is True
//      3. If nums[i] <= curValue, go to previous row and go curValue steps back and get that value
//         sumMap[i][j] = sumMap[i-1][j - nums[i]]
//
//     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
//  3: T, F, F, T, F, F, F, F, F, F, F,  F,  F,
// 34: T, F, F, T, F, F, F, F, F, F, F,  F,  F,
//  4: T, F, F, T, T, F, F, T, F, F, F,  F,  F,
// 11: T, F, F, T, T, F, F, T, F, F, F,  T,  F,
//  5: T, F, F, T, T, T, F, T, T, T, F,  T,  T,
//  2: T, F, T, T, T, T, T, T, T, T, T,  T,  T,
// ---------------------------------------------------------------------------------------
bool isSubsetSum(const vector<int>& nums, int target)
{
    // Create a 2D vector and fill it with 0s
    vector< vector<bool> > sumMap(nums.size(), vector<bool>(target + 1, 0));

    // Make sure colum 0 is T. Or if target is 0, return true
    for (uint32_t i = 0; i < nums.size(); i++)
    {
        sumMap[i][0] = 1;
    }

    for (int32_t i = 0; i < nums.size(); i++)
    {
        for (int32_t j = 1; j <= target; j++)
        {
            if (nums[i] == j ||
                (i - 1 >= 0 && sumMap[i - 1][j] == 1))
            {
                sumMap[i][j] = 1;
            }
            else if (nums[i] < j && (i - 1 >= 0) && (j - nums[i] >= 0))
            {
                sumMap[i][j] = sumMap[i - 1][j - nums[i]];
            }
            else if (nums[i] > j && (i - 1 >= 0))
            {
                sumMap[i][j] = sumMap[i - 1][j];
            }
        }
    }

    //printVecOfVec(sumMap);
    return sumMap[nums.size() - 1][target];
}

void printAllSubsetSum(const vector<int>& nums, int target)
{

}

bool canPartition(vector<int>& nums)
{
    int numsTotal = 0;

    for (int i : nums)
    {
        numsTotal += i;
    }

    // Return false if the total is ODD
    if (numsTotal & 1)
    {
        return false;
    }

    // Now check if we have a subset for half the sum
    return isSubsetSum(nums, numsTotal/2);
}

// ---------------------------------------------------------------------------------------
// Problem 8. Edit Distance between two Strings
// Logic:
//      If word1[i] == word2[j] then DP[i][j] will be same as DP[i-1][j-1]
//      Else DP[i][j] will be minimum of DP[i-1][j], DP[i][j-1], DP[i-1][j-1]
//
//     a z c e d
//   0 1 2 3 4 5
// a 1 0 1 2 3 4
// b 2 1 1 2 3 4
// c 3 2 2 1 2 3
// d 4 3 3 2 2 2
// e 5 4 4 3 2 3
// f 6 5 5 4 3 3
// ---------------------------------------------------------------------------------------
int minEditDistance(const string& word1, const string& word2)
{
    // Create a 2D vector and fill it with 0s
    vector<vector<uint32_t>> DPtable(word1.length() + 1, vector<uint32_t>(word2.length() + 1, 0));

    // Start with empty string on both sides. So add the cost for converting from 
    // empty string to word1 AND
    // Cost for converting empty string to word2
    iota(DPtable[0].begin(), DPtable[0].end(), 0);

    for (uint32_t i = 0; i < word1.length() + 1; i++)
    {
        DPtable[i][0] = i;
    }

    for (uint32_t i = 1; i < DPtable.size(); i++)

    {
        for (uint32_t j = 1; j < DPtable[i].size(); j++)
        {
            if (word1[i - 1] == word2[j - 1])
            {
                DPtable[i][j] = DPtable[i - 1][j - 1];
            }
            else
            {
                DPtable[i][j] = 1 + min(min(DPtable[i - 1][j], DPtable[i][j - 1]), DPtable[i - 1][j - 1]);
            }
        }
    }
    //printVecOfVec(DPtable);

    return DPtable[word1.length()][word2.length()];
}

// ---------------------------------------------------------------------------------------
// PROBLEM 9. Longest Palindromic Substring
// Logic:
//
// A palindrome can be expanded from its center, and there are only 2N-1 such centers.

// The reason is the center of a palindrome can be in between two letters.
// Such palindromes have even number of letters (such as abba)
// and its center are between the two �b�s.
// ---------------------------------------------------------------------------------------
string findSubString(const string& str, int stIdx, int endIdx)
{
    while(stIdx >= 0 && endIdx < str.length())
    {
        if (str[stIdx] == str[endIdx])
        {
            stIdx--;
            endIdx++;
        }
        else
        {
            break;
        }
    }

    return str.substr(stIdx + 1, endIdx - stIdx - 1);
}

string longestPalindromicString(const string& s)
{
    string palinSubStr = "";

    if (s.empty())
    {
        return "";
    }

    // At least a single char will be the answer for sure
    palinSubStr = s.substr(0, 1);

    for (int i = 0; i < s.length(); i++)
    {
        string tmpSubStr1 = findSubString(s, i , i);
        string tmpSubStr2 = findSubString(s, i , i + 1);

        if (tmpSubStr1.length() > palinSubStr.length())
        {
            palinSubStr = tmpSubStr1;
        }

        if (tmpSubStr2.length() > palinSubStr.length())
        {
            palinSubStr = tmpSubStr2;
        }
    }

    return palinSubStr;
}

// ---------------------------------------------------------------------------------------
// Main Function
// ---------------------------------------------------------------------------------------
int main()
{
    {
        cout << endl << "Problem 1. Fibonacci" << endl;
        int n = 10;
        cout << "1. " << fibonacci(n) << endl;
        cout << "2. " << fibonacciDynamic(n) << endl;

        cout << "3. " << fibonacciDynamic2(n) << endl;
    }

    // Problem 2. Ladder Problem
    {
        cout << endl << "Problem 2. Ladder Problem" << endl;
        ladderRec(5);
        ladderDynamic(5);
        cout << "Possibilities Rec 3: " << countPossibilitiesLadderRec(3) << endl;
        cout << "Possibilities Rec 4: " << countPossibilitiesLadderRec(4) << endl;
        cout << "Possibilities Rec 5: " << countPossibilitiesLadderRec(5) << endl;
        cout << "Possibilities Dy 3: " << countPossibilitiesLadderDynamic(3) << endl;
        cout << "Possibilities Dy 4: " << countPossibilitiesLadderDynamic(4) << endl;
        cout << "Possibilities Dy 5: " << countPossibilitiesLadderDynamic(5) << endl;
    }

    // Problem 3. Longest Increasing Subsequence
    {
        cout << endl << "Problem 3. LIS" << endl;
        int arr[] = {10,9,2,5,3,7,101,18};
        int arr2[] = {3,5,6,2,5,4,19,5,6,7,12};
        vector<int> vec5 = {3,5,6,2,5,4,19,5,6,7,12};

        cout << "LIS 0: " << longestIncreasingSubSequenceRec(arr2, sizeof(arr2) / sizeof(arr2[0])) << endl;
        cout << "LIS 1: " << longestIncreasingSubSequenceVec(vec5) << endl;
        cout << "LIS 2: " << longestIncreasingSubseq(vec5) << endl << endl;
    }

    // Problem 4. Longest Common Subsequence
    {
        cout << endl << "Problem 4. LCS" << endl;
        string str1 = "ABCDGH";
        string str2 = "AEDFHR";
        string str3 = "MZJAWXU";
        string str4 = "XMJYAUZ";
        cout << "LCS 1: " << longestCommonSubSequenceRec(str1, str2) << endl;
        cout << "LCS 2 Rec: " << longestCommonSubSequenceRec(str3, str4) << endl;
        cout << "LCS 2 DP: " << longestCommonSubSequenceDP(str3, str4) << endl;

    }

    // Problem 5: Coin Change Problem
    {
        cout << endl << "Problem 5. Min Coins: " << endl;
        uint32_t coins[] = {1, 8, 6, 5};
        cout << minCoinChangeWrapper(coins, sizeof(coins)/sizeof(uint32_t), 12) << endl;
    }

    // PROBLEM 6a. Longest Increasing Subsequence in a 2D Matrix considering Diagonals 
    {
        cout << endl << "PROBLEM 6a. Longest Increasing Subsequence in a 2D Matrix considering Diagonals " << endl;
        int arr[1][1] = {{1}};
        int arr0[2][2] = {{3, 6},
                         {4, 4}};
        int arr1[3][3] = {{1, 8, 3},
                         {6, 4, 2},
                         {3, 2, 1}};
        int arr2[10][10] = {{97, 47, 56, 36, 60, 31, 57, 54, 12, 55},
                        {35, 57, 41, 13, 82, 80, 71, 93, 31, 62},
                        {89, 36, 98, 75, 91, 46, 95, 53, 37, 99},
                        {25, 45, 26, 17, 15, 82, 80, 73, 96, 17},
                        {75, 22, 63, 96, 96, 36, 64, 31, 99, 86},
                        {12, 80, 42, 74, 54, 14, 93, 17, 14, 55},
                        {14, 15, 20, 71, 34, 50, 22, 60, 32, 41},
                        {90, 69, 44, 52, 54, 73, 20, 12, 55, 52},
                        {39, 33, 25, 31, 76, 45, 44, 84, 90, 52},
                        {94, 35, 55, 24, 41, 63, 87, 93, 79, 24}};

        cout << longestIncSubSeqTwoDMat(arr2) << endl;
    }

    // PROBLEM 6b. Longest Increasing Path in a 2D Matrix without Diagonals 
    {

        cout << endl << "PROBLEM 6b. Longest Increasing Path in a 2D Matrix without Diagonals" << endl;
        vector<vector<int>> nums1 = { {9,9,4},
                                      {6,6,8},
                                      {2,1,1} };
        vector<vector<int>> nums2 = { {3,4,5},
                                      {3,2,6},
                                      {2,2,1} };
        vector<vector<int>> nums3 = {{1}};
        vector<vector<int>> nums4 = {{3, 6},
                                     {4, 4}};
        vector<vector<int>> nums5 = {{1, 8, 3},
                                     {6, 4, 2},
                                     {3, 2, 1}};
        vector<vector<int>> nums6 = {{97, 47, 56, 36, 60, 31, 57, 54, 12, 55},
                                     {35, 57, 41, 13, 82, 80, 71, 93, 31, 62},
                                     {89, 36, 98, 75, 91, 46, 95, 53, 37, 99},
                                     {25, 45, 26, 17, 15, 82, 80, 73, 96, 17},
                                     {75, 22, 63, 96, 96, 36, 64, 31, 99, 86},
                                     {12, 80, 42, 74, 54, 14, 93, 17, 14, 55},
                                     {14, 15, 20, 71, 34, 50, 22, 60, 32, 41},
                                     {90, 69, 44, 52, 54, 73, 20, 12, 55, 52},
                                     {39, 33, 25, 31, 76, 45, 44, 84, 90, 52},
                                     {94, 35, 55, 24, 41, 63, 87, 93, 79, 24}};

        cout << longestIncreasingPath(nums1) << endl;
        cout << longestIncreasingPath(nums2) << endl;
        cout << longestIncreasingPath(nums3) << endl;
        cout << longestIncreasingPath(nums4) << endl;
        cout << longestIncreasingPath(nums5) << endl;
        cout << longestIncreasingPath(nums6) << endl;
    }

    // Problem 7. Partition Equal Subset Sum
    {
        cout << endl << "Problem 7. Partition Equal Subset Sum" << endl;
        vector<int> nums = {3, 34, 4, 11, 5, 2};
        cout << isSubsetSum(nums, 12) << endl;
        printAllSubsetSum(nums, 12);
    }

    // Problem 8. Edit Distance between two Strings
    {
        cout << endl << "Problem 8. Edit Distance between two Strings" << endl;
        string word1a = "abcdef";
        string word2a = "azced";
        string word1b = "howareyo";
        string word2b = "whoareyo";
        string word1c = " what is this";
        string word2c = "whatisthis";
        cout << "Min Edit Dist: " << minEditDistance(word1a, word2a) << endl;
        cout << "Min Edit Dist: " << minEditDistance(word1b, word2b) << endl;
    }

    // PROBLEM 9. Longest Palindromic Substring
    {
        cout << endl << "Problem 9. Longest Palindromic Substring" << endl;
        cout << longestPalindromicString("caba") << ", ";
        cout << longestPalindromicString("babad") << ", ";
        cout << longestPalindromicString("abacdfgdcaba") << ", ";
        cout << longestPalindromicString("cbbd") << ", ";
        cout << endl;
    }
}
