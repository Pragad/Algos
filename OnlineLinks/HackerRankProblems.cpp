#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

void printVectorInt(vector<int> nums)
{
    for (int num : nums)
    {
        cout << num << ", ";
    }
    cout << endl;
}


// -----------------------------------------------------------------------------------------
// Problem 1:
// https://www.hackerrank.com/challenges/circular-array-rotation
//
//     Sample Input
//     3 2 3
//     1 2 3
//     0
//     1
//     2
//     
//     Sample Output
//     2
//     3
//     1
// 
// -----------------------------------------------------------------------------------------
void circularArrayRotation(const vector<int>& numsVec, const vector<int> & ipIndices, int k)
{
    int n = numsVec.size();  // Size of the input vector

    // Logic:
    //      if n - k + i < n, then n - k + i
    //      else i - k
    for(int a0 = 0; a0 < ipIndices.size(); a0++)
    {
        if ((n - k + ipIndices[a0]) < n)
        {
            cout << numsVec[n - k + ipIndices[a0]] << endl;
        }
        else
        {
            cout << numsVec[ipIndices[a0] - k] << endl;
        }
    }
} 

// -----------------------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------------------
int main()
{
    // Problem 1.
    {
        cout << endl << "Problem 1" << endl;
        vector<int> numsVec = { 1, 2, 3};
        vector<int> ipIndices = {0, 1, 2};

        int k = 23;
        circularArrayRotation(numsVec, ipIndices, k % numsVec.size());
    }

    return 0;
}

