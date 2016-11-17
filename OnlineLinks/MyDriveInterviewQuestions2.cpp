#include <iostream>
#include <string>
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
 */

// Utility function to print a vector of ints
void printVectorInt(vector<int> nums)
{
    for (int num : nums)
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
// Main Function
// -----------------------------------------------------------------------------------------
int main()
{
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

    return 0;
}
