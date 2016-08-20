#include <iostream>
using namespace std;

void swapInt(int &a, int &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void printArray(int a[], uint32_t n)
{
    for (uint32_t i = 0; i < n; i++)
    {
        cout << a[i] << "  ";
    }
    cout << endl;
}

void sort2(int a[], uint32_t n)
{
    for (uint32_t i = 1; i < n; i++)
    {
        for (uint32_t j = 0; j < i; j++)
        {
            if (a[i] < a[j])
            {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void insertionSort(int a[], uint32_t n)
{
    int key;
    for (uint32_t i = 1; i < n; i++)
    {
        // VERY IMP: Key should NOT be equated to a[i] here. Because next time
        // when the "j" loop continues the "key < a[j]" will still be true.
        // key = a[i];
        for (uint32_t j = 0; j < i; j++)
        {
            key = a[i];
            // If we pick an element that is less than the element in hand, then
            // we should move all the elements in hand accordingly to accomodate
            // the new element.
            if (key < a[j])
            {
                // We have to move all elements from j to i-1 by one place.
                // After that insert key (a[i]) at a[j]'s position.
                int temp = key;
                uint32_t k;
                for (k = i; k > j; k--)
                {
                    a[k] = a[k-1];
                }
                a[k] = key;
            }
        }
    }
}

void insertionSortOptimized(int arr[] uint32_t num)
{
    for (uint32_t i = 1; i < num; i++)
    {
        for (uint32_t j = i; j > 0 && arr[j - 1] > arr[j]; j--)
        {
            swapInt(arr[j-1], arr[j]);
        }
    }
}

int main()
{
    int a[] = {4, 3, 2, 1};

    uint32_t numElmts = sizeof(a)/sizeof(a[0]);
    printArray(a, numElmts);
    //insertionSort(a, numElmts);
    sort2(a, numElmts);
    printArray(a, numElmts);

    cout << endl;
    return 0;
}
