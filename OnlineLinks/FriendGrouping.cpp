// Two Sigma Friend Grouping
#include <map>
#include <set>
#include <list>
#include <cmath>
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

void printUnorderedMap(const unordered_map<uint32_t, uint32_t>& myMap)
{
    cout << endl << "Map" << endl;
    for (auto mm : myMap)
    {
        cout << mm.first << ": " << mm.second << " , ";
    }
    cout << endl;
}

void printUnorderedMapVec(const unordered_map<uint32_t, vector<uint32_t>>& myMap)
{
    cout << endl << "Map" << endl;
    for (auto mm : myMap)
    {
        cout << mm.first << ": ";
        for (auto i : mm.second)
        {
             cout << i << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void printTwoDVec(const vector< vector <uint32_t> >& twoDVec)
{
    cout << endl << "Two D Mat: " << endl;
    for (uint32_t i = 0; i < twoDVec.size(); i++)
    {
        for (uint32_t j = 0; j < twoDVec[i].size(); j++)
        {
            cout << twoDVec[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
 * Complete the function below.
 */
int friendCircles(vector < string > friends)
{
    vector< vector <uint32_t> > friendsMat;
    unordered_map<uint32_t, vector<uint32_t> > vecMap;
    unordered_map<uint32_t, uint32_t > indexMap;

    for (uint32_t i = 0; i < friends.size(); i++)
    {
        vecMap[i] = {i};
        indexMap[i] = i;
    }

    //printUnorderedMapVec(vecMap);
    //printUnorderedMap(indexMap);

    for (uint32_t i = 0; i < friends.size(); i++)
    {
        vector<uint32_t> tmpVec(friends.size(), 0);
        friendsMat.push_back(tmpVec);
    }

    //printTwoDVec(friendsMat);
    for (uint32_t i = 0; i < friends.size(); i++)
    {
        for (uint32_t j = 0; j < friends[i].length(); j++)
        {
            if (i == j)
            {
                friendsMat[i][j] = 0;
            }
            else
            {
                if (friends[i][j] == 'Y')
                {
                    friendsMat[i][j] = 1;
                }
            }
        }
    }

    //printTwoDVec(friendsMat);

    for (uint32_t i = 0; i < friendsMat.size(); i++)
    {
        for (uint32_t j = 0; j < friendsMat[i].size(); j++)
        {
            if (friendsMat[i][j] == 1)
            {
                if (i < j)
                {
                    vecMap.erase(j);
                    vecMap[indexMap[i]].push_back(j);   

                    indexMap[j] = indexMap[i];
                    //indexMap[j] = i;
                }
            }
        }
    }

    //printUnorderedMapVec(vecMap);
    //printUnorderedMap(indexMap);
    return vecMap.size();
}

int main() {
    vector<string> _friends;

    _friends.push_back("YYNN");
    _friends.push_back("YYYN");
    _friends.push_back("NYYN");
    _friends.push_back("NNNY");

    /*
    _friends.push_back("YYYN");
    _friends.push_back("YYNY");
    _friends.push_back("YNYN");
    _friends.push_back("NYNY");

    _friends.push_back("YNNY");
    _friends.push_back("NYYN");
    _friends.push_back("NYYN");
    _friends.push_back("YNNY");

    _friends.push_back("YYNY");
    _friends.push_back("YYNN");
    _friends.push_back("NNYN");
    _friends.push_back("YNNY");

    _friends.push_back("YNNYY");
    _friends.push_back("NYNNN");
    _friends.push_back("NNYNN");
    _friends.push_back("YNNYN");
    _friends.push_back("YNNNY");

    _friends.push_back("YNNNN");
    _friends.push_back("NYNNN");
    _friends.push_back("NNYNN");
    _friends.push_back("NNNYN");
    _friends.push_back("NNNNY");


    _friends.push_back("YYNN");
    _friends.push_back("YYYN");
    _friends.push_back("NYYN");
    _friends.push_back("NNNY");

    _friends.push_back("YYNNY");
    _friends.push_back("YYYNN");
    _friends.push_back("NYYYN");
    _friends.push_back("NNYYY");
    _friends.push_back("YNNYY");
    */

    res = friendCircles(_friends);
    cout << endl << "RESULT: " << res << endl;
    
    /*
    ofstream fout(getenv("OUTPUT_PATH"));
    int res;
    int _friends_size = 0;
    cin >> _friends_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<string> _friends;
    string _friends_item;
    for(int _friends_i=0; _friends_i<_friends_size; _friends_i++) {
        getline(cin, _friends_item);
        _friends.push_back(_friends_item);
    }
    
    res = friendCircles(_friends);
    fout << res << endl;
    */
    
    fout.close();
    return 0;
}
