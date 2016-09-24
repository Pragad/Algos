#include <iostream>
using namespace std;

void printArray(int a[], uint32_t n)
{
    for (uint32_t i = 0; i < n; i++)
    {
        cout << a[i] << "  ";
    }
    cout << endl;
}

void swapInt(int& a, int& b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void printArrayRange(int a[], uint32_t startIndex, uint32_t endIndex)
{
    for (uint32_t i = startIndex; i <= endIndex; i++)
    {
        cout << a[i] << "  ";
    }

    cout << endl;
}

uint32_t quickSortPartition(vector<int>& nums, uint32_t stIdx, uint32_t endIdx)
{
    int pivot = nums[stIdx];
    uint32_t low = stIdx;
    uint32_t high = endIdx;

    while (low < high)
    {
        while (nums[low] <= pivot)
        {
            low++;
        }

        while (nums[high] > pivot)
        {
            high--;
        }

        if (low < high)
        {
            mySwap(nums[low], nums[high]);
        }
    }

    // If partition has happened then we would be at a HIGH which will be the actual pivot's
    // position. So num[high] will be < pivot.
    if (nums[high] < pivot)
    {
        mySwap(nums[stIdx], nums[high]);
    }

    // Pivot is at high
    return high;
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

// IMP: Use start index and end index
uint32_t partitionRange(int a[], uint32_t sI, uint32_t eI)
{
    // Since range add 1 to it.
    uint32_t n = eI - sI + 1;
    if (n < 2)
    {
        return sI;
    }

    if (n == 2)
    {
        if (a[sI] > a[eI])
        {
            int t = a[sI];
            a[sI] = a[eI];
            a[eI] = t;

            return eI;
        }
        else
        {
            return sI;
        }
    }

    if (n > 2)
    {
        uint32_t lastSmallNumIdx = sI;
        uint32_t i = sI;

        int pivot = a[sI];

        for (i = sI; i < n; i++)
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
        a[lastSmallNumIdx] = a[sI];
        a[sI] = temp;

        return lastSmallNumIdx;
    }
}

// http://codereview.stackexchange.com/questions/77782/quick-sort-implementation
uint32_t partitionType2(int arr[], uint32_t sI, uint32_t eI)
{
    int pivot = arr[sI];
    uint32_t i = sI+1;
    uint32_t j = eI;

    while (i <= j)
    {
        while(arr[i] <= pivot && i <= j)
        {
            i++;
        }

        // VERY IMP: i <= j. "EQUALS" is very important here
        // That will make sure, J moves to one lesser element
        while (arr[j] > pivot && i <= j)
        {
            j--;
        }

        // Swap only if i < j
        if (i < j)
        {
            swapInt(arr[i], arr[j]);
        }
    }

    // After the crossing j will point to an element smaller than pivot.
    swapInt(arr[i - 1], arr[sI]);

    return i - 1;
}

void quickSortWrapper(int arr[], int sI, int eI)
{
    if (sI < eI)
    {
        uint32_t pivotPos = partitionRange(arr, sI, eI);
        printArrayRange(arr, sI, eI);

        quickSortWrapper(arr, sI, pivotPos - 1);
        quickSortWrapper(arr, pivotPos + 1, eI);
    }
    else
    {
        return;
    }
}

void quickSort(int arr[], uint32_t n)
{
    quickSortWrapper(arr, 0, n-1);
}

int main()
{
    {
        /*
        //int a[] = {5, 8, 1, 9, 2};
        int a[] = {5, 2, 1, 9, 8};
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

        cout << "Quick Sort 2" << endl;
        printArray(a, numElmts);
        //partitionRange(a, 3, 4);
        quickSort(a, numElmts);
        cout << "Answer : ";
        printArray(a, numElmts);
        cout << endl << endl;

        cout << "Quick Sort 3" << endl;
        printArray(a2, numElmts2);
        quickSort(a2, numElmts2);
        cout << "Answer : ";
        printArray(a2, numElmts2);
        cout << endl << endl;

        cout << "Quick Sort 4" << endl;
        printArray(a3, numElmts3);
        quickSort(a3, numElmts3);
        cout << "Answer : ";
        printArray(a3, numElmts3);
        cout << endl << endl;

        cout << "Quick Sort 5" << endl;
        printArray(a4, numElmts4);
        quickSort(a4, numElmts4);
        cout << "Answer : ";
        printArray(a4, numElmts4);
        cout << endl << endl;

        cout << "Quick Sort 6" << endl;
        printArray(a5, numElmts5);
        quickSort(a5, numElmts5);
        cout << "Answer : ";
        printArray(a5, numElmts5);
        cout << endl << endl;

        cout << "Quick Sort 7" << endl;
        printArray(a6, numElmts6);
        quickSort(a6, numElmts6);
        cout << "Answer : ";
        printArray(a6, numElmts6);
        cout << endl << endl;

        cout << "Quick Sort 8" << endl;
        printArray(a7, numElmts7);
        quickSort(a7, numElmts7);
        cout << "Answer : ";
        printArray(a7, numElmts7);
        cout << endl << endl;
        */
    }

    // Partition Type 2
    {
        int a[] = {5, 2, 1, 9, 8};

        printArray(a, sizeof(a) / sizeof(a[0]));
        cout << partitionType2(a, 0, 4) << endl;
        printArray(a, sizeof(a) / sizeof(a[0]));
    }

    cout << endl;
    return 0;
}
