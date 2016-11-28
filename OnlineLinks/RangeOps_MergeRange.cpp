#include <map>
#include <set>
#include <list>
#include <cmath>
#include <climits>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// -----------------------------------------------------------------------------------------
// Class Range
// Class to store Start Range and End Range in the form of an object
//-----------------------------------------------------------------------------------------
class Range
{
public:
    int _lower;
    int _upper;
    Range(int low, int high) : _lower(low),
                               _upper(high)
    { }

    // Overloading '<' in order to sort the vector of Ranges based on Start Range
    friend bool operator<(const Range& ls, const Range& rs)
    {
        return ls._lower < rs._lower;
    }
};

// -----------------------------------------------------------------------------------------
// Class RangeModule
// -----------------------------------------------------------------------------------------
class RangeModule
{    
private:
    // A vector to maintain the list of ranges sorted by Start Range
    std::vector<Range> _rangeList;

    // Utility function to find start and end Index of the Ranges that will get affected
    int32_t FindStartRangeWithEndMoreThanCurStart(const Range& currentRange);
    int32_t FindEndRangeWithStartMoreThanCurStart(const Range& currentRange);

    // Utility function to merge with the next set of Ranges
    void swallowNextItemsIfPossible(uint32_t curIndex, uint32_t endIndex);

public:
    
    void AddRange(int lower, int upper);

    bool QueryRange(int lower, int upper);

    void RemoveRange(int lower, int upper);

    // Utility function to check what is there in the Vector. Useful for debugging purpose
    void PrintRanges();

};

// -----------------------------------------------------------------------------------------
// This function calculates the start index from which the Ranges will get affected because
// of this range that we are trying to add
// Complexity: O(N); Can be improved to O(log N)
// -----------------------------------------------------------------------------------------
int32_t RangeModule::FindStartRangeWithEndMoreThanCurStart(const Range& currentRange)
{
    // TODO: This can be improved by doing a Binary Search

    // Doing linear scan to find the first element whose end is greater than or equal to
    // current start
    int32_t i = 0;
    for (; i < _rangeList.size(); i++)
    {
        if (_rangeList[i]._upper >= currentRange._lower ||
            _rangeList[i]._upper + 1 == currentRange._lower)
        {
            return i;
        }
    }

    // No element is present, so point to the last element of the vector
    return i - 1;
}

// -----------------------------------------------------------------------------------------
// This function calculates the end index until which the Ranges will get affected because
// of this range that we are trying to add
// Complexity: O(N); Can be improved to O(log N)
// -----------------------------------------------------------------------------------------
int32_t RangeModule::FindEndRangeWithStartMoreThanCurStart(const Range& currentRange)
{
    // TODO: This can be improved by doing a Binary Search

    // Doing linear scan to find the first element whose start is greater than current end
    int32_t i = 0;
    for (; i < _rangeList.size(); i++)
    {
        if (_rangeList[i]._lower > currentRange._upper)
        {
            if (_rangeList[i]._lower - 1 == currentRange._upper)
            {
                return i;
            }

            return i - 1;
        }
    }

    // No element is present, so point to the last element of the vector
    return i - 1;
}

// -----------------------------------------------------------------------------------------
// This function searches the next set of Ranges and deletes them if they fall within the
// current Index
// Complexity: Liner in time based on the number of elements between curIndex and endIndex
// -----------------------------------------------------------------------------------------
void RangeModule::swallowNextItemsIfPossible(uint32_t curIndex, uint32_t endIndex)
{
    for (uint32_t i = curIndex + 1; i <= endIndex; i++)
    {
        if (_rangeList[curIndex]._lower < _rangeList[i]._lower &&
            _rangeList[curIndex]._upper > _rangeList[i]._upper)
        {
            _rangeList.erase(_rangeList.begin() + i);
            i--;
            endIndex--;
        }
    }
}

// -----------------------------------------------------------------------------------------
// Function to Add a Range to the List
// -----------------------------------------------------------------------------------------
void RangeModule::AddRange(int lower, int upper)
{
    Range ob(lower, upper);

    // Find the startIndex and endIndex of the elements that will get affected because of
    // inserting this new element
    int32_t startIndex = FindStartRangeWithEndMoreThanCurStart(ob);
    int32_t endIndex = FindEndRangeWithStartMoreThanCurStart(ob);

    //cout << "SI: " << startIndex << "; EI: " << endIndex << endl;

    // If the list is empty OR if the start index is greater than endIndex, then just push
    // the element to the vector
    //
    // TODO: We can do a binary search to find where the element should be inserted into the
    // vector instead of pushing at the back and then sorting the vector.
    if (_rangeList.empty() || (startIndex > endIndex))
    {
        _rangeList.push_back(ob);
        sort(_rangeList.begin(), _rangeList.end());
    }
    else
    {
        // We have a valid startIndex and endIndex. All items within this will get affected.
        //      1. Swallow: Current Range we are adding will Swallow the Existing Range
        //      2. Expand: Current Range we are adding will Expand the Existing Range
        //          2a. Expand Left
        //          2b. Expand Right
        //          2c. Expand Both
        //      3. No Op: Current Range we are adding will be a no op to the Existing Range

        bool isSwallow = false;
        bool isExpandLeft = false;
        bool isExpandRight = false;

        for (uint32_t i = startIndex; i <= endIndex; i++)
        {
            isSwallow = false;
            // 1. Swallow
            if (ob._lower < _rangeList[i]._lower &&
                ob._upper > _rangeList[i]._upper)
            {
                isSwallow = true;
                _rangeList.erase(_rangeList.begin() + i);
                i--;
                endIndex--;
            }

            // 2. Expand Left
            //          10 - 20
            //  0 - 15, 0 - 10, 0 - 9, 0 - 20
            if (!isSwallow &&
                ob._lower < _rangeList[i]._lower &&
                (ob._upper >= _rangeList[i]._lower ||
                 ob._upper + 1 == _rangeList[i]._lower))
            {
                isExpandLeft = true;
                _rangeList[i]._lower = ob._lower;
            }

            // 2. Expand Right
            if (!isSwallow &&
                ob._upper > _rangeList[i]._upper &&
                (ob._lower <= _rangeList[i]._upper ||
                 ob._lower - 1 == _rangeList[i]._upper))
            {
                isExpandRight = true;
                _rangeList[i]._upper = ob._upper;

                swallowNextItemsIfPossible(i + 1, endIndex);
            }

            // Merge if both expand left and expand right has happened
            if (isExpandLeft && isExpandRight)
            {
                _rangeList[i - 1]._upper = _rangeList[i]._upper;
                _rangeList.erase(_rangeList.begin() + i);
                i--;
                endIndex--;
            }
        }

        if (isSwallow)
        {
            _rangeList.push_back(ob);
            sort(_rangeList.begin(), _rangeList.end());
        }
    }
}

// -----------------------------------------------------------------------------------------
// Function to Query if a range is tracked by our list
// Complexity: O(N); Can be improved to O(log N)
// -----------------------------------------------------------------------------------------
bool RangeModule::QueryRange(int lower, int upper)
{
    // This can be improved by doing a binary search as the list of ranges are sorted based
    // on start time
    for (uint32_t i = 0; i < _rangeList.size(); i++)
    {
        if (_rangeList[i]._lower >= lower &&
            _rangeList[i]._upper <= upper)
        {
            return true;
        }
    }

    return false;
}

// -----------------------------------------------------------------------------------------
// Function to Remove a Range from the List
// -----------------------------------------------------------------------------------------
void RangeModule::RemoveRange(int lower, int upper)
{
    // TODO
    // Similar to AddRange, here we have 3 possibilities
    //      1. shrinkLeft
    //      2. shrinkRight
    //      3. deleteEntry
    //      4. splitRange
    //
    // Logic: Find the list of entries that will get affected
}

// -----------------------------------------------------------------------------------------
// Utility function to print the list
// -----------------------------------------------------------------------------------------
void RangeModule::PrintRanges()
{
    std::cout << "\n\nRanges List\n";
    for (auto item : _rangeList)
    {
        std::cout << item._lower << " : " << item._upper << "\n";
    }
    std::cout << "\n";
}
 
int main()
{
    int a1 = 80;
    int b1 = 120;

    int a2 = 10;
    int b2 = 20;

    int a3 = 30;
    int b3 = 50;

    int a4 = 0;
    int b4 = 100;

    int a5 = 0;
    int b5 = 40;

    int a6 = 15;
    int b6 = 40;

    int a7 = 15;
    int b7 = 100;

    int a8 = 25;
    int b8 = 55;

    int a9 = 15;
    int b9 = 22;

    int a10 = 121;
    int b10 = 125;

    int a11 = 21;
    int b11 = 25;

    int a12 = 27;
    int b12 = 29;

    int a13 = 21;
    int b13 = 29;

    RangeModule ob;
    ob.AddRange(a1, b1);
    ob.AddRange(a2, b2);
    ob.AddRange(a3, b3);
    ob.PrintRanges();

    //ob.AddRange(a4, b4);
    //ob.AddRange(a5, b5);
    //ob.AddRange(a6, b6);
    //ob.AddRange(a7, b7);
    //ob.AddRange(a8, b8);
    //ob.AddRange(a9, b9);
    //ob.AddRange(a10, b10);
    //ob.AddRange(a11, b11);
    //ob.AddRange(a12, b12);
    //ob.AddRange(a13, b13);

    ob.PrintRanges();

    cout << endl;

/*
OUTPUT:
SI: 0; EI: 2
SI: 0; EI: 1
SI: 0; EI: 1
SI: 0; EI: 2
SI: 1; EI: 1
SI: 0; EI: 0
SI: 2; EI: 2
SI: 0; EI: 0
SI: 1; EI: 1
SI: 0; EI: 1
*/

/*
    ofstream fout(getenv("OUTPUT_PATH"));
    RangeModule* rm = new RangeModule();
    
    string line;
    string token;
    vector<string> tokens;
    while (getline(cin, line, '\n')) {
        // skip empty lines or lines that begin with #
        if (line.length() == 0 || line.at(0) == '#') {
            fout << line <<'\n';
            continue;
        }

        istringstream ss(line);
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        string func_name = tokens[0];
        int arg1 = atoi(tokens[1].c_str());
        int arg2 = atoi(tokens[2].c_str());
        tokens.clear();

        int result = _run_test(rm, func_name, arg1, arg2);
        
        if (result == 0)
            fout << func_name.c_str() << "(" << arg1 << "," << arg2 << ")";
        else
            fout << func_name.c_str() << "(" << arg1 << "," << arg2 << ") == " << (result > 0 ? "true" : "false");
        
        if (cin.peek() > 0)
            fout << "\n";
    }

    fout.close();
*/
    return 0;
}
