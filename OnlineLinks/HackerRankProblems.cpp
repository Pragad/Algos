#include <map>
#include <set>
#include <list>
#include <cmath>
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
// Problem 2:
// Giving a string s, count the number of substrings that match the below condition
//
//      1. The substring should have equal number of 0s and 1s
//      2. The substring should have continuous 0s and 1s
//
//      00110 : 01, 10, 0011
//      10001 : 10, 01
//      10101 : 10, 01, 10, 01
// -----------------------------------------------------------------------------------------
bool isValidString(string str)
{
    if (str.length() == 0)
    {
        return false;
    }

    if (str.length() % 2 != 0)
    {
        return false;
    }

    int zeroCnt = 0;
    int oneCnt = 0;
    for (char c : str)
    {
        if (c == '0')
        {
            zeroCnt++;
        }
        else
        {
            oneCnt++;
        }
    }

    if (zeroCnt != oneCnt)
    {
        return false;
    }

    bool startWithZero = false;
    zeroCnt = 0;
    oneCnt = 0;

    if (str[0] == '0')
    {
        startWithZero = true;
    }

    for (int i = 0; i < str.length() / 2; i++)
    {
        if (startWithZero)
        {
            if (str[i] == '1')
            {
                return false;
            }
            else
            {
                zeroCnt++;
            }
        }
        else
        {
            if (str[i] == '0')
            {
                return false;
            }
            else
            {
                oneCnt++;
            }
        }
    }
    
    for (int i = str.length() / 2; i < str.length(); i++)
    {
        if (startWithZero)
        {
            if (str[i] == '0')
            {
                return false;
            }
            else
            {
                oneCnt++;
            }
        }
        else
        {
            if (str[i] == '1')
            {
                return false;
            }
            else
            {
                zeroCnt++;
            }
        }   
    }


    if (zeroCnt != oneCnt)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

int countAllSubSring(string s)
{
    int count = 0;

    for (int i = 0; i < s.length(); i++)
    {
        // VERY IMP "num-i+1"
        // This gives the NUMBER of elements for each i
        // 'j' : Length # of chars
        for (int j = 0; j < s.length() - i + 1; j = j + 2)
        {
            string str = s.substr(i, j);

            if (isValidString(str))
            {
                count++;
            }
        }
    }

    return count;
}
        
int count(string s)
{
    bool lastSeenOne = false;
    bool lastSeenZero = false;
    int zeroCount = 0;
    int oneCount = 0;
    int subStringCount = 0;

    for(char c : s)
    {
        if (c == '0')
        {
            if(lastSeenOne)
            {
                zeroCount = 0;
            }

            lastSeenZero = true;
            lastSeenOne = false;
            zeroCount++;

            if(oneCount - zeroCount >= 0)
            {
                subStringCount++;
            }
        }
        else
        {
            if(lastSeenZero)
            {
                oneCount = 0;
            }

            lastSeenOne = true;
            lastSeenZero = false;
            oneCount++;

            if(zeroCount - oneCount >= 0)
            {
                subStringCount++;
            }
        }
    }

    return subStringCount;
}

// -----------------------------------------------------------------------------------------
// Anitha's attempt
// -----------------------------------------------------------------------------------------
int countAnit(string s)
{
    bool zero_bool = false;
    bool one_bool = false;
    int zero_count = 0;
    int one_count = 0;
    int answer = 0;

    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == '0')
        {
            if(zero_bool == true)
            {
                zero_count++;
                if(one_count - zero_count >= 0)
                {
                    answer++;
                }
            }
            else
            {
                zero_bool = true;
                one_bool = false;
                zero_count = 1;
                if(one_count - zero_count >= 0)
                {
                    answer++;
                }
            }
        }
        else if(s[i] == '1')
        {
            if(one_bool == true)
            {
                one_count++;
                if(zero_count - one_count >= 0)
                {
                    answer++;
                }
            }
            else
            {
                one_bool = true;
                zero_bool = false;
                one_count = 1;
                if(zero_count - one_count >= 0)
                {
                    answer++;
                }
            }
        }
    }

    return answer;
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

    // Problem 1.
    {
        cout << endl << "Problem 2" << endl;
        cout << countAnit("00110") << endl;
        cout << countAnit("10001") << endl;
        cout << countAnit("10101") << endl;
        cout << countAnit("001100011101") << endl << endl;

        cout << count("00110") << endl;
        cout << count("10001") << endl;
        cout << count("10101") << endl;
        cout << count("001100011101") << endl;

        cout << endl;
    }

    return 0;
}

