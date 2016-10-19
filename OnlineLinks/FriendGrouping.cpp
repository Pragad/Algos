// Two Sigma Friend Grouping
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

namespace
{
    int ROWPOS[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int COLPOS[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
}

// Procedure to do the DFS search Recursively
void dfsCountIslands(vector<vector <uint32_t> >& twoDMat, int32_t curRow, int32_t curCol)
{
    twoDMat[curRow][curCol] = 2;

    for (uint32_t i = 0; i < 8; i++)
    {
        int32_t newRow = curRow + ROWPOS[i];
        int32_t newCol = curCol + COLPOS[i];

        if (newRow >=0 && newRow < twoDMat.size() &&
            newCol >=0 && newCol < twoDMat[0].size() &&
            twoDMat[newRow][newCol] == 1)
        {
            dfsCountIslands(twoDMat, newRow, newCol);
        }
    }
}

// Procedure to do the DFS search Iteratively
void dfsCountIslandsIterative(vector<vector <uint32_t> >& twoDMat, uint32_t curRow, uint32_t curCol)
{
    // Create a queue
    // Put the current valid element into the queue
    queue<pair<int32_t, int32_t> > dfsQueue;
    dfsQueue.push(pair<int32_t, int32_t> {curRow, curCol});

    // While the queue is not empty take the top element
    // Scan all its neighbors and add valid elements (1s) to the queue
    // Repeat the process till the queue is not empty
    while (!dfsQueue.empty())
    {
        pair<uint32_t, uint32_t> tmp = dfsQueue.front();
        twoDMat[tmp.first][tmp.second] = 2;
        dfsQueue.pop();

        for (uint32_t i = 0; i < 8; i++)
        {
            int32_t newRow = tmp.first + ROWPOS[i];
            int32_t newCol = tmp.second + COLPOS[i];

            if (newRow >=0 && newRow < twoDMat.size() &&
                newCol >=0 && newCol < twoDMat[0].size() &&
                twoDMat[newRow][newCol] == 1)
            {
                dfsQueue.push(pair<int32_t, int32_t> {newRow, newCol});
            }
        }
    }
}

uint32_t countIslands(vector<vector <uint32_t> >& twoDMat)
{
    uint32_t numIslands = 0;
    for (uint32_t i = 0; i < twoDMat.size(); i++)
    {
        for (uint32_t j = 0; j < twoDMat[i].size(); j++)
        {
            if (twoDMat[i][j] == 1)
            {
                //dfsCountIslands(twoDMat, i, j);
                dfsCountIslandsIterative(twoDMat, i, j);
                ++numIslands;
            }
        }
    }

    // Convert the input matrix back to original by replace '2' with '1'
    return numIslands;
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

    printTwoDVec(friendsMat);
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

    printTwoDVec(friendsMat);

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

    printUnorderedMapVec(vecMap);
    printUnorderedMap(indexMap);
    return vecMap.size();
}

/*
int friendCircles2(vector < string > friends) {

    vector< vector <uint32_t> > friendsMat;
    unordered_map<uint32_t, vector<uint32_t> > vecMap;
    unordered_map<uint32_t, uint32_t > indexMap;


    for (uint32_t i = 0; i < friends.size(); i++)
    {
        vector<uint32_t> tmpVec(friends.size(), 0);
        friendsMat.push_back(tmpVec);
    }

    printTwoDVec(friendsMat);
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

    printTwoDVec(friendsMat);

    vector<uint32_t> num(300, 1);
    int a = 0;
    int b = 1

        while(1<=a && a <=300) {
            while(1<=b && b <=300){
                if(a!=b) {
                    if(friends[a][b] == 1) {
                        if(num[a] >= num[b]) {
                            num[b] = num[b]-1;
                            num[a] = num[a]+1;
                        }
                        else if(num[a] < num[b]) {
                            num[b] = num[b]+1;
                            num[a] = num[a]-1;
                        }
                    }
                }
                b++;
            }
            a++;
        }

    int count = 0;

    for(int i=0; i<300; i++) {
        if(num[i] > 0) {
            count++;
        }
    }

    cout << "FINAL ANSWER: "<< count << endl;
    return count;
}
*/

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));
    int res;
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

    /*
    int _friends_size = 0;
    cin >> _friends_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    string _friends_item;
    for(int _friends_i=0; _friends_i<_friends_size; _friends_i++) {
        getline(cin, _friends_item);
        _friends.push_back(_friends_item);
    }
    */
    
    res = friendCircles(_friends);
    //res = friendCircles2(_friends);
    cout << endl << "RESULT: " << res << endl;
    
    /*
    _friends.push_back("YNNYY");
    _friends.push_back("NYNNN");
    _friends.push_back("NNYNN");
    _friends.push_back("YNNYN");
    _friends.push_back("YNNNY");


    _friends.push_back("YYNN");
    _friends.push_back("YYYN");
    _friends.push_back("NYYN");
    _friends.push_back("NNNY");

    _friends.push_back("YYNN");
    _friends.push_back("YYYN");
    _friends.push_back("NYYN");
    _friends.push_back("NNNY");
    */

    /*
    int _friends_size = 0;
    cin >> _friends_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    string _friends_item;
    for(int _friends_i=0; _friends_i<_friends_size; _friends_i++) {
        getline(cin, _friends_item);
        _friends.push_back(_friends_item);
    }
    */
    
    res = friendCircles(_friends);
    //res = friendCircles2(_friends);
    cout << endl << "RESULT: " << res << endl;
    
    /*
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
