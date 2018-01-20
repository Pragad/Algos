#include <iostream>
#include <bitset>
#include <string>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>        // std::fill_n, std::reverse, std::swap
#include <queue>            // Priority Queue
#include <typeinfo>         // typeid
#include <vector>
#include <cmath>            // ciel
#include <cstring>          // memset
#include <functional>       // std::function
#include <sstream>
#include <cassert>
#define __STDC_LIMIT_MACROS
#include <cstdint>
using namespace std;

// Used to print out additionals log messages
// #define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

/*
 * PROBLEM 1. Convert Int to Roman Numbers
 * string intToRomanNumerals(uint32_t num)
 *
 * PROBLEM 2. Convert Roman Numbers to Int
 * uint32_t romanNumeralsToInt(string str)
 *
 * PROBLEM 3. Isomorphic Strings
 * bool isIsomorphic(string s, string t)
 *
 * PROBLEM 4. Evaluate Reverse Polish Notation
 * int evalRPN(vector<string>& tokens)
 *
 * PROBLEM 5. myAtoi function String to Integer
 * int myAtoi(string str)
 *
 * PROBLEM 6. Reverse words in a sentence
 * void reverseWords(string &s)
 * 
 * PROBLEM 7.   Find Minimum range that covers all the lists
 * pair<uint32_t, uint32_t> findMinRangeForAllLists(vector<vector<int>> lists)
 *
 * PROBLEM 8. Reverse a Integer Number
 * int reverse(int x)
 *
 * PROBLEM 9. Reverse Bits in a Number
 * uint32_t reverseBits(uint32_t n)
 *
 * PROBLEM 10. Sorted Array. Find first element smaller than given number
 * int findFirstSmallerElementIndex(vector<int> nums, int myNum)
 *
 * PROBLEM 11. Sorted Array. Find first element smaller than given number
 * int findFirstGreaterElementIndex(vector<int> nums, int myNum)
 *
 * PROBLEM 12: Square root of a number
 * double squareRoot(double number)
 *
 * PROBLEM 13: Power of a number
 * double myPow(double x, int n)
 *
 * PROBLEM 14. Replace 0s with 5 in a given number
 * int replaceZerosWithFives(int num)
 */

// Utility function to print a vector of ints
template<typename T>
void printVector(vector<T> nums)
{
    for (auto num : nums)
    {
        cout << num << ", ";
    }
    cout << endl;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 1.   Convert Int to Roman Numbers
// http://stackoverflow.com/questions/4986521/how-to-convert-integer-value-to-roman-numeral-string
//              Eg: 3549
//                  MMMDXLIX
// -----------------------------------------------------------------------------------------

string intToRomanNumerals(uint32_t num)
{
    string res;
    vector<string> ones = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    vector<string> tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    vector<string> hundreds = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};

    if (num > 3999)
    {
        return "";
    }

    // At max we will be adding 3 'M's
    while (num >= 1000)
    {
        res += 'M';
        num -= 1000;
    }

    int quo = num / 100;
    res += hundreds[quo];

    num = num % 100;
    quo = num / 10;
    res += tens[quo];

    num = num % 10;
    res+= ones[num];

    return res;
}

string intToRomanNumeralsRec(uint32_t num)
{
    // Can add a special case for error
    if (num > 3999 || num <= 0)
    {
        return "";
    }
    
    if (num >= 1000)
    {
        return "M" + intToRomanNumeralsRec(num - 1000);
    }
    if (num >= 900)
    {
        return "CM" + intToRomanNumeralsRec(num - 900);
    }
    if (num >= 500)
    {
        return "D" + intToRomanNumeralsRec(num - 500);
    }
    if (num >= 400)
    {
        return "CD" + intToRomanNumeralsRec(num - 400);
    }
    if (num >= 100)
    {
        return "C" + intToRomanNumeralsRec(num - 100);
    }
    if (num >= 90)
    {
        return "XC" + intToRomanNumeralsRec(num - 90);
    }
    if (num >= 50)
    {
        return "L" + intToRomanNumeralsRec(num - 50);
    }
    if (num >= 40)
    {
        return "XL" + intToRomanNumeralsRec(num - 40);
    }
    if (num >= 10)
    {
        return "X" + intToRomanNumeralsRec(num - 10);
    }
    if (num >= 9)
    {
        return "IX" + intToRomanNumeralsRec(num - 9);
    }
    if (num >= 5)
    {
        return "V" + intToRomanNumeralsRec(num - 5);
    }
    if (num >= 4)
    {
        return "IV" + intToRomanNumeralsRec(num - 4);
    }
    if (num >= 1)
    {
        return "I" + intToRomanNumeralsRec(num - 1);
    }
}

// -----------------------------------------------------------------------------------------
// PROBLEM 2.   Convert Roman Numbers to Int
//
//              Eg: MMMDXLIX
//                  3549
//
//              IV, IX, XL, XC, CD, CM
// -----------------------------------------------------------------------------------------
uint32_t romanNumeralsToInt(string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    uint32_t result = 0;
    bool oneFlag = false;
    bool tenFlag = false;
    bool hundFlag = false;

    for (char c : str)
    {

        switch (c)
        {

            case 'M':
                result += 1000;

                if (hundFlag)
                {
                    result -= 200;
                    hundFlag = false;
                }
                break;

            case 'D':
                result += 500;

                if (hundFlag)
                {
                    result -= 200;
                    hundFlag = false;
                }
                break;

            case 'C':
                result += 100;

                if (tenFlag)
                {
                    result -= 20;
                    tenFlag = false;
                }
                hundFlag = true;
                break;

            case 'L':
                result += 50;

                if (tenFlag)
                {
                    result -= 20;
                    tenFlag = false;
                }
                break;

            case 'X':
                result += 10;

                if (oneFlag)
                {
                    result -= 2;
                    oneFlag = false;
                }
                tenFlag = true;
                break;

            case 'V':
                result += 5;

                if (oneFlag)
                {
                    result -= 2;
                    oneFlag = false;
                }
                break;

            case 'I':
                result += 1;
                oneFlag = true;
                break;
        }
    }

    return result;
}

uint32_t romanNumeralsToIntRec(string str)
{
    if (str.empty())
    {
        return 0;
    }

    if (str.compare(0, 1, "M") == 0)
    {
        return 1000 + romanNumeralsToIntRec(str.erase(0, 1));
    }
    if (str.compare(0, 2, "CM") == 0)
    {
        return 900 + romanNumeralsToIntRec(str.erase(0, 2));
    }
    if (str.compare(0, 1, "D") == 0)
    {
        return 500 + romanNumeralsToIntRec(str.erase(0, 1));
    }
    if (str.compare(0, 2, "CD") == 0)
    {
        return 400 + romanNumeralsToIntRec(str.erase(0, 2));
    }
    if (str.compare(0, 1, "C") == 0)
    {
        return 100 + romanNumeralsToIntRec(str.erase(0, 1));
    }
    if (str.compare(0, 2, "XC") == 0)
    {
        return 90 + romanNumeralsToIntRec(str.erase(0, 2));
    }
    if (str.compare(0, 1, "L") == 0)
    {
        return 50 + romanNumeralsToIntRec(str.erase(0, 1));
    }
    if (str.compare(0, 2, "XL") == 0)
    {
        return 40 + romanNumeralsToIntRec(str.erase(0, 2));
    }
    if (str.compare(0, 1, "X") == 0)
    {
        return 10 + romanNumeralsToIntRec(str.erase(0, 1));
    }
    if (str.compare(0, 2, "IX") == 0)
    {
        return 9 + romanNumeralsToIntRec(str.erase(0, 2));
    }
    if (str.compare(0, 1, "V") == 0)
    {
        return 5 + romanNumeralsToIntRec(str.erase(0, 1));
    }
    if (str.compare(0, 2, "IV") == 0)
    {
        return 4 + romanNumeralsToIntRec(str.erase(0, 2));
    }
    if (str.compare(0, 1, "I") == 0)
    {
        return 1 + romanNumeralsToIntRec(str.erase(0, 1));
    }
}

// -----------------------------------------------------------------------------------------
// PROBLEM 3.   Isomorphic Strings
// -----------------------------------------------------------------------------------------
bool isIsomorphic(string s, string t)
{
    unordered_map<char, char> isoMapSrc;
    unordered_map<char, char> isoMapTar;
    if (s.length() != t.length())
    {
        return false;
    }

    for (uint32_t i = 0; i < s.length(); i++)
    {
        auto itr1 = isoMapSrc.find(s[i]);
        auto itr2 = isoMapTar.find(t[i]);

        if ((itr1 == isoMapSrc.end() && itr2 != isoMapTar.end()) ||
            (itr1 != isoMapSrc.end() && itr2 == isoMapTar.end()))
        {
            return false;
        }

        else if (itr1 == isoMapSrc.end() && itr2 == isoMapTar.end())
        {
            isoMapSrc[s[i]] = t[i];
            isoMapTar[t[i]] = s[i];
        }
        else if (itr1 != isoMapSrc.end() && itr2 != isoMapTar.end())
        {
            if ((isoMapSrc[s[i]] != t[i]) || (isoMapTar[t[i]] != s[i]))
            {
                return false;
            }
        }
    }

    return true;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 4. Evaluate Reverse Polish Notation
// -----------------------------------------------------------------------------------------
int evalRPN(const vector<string>& tokens)
{
    int result = 0;
    stack<int> tokStack;

    for (string curToken : tokens)
    {
        if (curToken == "*" ||
            curToken == "+" ||
            curToken == "-" ||
            curToken == "/")
        {
            int a;
            int b;

            if (!tokStack.empty())
            {
                b = tokStack.top();
                tokStack.pop();

                // Get the next element
                if (!tokStack.empty())
                {
                    int tmpRes;
                    a = tokStack.top();
                    tokStack.pop();

                    // Now we got 'a' and 'b' and a binary operator
                    // Evaluate and push the result to the stack
                    if (curToken == "*")
                    {
                        tokStack.push(a * b);
                    }
                    else if (curToken == "+")
                    {
                        tokStack.push(a + b);
                    }
                    else if (curToken == "-")
                    {
                        tokStack.push(a - b);
                    }
                    else if (curToken == "/")
                    {
                        tokStack.push(a / b);
                    }
                }
                else
                {
                    cout << "Error" << endl;
                    return -1;
                }
            }
            else
            {
                cout << "Error" << endl;
                return -1;
            }
        }
        else
        {
            tokStack.push(stoi(curToken));
        }
    }

    result = tokStack.top();
    return result;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 5. myAtoi function
// -----------------------------------------------------------------------------------------
int myAtoi(string str) 
{
    int numSign = 1;
    int stIdx = 0;
    int num = 0;
    
    if (str.length() > log10(std::numeric_limits<int>::max()) + 1)
    {
        cout << "Max Int" << endl;
        return num;
    }

    if (str[0] == '-')
    {
        numSign = -1;
        stIdx = 1;
    }
    else if (str[0] == '+')
    {
        numSign = 1;
        stIdx = 1;
    }

    for (int i = stIdx; i < str.length(); i++)
    {
        if ((str[i] - '0' >=0) && (str[i] - '0' <= 9))
        {
            num = (num * 10) + (str[i]) - '0';
        }
        else if (str[i] == ' ')
        {
            continue;
        }
        else
        {
            return 0;
        }
    }

    return numSign * num;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 6.   Reverse words in a string
// IMP:    
//          1. reverseString should use TWO variable, i and j
//          2. Make sure "int i" is done before for loop
//          3. check for the last word i.e. stIdx < i
//          4. Check if the input string is not empty
// -----------------------------------------------------------------------------------------
void reverseString(string& s, uint32_t stIdx, uint32_t endIdx)
{
    for (uint32_t i = stIdx, j = endIdx; i < j; i++, j--)
    {
        s[i] ^= s[j];
        s[j] ^= s[i];
        s[i] ^= s[j];
    }
}

void reverseWords(string &s)
{
    if (s.empty())
    {
        return;
    }

    uint32_t stIdx = 0;
    uint32_t i = 0;
    reverseString(s, 0, s.length() - 1);

    for (i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            if (stIdx != i)
            {
                reverseString(s, stIdx, i - 1);
            }
            stIdx = i+1;
        }
    }

    if (stIdx < i)
    {
        reverseString(s, stIdx, i - 1);
    }
}

// -----------------------------------------------------------------------------------------
// PROBLEM 7.   Find Minimum range that covers all the lists
// Logic:   
//      Take first number from all the lists and put them in a min-heap
//      Store the maxNum and the minNum to find the range
//
// -----------------------------------------------------------------------------------------
struct heapStuff
{
    int num;
    uint32_t row;
    uint32_t col;

    /*
    friend bool operator<(const heapStuff& ls, const heapStuff& rs)
    {
        return ls.num > rs.num;
    }
    */

    friend bool operator>(const heapStuff& ls, const heapStuff& rs)
    {
        return ls.num > rs.num;
    }

    friend bool operator<(const heapStuff& ls, const heapStuff& rs)
    {
        return ls.num < rs.num;
    }
};

pair<int, int> findMinRangeForAllLists(vector<vector<int>> lists)
{
    int maxNum = numeric_limits<int>::min();

    // Store the difference between max and min numbers. 
    // This is needed to check when we get the next set of numbers
    int minRangeDiff = numeric_limits<int>::max();

    // A pair of ints to store the range
    pair<int, int> minRange = {0, numeric_limits<int>::max()};

    // A min-heap that holds the num, row and col position
    priority_queue<heapStuff, vector<heapStuff>, greater<heapStuff>> numsHeap;

    // First push the first element from each of the lists into the heap
    for (uint32_t i = 0; i < lists.size(); i++)
    {
        // One of the list is empty. So we can break
        if (lists[i].empty())
        {
            return minRange;
        }

        if (lists[i][0] > maxNum)
        {
            maxNum = lists[i][0];
        }
        numsHeap.push({lists[i][0], i, 0});
    }

    while(true)
    {
        heapStuff topNum = numsHeap.top();
        numsHeap.pop();

        // Make the minimum Range from the top element of the heap and the max number so far
        if ((minRange.second - minRange.first) > (maxNum - topNum.num))
        {
            minRange = make_pair(topNum.num, maxNum);
        }

        if (topNum.col + 1 >= lists[topNum.row].size())
        {
            // Once we have reached end in any of the list, we can break out
            break;
        }
        else
        {
            if (lists[topNum.row][topNum.col + 1] > maxNum)
            {
                maxNum = lists[topNum.row][topNum.col + 1];
            }
            numsHeap.push({lists[topNum.row][topNum.col + 1], topNum.row, topNum.col + 1});
        }
    }

    return minRange;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 8. Reverse a Integer Number
// -----------------------------------------------------------------------------------------
int reverse(int x) 
{
    int revNum = 0;
    int newX = x;
    int negNumMultiplier = 1;
    if (x < 0)
    {
        negNumMultiplier = -1;
        newX = x * (-1);
    }
    
    if (newX == 0 || (log10(newX) + 1 == 1))
    {
        return x;
    }
    
    while(newX != 0)
    {
        int rem = newX % 10;
        newX = newX / 10;

        // VERY IMP: Check for multiplication and addition overflow
        if ((revNum > (numeric_limits<int>::max() / 10)) ||
            ((revNum * 10) > (numeric_limits<int>::max() - rem)))
        {
            return 0;
        }

        revNum = (revNum * 10) + rem;
    }
    
    return revNum * negNumMultiplier;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 9. Reverse Bits in a Number
//      43261596 (represented in binary as 00000010100101000001111010011100),
//      Return 964176192 (represented in binary as 00111001011110000010100101000000)
// -----------------------------------------------------------------------------------------
uint32_t reverseBits(uint32_t num)
{
    uint32_t revNum = 0;
    uint32_t numBits = (int)log2(num) + 1;
    for (; num; num >>= 1)
    {
        revNum = (revNum << 1) | (num & 1);
    }

    revNum = revNum << ((sizeof(num) * 8) - numBits);
    return revNum;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 10. Sorted Array. Find first element smaller than given number
// -----------------------------------------------------------------------------------------
int findFirstSmallerElementIndex(vector<int> nums, int myNum)
{
    if (nums.empty())
    {
        return -1;
    }

    if (myNum > nums[nums.size() - 1])
    {
        return nums.size() - 1;
    }

    int32_t stIdx = 0;
    int32_t endIdx = nums.size() - 1;

    while (stIdx <= endIdx)
    {
        int32_t midIdx = stIdx + (endIdx - stIdx) / 2;

        if (nums[midIdx] < myNum)
        {
            if (midIdx + 1 < nums.size() - 1 && nums[midIdx + 1] >= myNum)
            {
                return midIdx;
            }
            else
            {
                stIdx = midIdx + 1;
            }
        }
        else
        {
            if (midIdx - 1 >= 0 && nums[midIdx - 1] < myNum)
            {
                return midIdx - 1;
            }
            else
            {
                endIdx = midIdx - 1;
            }
        }
    }

    return -1;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 11. Sorted Array. Find first element smaller than given number
// -----------------------------------------------------------------------------------------
int findFirstGreaterElementIndex(vector<int> nums, int myNum)
{
    if (nums.empty())
    {
        return -1;
    }

    if (myNum < nums[0])
    {
        return 0;
    }

    int32_t stIdx = 0;
    int32_t endIdx = nums.size() - 1;

    while (stIdx <= endIdx)
    {
        int32_t midIdx = stIdx + (endIdx - stIdx) / 2;

        if (nums[midIdx] <= myNum)
        {
            if (midIdx + 1 < nums.size() - 1 && nums[midIdx + 1] > myNum)
            {
                return midIdx + 1;
            }
            else
            {
                stIdx = midIdx + 1;
            }
        }
        // So num[midIdx] is GREATER than myNum
        // If the previous number is a smaller or equal number, we go the answer
        else
        {
            if (midIdx - 1 >= 0 && nums[midIdx - 1] <= myNum)
            {
                return midIdx;
            }
            else
            {
                endIdx = midIdx - 1;
            }
        }
    }

    return -1;
}

// ------------------------------------------------------------------------------------------
// PROBLEM 12: Square root of a number
//
// Algorithm 1: My algorithm to return Square root to nearest whole number.
//      For a given number, go from 1 to n/2 and find the number for which n * n = Given number.
//      Return the answer.
//
// Complexity:
//      With real math, you could keep dividing the search space in two forever
//      (if it doesn't have a rational square root).
//      In reality, computers will eventually run out of precision and
//      you'll have your approximation.
//
// http://stackoverflow.com/questions/1623375/writing-your-own-square-root-function
// ------------------------------------------------------------------------------------------
static const double EPSILON = 0.00001;

bool areDoubleSame(double a, double b)
{
    return fabs(a - b) < 0.00001;
}

double squareRoot(double number)
{
    if (number == 0 || number == 1)
    {
        return number;
    }

    // Start x from number and y from 0.
    // The point where x and y meets is the approximate square root.
    double low = 0;
    double high = number;
    double mid = 0;

    // Loop will continue till we get an accuracy of 0.001
    while ((high - low) >= 0.00001)
    {
        cout << "low: " << low << "; high: " << high << endl;
        mid = low + (high - low) / 2;
        /*
        if (areDoubleSame(mid * mid, number))
        {
            cout << "same" << endl;
            return round(mid);
        }
        */
        if (mid * mid > number)
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
    }

    return mid;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 13. Power of a number
// http://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
// http://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/
//
// Logic:
// For any number 'exp' it will have atleast A SINGLE '1' in its binary form.
// So till you get that one, if you see a 0 in binary form, multiply x * x
// Whenever you see a 1. multiply answer with x
// -----------------------------------------------------------------------------------------
double myPowRec(double x, int n)
{
    if (n == 0)
    {
        return 1;
    }

    if (n < 0)
    {
        n = -n;
        x = 1/x;
    }

    if (n & 1)
    {
        if (x == 0)
        {
            return 0;
        }
        return x * myPowRec(x * x, n/2);
    }
    else
    {
        return myPowRec(x * x, n/2);
    }
}

double myPow(double x, int n)
{
    /*
    bool isNegativePower = false;
    bool isNegativeNumOddPow = false;
    */

    int newN = n;
    double newX = x;
    double answer = 1;

    // Corner Cases
    if (n < 0)
    {
        //isNegativePower = true;

        // Convert the number to positive. Finally divide the answer by 1 i.e. 1/(x^n)
        newN = -n;
        newX = 1/x;
    }

    /*
    if (x < 0)
    {
        // Only if the power is an odd number then we have to multiply by -1
        if (n % 2 != 0)
        {
            isNegativeNumOddPow = true;
        }
        newX *= -1;
    }

    // If number is 0, return 1
    if (n == 0)
    {
        return 1;
    }

    // If the number is '1' or power is '1' return it as such
    if (n == 1 || x == 1 || x == -1)
    {
        if (x == -1 && !isNegativeNumOddPow)
        {
            return x * -1;
        }
        return x;
    }
    */

    // Main Loop 
    while (newN > 0)
    {
        if (newN % 2 != 0)
        {
            answer *= newX;
        }

        newX *= newX;
        newN = newN >> 1;
    }

    // Multiply by -1 only when the power is Odd number
    /*
    if (isNegativeNumOddPow)
    {
        answer *= -1;
    }

    // If negative power do 1/answer
    if (isNegativePower)
    {
        return 1 / answer;
    }
    */

    return answer;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 14. Replace 0s with 5 in a given number
//
//      Eg : 1208 ; 1258 120096045 ; 125596545 
// -----------------------------------------------------------------------------------------
int replaceZerosWithFives(int num)
{
    int result;
    int i = 0;
    int multiplier = 1;

    if (num < 0)
    {
        num = -num;
        multiplier = -1;
    }

    result = num;
    while (num)
    {

        if (num % 10 == 0)
        {
            result += 5 * pow(10, i);
        }

        i++;
        num /= 10;
    }

    return result * multiplier;
}

// -----------------------------------------------------------------------------------------
// PROBLEM 15. 
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------------------
int main()
{
    // Problem 1.
    {
        cout << endl << "PROBLEM 1" << endl;
        cout << "Convert Int to Roman Numbers" << endl;
        cout << intToRomanNumerals(3549) << endl;
        cout << intToRomanNumeralsRec(3549) << endl;
        cout << intToRomanNumerals(2900) << endl;
        cout << intToRomanNumeralsRec(2900) << endl;
        cout << intToRomanNumerals(14) << endl;
        cout << intToRomanNumeralsRec(14) << endl;
    }

    // Problem 2.
    {
        cout << endl << "PROBLEM 2" << endl;
        cout << "Convert Roman Numbers to Int" << endl;
        cout << romanNumeralsToInt("MMMDXLIX") << endl;
        cout << romanNumeralsToIntRec("MMMDXLIX") << endl;
        cout << romanNumeralsToInt("MMCM") << endl;
        cout << romanNumeralsToIntRec("MMCM") << endl;
        cout << romanNumeralsToInt("XIV") << endl;
        cout << romanNumeralsToIntRec("XIV") << endl;
    }

    // Problem 3.
    {
        cout << endl << "PROBLEM 3" << endl;
        cout << "Isomorphic Strings" << endl;
        string str1a = "egg";
        string str1b = "add";
        string str2a = "foo";
        string str2b = "bar";
        string str3a = "paper";
        string str3b = "title";
        string str4a = "ab";
        string str4b = "aa";
        cout << isIsomorphic(str1a, str1b) << endl;
        cout << isIsomorphic(str2a, str2b) << endl;
        cout << isIsomorphic(str3a, str3b) << endl;
        cout << isIsomorphic(str4a, str4b) << endl;
    }

    // Problem 4.
    {
        cout << endl << "PROBLEM 4" << endl;
        cout << "Evaluate Reverse Polish Notation" << endl;
        vector<string> tok1 = {"3", "11", "+"};
        vector<string> tok2 = {"3", "11", "5", "+", "-"};
        vector<string> tok3 = {"3", "11", "+", "5", "-"};
        vector<string> tok4 = {"2", "3", "11", "+", "5", "-", "*"};
        //vector<string> tok5 = {"9", "5", "3", "+", "2", "4", "^", "-", "+"};

        assert(evalRPN(tok1) == 14);
        assert(evalRPN(tok2) == -13);
        assert(evalRPN(tok3) == 9);
        assert(evalRPN(tok4) == 18);
        //assert(evalRPN(tok5) == 1);
    }

    // Problem 5.
    {
        cout << endl << "PROBLEM 5. myAtoi  String to Integer" << endl;
        cout << myAtoi("54321") << endl;
        cout << myAtoi("0") << endl;
        cout << myAtoi("-1") << endl;
        cout << myAtoi("-54321") << endl;
        cout << myAtoi("    010") << endl;
        cout << myAtoi("+-2") << endl;
    }

    // PROBLEM 6. Reverse words in a sentence
    {
        cout << endl << "PROBLEM 6. Reverse words in a sentence  " << endl;
        string s1 = "   PROBLEM 6.  ,.  Reverse words in a sentence  ";
        cout << s1 << endl;
        reverseWords(s1);
        cout << s1 << endl;

        cout << s1 << endl;
        s1 = "      ";
        reverseWords(s1);
        cout << s1 << endl;
    }

    // PROBLEM 7. Find Minimum range  that covers all the lists
    {
        cout << endl << "PROBLEM 7. Find Minimum range  that covers all the lists" << endl;
        vector< vector<int> > lists1 = {{20, 24, 100}, {2, 19, 22, 79, 800}, {10, 12, 23, 24, 119}};
        vector< vector<int> > lists2 = {{1, 4, 10}, {2, 15, 20}, {10, 12}};

        pair<int, int> minRange = findMinRangeForAllLists(lists1);
        cout << minRange.first << ".." << minRange.second << endl;

        pair<int, int> minRange2 = findMinRangeForAllLists(lists2);
        cout << minRange2.first << ".." << minRange2.second << endl;
    }

    // PROBLEM 8. Reverse a Integer Number
    {
        cout << endl << "PROBLEM 8. Reverse a Integer Number" << endl;
        cout << reverse(53) << endl;
        cout << reverse(-53) << endl;
        cout << reverse(123456789) << endl;
        cout << reverse(-123456789) << endl;
        cout << reverse(0) << endl;
        cout << reverse(-0) << endl;
        cout << reverse(1) << endl;
        cout << reverse(-1) << endl;
        cout << reverse(1534236469) << endl;
    }

    // PROBLEM 9. Reverse Bits in a Number
    {
        cout << endl << "PROBLEM 9. Reverse Bits in a Number" << endl;
        cout << reverseBits(6) << endl;
        cout << reverseBits(16) << endl;
        cout << reverseBits(26) << endl;
        cout << reverseBits(36) << endl;
        cout << reverseBits(43261596) << endl;
    }

    // PROBLEM 10. Sorted Array. Find first element smaller than given number
    {
        cout << endl << "PROBLEM 10. Sorted Array. Find first element smaller than given number" << endl;
        vector<int> nums = {2, 4, 6, 7, 8, 9, 11, 15};
        cout << findFirstSmallerElementIndex(nums, 1) << ", ";
        cout << findFirstSmallerElementIndex(nums, 2) << ", ";
        cout << findFirstSmallerElementIndex(nums, 4) << ", ";
        cout << findFirstSmallerElementIndex(nums, 5) << ", ";
        cout << findFirstSmallerElementIndex(nums, 6) << ", ";
        cout << findFirstSmallerElementIndex(nums, 7) << ", ";
        cout << findFirstSmallerElementIndex(nums, 8) << ", ";
        cout << findFirstSmallerElementIndex(nums, 9) << ", ";
        cout << findFirstSmallerElementIndex(nums, 11) << ", ";
        cout << findFirstSmallerElementIndex(nums, 15) << ", ";
        cout << findFirstSmallerElementIndex(nums, 17) << endl;
    }

    // PROBLEM 11. Sorted Array. Find first element smaller than given number
    {
        cout << endl << "PROBLEM 11. Sorted Array. Find first element smaller than given number" << endl;
        vector<int> nums = {2, 4, 6, 7, 8, 9, 11, 15};
        cout << findFirstGreaterElementIndex(nums, 1) << ", ";
        cout << findFirstGreaterElementIndex(nums, 2) << ", ";
        cout << findFirstGreaterElementIndex(nums, 4) << ", ";
        cout << findFirstGreaterElementIndex(nums, 5) << ", ";
        cout << findFirstGreaterElementIndex(nums, 6) << ", ";
        cout << findFirstGreaterElementIndex(nums, 7) << ", ";
        cout << findFirstGreaterElementIndex(nums, 8) << ", ";
        cout << findFirstGreaterElementIndex(nums, 9) << ", ";
        cout << findFirstGreaterElementIndex(nums, 11) << ", ";
        cout << findFirstGreaterElementIndex(nums, 15) << ", ";
        cout << findFirstGreaterElementIndex(nums, 17) << endl;
    }

    // PROBLEM 12: Square root of a number
    {
        cout << endl << "PROBLEM 12: Square root of a number" << endl;
        /*
        cout << squareRoot(0) << ", ";
        cout << squareRoot(1) << ", ";
        cout << squareRoot(2) << ", ";
        cout << squareRoot(3) << ", ";
        cout << squareRoot(4) << ", ";
        cout << squareRoot(5) << ", ";
        cout << squareRoot(6) << ", ";
        cout << squareRoot(7) << ", ";
        cout << squareRoot(8) << ", ";
        cout << squareRoot(9) << ", ";
        cout << squareRoot(49) << ", ";
        cout << squareRoot(62.104) << ", ";
        cout << squareRoot(77) << endl;
        */
        cout << squareRoot(77) << endl;
    }

    // PROBLEM 13: Power of a number
    {
        cout << endl << "PROBLEM 13: Power of a number" << endl;
        cout << myPow(-4, 4) << ", ";
        cout << myPow(2, -2147483648) << ", ";
        cout << myPow(6, -1) << ", ";
        cout << myPow(-1, -1) << ", ";
        cout << myPow(4, -5) << ", ";
        cout << myPow(6, 3) << ", ";
        cout << myPow(2, 1) << ", ";
        cout << myPow(2, 2) << ", ";
        cout << myPow(2, 3) << ", ";
        cout << myPow(2, 4) << ", ";
        cout << myPow(2, 5) << ", ";
        cout << myPow(2, 3) << ", ";
        cout << myPow(2, 3) << ", ";
        cout << myPow(2, 3) << ", ";
        cout << endl;

        cout << myPowRec(2, -2147483648) << ", ";
        cout << endl;

    }

    // PROBLEM 14: Replace 0s with 5 in a given number
    {
        cout << endl << "PROBLEM 14: Replace 0s with 5 in a given number" << endl;
        cout << replaceZerosWithFives(1208) << ", ";
        cout << replaceZerosWithFives(120096045) << ", ";
        cout << replaceZerosWithFives(-100) << ", ";
        cout << endl;
    }

    // PROBLEM 15: 
    {
        cout << endl << "PROBLEM 15: " << endl;
        cout << endl;
    }

    return 0;
}
