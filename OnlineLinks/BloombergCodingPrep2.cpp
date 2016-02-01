#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <stdlib.h>
using namespace std;

struct node
{
    int data;
    struct node* next;
};

// A simple push function that inserts the new value at the beginning of the list.
void Push(node*& head, int value)
{
    struct node* temp = new node();

    temp->data = value;
    temp->next = head;
    head = temp; 
}

// Utility function to print all values of the list.
void printList(node* head)
{
    while (head != NULL)
    {
        cout << head->data << " " ;
        head = head->next;
    }
    cout << endl;
}

/*
1. Given the root node to a singly linked list, reverse the last 5
nodes in the list. For a list with 5 or less nodes, reverse the whole list.

2. Implement a deque. Think about what properties a deque must have.
Implement it as a base class that can be extended and as a template.
In general, start thinking about what's underneath all the other STL
data types and how they work.

3. Given a char pointer to large buffer of memory, write your own
version of my_malloc and my_free without using any system calls. Make
it as robust as possible. How would you minimize memory fragmentation?

4. Given a char array with only Xs and Ys, do an in-place separation of the Xs and Ys.
Example: "XYXXYYYXX" -> "YYYYXXXXX"

5. The standard library function of atoi() is not very robust. How
would you design/implement a better version of it?

6. Implement a Singleton. Everyone knows the "textbook" implementation of the singleton but think of all the different ways you can implement it and what are their pros/cons? Make a thread-safe version.
*/

void printCharArray(char arr[], unsigned int num)
{
    for (unsigned int i = 0; i < num; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//----------------------------------------------------------------------------------------------
// Problem 4: Rearrange Xs and Ys
// Algorithm: Take two pointers (say i & j) one pointing to the beginning
//            and one to the end of the array. 
//            Traverse 'i' till you find the first position of 'Y'
//            Traverse 'j' till you find the first position of 'X'
//            Swap i & j.
//            Continue till i crosses j
// Complexit: O(N)

void rearrangeXsYs(char arr[], unsigned int num)
{
    // Start 'i' from the beignning of the array.
    unsigned int i = 0;

    // Start 'j' from the end of the array.
    unsigned int j = num - 1;
    while (i < j)
    {
        for (; i < j; i++)
        {
            if (arr[i] == 'Y')
            {
                break;
            }
        }

        for (; j > i; j--)
        {
            if (arr[j] == 'X')
            {
                break;
            }
        }
        
        // I can also use swap without using a temporary suing '^' operator.
        if (arr[i] == 'Y' && arr[j] == 'X')
        {
            arr[i] ^= arr[j];
            arr[j] ^= arr[i];
            arr[i] ^= arr[j];
            //arr[j] = temp;
            i++;
            j--;
        }
        else
        {
            break;
        }
    }
}

int main()
{
    //char arr[5] = {'X', 'Y', 'Y', 'X', 'Y'};
    char arr[] = {'X', 'X', 'Y', 'Y', 'X', 'Y', 'X', 'Y', 'Y', 'X', 'X', 'X', 'X', 'X'};
    printCharArray(arr, sizeof(arr) / sizeof(char));
    rearrangeXsYs(arr, sizeof(arr) / sizeof(char));
    printCharArray(arr, sizeof(arr) / sizeof(char));

    // Linkedlist Problems
    struct node* head;

    cout << endl;
    return 0;
}
