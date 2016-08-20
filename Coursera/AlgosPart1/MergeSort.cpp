#include <iostream>
using namespace std;

//int* merge(int a1[], int a1_size, int a2[], int a2_size) 
void merge(int a1[], int a1_size, int a2[], int a2_size) 
{
    int* c1 = new int [a1_size + a2_size];
    unsigned int k = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    while (i < a1_size && j < a2_size)
    {
        if (a1[i] < a2[j])
        {
            c1[k] = a1[i];
            i++;
            k++;
        }
        else if (a1[i] >= a2[j])
        {
            c1[k] = a2[j];
            j++;
            k++;
        }
    }

    while (i < a1_size)
    {
        c1[k] = a1[i];
        i++;
        k++;
    }

    while (j < a2_size)
    {
        c1[k] = a2[j];
        j++;
        k++;
    }

    for (int x = 0; x < k; x++)
    {
        cout << c1[x] << " ";
    }

    delete [] c1;
}

int* merge_1(int a1[], int a1_size, int a2[], int a2_size) 
{
    int* c1 = new int [a1_size + a2_size];
    unsigned int k = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    while (i < a1_size && j < a2_size)
    {
        if (a1[i] < a2[j])
        {
            c1[k] = a1[i];
            i++;
            k++;
        }
        else if (a1[i] >= a2[j])
        {
            c1[k] = a2[j];
            j++;
            k++;
        }
    }

    while (i < a1_size)
    {
        c1[k] = a1[i];
        i++;
        k++;
    }

    while (j < a2_size)
    {
        c1[k] = a2[j];
        j++;
        k++;
    }

    return c1;
}

void print_array (int arr[], int ar_size)
{
    for (unsigned int i = 0; i < ar_size; i++)
    {
        cout << arr[i] << "  " ;
    }
    cout << endl;
}

int* merge_sort(int array[], int start, int end)
{
    if (end <= 1)
    {
        return array;
    }

    int* left_hal = new int [end/2 - start];
    int* right_hal = new int [end - end/2];

    left_hal = merge_sort(array, start, end/2);
    right_hal = merge_sort(array, end/2, end);

    return merge_1(left_hal, end/2 - start, right_hal, end - end/2);
}

int main()
{
    int unsorted[] = {5,4,3,2,1,6,7,8};
    unsigned int num_elmts = sizeof(unsorted) / sizeof(unsorted[0]);

    cout << "Merge Sort" << endl;
    int b1[] = {1,6,7,80};    
    int b2[] = {2,6,6,10,12, 13, 15, 16}; 
    unsigned int b1_size =  sizeof(b1)/sizeof(b1[0]);
    unsigned int b2_size =  sizeof(b2)/sizeof(b2[0]);
    int *c = new int [b1_size + b2_size];
    merge(b1, b1_size, b2, b2_size);

    cout << endl;
    c = merge_1(b1, b1_size, b2, b2_size);


    print_array(c, b1_size + b2_size);

    delete [] c;

    return 0;
}
