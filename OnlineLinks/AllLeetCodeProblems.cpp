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
 * PROBLEM 1. Range Sum Query - Immutable
 * bool     findFirstNonMatchingChar(string s1, string s2, char& result)
 *
 * PROBLEM 2: 
 *
 */

// Utility function to print a vector of ints
void printVectorInt(vector<int> nums)
{
    for (int num : nums)
    {
        cout << num << ", ";
    }
    cout << endl;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 1.   Given an integer array nums, find the sum of the elements between indices i and j (i = j), inclusive.
//              Given nums = [-2, 0, 3, -5, 2, -1]
//
//              sumRange(0, 2) -> 1
//              sumRange(2, 5) -> -1
//              sumRange(0, 5) -> -3
// -----------------------------------------------------------------------------------------
class NumArray
{
public:
    NumArray(vector<int> &nums)
    {
        _nums = nums;
        _totalSum = getTotalSum();
        buildLeftRightSumMapForEachIndex();
    }

    void buildLeftRightSumMapForEachIndex()
    {
        int leftSum = 0;

        for (int i = 0; i < _nums.size(); i++)
        {
            _leftRightSumMap[i] = make_pair(leftSum, _totalSum - leftSum - _nums[i]);
            leftSum += _nums[i];
        }
    }

    // Calculate the total sum of the vector
    int getTotalSum()
    {
        int vecSum = 0;
        for (int num : _nums)
        {
            vecSum += num;
        }

        return vecSum;
    }

    // Find sum of a range of numbers
    int sumRange(int i, int j)
    {
        pair<int, int> leftRightSumForI = _leftRightSumMap[i];
        pair<int, int> leftRightSumForJ = _leftRightSumMap[j];

        return _totalSum - leftRightSumForI.first - leftRightSumForJ.second;
    }
    
    // Print elements of the vector
    void printNums()
    {
        for (int num : _nums)
        {
            cout << num << ", ";
        }
        cout << endl;
    }

private:
    vector<int> _nums;
    int         _totalSum;
    unordered_map<int, pair<int, int> > _leftRightSumMap;

};

// -----------------------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------------------
int main()
{
    {
        cout << endl << "PROBLEM 1" << endl;
        cout << "Range Sum Query Immutable" << endl;

        vector<int> nums = {-2, 0, 3, -5, 2, -1};

        NumArray numArray(nums);
        cout << numArray.sumRange(0, 1) << endl;
        cout << numArray.sumRange(1, 2) << endl;
        cout << numArray.sumRange(0, 2) << endl;
        cout << numArray.sumRange(2, 5) << endl;
        cout << numArray.sumRange(0, 5) << endl;
        cout << numArray.sumRange(1, 4) << endl;
    }

    return 0;
}
