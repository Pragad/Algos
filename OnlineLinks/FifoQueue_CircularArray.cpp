// To compile: g++ -std=c++11 file_name.cpp

#include <iostream>
#include <vector>
using namespace std;

// Global Variables
int ARRAY_SIZE = 5;
vector<int> circularArray(ARRAY_SIZE);
int START_POS = 0;
int END_POS = -1;
int numElements = 0;

// Clear the entries in the Queue
void initialize_to_empty()
{
    circularArray.clear();
    START_POS = 0;
    END_POS = -1;
}

bool insert_at_rear(int elmt)
{
    // Fail if the Queue is full
    if (numElements == ARRAY_SIZE)
    {
        return false;
    }

    // If we have reached end of the array and if we have space at front
    // END should go to 0
    if (END_POS == ARRAY_SIZE - 1)
    {
        END_POS = 0;
    }
    else
    {
        END_POS++;
    }

    // We have increment END_POS to point to next position.
    // Insert the new element there.
    circularArray[END_POS] = elmt;
    numElements++;

    return true;
}

int remove_front_front()
{
    // If Queue is already empty, fail the operation
    if (numElements == 0)
    {
        return false;
    }

    int tmpNum = circularArray[START_POS];
    numElements--;

    // If we have reached end of the array and if we have space at front
    // START should go to 0
    if (START_POS == ARRAY_SIZE - 1)
    {
        START_POS = 0;
    }
    else
    {
        START_POS++;
    }
    return 0;
}

bool is_full()
{
    return numElements == ARRAY_SIZE;
}

// Utility function to print the Queue for debugging purpose
void printQueue()
{
    cout << "Start: " << START_POS << endl;
    cout << "End: " << END_POS << endl;

    for (int entry : circularArray)
    {
        cout << entry << ", ";
    }
    cout << endl;
}

int main()
{
    insert_at_rear(1);
    insert_at_rear(2);
    insert_at_rear(3);
    insert_at_rear(4);
    insert_at_rear(5);
    printQueue();

    remove_front_front();
    printQueue();
    insert_at_rear(6);
    printQueue();
    remove_front_front();
    printQueue();
    remove_front_front();
    printQueue();
    remove_front_front();
    printQueue();
    remove_front_front();
    printQueue();
    remove_front_front();
    printQueue();
    remove_front_front();
    printQueue();
    insert_at_rear(7);
    printQueue();

    cout << endl;
}
