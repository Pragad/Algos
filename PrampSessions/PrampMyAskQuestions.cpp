#include <iostream>
#include <vector>
using namespace std;

/*
 * PROBLEM 1.   Array Index & Element Equality
 * int          indexEqualsValueSearch(vector<int> nums)
 *
 * PROBLEM 2.   Find Award Budget Cuts Problem
 * uint32_t     findGrantsCap(vector<int> grants, uint32_t budget)
 *
 * PROBLEM 3.   Smallest Substring of All Characters
 * 
 * PROBLEM 4.   Find if an element is present in a rotated sorted array
 * bool         binarySearchRecursion(vector<int> nums, int low, int high, int elmt)
 * bool         binarySearch(vector<int> nums, int elmt)
 * int          findInSortedRotatedArray(vector<int> nums, int elmt)
  */

// ------------------------------------------------------------------------------------------------
// PROBLEM 1. Array Index & Element Equality
//            Idx:  0,  1,  2, 3, 4, 5, 6, 7, 8, 9
//            Arr: -5, -3, -1, 0, 1, 2, 3, 6, 8, 10
//            Ans: 8
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------
int indexEqualsValueSearch(const vector<int>& nums)
{
    uint32_t low = 0;
    uint32_t high = nums.size() - 1;

    while (low <= high)
    {
        uint32_t mid = low + (high - low)/2;

        if (nums[mid] == mid)
        {
            return mid;
        }
        else if (nums[mid] < mid)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}
 
// ------------------------------------------------------------------------------------------------
// PROBLEM 2. Find Award Budget Cuts Problem
//             
// 40,    50,      50,      100,       160,       200,       325,       500,       1075,        1500
// 400,   490,     490,     840,       1200,      1400,      1900,      2425,      3575,        4000
// 40*10, 40+50*9, 90+50*8, 140+100*7, 240+160*6, 400+200*5, 600+325*4, 925+500*3, 1425+1075*2, 2500+1500 
// ------------------------------------------------------------------------------------------------
double findGrantsCap(vector<uint32_t> grants, uint32_t budget)
{
    uint32_t curSum = 0;
    uint32_t tmpSum = 0;
    uint32_t i = 0;

    //Find the first entry where we exceed the budget if we give the amount that is requested
    for (; i < grants.size(); i++)
    {
        tmpSum = curSum + grants[i] * (grants.size() - i);

        if (tmpSum == budget)
        {
            return grants[i];
        }
        else if(tmpSum > budget)
        {
            break;
        }

        curSum += grants[i];
    }

    if (i == grants.size())
    {
        // Returning the max value
        return grants[i-1];
    }
    else
    {
        return (double)(budget - curSum) / (grants.size() - i);
    }
}

double findGrantsCapModified(vector<uint32_t> grants, uint32_t budget)
{
    uint32_t i = 0;
    double cap = budget / grants.size();

    // Find the minimum Cap that can be given and start incrementing the cap if we have a 
    // grant that is less than the cap
    for (; i < grants.size(); i++)
    {
        cout << cap << ", ";
        if (grants[i] <= cap)
        {
            cap += (double)(cap - grants[i]) / (grants.size() - i - 1);
        }
        else
        {
            break;
        }
    }
    cout << endl;

    return cap;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 3. Smallest Substring of All Characters
//            arr: [x,y,z], str: xyyzyzyx
//            Ans: zyx
// ------------------------------------------------------------------------------------------------
int getShortestUniqueSubstring(vector<int> nums)
{

}
 
// ------------------------------------------------------------------------------------------------
// PROBLEM 4. Find if an element is present in a rotated sorted array
//             http://stackoverflow.com/questions/4773807/searching-in-an-sorted-and-rotated-array
//             Complexity: O(log(n)).
// ------------------------------------------------------------------------------------------------
bool binarySearchRecursion(vector<int> nums, int low, int high, int elmt)
{
    if (low > high)
    {
        return false;
    }

    // IMP: should be SIGNED. Imagine a CASE with just ONE element
    int32_t mid = low + (high - low) / 2;

    if (nums[mid] == elmt)
    {
        return true;
    }
    else if (elmt < nums[mid])
    {
        return binarySearchRecursion(nums, low, mid - 1, elmt);
    }
    else
    {
        return binarySearchRecursion(nums, mid + 1, high, elmt);
    }

}

bool binarySearch(vector<int> nums, int elmt)
{
    uint32_t low = 0;
    uint32_t high = nums.size() - 1;

    while (low <= high)
    {
        int32_t mid = low + (high - low) / 2;

        if (nums[mid] == elmt)
        {
            return true;
        }
        else if (elmt < nums[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return false;
}

bool findInSortedRotatedArray(vector<int> nums, int elmt)
{
    uint32_t low = 0;
    uint32_t high = nums.size() - 1;

    while (low <= high)
    {
        uint32_t mid = low + (high - low) / 2;

        // First part is sorted
        if (nums[low] <= nums[mid])
        {
            // Element present in Sorted first half
            if (elmt >= nums[low] && elmt <= nums[mid])
            {
                // Do a binary search for the element here
                return binarySearchRecursion(nums, low, mid, elmt);
            }
            else
            {
                // Element present in 2nd half which is not sorted
                low = mid + 1;
            }
        }
        else
        {
            // Element present in Sorted Second Half
            if (elmt >= nums[mid] && elmt <= nums[high])
            {
                // Do a binary search for the element here
                return binarySearchRecursion(nums, mid, high, elmt);
            }
            else
            {
                // Element present in 1st half which is not sorted
                high = mid - 1;
            }
        }
    }

    return false;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 4b. Find Index where array is rotated
//              http://stackoverflow.com/questions/11855709/how-to-determine-at-which-index-has-a-sorted-array-been-rotated-around
//              Complexity: O(log(n)).
// ------------------------------------------------------------------------------------------------
bool IsArrayRotatedSorted(vector<int> nums)
{
    bool foundDip = false;

    for (uint32_t i = 1; i < nums.size() - 1; i++)
    {
        if (!foundDip && nums[i] < nums[i - 1])
        {
            foundDip = true;
        }
    }

    return foundDip;
}

int IndexOfRotatedSortedArray(vector<int> nums)
{
    if (!IsArrayRotatedSorted(nums))
    {
        return -1;
    }

    uint32_t low = 0;
    uint32_t high = nums.size() - 1;

    uint32_t mid = low + (high - low) / 2;

    while (mid != low && mid != high)
    {
        // Check if 1st half is sorted
        if (nums[low] < nums[mid])
        {
            low = mid;
        }
        else
        {
            high = mid;
        }

        mid = low + (high - low) / 2;
    }

    return high;

    /*
    while (low < high)
    {
        uint32_t mid = low + (high - low) / 2;

        // Check if 1st half is sorted
        if (nums[low] < nums[mid])
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    */
}


int main()
{
    // PROBLEM 1. Array Index & Element Equality
    {
        cout << "PROBLEM 1. Array Index & Element Equality" << endl;
        vector <int> nums = {-5, -3, -1, 0, 1, 2, 3, 6, 8, 10};
        cout << indexEqualsValueSearch(nums);
        cout << endl;
        cout << endl;
    }

    // PROBLEM 2. Find Award Budget Cuts Problem
    {
        cout << "PROBLEM 2. Find Award Budget Cuts Problem" << endl;
        vector<uint32_t> grants = {40, 50, 50, 100, 160, 200, 325, 500, 1075, 1500};
        cout << findGrantsCap(grants, 2000) << endl;
        cout << findGrantsCapModified(grants, 2000) << endl;
        cout << endl;
    }

    // Problem 3. Smallest Substring of All Characters
    {
        cout << "Problem 3. Smallest Substring of All Characters" << endl;

        cout << endl;
    }

    // Problem 4. Find if an element is present in a rotated sorted array
    {
        cout << "Problem 4. Find if an element is present in a rotated sorted array" << endl;
        cout << endl << "Binary Search and Rotated Sorted Array" << endl;
        vector<int> nums = {2, 3, 17, 19, 22, 46, 82};
        cout << binarySearch(nums, 2) << " ";
        cout << binarySearch(nums, 3) << " ";
        cout << binarySearch(nums, 17) << " ";
        cout << binarySearch(nums, 19) << " ";
        cout << binarySearch(nums, 22) << " ";
        cout << binarySearch(nums, 46) << " ";
        cout << binarySearch(nums, 82) << " ";
        cout << binarySearch(nums, 83) << endl;
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 2) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 3) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 17) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 19) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 22) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 46) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 82) << " ";
        cout << binarySearchRecursion(nums, 0, nums.size()-1, 83) << endl;

        vector<int> nums2 = {17, 19, 22, 46, 82, 2, 3};
        cout << findInSortedRotatedArray(nums, 2) << " ";
        cout << findInSortedRotatedArray(nums, 3) << " ";
        cout << findInSortedRotatedArray(nums, 17) << " ";
        cout << findInSortedRotatedArray(nums, 19) << " ";
        cout << findInSortedRotatedArray(nums, 22) << " ";
        cout << findInSortedRotatedArray(nums, 46) << " ";
        cout << findInSortedRotatedArray(nums, 82) << " ";
        cout << findInSortedRotatedArray(nums, 20) << endl;
    }

    // PROBLEM 4b. Find Index where array is rotated
    {
        cout << endl << "Find Index where array is rotated" << endl;
        vector<int> nums = {17, 19, 22, 46, 82, 2, 3};
        cout << IndexOfRotatedSortedArray(nums) << endl;
    }

    return 0;
}
