#include <vector>
#include <iostream>
using namespace std;

int findMaxList(const vector<int>& arrList)
{
    int maxVal = arrList[0];

    for (int i = 1; i < arrList.size(); i++)
    {
        if (maxVal < arrList[i])
        {
            maxVal = arrList[i];
        }
    }

    return maxVal;
}

void addValToList(vector<int>& arrList, int stPos, int endPos, int value, int& maxValue)
{
    for (int i = stPos-1; i < endPos; i++)
    {
        arrList[i] += value;

        if (maxValue < arrList[i])
        {
            maxValue = arrList[i];
        }
    }
}

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int arrSize;
    int numOps;
    int stPos;
    int endPos;
    int value;
    int maxValue = INT_MIN;
    cin >> arrSize;
    cin >> numOps;
    
    vector<int> arrList(arrSize, 0);
   
    for (int i = 0; i < numOps; i++)
    {
        cin >> stPos;
        cin >> endPos;
        cin >> value;
		
		addValToList(arrList, stPos, endPos, value, maxValue);
    }
    
    cout << maxValue;
    //cout << findMaxList(arrList) << endl;

    return 0;
}
