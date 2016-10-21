// Lifion
//
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

void printVectorInt(vector<int> nums)
{
    cout << endl << "Vec Int" << endl;
    for (int num : nums)
    {
        cout << num << ", ";
    }
    cout << endl;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

void maximumCupcakes(vector < string > trips) 
{
    vector<string> tripStr;
    vector<int32_t> tripNum;
    int cupcakes = 0;
    int wrappers = 0;
    int rem = 0;
    
    for (uint32_t i = 0; i < trips.size(); i++)
    {

        split(trips[i], ' ', tripStr);
        
        for (uint32_t y = 0; y < tripStr.size(); y++)
        {
            int tmp = stoi(tripStr[y]);
            tripNum.push_back(tmp);
        }

        cupcakes = tripNum[0] / tripNum[1];

        rem = cupcakes % tripNum[2];

        wrappers = cupcakes / tripNum[2];
        bool count = true;
        
        while (count)
        {
            if (wrappers < 1)
            {
                cout << cupcakes << endl;
                count = false;
            }
            else
            {
                cupcakes = wrappers + cupcakes;
                wrappers = wrappers + rem;

                rem = wrappers % tripNum[2];
                wrappers = wrappers / tripNum[2];
            }
        }

        tripStr.clear();
        tripNum.clear();
    }    
}

int main() {
    
    vector<string> _trips;
    /*
    int _trips_size = 0;
    cin >> _trips_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<string> _trips;
    string _trips_item;
    for(int _trips_i=0; _trips_i<_trips_size; _trips_i++) {
        getline(cin, _trips_item);
        _trips.push_back(_trips_item);
    }
    */
    
    _trips.push_back("10 2 5");
    _trips.push_back("12 4 4");
    _trips.push_back("6 2 2");
    maximumCupcakes(_trips);
    
    return 0;
}

