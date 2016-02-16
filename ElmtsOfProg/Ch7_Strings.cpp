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

// 7.1 String to Integer
string intToString(int x)
{
    uint32_t len = abs(log10(x)) + 1;
    char* strNum = new char[len];
    int i = len - 1;

    while (x > 0)
    {
        int rem = x % 10;

        strNum[i] = rem + '0';
        i--;
        x = x / 10;
    }
    
    strNum[len] = '\0';

    return string(strNum);
}


// 7.1 b Integer to String
int stringToInt(string s)
{
    int result = 0;
    for (int i = s.length() - 1, j = 0; i >= 0; i--, j++)
    {
        result += (s[i] - '0') * (pow(10,j));
    }

    return result;
}

// 7.2 Reverse Words in a Sentence
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

char phoneDigitMap[10][5] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

// 7.3 Phone number permutations
void printPhonePermuteRecursive(int number[], uint32_t currentDigit, char result[], uint32_t length)
{
    if (currentDigit == length)
    {
        cout << string(result) << endl;
        return;
    }

    for (uint32_t i = 0; i < strlen(phoneDigitMap[number[currentDigit]]); i++)
    {
        result[currentDigit] = phoneDigitMap[number[currentDigit]][i];
        printPhonePermuteRecursive(number, currentDigit + 1, result, length);

        if (number[currentDigit] == '0' || number[currentDigit] == '1')
        {
            return;
        }
    }
}

void printPhoneNumberPermutations(int number[], uint32_t len)
{
    char result[len + 1];

    // Add Null Character to the end of the string
    result[len] = 0;
    printPhonePermuteRecursive(number, 0, result, len);
}

void printVectorString(vector<string> vecString)
{
    for (string s : vecString)
    {
        cout << s << " , ";
    }
    cout << endl;
}

void printPhoneNumPermuteIterative(string number)
{
    unordered_map<char, string> numberMap = {{'0', ""},
                                             {'1', ""},
                                             {'2', "abc"},
                                             {'3', "def"},
                                             {'4', "ghi"},
                                             {'5', "jkl"},
                                             {'6', "mno"},
                                             {'7', "pqrs"},
                                             {'8', "tuv"},
                                             {'9', "wxyz"},
                                             };
    vector<string> result;
    vector<string> preResult;

    result.push_back("");

    // Length of your phone number will be "number.length()"
    // We have to traverse each digit of the phone number
    for (uint32_t i = 0; i < number.length(); i++)
    {
        // Initially this will be empty. But we keep adding letters to it.
        //      Iteration 0: Result: a, b, c
        //      Iteration 1: Result: ad, bd, cd
        //
        for (string s : result)
        {
            // For each of the string we have in "s" add all letters corresponding to the next
            // digit.
            // So "s" will become, "ad", "ae", "af". 
            for (uint32_t j = 0; j < numberMap[number[i]].length(); j++)
            {
                preResult.push_back(s + numberMap[number[i]][j]);
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

int main()
{
    string line = "he is my cat. This dog does not run fast";

    cout << line << endl;
    //reverseWord(line, 0, line.length() - 1);
    reverseLine(line);
    cout << line << endl;

    cout << intToString(5432) << endl;

    string str = "123";
    cout << stringToInt(str) << endl;

    //int number[] = {2, 3, 4};
    int number[] = {2, 3};
    //printPhoneNumberPermutations(number, sizeof(number) / sizeof(int));

    string strPhoneNo = "2648";
    printPhoneNumPermuteIterative(strPhoneNo);

    cout << endl;
    return 0;
}