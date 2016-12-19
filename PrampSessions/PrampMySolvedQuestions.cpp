#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>        // sort, binary_search
#include <bitset>
#include <functional>   // Contains function for std::hash
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
 * PROBLEM 15. Sudoku Solver
 *
 */

template<typename T>
void printVector(vector<T> nums)
{
    for (T i : nums)
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
void dfsCountIslands(vector<vector <uint32_t> >& twoDMat, int32_t curRow, int32_t curCol)
{
    twoDMat[curRow][curCol] = 2;

    for (uint32_t i = 0; i < 8; i++)
    {
        int32_t newRow = curRow + ROWPOS[i];
        int32_t newCol = curCol + COLPOS[i];

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
    queue<pair<int32_t, int32_t> > dfsQueue;
    dfsQueue.push(pair<int32_t, int32_t> {curRow, curCol});

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
            int32_t newRow = tmp.first + ROWPOS[i];
            int32_t newCol = tmp.second + COLPOS[i];

            if (newRow >=0 && newRow < twoDMat.size() &&
                newCol >=0 && newCol < twoDMat[0].size() &&
                twoDMat[newRow][newCol] == 1)
            {
                dfsQueue.push(pair<int32_t, int32_t> {newRow, newCol});
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
//            The array need not be sorted
//            Arr: 1, 2, 5, 7, 15, 20, 25
//            Sum: 30
//            Ans: 1, 2, 7, 20
// ------------------------------------------------------------------------------------------------
vector<int> quadCombination(const vector<int>& nums, int sum)
{
    unordered_map<int, pair<int, int> > sumMap;
    vector<int> result;

    for (uint32_t i = 0; i < nums.size() - 1; i++) // IMP: as j start from i + 1
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
// Implement a meeting planner that can schedule meetings between two persons at a time.
// https://www.pramp.com/question/3QnxW6xoPLTNl5jX5Lg1
// Session11_2016_07_08.cpp
//
// |     |               |  -> B completely lies outside A
// |
// |         |           |  -> B.end goes outside A
// |           |   |        -> B completely lies within A
// |     |         |        -> B.start goes outside A
// |--------------------------------------------------------------
// |        |         |     -> A
//
// Use std::chrono time
// http://stackoverflow.com/questions/25136657/how-do-i-use-tm-structure-to-add-minutes-to-current-time
// ------------------------------------------------------------------------------------------------
pair<uint32_t, uint32_t> meetingScheduler(const vector<pair<uint32_t, uint32_t> >& availA, const vector<pair<uint32_t, uint32_t> >& availB, uint32_t dur)
{
    pair<uint32_t, uint32_t> result;

    uint32_t i = 0;
    uint32_t j = 0;
    while (i < availA.size() && j < availB.size())
    {
        // Check if there is overlap and if we should increment 'i' or 'j'
        if (availA[i].first <= availB[j].first &&
            availB[j].first + dur > availA[i].first &&
            availB[j].first + dur <= availA[i].second &&
            availB[j].first + dur <= availB[j].second)
        {
            result = make_pair(availB[j].first, availB[j].first + dur);
            return result;
        }
        else if (availB[j].first <= availA[i].first &&
                 availA[i].first + dur > availB[j].first &&
                 availA[i].first + dur <= availA[i].second &&
                 availA[i].first + dur <= availB[j].second)
        {
            result = make_pair(availA[i].first, availA[i].first + dur);
            return result;
        }
        else
        {
            // We don't have an answer. We have to increment either i or j
            if (availA[i].second == availB[j].second)
            {
                i++;
                j++;
            }
            else if (availA[i].second < availB[j].second)
            {
                i++;
            }
            else if (availA[i].second > availB[j].second)
            {
                j++;
            }
        }
    }

    return result;
}

 // ------------------------------------------------------------------------------------------------
// PROBLEM 9. Flatten a Dictionary
// https://www.pramp.com/question/AMypWAprdmUlaP2gPVLZ
// Session12_2016_07_09.cpp
// ------------------------------------------------------------------------------------------------

 // ------------------------------------------------------------------------------------------------
// PROBLEM 10. Merging 2 Packages
// https://www.pramp.com/question/L3wQBnQYAEh5K97W9ONK
// Session13_2016_07_10.cpp
// ------------------------------------------------------------------------------------------------
pair<int, int> mergePackages(const vector<uint32_t>& weights, uint32_t sum)
{
    unordered_map<uint32_t, uint32_t> sumMap;
    pair<int, int> result = make_pair(-1, -1);

    for (uint32_t i = 0; i <weights.size(); i++)
    {
        auto itr = sumMap.find(weights[i]);

        if (itr != sumMap.end())
        {
            result = make_pair(itr->second, i);
        }
        else
        {
            sumMap[sum - weights[i]] = i;
        }
    }

    return result;
}

 // ------------------------------------------------------------------------------------------------
// PROBLEM 11. Find The Duplicates
// https://www.pramp.com/question/15oxrQx6LjtQj9JK9XlA
// Session14_2016_07_11.cpp
//
// Complexity: O(n log m). Better than O(n + m) when M >> N
// If m and n are of same size use hash table approach. Don't have to sort
// ------------------------------------------------------------------------------------------------
//vector<int> findDuplicatesOptimized(const vector<int>& arr1, const vector<int>& arr2)
vector<int> findDuplicatesOptimized(const vector<int>& arr1, const vector<int>& arr2)
{
   vector<int> uniqPersons;
   vector<int> tmp;

   // As Arr2 is smaller, find if each element in arr2 is present in arr1
   // If so, add it to the result
   if (arr1.size() > arr2.size())
   {
       for (uint32_t j = 0; j < arr2.size(); j++)
       {
           if (binary_search(arr1.begin(), arr1.end(), arr2[j]))
           {
               uniqPersons.push_back(arr2[j]);
           }
       }
   }
   else
   {
       for (uint32_t j = 0; j < arr1.size(); j++)
       {
           if (binary_search(arr2.begin(), arr2.end(), arr1[j]))
           {
               uniqPersons.push_back(arr1[j]);
           }
       }

   }
   
   return uniqPersons;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 12. Getting a Different Number
//             Find a number not present in the array
// https://www.pramp.com/question/aK6V5GVZ9MSPqvG1vwQp
// http://stackoverflow.com/questions/27449831/create-a-large-bitset
// Session15_2016_07_12.cpp
// ------------------------------------------------------------------------------------------------
uint32_t differentNumber(vector<uint32_t> nums)
{
    bitset<400000000UL>& bitsVec = *(new bitset<400000000UL>());
    uint32_t uniqNum = 0;

    cout << bitsVec[0] << " ";
    cout << bitsVec[1] << endl;

    for (uint32_t num : nums)
    {
        size_t t = std::hash<uint32_t>()(num);
        bitsVec[num] = 1;
    }

    cout << bitsVec.size() << endl;
    for (uint32_t i = 0; i < bitsVec.size(); i++)
    {
        if (bitsVec[i] == 1)
        {
            cout << i << ", ";
        }
        else
        {
            break;
        }
    }
    cout << endl;

    delete &bitsVec;
    return uniqNum;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 12. Find an integer not among four billion given ones
// http://stackoverflow.com/questions/7153659/find-an-integer-not-among-four-billion-given-ones?page=1&tab=votes#tab-top
// Logic:
//      Use 16 bits, i.e. 65536.
//      For any 32bit number, check the first 16bits and count the numbers that have the same
//      1st 16bits.
//
//      For one possible 16bit prefix, we should have 65535 numbers.
//      If any 16bit prefix's COUNT is less than 65535, ---> (A)
//      Then that prefix has a vacant spot.
//
//      Scan the input file again and for all 65535 combination that matches (A)
//
//      Say numbers are:
//      00 00   01 00   10 00   11 00
//         01      01      01      01
//         10      10      10      10
//         11      11      11      11
//
//      Say 1010 is mission. So Count of '10' will be 3. While other high bits will have 4.
//
//      Now we have found 10 as the high bit.
//      Then take the low bits and do a count of it. So 00, 01, 11 will have count 1.
//
//      Go over all the cobinations and find the one that has 0 count.
// ------------------------------------------------------------------------------------------------
uint32_t findUniqueNumber(const vector<uint32_t>& nums)
{
    uint32_t uniqNum = 0;
    uint32_t highBit = 0;
    uint32_t lowBit = 0;
    vector<uint16_t> bitMap (65535, 0);

    cout << bitMap.size() << endl;

    // 1st pass. Compute count of all numbers by looking at higher 16 bits
    for (uint32_t i = 0; i < nums.size(); i++)
    {
        bitMap[nums[i] >> 16]++;
    }

    for (uint32_t i = 0; i < bitMap.size(); i++)
    {
        if (bitMap[i] < 65535)
        {
            highBit = i;
            break; // Very IMP. Break once we have found a gap
        }
    }
    cout << "HighBit: " << highBit << endl;

    // Rest all elements in bitMap back to 0.
    // We can now use the same vector to count the lower 16 bits
    std::fill(bitMap.begin(), bitMap.end(), 0);

    // 2nd pass. For all numbers that have THE specific higher 16 bits, count the lower 16
    // bits and find which is missing
    // Combinaiton of highBit and LowBit is the answer
    for (uint32_t i = 0; i < nums.size(); i++)
    {
        uint32_t t = nums[i] >> 16;

        // Take the lower 16bits of the numbers whose higher 16 bits are same as HIGH BIT
        // Compare with highBit

        if (t == highBit)
        {
            uint16_t x = nums[i] & 0xFFFF;
            bitMap[nums[i] & 0xFFFF]++;
        }
    }

    for (uint32_t i = 0; i < bitMap.size(); i++)
    {
        if (bitMap[i] == 0) // Place where we don't have the low bit set
        {
            lowBit = i;
            break; // Very IMP. Break once we have found a gap
        }
    }
    cout << "LowBit: " << lowBit << endl;

    uniqNum = highBit << 16;
    uniqNum |= lowBit;

    return uniqNum;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 13. Drone Flight Planner
// https://www.pramp.com/question/BrLMj8M2dVUoY95A9x3X
//             [{x:0, y:2, z:10}, {x:3, y:5, z:0}, {x:9, y:20, z:6}, {x:10, y:12, z:15}, {x:10, y:10, z:8}]
// Session16_2016_07_13.cpp
// ------------------------------------------------------------------------------------------------
struct CoOrd
{
    uint32_t x;
    uint32_t y;
    uint32_t z;
};

uint32_t findMinFuelReq(vector<CoOrd> points)
{
    if (points.size() < 2)
    {
        return 0;
    }

    uint32_t maxHeight = points[0].z;

    for (uint32_t i = 1; i < points.size(); i++)
    {
        if (points[i].z > maxHeight)
        {
            maxHeight = points[i].z;
        }
    }

    return maxHeight - points[0].z;
}

 // ------------------------------------------------------------------------------------------------
// PROBLEM 14. Word Count Engine
// https://www.pramp.com/question/W5EJq2Jld3t2ny9jyZXG
// http://stackoverflow.com/questions/9333333/c-split-string-with-space-and-punctuation-chars
// Session17_2016_07_14.cpp
//
// http://www.cplusplus.com/reference/algorithm/transform/
// http://www.cplusplus.com/reference/string/string/substr/
// http://en.cppreference.com/w/cpp/string/byte/ispunct
// http://www.cplusplus.com/reference/string/string/find_first_not_of/
// ------------------------------------------------------------------------------------------------
void printUnorderedMap(const unordered_map<string, uint32_t>& myMap)
{
    for (auto i : myMap)
    {
        cout << i.first << "-" << i.second << endl;
    }
    cout << endl;
}

void printVectorPairs(const vector< pair <string, uint32_t> >& myVec)
{
    for (auto i : myVec)
    {
        cout << i.first << "-" << i.second << endl;
    }
    cout << endl;
}

vector< pair< string, uint32_t > > convertUnorderedMapToVector(const unordered_map<string, uint32_t>& myMap)
{
    vector< pair< string, uint32_t > > result;

    for (auto i : myMap)
    {
        result.push_back({i.first, i.second});
    }

    return result;
}

string getNextWord(const string& str, uint32_t& startIdx)
{
    string result = "";
    uint32_t idx = 0;

    if (startIdx == str.length() - 1)
    {
        return result;
    }

    for (idx = startIdx; idx < str.length();)
    {
        if (str[idx] == ' ' || ispunct(str[idx]))
        {
            if (startIdx != idx)
            {
                result = str.substr(startIdx, idx - startIdx);
                startIdx = idx + 1;
                return result;
            }
            startIdx++;
            idx++;
        }
        else
        {
            idx++;
        }
    }

    if (startIdx < idx)
    {
        result = str.substr(startIdx, idx - startIdx);
        startIdx = idx + 1;
    }

    return result;
}

vector< pair< string, uint32_t > > wordCount(const string& str)
{
    vector< pair< string, uint32_t > > result;
    unordered_map<string, uint32_t> wrdCntMap;

    for (uint32_t idx = 0; idx < str.length();)
    {
        string tmp = getNextWord(str, idx);
        if (!tmp.empty())
        {
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            wrdCntMap[tmp]++;
        }
    }

    result = convertUnorderedMapToVector(wrdCntMap);
    return result;
}

// ----------------------------------------------------------------------------------------
// PROBLEM 15. Sudoku Solver
// https://www.pramp.com/question/O5PGrqGEyKtq9wpgw6XP
//
// Write the function sudokuSolve(board) that checks whether a given sudoku board (i.e. sudoku puzzle) is solvable. 
//
// Assumption: Empty grid = 0
// ----------------------------------------------------------------------------------------

void findPossibleNums(int twoDMat[9][9], int i, int j, vector<int>& possibleNums)
{
    // 1. Go through column and remove numbers already present
    for (int x = 0; x < 9; x++)
    {
        if (twoDMat[x][j] != 0)
        {
            possibleNums.erase(std::remove(possibleNums.begin(), possibleNums.end(), twoDMat[x][j]), possibleNums.end());
        }
    }

    // 2. Go through row and remove numbers already present
    for (int x = 0; x < 9; x++)
    {
        if (twoDMat[i][x] != 0)
        {
            possibleNums.erase(std::remove(possibleNums.begin(), possibleNums.end(), twoDMat[i][x]), possibleNums.end());
        }
    }  

    // 3. Go through sub matrix and remove numbers already present
    int startRow;
    int startCol;
    if (i < 3)
    {
        startRow = 0;
    }
    else if (i < 6)
    {
        startRow = 3;
    }
    else if (i < 9)
    {
        startRow = 6;
    }

    if (j < 3)
    {
        startCol = 0;
    }
    else if (j < 6)
    {
        startCol = 3;
    }
    else if (j < 9)
    {
        startCol = 6;
    }

    for (int x = startRow; x < startRow + 3; x++)
    {
        for (int y = startCol; y < startCol + 3; y++)
        {
            if (twoDMat[x][y] != 0)
            {
                possibleNums.erase(std::remove(possibleNums.begin(), possibleNums.end(), twoDMat[x][y]), possibleNums.end());
            }        
        }
    }

    return;
}

bool isSudokuBoardSolvable(int twoDMat[9][9], int stRow, int stCol)
{
    int i = stRow;
    int j = stCol;
    bool isSolvable = false;

    for ( i = stRow; i < 9; i++)
    {
        for ( j = stCol; j < 9; j++)
        {
            if (twoDMat[i][j] == 0)
            {
                // Empty grid. Find all possible numbers for this grid
                vector<int> possibleNums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                findPossibleNums(twoDMat, i, j, possibleNums);

                // If we can't find a possible number, then we should go back
                // and try the next number
                if (possibleNums.empty())
                {
                    return false;
                }

                for (int possibleNum : possibleNums)
                {

                    twoDMat[i][j] = possibleNum;
                    isSolvable |= isSudokuBoardSolvable(twoDMat, i, j);

                    // If one guys says it is not solvable we should still go on an try the 
                    // next number
                    // Only when all guys say that it is not solvable we should return false
                }
            }
        }
    }

    // OLD: If we are able to get there then some guy has filled the Sudoku Board.
    // OLD: So it is solvable
    // Even if one guy says it can solve it, the board is solvable
    // Only if all guys give up we should return false
    //
    // TODO: We could come here even if the board is wrongly filled or correctly filled
    return isSolvable;
}

// -----------------------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------------------
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

        printVector(result);
        cout << endl << endl;
    }

    // PROBLEM 4. Array of Array Products
    {
        cout << "PROBLEM 4. Array of Array Products" << endl;
        vector<int> nums = {1, 2, 3, 4, 5};
        vector<int> result = arryOfProds(nums);

        printVector(result);
        cout << endl << endl;
    }

    // PROBLEM 5. K-Messed Array Sort
    {
        cout << "PROBLEM 5. K-Messed Array Sort" << endl;
        vector<int> nums = {8, 10, 3, 7, 15, 20, 13};

        kMessedArraySort(nums, 2);
        printVector(nums);

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

        // Method 1 gives compilation error
        //std::sort(mallData.begin(), mallData.end()); // Method 1
        sort(mallData.begin(), mallData.end(), compMallData); // Method 2
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

        // Ans: 1615 - 1715
        // Assumption: Can combine times like the one we have in the example
        // 1615 - 1715 and again free from 1715 - 1800
        vector<pair<uint32_t, uint32_t> > availA1 = {{900, 930}, {1015, 1115}, {1200, 1400},
                                                     {1445, 1500}, {1600, 1800}, {1900, 2000}};
        vector<pair<uint32_t, uint32_t> > availB1 = {{915, 945}, {950, 1030}, {1430, 1530},
                                                     {1615, 1715}, {1715, 1800}};

        /*
        // Ans: 1600 - 1630
        vector<pair<uint32_t uint32_t> > availA2 = {{900, 930}, {1015, 1115}, {1200, 1400}
                                                   {1445, 1500}, {1600, 1800}, {1900, 2000}};
        vector<pair<uint32_t uint32_t> > availB2 = {{915, 945}, {950, 1030}, {1430, 1530}
                                                   {1515, 1715}, {1715, 1800}};
        */

        /*
        // Ans: 1715 - 1745
        vector<pair<uint32_t uint32_t> > availA3 = {{900, 930}, {1015, 1115}, {1200, 1400}
                                                   {1445, 1500}, {1600, 1800}, {1900, 2000}};
        vector<pair<uint32_t uint32_t> > availB3 = {{915, 945}, {950, 1030}, {1430, 1530}
                                                   {1515, 1555}, {1715, 1900}};
        */

        pair<uint32_t, uint32_t> meetTime = meetingScheduler(availA1, availB1, 30);
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
        vector<uint32_t> weights = {20, 30, 40, 50, 60, 65, 75, 85};
        pair<int, int> tmp = mergePackages(weights, 100);
        cout << tmp.first << ", " << tmp.second << endl;
        cout << endl << endl;
    }

    // PROBLEM 11. Find The Duplicates
    {
        cout << "PROBLEM 11. Find The Duplicates" << endl;
        vector<int> arrA = {5, 8, 10, 20, 30, 40, 50, 60};
        vector<int> arrB = {8, 15, 20};

        vector<int> result = findDuplicatesOptimized(arrA, arrB);
        printVector(result);
        cout << endl << endl;
    }

    // PROBLEM 12. Getting a Different Number
    {
        cout << "PROBLEM 12. Getting a Different Number" << endl;
        vector<uint32_t> arrA = {0, 8, 1, 2, 3, 4, 5, 6};
        //cout << "Uniq Num: " << differentNumber(arrA);
        cout << "Uniq Num: " << findUniqueNumber(arrA);

        cout << endl << endl;
    }

    // PROBLEM 13. Drone Flight Planner
    {
        cout << "PROBLEM 13. Drone Flight Planner" << endl;
        vector<CoOrd> points = {{0, 2, 10}, {3, 5, 0}, {9, 20, 6}, {10, 12, 15}, {10, 10, 8}};

        cout << "Min Fuel Req: " << findMinFuelReq(points);
        cout << endl << endl;
    }

    // PROBLEM 14. Word Count Engine
    {
        cout << "PROBLEM 14. Word Count Engine" << endl;
        string str = "  Hello.   World!! Hi.there!how are?you.  You!hI HI, world ??";
        vector< pair <string, uint32_t> > result = wordCount(str);
        printVectorPairs(result);

        cout << endl << endl;
    }

    // PROBLEM 15. Find if a Sudoku puzzle is solvable
    {
        cout << "PROBLEM 14. Word Count Engine" << endl;
        cout << endl << endl;
    }
    return 0;
}
