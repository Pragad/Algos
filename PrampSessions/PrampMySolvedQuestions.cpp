#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>        // sort
using namespace std;

/*
 * PROBLEM 1. Island Count Iterative
 *
 * PROBLEM 2. BST Successor Search
 *
 * PROBLEM 3. Quad Combination
 *
 * PROBLEM 4. Array of Array Products
 *
 * PROBLEM 5. K-Messed Array Sort
 *
 * PROBLEM 6. Busiest Time in The Mall
 *
 * PROBLEM 7. Sentence Reverse
 *
 * PROBLEM 8. Time Planner
 *
 * PROBLEM 9. Flatten a Dictionary
 *
 * PROBLEM 10. Merging 2 Packages
 *
 * PROBLEM 11. Find The Duplicates
 *
 * PROBLEM 12. Getting a Different Number
 *
 * PROBLEM 13. Drone Flight Planner
 *
 * PROBLEM 14. Word Count Engine
 *
 */

void printVectorInt(vector<int> nums)
{
    for (int i : nums)
    {
        cout << i << ", ";
    }
    cout << endl;
}
 

// ------------------------------------------------------------------------------------------------
// PROBLEM 1. Island Count Iterative
// https://www.pramp.com/question/yZm60L6d5juM7K38KYZ6
// Session3_2015_06_04.cpp
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------
// Unnamed Namespace replacing static const
namespace
{
    int ROWPOS[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int COLPOS[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
}

// Procedure to do the DFS search Recursively
void dfsCountIslands(vector<vector <uint32_t> >& twoDMat, uint32_t curRow, uint32_t curCol)
{
    twoDMat[curRow][curCol] = 2;

    for (uint32_t i = 0; i < 8; i++)
    {
        uint32_t newRow = curRow + ROWPOS[i];
        uint32_t newCol = curCol + COLPOS[i];

        if (newRow >=0 && newRow < twoDMat.size() &&
            newCol >=0 && newCol < twoDMat[0].size() &&
            twoDMat[newRow][newCol] == 1)
        {
            dfsCountIslands(twoDMat, newRow, newCol);
        }
    }
}

// Procedure to do the DFS search Iteratively
void dfsCountIslandsIterative(vector<vector <uint32_t> >& twoDMat, uint32_t curRow, uint32_t curCol)
{
    // Create a queue
    // Put the current valid element into the queue
    queue<pair<uint32_t, uint32_t> > dfsQueue;
    dfsQueue.push(pair<uint32_t, uint32_t> {curRow, curCol});

    // While the queue is not empty take the top element
    // Scan all its neighbors and add valid elements (1s) to the queue
    // Repeat the process till the queue is not empty
    while (!dfsQueue.empty())
    {
        pair<uint32_t, uint32_t> tmp = dfsQueue.front();
        twoDMat[tmp.first][tmp.second] = 2;
        dfsQueue.pop();

        for (uint32_t i = 0; i < 8; i++)
        {
            uint32_t newRow = tmp.first + ROWPOS[i];
            uint32_t newCol = tmp.second + COLPOS[i];

            if (newRow >=0 && newRow < twoDMat.size() &&
                newCol >=0 && newCol < twoDMat[0].size() &&
                twoDMat[newRow][newCol] == 1)
            {
                dfsQueue.push(pair<uint32_t, uint32_t> {newRow, newCol});
            }
        }

    }
}

uint32_t countIslands(vector<vector <uint32_t> >& twoDMat)
{
    uint32_t numIslands = 0;
    for (uint32_t i = 0; i < twoDMat.size(); i++)
    {
        for (uint32_t j = 0; j < twoDMat[i].size(); j++)
        {
            if (twoDMat[i][j] == 1)
            {
                //dfsCountIslands(twoDMat, i, j);
                dfsCountIslandsIterative(twoDMat, i, j);
                ++numIslands;
            }
        }
    }

    // Convert the input matrix back to original by replace '2' with '1'
    return numIslands;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 2. BST Successor Search
// https://www.pramp.com/question/MW75pP53wAtzNPVLPG2b
// Session5_2016_06_15.cpp
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------

 // ------------------------------------------------------------------------------------------------
// PROBLEM 3. Quad Combination
// https://www.pramp.com/question/gKQ5zA52mySBOA5GALj9
// Session6_2016_06_17.cpp
//            Let's assume the array is sorted
//            Arr: 1, 2, 5, 7, 15, 20, 25
//            Sum: 30
//            Ans: 1, 2, 7, 20
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------
vector<int> quadCombination(const vector<int>& nums, int sum)
{
    unordered_map<int, pair<int, int> > sumMap;
    vector<int> result;

    for (uint32_t i = 0; i < nums.size(); i++)
    {
        for (uint32_t j = i+1; j < nums.size(); j++)
        {
            auto itr = sumMap.find(nums[i] + nums[j]);
            if (itr != sumMap.end())
            {
                // We found a Quad pair that will give the sum
                uint32_t idx1 = itr->second.first;
                uint32_t idx2 = itr->second.second;

                // Very IMP check if all indices are different.
                // We are forming pairs.
                // So we could have one pair with index 1 and 2
                // And another pair with index 2 and 5 which could give the same sum.
                if (idx1 != i && idx1 != j &&
                    idx2 != i && idx2 != j)
                {
                    result.push_back(nums[idx1]); // First value in the stored pair
                    result.push_back(nums[idx2]); // Second value in the stored pair
                    result.push_back(nums[i]); // The first number that we have right now
                    result.push_back(nums[j]); // The second number that we have right now

                    return result;
                }
            }
            else
            {
                sumMap[sum - (nums[i] + nums[j])] = pair<int, int> {i, j};
            }
        }
    }

    // Return an empty vector
    return result;
}

 // ------------------------------------------------------------------------------------------------
// PROBLEM 4. Array of Array Products Without Divison
// https://www.pramp.com/question/7Lg1WA1nZqfoWgPbgM0M
// Session8_2016_06_19.cpp
// ------------------------------------------------------------------------------------------------
vector<int> arryOfProds(const vector<int>& nums)
{
    // Fill in the vector with 1s
    vector<int> result(nums.size(), 1);

    uint32_t curProd = 1;
    
    for (uint32_t i = 0; i < nums.size(); i++)
    {
        curProd *= nums[i];
        result[i] = curProd;
    }

    curProd = 1;
    for (int i = nums.size()-1; i >0; i--)
    {
        result[i] = curProd * result[i-1];
        curProd *= nums[i];
    }
    result[0] = curProd;
    
    return result;
}

 // ------------------------------------------------------------------------------------------------
// PROBLEM 5. K-Messed Array Sort
// https://www.pramp.com/question/XdMZJgZoAnFXqwjJwnBZ
// Session9_2016_06_20.cpp
// ------------------------------------------------------------------------------------------------
void kMessedArraySort(vector<int>& nums, uint32_t k)
{
    priority_queue<int, vector<int>, std::greater<int> > kHeapNums;
    uint32_t i = 0;
    uint32_t j = 0;

    for(; i <= k && i < nums.size(); i++)
    {
        kHeapNums.push(nums[i]);
    }

    for (; i < nums.size(); i++, j++)
    {
        nums[j] = kHeapNums.top();
        kHeapNums.pop();
        kHeapNums.push(nums[i]);
    }

    for (; j < nums.size(); j++)
    {
        nums[j] = kHeapNums.top();
        kHeapNums.pop();
    }
}

 // ------------------------------------------------------------------------------------------------
// PROBLEM 6. Busiest Time in The Mall
// https://www.pramp.com/question/2WBx3Axln1t7JQ2jQq96
// ------------------------------------------------------------------------------------------------
struct MallData
{
    uint32_t timeStamp;
    uint32_t numPeople;
    string type; // Enter or Exit

    // Method 1
    bool operator<(MallData ob)
    {
        return timeStamp < ob.timeStamp;
    }
};

// Method 2
bool compMallData(MallData a, MallData b)
{
    return a.timeStamp < b.timeStamp;
}

// Method 3
struct MyComp
{
    bool operator() (MallData a, MallData b)
    {
        return a.timeStamp < b.timeStamp;
    }
}obMyComp;

void printMallData(vector<MallData> mallData)
{
    for (auto ob : mallData)
    {
        cout << "Time: " << ob.timeStamp << "; NumPeople: " << ob.numPeople << "; Type: " \
             << ob.type << endl;
    }
    cout << endl;
}

pair<uint32_t, uint32_t> findBusiestPeriod(const vector<MallData>& mallData)
{
    uint32_t curCount = 0;
    uint32_t maxCount = 0;
    uint32_t stTime = 0;
    uint32_t enTime = 0;

    for (uint32_t i = 0; i < mallData.size(); i++)
    {
        if (mallData[i].type == "enter")
        {
            curCount += mallData[i].numPeople;
        }
        else if (mallData[i].type == "exit")
        {
            curCount -= mallData[i].numPeople;
        }

        cout << curCount << ", ";
        if (curCount > maxCount)
        {
            maxCount = curCount;
            stTime = mallData[i].timeStamp;

            if (i < mallData.size() - 1) // If we have one more entry left then we can have end time
            {
                enTime = mallData[i+1].timeStamp;
            }
            else
            {
                enTime = 0;
            }
        }
    }
    cout << endl;

    return pair<uint32_t, uint32_t> {stTime, enTime};
}

 // ------------------------------------------------------------------------------------------------
// PROBLEM 7. Sentence Reverse
// https://www.pramp.com/question/VKdqbrq6B1S5XAyGAOn4
// Session10_2016_06_29.cpp
// ------------------------------------------------------------------------------------------------
void reverseWord(string& str, uint32_t stIdx, uint32_t enIdx)
{
    for (uint32_t i = stIdx, j = enIdx; i < j; i++, j--)
    {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

void reverseWordsInSentence(string& str)
{
    reverseWord(str, 0, str.length()-1);

    uint32_t stIdx = 0;
    uint32_t i = 0;

    for (; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            if (stIdx != i)
            {
                reverseWord(str, stIdx, i - 1);
                stIdx = i + 1;
            }
            else
            {
                ++stIdx; //stIdx and i point to the same ' '. Move stIdx by 1;
            }
        }
    }

    if (stIdx < i)
    {
        reverseWord(str, stIdx, i - 1);
    }
}

 // ------------------------------------------------------------------------------------------------
// PROBLEM 8. Time Planner
// https://www.pramp.com/question/3QnxW6xoPLTNl5jX5Lg1
// Session11_2016_07_08.cpp
// ------------------------------------------------------------------------------------------------
meetingScheduler()
{
}

 // ------------------------------------------------------------------------------------------------
// PROBLEM 9. Flatten a Dictionary
// https://www.pramp.com/question/AMypWAprdmUlaP2gPVLZ
// Session12_2016_07_09.cpp
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------

 // ------------------------------------------------------------------------------------------------
// PROBLEM 10. Merging 2 Packages
// https://www.pramp.com/question/L3wQBnQYAEh5K97W9ONK
// Session13_2016_07_10.cpp
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------

 // ------------------------------------------------------------------------------------------------
// PROBLEM 11. Find The Duplicates
// https://www.pramp.com/question/15oxrQx6LjtQj9JK9XlA
// Session14_2016_07_11.cpp
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------

 // ------------------------------------------------------------------------------------------------
// PROBLEM 12. Getting a Different Number
// https://www.pramp.com/question/aK6V5GVZ9MSPqvG1vwQp
// Session15_2016_07_12.cpp
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------

 // ------------------------------------------------------------------------------------------------
// PROBLEM 13. Drone Flight Planner
// https://www.pramp.com/question/BrLMj8M2dVUoY95A9x3X
// Session16_2016_07_13.cpp
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------

 // ------------------------------------------------------------------------------------------------
// PROBLEM 14. Word Count Engine
// https://www.pramp.com/question/W5EJq2Jld3t2ny9jyZXG
// http://stackoverflow.com/questions/9333333/c-split-string-with-space-and-punctuation-chars
// Session17_2016_07_14.cpp
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------

 // ------------------------------------------------------------------------------------------------
// PROBLEM 15. 
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------

int main()
{
    // PROBLEM 1. Island Count Iterative
    {
        cout << "PROBLEM 1. Island Count Iterative" << endl;

        vector< vector <uint32_t> > twoDMat = {{1, 1, 0, 0, 0},
                                               {0, 1, 0, 0, 1},
                                               {1, 0, 0, 1, 1},
                                               {0, 0, 0, 0, 0},
                                               {1, 0, 1, 0, 1}};
        cout << countIslands(twoDMat) << endl << endl;
    }

    // PROBLEM 2. BST Successor Search
    {
        // Refer tree_stanford file
    }

    // PROBLEM 3. Quad Combination
    {
        cout << "PROBLEM 3. Quad Combination" << endl;
        vector<int> nums = {1, 2, 5, 7, 15, 20, 25};
        vector<int> result = quadCombination(nums, 30);

        printVectorInt(result);
        cout << endl << endl;
    }

    // PROBLEM 4. Array of Array Products
    {
        cout << "PROBLEM 4. Array of Array Products" << endl;
        vector<int> nums = {1, 2, 3, 4, 5};
        vector<int> result = arryOfProds(nums);

        printVectorInt(result);
        cout << endl << endl;
    }

    // PROBLEM 5. K-Messed Array Sort
    {
        cout << "PROBLEM 5. K-Messed Array Sort" << endl;
        vector<int> nums = {8, 10, 3, 7, 15, 20, 13};

        kMessedArraySort(nums, 2);
        printVectorInt(nums);

        cout << endl << endl;
    }

    // PROBLEM 6. Busiest Time in The Mall
    {
        cout << "PROBLEM 6. Busiest Time in The Mall" << endl;
        // Sorted Order 4, 2, 7, 6, 8, 5, 1, 9, 3, 10
        vector<MallData> mallData = {{20160717, 10, "exit"},
                                     {20120115, 4, "enter"},
                                     {20140620, 5, "exit"},
                                     {20140225, 8, "exit"},
                                     {20130425, 6, "enter"},
                                     {20120318, 2, "exit"},
                                     {20150819, 1, "exit"},
                                     {20160225, 3, "enter"},
                                     {20160105, 9, "enter"},
                                     {20120919, 7, "enter"} };

        sort(mallData.begin(), mallData.end()); // Method 1
        //sort(mallData.begin(), mallData.end(), compMallData); // Method 2
        //sort(mallData.begin(), mallData.end(), obMyComp); // Method 3
        printMallData(mallData);
        pair<uint32_t, uint32_t> busyTime = findBusiestPeriod(mallData);
        cout << "Busy Time: " << busyTime.first << " - " << busyTime.second << endl;

        cout << endl << endl;
    }

    // PROBLEM 7. Sentence Reverse
    {
        cout << "PROBLEM 7. Sentence Reverse" << endl;
        string str = " My name is hello    one  ";
        cout << "Ori: " << str << endl;

        reverseWordsInSentence(str);
        cout << "Rev: " << str << endl;
        cout << endl << endl;
    }

    // PROBLEM 8. Time Planner
    {
        cout << "PROBLEM 8. Time Planner" << endl;
        vector<pair<uint32_t uint32_t> > availA = {{900, 930},
                                                   {, }};
        vector<pair<uint32_t uint32_t> > availB = {{900, 930},
                                                   {, }};
        pair<uint32_t, uint32_t> meetTime = meetingScheduler(30, timesA, timesB);
        cout << "Meeting: " << meetTime.first << " - " << meetTime.second << endl;

        cout << endl << endl;
    }

    // PROBLEM 9. Flatten a Dictionary
    {
        cout << "PROBLEM 9. Flatten a Dictionary" << endl;


        cout << endl << endl;
    }

    // PROBLEM 10. Merging 2 Packages
    {
        cout << "PROBLEM 10. Merging 2 Packages" << endl;


        cout << endl << endl;
    }

    // PROBLEM 11. Find The Duplicates
    {
        cout << "PROBLEM 11. Find The Duplicates" << endl;


        cout << endl << endl;
    }

    // PROBLEM 12. Getting a Different Number
    {
        cout << "PROBLEM 12. Getting a Different Number" << endl;


        cout << endl << endl;
    }

    // PROBLEM 13. Drone Flight Planner
    {
        cout << "PROBLEM 13. Drone Flight Planner" << endl;


        cout << endl << endl;
    }

    // PROBLEM 14. Word Count Engine
    {
        cout << "PROBLEM 14. Word Count Engine" << endl;


        cout << endl << endl;
    }

    // PROBLEM 15. 
    {

    }

    // PROBLEM 16. 
    {

    }

    return 0;
}

