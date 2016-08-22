#include <iostream>
using namespace std;

#ifdef _WIN32
typedef char 	                int8_t;
typedef unsigned char 	        uint8_t;
typedef unsigned short int 	    uint16_t;
typedef unsigned int 	        uint32_t;
typedef unsigned long long int 	uint64_t;
#else
#include <stdint.h>
#endif

void printArray(int a[], uint32_t n)
{
    for (uint32_t i = 0; i < n; i++)
    {
        cout << a[i] << "  ";
    }
    cout << endl;
}

void partition(int a[], uint32_t n)
{
    if (n < 2)
    {
        return;
    }

    if (n == 2)
    {
        if (a[0] > a[1])
        {
            int t = a[0];
            a[0] = a[1];
            a[1] = t;
        }
    }

    if (n > 2)
    {
        uint32_t lastSmallNumIdx = 0;
        uint32_t i = 0;

        int pivot = a[0];

        for (i = 1; i < n; i++)
        {
            if (a[i] < pivot)
            {
                lastSmallNumIdx++;
                if (i != lastSmallNumIdx)
                {
                    int temp = a[i];
                    a[i] = a[lastSmallNumIdx];
                    a[lastSmallNumIdx] = temp;
                }
            }
        }

        // Swap Pivot and a[i].
        // i will have the position of the Last number less than pivot
        int temp = a[lastSmallNumIdx];
        a[lastSmallNumIdx] = a[0];
        a[0] = temp;
    }
}

int main()
{
    int a[] = {5, 8, 1, 9, 2};
    int a2[] = {5, 1, 8, 2, 9};
    int a3[] = {5, 1, 3};
    int a4[] = {5, 1, 8};
    int a5[] = {5, 7};
    int a6[] = {5, 1};
    int a7[] = {5, 9, 8};

    uint32_t numElmts = sizeof(a)/sizeof(a[0]);
    uint32_t numElmts2 = sizeof(a2)/sizeof(a2[0]);
    uint32_t numElmts3 = sizeof(a3)/sizeof(a3[0]);
    uint32_t numElmts4 = sizeof(a4)/sizeof(a4[0]);
    uint32_t numElmts5 = sizeof(a5)/sizeof(a5[0]);
    uint32_t numElmts6 = sizeof(a6)/sizeof(a6[0]);
    uint32_t numElmts7 = sizeof(a7)/sizeof(a7[0]);

    printArray(a, numElmts);
    partition(a, numElmts);
    //quickSort(a, numElmts);
    printArray(a, numElmts);
    cout << endl;

    printArray(a2, numElmts2);
    partition(a2, numElmts2);
    printArray(a2, numElmts2);
    cout << endl;

    printArray(a3, numElmts3);
    partition(a3, numElmts3);
    printArray(a3, numElmts3);
    cout << endl;

    printArray(a4, numElmts4);
    partition(a4, numElmts4);
    printArray(a4, numElmts4);
    cout << endl;

    printArray(a5, numElmts5);
    partition(a5, numElmts5);
    printArray(a5, numElmts5);
    cout << endl;

    printArray(a6, numElmts6);
    partition(a6, numElmts6);
    printArray(a6, numElmts6);
    cout << endl;

    printArray(a7, numElmts7);
    partition(a7, numElmts7);
    printArray(a7, numElmts7);
    cout << endl;

    cout << endl;
    return 0;
}
