/*
void printPhoneNumPermuteIterative(string number)
void printVectorString(vector<string> vecString)
void printPhoneNumberPermutations(int number[], uint32_t len)
void printPhonePermuteRecursive(int number[], uint32_t currentDigit, char result[], uint32_t length)
void reverseLine(string &line)
void reverseWord(string &word, uint32_t start, uint32_t end)
void swapChar(char &a, char &b)
int stringToInt(string s)
string intToString(int x)
*/
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <unordered_map>
using namespace std;

//-----------------------------------------------------------------------------------------
// 7.1 b Integer to String
//-----------------------------------------------------------------------------------------
string intToString(int x)
{
    uint32_t len = abs(log10(x)) + 1;
    char* strNum = new char[len];       // Memleak here
    int i = len - 1;

    while (x > 0)
    {
        int rem = x % 10;

        strNum[i] = rem + '0';          // IF "rem < 0" then num is NEGATIVE
        i--;
        x = x / 10;
    }
    
    strNum[len] = '\0';

    return string(strNum);
}

//-----------------------------------------------------------------------------------------
// 7.1 String to Integer
//-----------------------------------------------------------------------------------------
int stringToInt(string s)
{
    int result = 0;
    for (int i = s.length() - 1, j = 0; i >= 0; i--, j++)
    {
        result += (s[i] - '0') * (pow(10,j));
    }

    return result;
}

// 7.1b Implement atoi
bool myAtoI(string str, int& resNum)
{
    if (str.length() == 0)
    {
        return false;
    }

    int sign = 1;
    int stIdx = 0;
    resNum = 0;

    if (str[0] == '-')
    {
        sign = -1;
        stIdx = 1;      // IMP
    }

    for (; stIdx < str.length(); stIdx++)
    {
        // Check if the string is a valid number
        if ((str[stIdx] - '0' < 0) || (str[stIdx] - '0' > 9))
        {
            return false;
        }
        else
        {
            resNum = resNum * 10 + (str[stIdx] - '0');
        }
    }

    resNum *= sign;

    return true;
}

//-----------------------------------------------------------------------------------------
// 7.2 Reverse Words in a Sentence
//-----------------------------------------------------------------------------------------
void swapChar(char &a, char &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

// VERY IMP: String should be passed by reference
void reverseWord(string &word, uint32_t start, uint32_t end)
{
    for (; start < end; start++, end--)
    {
        swap(word[start], word[end]);
    }
}

void reverseLine(string &line)
{
    uint32_t st = 0;
    uint32_t en = 0;
    for (; en < line.length(); en++)
    {
        if (line[en] == ' ')
        {
            // Add extra check to not swap a single space.
            // This can happen when "hello         world"
            if (st != en)
            {
                reverseWord(line, st, en-1);
                line[en] = ' ';
            }
            st = en + 1;
        }
    }

    // Reverse the final word.
    if (st != line.length())
    {
        reverseWord(line, st, en - 1);
    }

    // Reverse the entire thing once
    reverseWord(line, 0, en - 1);
    line[en] = '\0';
}

//-----------------------------------------------------------------------------------------
// 7.3 Phone number permutations Recursive
// http://stackoverflow.com/questions/2344496/how-can-i-print-out-all-possible-letter-combinations-a-given-phone-number-can-re
// http://www.geeksforgeeks.org/find-possible-words-phone-digits/
// Time Complexity: O(4^N)
//-----------------------------------------------------------------------------------------
void printPhonePermuteRecursive(const vector<uint32_t>& nums,
                                uint32_t currentDigit,
                                const unordered_map<uint32_t, string>& phoneDigitMap,
                                string result)
{
    if (currentDigit == nums.size())
    {
        cout << result << ", ";
        return;
    }

    // Get all set of characters for the current digit from the map
    for (uint32_t i = 0; i < phoneDigitMap.at(nums[currentDigit]).length(); i++)
    {
        result += phoneDigitMap.at(nums[currentDigit])[i];
        printPhonePermuteRecursive(nums, currentDigit + 1, phoneDigitMap, result);
        result.pop_back();

        // 0 or 1 has only one digit. So we can safely return here;
        // Even if we don't do this, for loop will take care of it right after this
        if (nums[currentDigit] == 0 || nums[currentDigit] == 1)
        {
            return;
        }
    }
}

void printPhoneNumberPermutations(vector<uint32_t> nums)
{
    string result;
    unordered_map<uint32_t, string> numberMap = {{0, "0"}, {1, "1"}, {2, "abc"},
                                                 {3, "def"}, {4, "ghi"}, {5, "jkl"},
                                                 {6, "mno"}, {7, "pqrs"}, {8, "tuv"},
                                                 {9, "wxyz"}, };

    printPhonePermuteRecursive(nums, 0, numberMap, result);
    cout << endl;
}

//-----------------------------------------------------------------------------------------
// 7.3 Phone number permutations Iterative
// http://stackoverflow.com/questions/2344496/how-can-i-print-out-all-possible-letter-combinations-a-given-phone-number-can-re
//-----------------------------------------------------------------------------------------
void printVectorString(vector<string> vecString)
{
    for (string s : vecString)
    {
        cout << s << ", ";
    }
    cout << endl;
}

void printPhoneNumPermuteIterativeNew(const vector<uint32_t>& nums)
{
    vector<string> result;
    vector<string> preResult;
    unordered_map<uint32_t, string> phoneDigitMap = {{0, "0"}, {1, "1"}, {2, "abc"},
                                                     {3, "def"}, {4, "ghi"}, {5, "jkl"},
                                                     {6, "mno"}, {7, "pqrs"}, {8, "tuv"},
                                                     {9, "wxyz"}, };

    result.push_back("");

    // We have to traverse each digit of the phone number
    for (uint32_t i = 0; i < nums.size(); i++)
    {
        // Initially this will be empty. But we keep adding letters to it.
        //      Iteration 0: Result: a, b, c
        //      Iteration 1: Result: ad, bd, cd
        for (string s : result)
        {
            // For each of the string we have in "s"
            // Add all letters corresponding to the next digit.
            // So "a" will become, "ad", "ae", "af". 
            for (uint32_t j = 0; j < phoneDigitMap.at(nums[i]).length(); j++)
            {
                preResult.push_back(s + phoneDigitMap.at(nums[i])[j]);
            }
        }

        // Save what we have built till now in "result" so we can continue using the result
        // for our next loop.
        result = preResult;

        // Clear our the preResult. This is because, we have the updated preResult in result.
        // So we have to extract each string from "s", add corresponding characters to it
        // and finally put all the results built till now in "result".
        preResult.erase(preResult.begin(), preResult.end());
    }

    printVectorString(result);
}

//-----------------------------------------------------------------------------------------
// Main function
//-----------------------------------------------------------------------------------------
int main()
{
    {
        string line = "he is my cat. This dog does not run fast";
        cout << line << endl;
        //reverseWord(line, 0, line.length() - 1);
        reverseLine(line);
        cout << line << endl;
    }

    {
        int result;
        cout << "ItoS: " << intToString(5432) << endl;
        string str = "123";
        cout << "StoI: " << stringToInt(str) << endl;

        str = "-123";
        if (myAtoI(str, result))
        {
            cout << "atoi: " << result << endl;
        }
        else
        {
            cout << "Not a valid num" << endl;
        }
    }

    {
        //int number[] = {2, 3, 4};
        //vector<uint32_t> nums = {2, 3, 4};

        int number[] = {0, 2, 1};
        vector<uint32_t> nums = {0, 2, 1};

        string strPhoneNo = "021";
        printPhoneNumberPermutations(nums);
        printPhoneNumPermuteIterativeNew(nums);
    }

    cout << endl;
    return 0;
}
