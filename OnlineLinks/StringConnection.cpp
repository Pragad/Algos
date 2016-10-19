// Two Sigma String Chains
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// This utility function that calculates the length recursively
// maxResult : stores the 
void longestChainRecursive(string word, const unordered_map<string, uint32_t>& wordsMap, uint32_t maxResult, uint32_t& finalResult)
{
    // cout << "Word: " << word << "; Max: " << maxResult << "; Fin: " << finalResult << endl;

    // Base Case: If length of the words is 1, then just update the result with max
    if (word.length() == 1)
    {
        if (maxResult > finalResult)
        {
            finalResult = maxResult;
        }

        return ;
    }

    for (uint32_t i = 0; i < word.length(); i++)
    {
        string tmpWord = word;
        word.erase(word.begin() + i);
        
        auto itr = wordsMap.find(word);
        if (itr != wordsMap.end())
        {
            longestChainRecursive(word, wordsMap, maxResult + 1, finalResult);
        }
        word = tmpWord;
    }

    if (maxResult > finalResult)
    {
        finalResult = maxResult;
    }

    return ;
}

/*
 * Complete the function below.
 */
int longestChain(vector < string > words)
{
    uint32_t maxChainLen = 0;
    uint32_t maxFunChainLen = 0;
    uint32_t tmp = 0;
    unordered_map<string, uint32_t> wordsMap;

    // Put all words in a map
    for (string word : words)
    {
        wordsMap[word]++;
    }

    for (string word : words)
    {
        if (word.length() > 1)
        {
            maxFunChainLen = 0;
            tmp = 1;

            longestChainRecursive(word, wordsMap, tmp, maxFunChainLen);
        }
        else
        {
            maxFunChainLen = 1;
        }

        if (maxFunChainLen > maxChainLen)
        {
            maxChainLen = maxFunChainLen;
        }

    }

    return maxChainLen;
}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));
    int res;
    
    vector<string> _words;
    /*
    int _words_size = 0;
    cin >> _words_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    string _words_item;
    for(int _words_i=0; _words_i<_words_size; _words_i++) {
        getline(cin, _words_item);
        _words.push_back(_words_item);
    }
    */
    
    _words.push_back("a");
    _words.push_back("b");
    _words.push_back("ba");
    _words.push_back("bca");
    _words.push_back("bda");
    _words.push_back("bdca");
    res = longestChain(_words);
    fout << res << endl;
    
    fout.close();

    /*
    int _words_size = 0;
    cin >> _words_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<string> _words;
    string _words_item;
    for(int _words_i=0; _words_i<_words_size; _words_i++) {
        getline(cin, _words_item);
        _words.push_back(_words_item);
    }
    
    res = longestChain(_words);
    fout << res << endl;
    
    fout.close();
    */
    return 0;
}

