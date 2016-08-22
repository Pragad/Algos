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
