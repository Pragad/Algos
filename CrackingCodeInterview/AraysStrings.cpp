// Chapter: Arrays and Strings
#include <iostream>
#include <stdlib.h>
#include <bitset>
using namespace std;

// Arrays and Strings

// 1.1 Implement an algorithm to determine if a string has all unique characters.
// What if you can not use additional data structures?
bool hasUniqueChars(char* str, unsigned int strSize)
{
    // IMP: Use boolean array instead of a CHAR array.
    unsigned char a[512];
    for (unsigned int i = 0; i < strSize; i++)
    {
        if (a[str[i]] == 1)
        {
            return false;
        }
        else
        {
            a[str[i]] = 1;
        }
    }

    return true;
}

// 1.1 Unique characters in a string using Bit Vector
bool hasUniqueCharsBitSet(string str)
{
    // Total no. of Unicode characters can be 2^21.
    // http://stackoverflow.com/questions/19212306/whats-the-difference-between-ascii-and-unicode
    // 2^21 = 2097152 characters. It can be represented using 2097152 bits = 256KB
    std::bitset<512> uniqChar;

    for (char c : str)
    {
        if (uniqChar[c])
        {
            return false;
        }
        else
        {
            uniqChar[c] = 1;
        }
    }

    return true;
}

// 1.2 Write code to reverse a C-Style String  (C-String means that “abcd” is represented as
// five characters, including the null character )
char* stringReverse(char* str, unsigned int strSize)
{
    char temp;

    // IMP: have another variable to come backwards from strSize
    // IMP: for loop requires only one "UNSIGNED INT"
    for (unsigned int i = 0, j = strSize-1; i < strSize/2; i++, j--)
    {
        cout << str[i] << ".." << str[j] << endl;
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    return str;
}

// 1.2b Reverse a String using "string" instead of "char*"
string stringReverseStr(string str)
{
    char temp;

    // IMP: have another variable to come backwards from strSize
    // IMP: for loop requires only one "UNSIGNED INT"
    for (unsigned int i = 0, j = str.size()-1; i < j; i++, j--)
    {
        str[i] = str[i] ^ str[j];
        str[j] = str[i] ^ str[j];
        str[i] = str[i] ^ str[j];

        /*
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        */
    }

    return str;
}

// 1.2c String Reverse Recursive
void stringReverseRec(string& str, uint32_t l, uint32_t r)
{
    if (l >= r)
    {
        return;
    }
    
    char c = str[l];
    str[l] = str[r];
    str[r] = c;

    stringReverseRec(str, l+1, r-1);
}

// 1.3 Remove duplicate characters in a string
char* removeDuplicates(char* str, unsigned int strSize)
{
    // IMP: Initializing all elements of the arry to 0.
    bool temp[512] = {};
    unsigned tail = 0;
    bool unique = false;
    unsigned int i = 0;

    for (i =0; i < strSize; i++)
    {
        if (temp[str[i]])
        {
            unique = false;
        }
        else
        {
            temp[str[i]] = true;
            unique = true;
            if (tail != i)
            {
                str[tail] = str[i];
            }

            // IMP: After incrementing the TAIL, go to the start of for loop
            // Else tail and i will mismatch. We should do anything like comparing tail and i
            tail++;
        }

    }

    // If the last character is not a unique character then we should trim the string
    // at the last seen non-unique character.
    //if (unique && (tail != i))
    if (tail != i)
    {
        str[tail] = '\0';
    }

    return str;
}

// 1.4 Anagrams or not; Permutation of a string or not
// Solution: Sort the string and find if they are the same or not.
// Have a bool array and store the count of each letters; Agains traverse the target
// string and check if it has the same number of characters.

// 1.5 Replace space with %20
char* replaceSpace(char* str, uint32_t strSize)
{
    uint32_t numSpaces = 0;
    uint32_t newSize = 0;

    for (uint32_t i =0; i < strSize; i++)
    {
        if (str[i] == ' ')
        {
            numSpaces++;
        }
    }

    newSize = numSpaces * 2 + strSize;

    str[newSize] = '\0';

    // VERY IMP: Make "i" and "j" INT and NOT UNSIGNED INT.
    for (int32_t i = newSize-1, j = strSize-1; j >=0 && i >= 0; i--, j--)
    {
        if (str[j] != ' ') 
        {
            str[i] = str[j];
        }
        else
        {
            str[i] = '0';
            i--;
            str[i] = '2';
            i--;
            str[i] = '%';
        }
        cout << endl;
    }

    return str;
}

// IMP: How to pass a 2D array in C
// http://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
// IMP1: Template is a must
// IMP2: braces () around "matrix" is a must.
template <size_t rows, size_t cols>
void printMatrix(int (&matrix)[rows][cols])
{
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// IMP: Store the Col and Rows where we have 0.
// IMP: Store it in a way that we can directly see which COL/ROW is zero.
// i.e Use Col / Row number as index
template <size_t rows, size_t cols>
void setZeroMatrix(int (&matrix)[rows][cols])
{
    int r[rows];
    int c[cols];

    // Get the rows and cols that have an element 0
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            if(matrix[i][j] == 0)
            {
                r[i] = 1;
                c[j] = 1;
            }
        }
    }

    for (uint32_t j = 0; j < cols; j++)
    {
        for (uint32_t i = 0; i < rows; i++)
        {
            if(r[i] == 1 || c[j] == 1)
            {
                matrix[i][j] = 0;
            }
        }
    }
}



int main()
{
    // 1. Check if a string has all unique characters.
    {
        char asdf[] = "hello";
        char qewr[] = "helo";
        cout << "Unique 1: " << hasUniqueChars(asdf, 5);
        cout << endl;

        cout << "Unique 2: " << hasUniqueChars(qewr, 4);
        cout << endl;

        string str = "hello";
        cout << "Unique 3: " << hasUniqueCharsBitSet(str) << endl;
    }

    // IMP: The below line will cause a segmentation fault.
    // http://stackoverflow.com/questions/1011455/is-it-possible-to-modify-a-string-of-char-in-c
    //asdf[0] = 'b';
    {
        char qwer[] = "mala";
        string str = "mala";
        cout << "String Rev 1: " << stringReverse(qwer, 4) << endl;
        cout << "String Rev 2: " << stringReverseStr(str) << endl;
        stringReverseRec(str, 0, str.length()-1);
        cout << "String Rev 3: " << str << endl;
        cout << endl;
    }

    {
        char qwer[] = "mala";
        cout << removeDuplicates(qwer, 4);
        cout << endl;

        char qwer1[] = "malaa";
        cout << removeDuplicates(qwer1, 5);
        cout << endl;

        char qwer2[] = "maaa";
        cout << removeDuplicates(qwer2, 4);
        cout << endl;
    }

    {
        char qwer3[] = "a b c";
        cout << replaceSpace(qwer3, 5);
        cout << endl;
    }


    {
        int mat[4][3] = {{1,2,3}, {0,5,6}, {7,8,0}, {10,11,12}};
        printMatrix(mat);
        cout << endl;

        setZeroMatrix(mat);
        printMatrix(mat);
        cout << endl;
    }


    cout << endl;
    return 0;
}
