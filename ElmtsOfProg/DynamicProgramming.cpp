#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unsigned int fibonacci(int n)
{
    // VERY IMP: // If N is less than 2, return n
    //if (n == 1 || n == 2)
    if (n <= 1)
    {
        return n;
        //return 1;
    }
    else
    {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

unsigned int fibonacciDynamic(int n)
{
    vector<unsigned int> fibVec;

    fibVec.push_back(1);
    fibVec.push_back(1);

    for (unsigned int i = 2; i < n; i++)
    {
        fibVec.push_back(fibVec[i - 1] + fibVec[i - 2]);
    }

    for (int i = 0; i < fibVec.size(); i++)
    {
        cout << fibVec[i] << " ";
    }
    cout << endl;

    return fibVec[n - 1];
}

unsigned int fibonacciDynamic2(int n)
{
    if ( n <= 1)
    {
        return n;
    }

    int a = 1;
    int b = 0;
    int result;

    for (unsigned int i = 1; i < n; i++)
    {
        result = a + b;
        b = a;
        a = result;
    }

    cout << endl;

    return result;
}

// Problem 1: Ladder Problem
// Algorithm: Used Dynamic Programming to get the result.
// So Complexity is O(N).
// I store the "n-1" and "n-2" lader positions. Then I append
// '1' to 'n-1' positions and '2' to all 'n-2' positions.

// Utility function to print a Vector of Vector
void printVecOfVec(vector< vector<unsigned int> > vecOfVec)
{
    cout << "Vector of Vectors" << endl;
    for (unsigned int i = 0; i < vecOfVec.size(); i++)
    {
        for (unsigned int j = 0; j < vecOfVec[i].size(); j++)
        {
            cout << vecOfVec[i][j] << " ";
        }
        cout <<  endl;
    }
    cout << endl;
}

// Given a source vector and a number, it appends the number to each source vectors
// and puts the final values in the destination vector
void appendElementToVector(vector< vector <unsigned int> > src,
                           unsigned int num,
                           vector< vector <unsigned int> > &dest)
{
    for (int i = 0; i < src.size(); i++)
    {
        src[i].push_back(num);
        dest.push_back(src[i]);
    }
}

// Ladder Problem
void ladderDynamic(int number)
{
    vector< vector<unsigned int> > vecNminusTwo = {{}};
    vector< vector<unsigned int> > vecNminusOne = {{1}};
    vector< vector<unsigned int> > vecResult;

    for (int i = 2; i <= number; i++)
    {
        // Empty the result vector to hold fresh set
        vecResult.clear();

        // Append '2' to all N-2 ladder positions
        appendElementToVector(vecNminusTwo, 2, vecResult);

        // Append '1' to all N-1 ladder positions
        appendElementToVector(vecNminusOne, 1, vecResult);

        vecNminusTwo = vecNminusOne;
        vecNminusOne = vecResult;
    }

    printVecOfVec(vecResult);
}

/*
void ladderPathsRec(char* strPath, unsigned int num, unsigned int recLevel)
{
    if (num == 0)
    {
        strPath[recLevel] = '\0';
        cout << strPath << endl;
    }

    if (num >= 1)
    {
        strPath[recLevel] = '1';
        //cout << "1. " << strPath << endl;
        ladderPathsRec(strPath, num - 1, recLevel + 1);
    }

    if (num >= 2)
    {
        strPath[recLevel] = '2';
        //cout << "2. " << strPath << endl;
        ladderPathsRec(strPath, num - 2, recLevel + 1);
    }
}

void ladderRec(unsigned int number)
{
    char* strPath = new char[number + 1];
    ladderPathsRec(strPath, number, 0);
}
*/

// Problem 1: Print paths down a ladder
// Algorithm: Use recursion to print the paths
//            One call to the function is made for every single path entry.

void ladderPathsRec(char* strPath, unsigned int num, unsigned int recLevel)
{
    if (num == 0)
    {
        strPath[recLevel] = '\0';
        cout << strPath << endl;
    }

    if (num >= 1)
    {
        // Add '1' to our paths and go one step further
        strPath[recLevel] = '1';
        ladderPathsRec(strPath, num - 1, recLevel + 1);
    }

    if (num >= 2)
    {
        // Add '2' to our paths and go two steps further
        strPath[recLevel] = '2';
        ladderPathsRec(strPath, num - 2, recLevel + 1);
    }
}

void ladderRec(unsigned int number)
{
    // This array will hold one valid path to reach 'N' steps.
    // So the max memory required would be 'N + 1'
    char* strPath = new char[number + 1];
    ladderPathsRec(strPath, number, 0);
    delete[] strPath;
}


int main()
{
    int n = 10;
    cout << "1. " << fibonacci(n) << endl;
    cout << "2. " << fibonacciDynamic(n) << endl;

    cout << "3. " << fibonacciDynamic2(n) << endl;
    //ladderDynamic(6);

    ladderRec(3);
    cout << endl;
    return 0;
}
