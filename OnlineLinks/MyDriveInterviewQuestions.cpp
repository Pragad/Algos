#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Find the first non-match character in two strings.
bool findFirstNonMatchingChar(string s1, string s2, char& result)
{
    uint32_t shortLen = (s1.length() < s2.length() ? s1.length() : s2.length());
    uint32_t i = 0;

    if (s1.empty() && s2.empty())
    {
        return false;
    }

    if (s1.empty())
    {
        result = s2[0];
        return true;
    }

    if (s2.empty())
    {
        result = s1[0];
        return true;
    }

    for (; i < shortLen; i++)
    {
        if (s1[i] != s2[i])
        {
            // Found a mismatch. Either s1[i] or s2[i]
            uint32_t x = i + 1;
            uint32_t y = i + 1;

            // Find first occurence of s2[i] in s1
            for (; x < shortLen; x++)
            {
                if (s1[x] == s2[i])
                {
                    break;
                }
            }    

            // Find first occurence of s1[i] in s2
            for (; y < shortLen; y++)
            {
                if (s2[y] == s1[i])
                {
                    break;
                }
            }

            if (x < y)
            {
                result = s1[i];
                return true;
            }
            if ( x > y)
            {
                result = s2[i];
                return true;
            }
        }
    }

    // If string 1 is bigger then return s1[i]
    if (i < s1.length())
    {
        result = s1[i];
        return true;
    }

    // If string 2 is bigger then return s2[i]
    if (i < s2.length())
    {
        result = s2[i];
        return true;
    }

    return false;
}

struct uniqChar
{
    bool isPresent;
    uint32_t index;
};

char findUniqueChar(string str)
{
    if (str.empty())
    {
        return str[0];
    }

    uint32_t minIndex = INT_MAX;
    unordered_map<char, uniqChar> charMap;

    for (uint32_t i = 0; i < str.length(); i++)
    {
        auto itr = charMap.find(str[i]);
        if (itr != charMap.end())
        {
            itr->second.isPresent = true;
        }
        else
        {
            uniqChar temp{false, i};
            charMap[str[i]] = temp;
        }
    }

    //for (unordered_map<char, uniqChar>::iterator itr = charMap.begin(); itr != charMap.end(); itr++)
    for (auto it = charMap.begin(); it != charMap.end(); it++)
    {

        if (!(it->second).isPresent)
        {
            if ((it->second).index < minIndex)
            {
                minIndex = it->second.index;
            }
        }
    }

    // VERY IMP: What if we don't have a Unique Char. Min index could be infinity.
    if (minIndex < str.length())
    {
        return str[minIndex];
    }
    else
    {
        // Return NULL if nothing is present.
        return 0;
    }
}

template <size_t rows, size_t cols>
void printTwoDMatrix(int (&twoDmat)[rows][cols])
{
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            cout << twoDmat[i][j] << ", ";
        }
        cout << endl;
    }
}

template <typename T>
void printTwoDPtrToPtr(T** array, uint32_t rows, uint32_t cols)
{
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            cout << array[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

int rowDirection[8] = {-1, -1, -1, 0 , 0, 1 , 1, 1};
int colDirection[8] = {-1, 0 , 1 , -1, 1, -1, 0, 1};

bool isValid(int** twoDmat, int row, int col, bool** visited, uint32_t maxRows, uint32_t maxCols)
{
    if (row < 0 || col < 0 || row >= maxRows || col >= maxCols)
    {
        return false;
    }

    // VERY IMP:
    // If we have already seen this, then we shouldn't go further deep. So return false;
    if (visited[row][col])
    {
        return false;
    }

    return (twoDmat[row][col] == 1);
}

void dfs(int** twoDmat, uint32_t row, uint32_t col, bool** visited, uint32_t maxRows, uint32_t maxCols)
{
    visited[row][col] = true;
    
    for (uint32_t i = 0; i < 8; i++)
    {
        int newRow = row + rowDirection[i];
        int newCol = col + colDirection[i];

        // We need maxRows and maxCols to find the size of the matrix.
        if (isValid(twoDmat, newRow, newCol, visited, maxRows, maxCols))
        {
            // newRow and newCol will be a positive number and within the range
            dfs(twoDmat, newRow, newCol, visited, maxRows, maxCols);
        }
    }
}

uint32_t countConnectedIslands(int** twoDmat, uint32_t rows, uint32_t cols)
{
    uint32_t numIslands = 0;
    bool **visited = new bool*[rows];
    for (uint32_t i = 0; i < rows; i++)
    {
        visited[i] = new bool[cols];
    }

    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            visited[i][j] = false;
        }
    }

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            // IMP: go DFS only when we have a 1.
            if (visited[x][y] == false && twoDmat[x][y] == 1)
            {
                dfs(twoDmat, x, y, visited, rows, cols);
                numIslands++;
            }
        }
    }

    return numIslands;
}

int main()
{
    // Problem 1:
    string s1 = "hexlloahao";
    string s2 = "hexlloab";
    char result;
    if (findFirstNonMatchingChar(s1, s2, result))
    {
        cout << "First Non Match Char: " << result << endl;
    }
    else
    {
        cout << "No non Match Char" << endl;
    }

    // Problem 2:
    s1 = "hlllhabcdedcba";
    cout << "Unique Char: " << findUniqueChar(s1) << endl;

    // Problem 3:
    uint32_t rows = 5;
    uint32_t cols = 5;
    /*
    int twoD[rows][cols] = {{1, 1, 0},
                            {0, 1, 0},
                            {1, 0, 0} };
                            */
    int twoD[rows][cols] = {{1, 1, 0, 0, 0},
                            {0, 1, 0, 0, 1},
                            {1, 0, 0, 1, 1},
                            {0, 0, 0, 0, 0},
                            {1, 0, 1, 0, 1}};

    int **arrayTwoD = new int *[rows];
    for (uint32_t i = 0; i < rows; i++)
    {
        arrayTwoD[i] = new int[cols];
    }

    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            arrayTwoD[i][j] = twoD[i][j];
        }
    }

    printTwoDPtrToPtr(arrayTwoD, rows, cols);
    cout << "Num Islands: " << countConnectedIslands(arrayTwoD, rows, cols) << endl;
        
    cout << endl;
    return 0;
}
