#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// ------------------------------------------------------------------------------------------------
// Problem 1: Fibonacci of a number
// ------------------------------------------------------------------------------------------------
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

    cout << endl;

    return result;
}

// ------------------------------------------------------------------------------------------------
// Problem 2: Ladder Problem
// Algorithm: Used Dynamic Programming to get the result.
// So Complexity is O(N).
// I store the "n-1" and "n-2" lader positions. Then I append
// '1' to 'n-1' positions and '2' to all 'n-2' positions.
// ------------------------------------------------------------------------------------------------

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

/*
void ladderPathsRec(char* strPath, unsigned int num, unsigned int recLevel)
{
    if (num == 0)
    {
        strPath[recLevel] = '\0';
        cout << strPath << endl;
    }

    if (num >= 1)
    {
        strPath[recLevel] = '1';
        //cout << "1. " << strPath << endl;
        ladderPathsRec(strPath, num - 1, recLevel + 1);
    }

    if (num >= 2)
    {
        strPath[recLevel] = '2';
        //cout << "2. " << strPath << endl;
        ladderPathsRec(strPath, num - 2, recLevel + 1);
    }
}

void ladderRec(unsigned int number)
{
    char* strPath = new char[number + 1];
    ladderPathsRec(strPath, number, 0);
}
*/

// Problem 1: Print paths down a ladder
// Algorithm: Use recursion to print the paths
//            One call to the function is made for every single path entry.

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
    char* strPath = new char[number + 1];
    ladderPathsRec(strPath, number, 0);
    delete[] strPath;
}

// ------------------------------------------------------------------------------------------------
// Problem 3: Longest Common Subsequence
// ------------------------------------------------------------------------------------------------
uint32_t longestIncreasingSubSequence(int arr[], int num)
{
    if (num < 2)
    {
        return 1;
    }

    uint32_t maxSoFar;
    uint32_t endIdx;
    int DP[num];
    DP[0] = 1;
    
    for (uint32_t i = 1; i < num; i++)
    {
        DP[i] = 1;
        for (int32_t j = i-1; j >=0; j--)
        {
            if ((DP[j] + 1 > DP[i]) && (arr[j] < arr[i]))
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

    return maxSoFar;
}

uint32_t longestIncreasingSubSequenceVec(vector<int>& nums)
{
    if (nums.size() < 2)
    {
        return 1;
    }

    // VERY IMP
    // maxSoFar should be initialized
    uint32_t maxSoFar = 0;
    uint32_t endIdx;
    int DP[nums.size()];
    DP[0] = 1;
    
    for (uint32_t i = 1; i < nums.size(); i++)
    {
        DP[i] = 1;
        for (int32_t j = i-1; j >=0; j--)
        {
            if ((DP[j] + 1 > DP[i]) && (nums[j] < nums[i]))
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

    return maxSoFar;
}

// O(n log(n)) dynamic programming approach
// VERY IMP:
// Should find the FIRST NUMBER that is large or EQUAL.
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
            // middle element is the first element smaller.
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
            // and insert the new element there
            uint32_t index = findFirstLargerElement(longIncSeq, nums[i]);
            longIncSeq[index] = nums[i];
        }
    }

    return maxLisLen;
}

// ------------------------------------------------------------------------------------------------
// Main Function
// ------------------------------------------------------------------------------------------------
int main()
{
    {
        int n = 10;
        cout << "1. " << fibonacci(n) << endl;
        cout << "2. " << fibonacciDynamic(n) << endl;

        cout << "3. " << fibonacciDynamic2(n) << endl;
    }

    // Problem 2. Ladder Problem
    {
        ladderRec(3);
    }

    // Problem 3. Longest Increasing Subsequence
    {
        int arr[] = {10,9,2,5,3,7,101,18};
        vector<int> vec5 = {3,5,6,2,5,4,19,5,6,7,12};

        cout << "LIS 1: " << longestIncreasingSubSequenceVec(vec5) << endl;
        cout << "LIS 2: " << longestIncreasingSubseq(vec5) << endl << endl;
    }

    cout << endl;
    return 0;
}
