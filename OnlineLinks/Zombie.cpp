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


int zombieCluster2(vector < string > zombies)
{
    vector< vector <uint32_t> > zombiesMat;
    unordered_map<uint32_t, vector<uint32_t> > vecMap;
    unordered_map<uint32_t, uint32_t > indexMap;

    for (uint32_t i = 0; i < zombies.size(); i++)
    {
        vecMap[i] = {i};
        indexMap[i] = i;
    }

    //printUnorderedMapVec(vecMap);
    //printUnorderedMap(indexMap);

    for (uint32_t i = 0; i < zombies.size(); i++)
    {
        vector<uint32_t> tmpVec(zombies.size(), 0);
        zombiesMat.push_back(tmpVec);
    }

    //printTwoDVec(zombiesMat);
    for (uint32_t i = 0; i < zombies.size(); i++)
    {
        for (uint32_t j = 0; j < zombies[i].length(); j++)
        {
            if (i == j)
            {
                zombiesMat[i][j] = 0;
            }
            else
            {
                if (zombies[i][j] == '1')
                {
                    zombiesMat[i][j] = 1;
                }
            }
        }
    }

    //printTwoDVec(zombiesMat);

    for (uint32_t i = 0; i < zombiesMat.size(); i++)
    {
        for (uint32_t j = 0; j < zombiesMat[i].size(); j++)
        {
            if (zombiesMat[i][j] == 1)
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

int zombieCluster(vector < string > zombies)
{
    unordered_map<uint32_t, uint32_t > indexMap;
    vector<uint32_t> resultVec;
    std::vector<int>::iterator it;

    for (uint32_t i = 0; i < zombies.size(); i++)
    {
        indexMap[i] = i;
    }

    for (uint32_t i = 0; i < zombies.size(); i++)
    {
        for (uint32_t j = i + 1; j < zombies[i].length(); j++)
        {
            if (zombies[i][j] == '1')
            {
                indexMap[j] = indexMap[i];
            }
        }
    }

    for (auto mm : indexMap)
    {
        resultVec.push_back(mm.second);
    }

    resultVec.erase( unique( resultVec.begin(), resultVec.end() ), resultVec.end() );
    
//    it = std::unique (resultVec.begin(), resultVec.end());   // 10 20 30 20 10 ?  ?  ?  ?
//    resultVec.resize( std::distance(resultVec.begin(),it) ); // 10 20 30 20 10
    
    return (resultVec.size());
}

// Lifion
int main()
{
    vector<string> _zombies;
    
    /*
    _zombies.push_back("1100");
    _zombies.push_back("1110");
    _zombies.push_back("0110");
    _zombies.push_back("0001");
    */

    //_zombies.push_back("1");

    /*
    _zombies.push_back("10");
    _zombies.push_back("01");
    */

    /*
    _zombies.push_back("10");
    _zombies.push_back("01");
    */

    _zombies.push_back("111");
    _zombies.push_back("111");
    _zombies.push_back("111");

    /*
    _zombies.push_back("100");
    _zombies.push_back("010");
    _zombies.push_back("001");

    _zombies.push_back("100");
    _zombies.push_back("010");
    _zombies.push_back("001");
    */

    cout << zombieCluster(_zombies) << endl;

    /*
    ofstream fout(getenv("OUTPUT_PATH"));
    int res;
    int _zombies_size = 0;
    cin >> _zombies_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    string _zombies_item;
    for(int _zombies_i=0; _zombies_i<_zombies_size; _zombies_i++) {
        getline(cin, _zombies_item);
        _zombies.push_back(_zombies_item);
    }
    
    res = zombieCluster(_zombies);
    fout << res << endl;
    
    fout.close();
    */
    return 0;
}
