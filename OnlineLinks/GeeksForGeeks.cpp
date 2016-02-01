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

// Given an array arr[], find the maximum j & i such that arr[j] > arr[i]
// http://www.geeksforgeeks.org/given-an-array-arr-find-the-maximum-j-i-such-that-arrj-arri/
int maxIndexDiff(int arr[], int num)
{
    for (int i = 0, j = num - 1; i < j;)
    {
        if (arr[i] < arr[j])
        {
            cout << "i: " << i << "; j: " << j << endl;
            return j-i;
        }
        else
        {
            if (i+1 < j)
            {
                if (arr[i+1] < arr[j])
                {
                    cout << "i: " << i+1 << "; j: " << j << endl;
                    return j-(i+1);
                }
            }
            if (j-1 > i)
            {
                if (arr[i] < arr[j-1])
                {
                    cout << "i: " << i << "; j: " << j-1 << endl;
                    return (j-1)-i;
                }
            }

            i++;
            j--;
        }
    }

    return -1;
}

int main()
{
    int arr1[] = {34, 8, 10, 3, 2, 80, 30, 33, 1};
    int arr2[] = {9, 2, 3, 4, 5, 6, 7, 8, 18, 0};
    int arr3[] = {1, 2, 3, 4, 5, 6};
    int arr4[] = {6, 5, 4, 3, 2, 1};

    cout << maxIndexDiff(arr1, sizeof(arr1) / sizeof(int)) << endl;
    cout << maxIndexDiff(arr2, sizeof(arr2) / sizeof(int)) << endl;
    cout << maxIndexDiff(arr3, sizeof(arr3) / sizeof(int)) << endl;
    cout << maxIndexDiff(arr4, sizeof(arr4) / sizeof(int)) << endl;

    cout << endl;
}
