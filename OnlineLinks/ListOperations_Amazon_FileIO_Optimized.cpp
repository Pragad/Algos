#include <vector>
#include <iostream>
#include <climits>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

void splitString(const std::string &str, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
}

// ----------------------------------------------------------------------------------------------
// PROBLEM 2: 
// ----------------------------------------------------------------------------------------------
// Sping strings using a STRING of chars
void splitStringByPatternString(const string& s, const string& pattern, vector<string>& words)
{
    int startIndex = 0;
    unordered_set<char> patternSet;

    for (char c : pattern)
    {
        patternSet.insert(c);
    }

    int i = 0;
    for(i = 0; i < s.length(); i++)
    {
        // If the character is present in the pattern, the split the word
        if (patternSet.find(s[i]) != patternSet.end())
        {
            if (startIndex != i)
            {
                words.push_back(s.substr(startIndex, i - startIndex));
                startIndex = i + 1;
            }
            else
            {
                ++startIndex;
            }
        }
    }

    // Very important to put the last word into the Vector
    if (startIndex < i)
    {
        words.push_back(s.substr(startIndex, i - startIndex));
    }
}

// Find the first repeated word in a sentence
string findFirstRepeatedWord(const string& str)
{
    vector<string> words;
    string pat = " ,!().";
    splitStringByPatternString(str, pat, words);
    unordered_map<string, uint64_t> mapWords;


    // Insert all the words into a map
    for (string word : words)
    {
        cout << word << ", ";
        mapWords[word]++;
        /*
        auto itr = mapWords.find(word);
        if (itr == mapWords.end())
        {
            mapWords[word] = 1;
        }
        else
        {
            (itr->second)++;
        }
        */
    }
    cout << endl;

    // Check if each word is present in the set
    for (string word : words)
    {
        auto itr = mapWords.find(word);

        // The below if will always be true
        if (itr != mapWords.end())
        {
            if (itr->second > 1)
            {
                return word;
            }
        }
    }

    return "";
}

// ----------------------------------------------------------------------------------------------
// PROBLEM 3: 
// ----------------------------------------------------------------------------------------------
void addValToList(vector<uint64_t>& arrList, uint64_t stPos, uint64_t endPos, uint64_t value, uint64_t& maxValue)
{
    for (uint64_t i = stPos-1; i < endPos; i++)
    {
        arrList[i] += value;

        if (maxValue < arrList[i])
        {
            maxValue = arrList[i];
        }
    }
}

uint64_t findMaxList(const vector<uint64_t>& arrList)
{
    uint64_t maxVal = arrList[0];

    for (uint64_t i = 1; i < arrList.size(); i++)
    {
        if (maxVal < arrList[i])
        {
            maxVal = arrList[i];
        }
    }

    return maxVal;
}

// ----------------------------------------------------------------------------------------------
// Main Function
// ----------------------------------------------------------------------------------------------
int main()
{
    // Problem 2:
    {
        string str = "I had my,.,first. ,backpacking (,)! trip! We (had) a wonderful time in our  trip!!I";

        cout << "First Repeated Word: " << findFirstRepeatedWord(str) << endl;
    }

    // Problem 3:
    {
        uint64_t arrSize;
        uint64_t numOps;
        uint64_t stPos;
        uint64_t endPos;
        uint64_t value;
        uint64_t maxValue = 0;
        string line;
        vector<uint64_t> arrList;
        ifstream testCaseFile;
        uint64_t expectedOutput = 0;
        uint64_t x = 0;

        testCaseFile.open("ListOperations_Amazon_TC3.txt");
        if(testCaseFile.is_open())
        {
            while (!testCaseFile.eof())
            {
                // VERY IMP: Each time we will have a line that should be split into words
                vector<string> words;
                getline(testCaseFile, line);
                splitString(line, ' ', words);

                if ((words.size()) == 1)
                {
                    expectedOutput = stoul(words[0]);
                }
                else if ((words.size()) == 2)
                {
                    arrSize = stoul(words[0]);
                    numOps = stoul(words[1]);

                    if (arrSize >= 3 && arrSize <= 10000000 &&
                        numOps >= 1 && numOps <= 200000)
                    {
                        arrList.resize(arrSize + 1, 0);
                    }
                    else
                    {
                        // Error. So return.
                        return 0;
                    }
                }
                else if  ((words.size()) == 3)
                {
                    stPos = stoul(words[0]);
                    endPos = stoul(words[1]);
                    value = stoul(words[2]);

					arrList[stPos] += value;
					if ((endPos + 1) <= arrSize) 
                    {
                        arrList[endPos + 1] -= value;
                    }
				}
            }

            // As we have reached the EOF, time to close the file
            testCaseFile.close();
        }

		for(int i = 1; i <= arrSize; i++)
		{
		   x = x + arrList[i];
		   if(maxValue < x)
           {
               maxValue = x;
           }
		}

        cout << "Exp Out: " << expectedOutput << endl;
        cout << "Max Val: " << maxValue << endl;
        cout << "Result: " << (expectedOutput == maxValue) << endl;
    }

    return 0;
}
