#include <iostream>
#include <vector>
using namespace std;

/*
 * PROBLEM 1. Find out the maximum sub-array that gives the maxSum
 * bool     findFirstNonMatchingChar(string s1, string s2, char& result)
 *
 * PROBLEM 2: Find out the maximum sub-array of non negative numbers from an array.
 * char     findUniqueChar(string str)
 *
 */

// ------------------------------------------------------------------------------------------------
// UTILITY FUNCTIONS
// ------------------------------------------------------------------------------------------------
void printVectorInt(const vector<int>& A)
{
	for (auto a : A)
	{
        cout << a << ", ";
	}
    cout << endl;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 1. Find out the maximum sub-array that gives the maxSum
//
// ------------------------------------------------------------------------------------------------
vector<int> maxMaxSumSubArray(vector<int> &A)
{
    vector<int> result;
    if (A.size() == 0)
    {
        // Return an empty vector
        return result;
    }
    
    int curSum = A[0];
    int maxSum = A[0];
    int stIdx = 0;
    int endIdx = 0;
    int resStIdx = 0;
    int resEndIdx = 0;
    
    for (int i = 1; i < A.size() - 1; i++)
    {
        if (A[i] > curSum + A[i])
        {
            curSum = A[i];
            stIdx = i;
            endIdx = i;
        }
        else
        {
            curSum = curSum + A[i];
            endIdx = i;
        }
        
        if (curSum > maxSum)
        {
            maxSum = curSum;
            resStIdx = stIdx;
            resEndIdx = endIdx;
        }
    }
    
    vector<int> tmp(&A[resStIdx], &A[resEndIdx + 1]);
    result = tmp;
    
    return result;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 2: Find out the maximum sub-array of non negative numbers from an array.
//
// https://www.interviewbit.com/problems/max-non-negative-subarray/
// ------------------------------------------------------------------------------------------------
vector<int> maxNonNegativeSubArray(vector<int> &A)
{
    vector<int> result;
    if (A.size() == 0)
    {
        // Return an empty vector
        return result;
    }
    
    int maxLen = 0;
    int stIdx = 0;
    int endIdx = 0;
    int resStIdx = 0;
    int resEndIdx = 0;
    bool startAgain = true; // Will be turned true when a negative number is seen
    
    for (int i = 0; i < A.size() - 1; i++)
    {
        if (A[i] >= 0)
        {
            if (startAgain)
            {
                stIdx = i;
                endIdx = i;
                startAgain = false;
            }
            else
            {
                endIdx = i;
            }

            if (endIdx - stIdx + 1 > maxLen)
            {
                maxLen = endIdx - stIdx + 1;
                resStIdx = stIdx;
                resEndIdx = endIdx;
            }
        }
        else
        {
            startAgain = true;
        }
    }
    
    if (A[resStIdx] >= 0)
    {
        vector<int> tmp(&A[resStIdx], &A[resEndIdx+1]);
        result = tmp;
    }
    
    return result;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 3: Add One To Number
//
// https://www.interviewbit.com/problems/add-one-to-number/
// ------------------------------------------------------------------------------------------------
vector<int> plusOne(vector<int> &A)
{
    vector<int> result;
    
    if (A.size() == 0)
    {
        return result;
    }
    
    int lastNum = A[A.size() - 1] + 1;
    int carry = lastNum / 10;
    result.push_back(lastNum % 10);
    
    for (int i = A.size() - 2; i >=0; i--)
    {
        int tmp = A[i] + carry;
        result.push_back(tmp % 10);
        carry = tmp / 10;
    }
    
    if (carry > 0)
    {
        result.push_back(carry);
    }
    
    for (int i = result.size()-1; i >=0; i--)
    {
        if (result[i] == 0)
        {
            result.pop_back();
        }
        else
        {
            break;
        }
    }
    
    std::reverse(result.begin(), result.end());
    
    return result;
}

// ----------------------------------------------------------------------------------------------
// PROBLEM 4.
// You are in an infinite 2D grid where you can move in any of the 8 directions :
// 
//  (x,y) to 
//     (x+1, y), 
//     (x - 1, y), 
//     (x, y+1), 
//     (x, y-1), 
//     (x-1, y-1), 
//     (x+1,y+1), 
//     (x-1,y+1), 
//     (x+1,y-1) 
// 
// You are given a sequence of points and the order in which you need to cover the points. Give the minimum number of steps in which you can achieve it. You start from the first point.
// 
// Example :
// 
// Input : [(0, 0), (1, 1), (1, 2)]
// Output : 2
// 
// It takes 1 step to move from (0, 0) to (1, 1). It takes one more step to move from (1, 1) to (1, 2).
// ----------------------------------------------------------------------------------------------


// ----------------------------------------------------------------------------------------------
// PROBLEM 5.
// You are given an array of N integers, A1, A2 ,…, AN. Return maximum value of f(i, j) for all 1 = i, j = N.
// f(i, j) is defined as |A[i] - A[j]| + |i - j|, where |x| denotes absolute value of x.
// 
// For example,
// 
// A=[1, 3, -1]
// 
// f(1, 1) = f(2, 2) = f(3, 3) = 0
// f(1, 2) = f(2, 1) = |1 - 3| + |1 - 2| = 3
// f(1, 3) = f(3, 1) = |1 - (-1)| + |1 - 3| = 4
// f(2, 3) = f(3, 2) = |3 - (-1)| + |2 - 3| = 5
// 
// So, we return 5.
// ----------------------------------------------------------------------------------------------


// ----------------------------------------------------------------------------------------------
// PROBLEM 6.
// You are given a binary string(i.e. with characters 0 and 1) S consisting of characters S1, S2, …, SN. In a single operation, you can choose two indices L and R such that 1 = L = R = N and flip the characters SL, SL+1, …, SR. By flipping, we mean change character 0 to 1 and vice-versa.
// 
// Your aim is to perform ATMOST one operation such that in final string number of 1s is maximised. If you don’t want to perform the operation, return an empty array. Else, return an array consisting of two elements denoting L and R. If there are multiple solutions, return the lexicographically smallest pair of L and R.
// 
// Notes:
// - Pair (a, b) is lexicographically smaller than pair (c, d) if a < c or, if a == c and b < d.
// 
// For example,
// 
// S = 010
// 
// Pair of [L, R] | Final string
// _______________|_____________
// [1 1]          | 110
// [1 2]          | 100
// [1 3]          | 101
// [2 2]          | 000
// [2 3]          | 001
// 
// We see that two pairs [1, 1] and [1, 3] give same number of 1s in final string. So, we return [1, 1].
// 
// Another example,
// 
// If S = 111
// 
// No operation can give us more than three 1s in final string. So, we return empty array [].
// ----------------------------------------------------------------------------------------------



// ------------------------------------------------------------------------------------------------
// MAIN FUNCTION
// ------------------------------------------------------------------------------------------------
int main()
{
    // PROBLEM 1. Find out the maximum sub-array that gives the maxSum
    {
        cout << "PROBLEM 1: Find out the maximum sub-array that gives the maxSum" << endl;
		vector<int> A = {1, 2, 5, -7, 2, 3};
		vector<int> result = maxMaxSumSubArray(A);
        printVectorInt(result);
        cout << endl;
    }

    // PROBLEM 2: Find out the maximum sub-array of non negative numbers from an array
	{
        cout << "PROBLEM 2: Find out the maximum sub-array of non negative numbers from an array" << endl;
		vector<int> A0 = {1, 2, 5, -7, 2, 3};
		vector<int> A1 = {-1, 2, 5, -7, 2, 3};
		vector<int> A2 = {-1, -2, 5, -7, 2, 3};
		vector<int> A3 = {-1};
		vector<int> result = maxNonNegativeSubArray(A3);
        printVectorInt(result);
        cout << endl;
	}

	// PROBLEM 3: Add One To Number
    {
        cout << "PROBLEM 3: Add One To Number" << endl;
		vector<int> A = {1, 2, 3};
		vector<int> result = plusOne(A);
        printVectorInt(result);
        cout << endl;
    }

    // 
    {
        cout << " " << endl;
        cout << endl;
    }

    cout << endl;
    return 0;
}
