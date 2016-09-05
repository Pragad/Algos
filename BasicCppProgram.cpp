#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

void printArray(int arr[], int num)
{
    for (int i = 0; i < num; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int a = 5;
    int b = 6;
    int c = a + b;
    c--;

    cout << c << endl;
    return 0;
}
