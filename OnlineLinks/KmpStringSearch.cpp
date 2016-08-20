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
 * PROBLEM 1. Substring match using KMP algorithm
 *            bool isSubstringPresentKMP(string s1, string s2)
 */ 

void printVectorInt(vector<uint32_t> vecInt)
{
    for (auto i : vecInt)
    {
        cout << i << ", ";
    }
    cout << endl;
}


// ------------------------------------------------------------------------------------------------
// PROBLEM 1. Substring match using KMP algorithm
//            hello
//            hexllo
//            Ans: x
// Use KMP algorithm to find if a substring is present
// ------------------------------------------------------------------------------------------------
void constructKmpTable(string str, vector<uint32_t>& kmpTable)
{
    uint32_t i = 0;
    uint32_t j = 0;
    bool elmtAdded = false;

    // Store 0 at 0th index
    kmpTable.push_back(0);

    for (i = 1; i < str.length(); i++)
    {
        if (str[i] == str[j])
        {
            // Get the last element in the table and add 1.
            kmpTable.push_back(kmpTable.back() + 1);
            j++;
        }
        else
        {
            // If j has not moved and if j is at 0, then put 0
            if (j == 0)
            {
                kmpTable.push_back(0);
            }
            else
            {
                elmtAdded = false;
                // j has moved. Take the value at 'j - 1' and go to that index and do a comparison
                while (j > 0)
                {
                    j = kmpTable[j - 1];

                    // If there exists a prefix which is a suffix
                    if (str[i] == str[j])
                    {
                        kmpTable.push_back(kmpTable[j] + 1);
                        elmtAdded = true;
                        j++;
                        break;
                    }
                }

                // If we came all the way to 0th index and nothing matched then push 0
                if (j == 0 && !elmtAdded)
                {
                    kmpTable.push_back(0);
                }


            }
        }
    }
}

bool isSubstringPresentKMP(string origStr, string strPat)
{
    vector<uint32_t> kmpTable;
    bool isSubStrPresent = false;

    constructKmpTable(strPat, kmpTable);
    printVectorInt(kmpTable);

    for (uint32_t i = 0, j = 0; i < origStr.length(); i++)
    {
        if (origStr[i] == strPat[j])
        {
            if (j == (strPat.length() - 1))
            {
                cout << "Pattern Found at :" << i - j << endl;
                j = 0;
                isSubStrPresent = true;
            }
            else
            {
                j++;
            }
        }
        else
        {
            if (j != 0)
            {
                j = kmpTable[j-1];

                // VERY IMP: Do matching again
                i--;
            }
        }
    }

    return isSubStrPresent;
}

// ------------------------------------------------------------------------------------------------
// Main Function
// ------------------------------------------------------------------------------------------------
int main()
{
    // Problem 1: KMP Search
    {
        string str1 = "abcxabcdabxabcdabcdabcy";
        string pat1 = "abcdabcy";

        string str2 = "AABAACAADAABAAABAA";
        string pat2 = "AABA";
        cout << isSubstringPresentKMP(str1, pat1) << endl;
        cout << isSubstringPresentKMP(str2, pat2) << endl;
    }

    cout << endl;
    return 0;
}
