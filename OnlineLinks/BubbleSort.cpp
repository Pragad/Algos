#include <iostream>
using namespace std;

void swapInt(int &a, int &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void printArray(int arr[], uint32_t num)
{
    cout << "Array: ";
    for (uint32_t i = 0; i < num; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
}

void bubbleSort(int arr[], uint32_t num)
{
    if (num < 2)
    {
        return;
    }

    for (uint32_t i = 0; i < num; i++)
    {
        bool swapped = false;
        for (uint32_t j = 0; j < num - i - 1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swapInt(arr[j], arr[j+1]);
                swapped = true;
            }
        }

        // If swap didn't happen break
        if (!swapped)
        {
            break;
        }
    }
}

int main()
{

    int arr[] = {5, 3, 8, 1, 2, 9, 4};

    for (int i : arr)
    {
        cout << i << ", ";
    }
    cout << endl;
    printArray(arr, sizeof(arr) / sizeof(int));
    bubbleSort(arr, sizeof(arr) / sizeof(int));
    printArray(arr, sizeof(arr) / sizeof(int));

    cout << endl;
    return 0;
}
