/*
 * Author: Pragad Thiru
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>
using namespace std;

// Used to print out additionals log messages
// #define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

// ------------------------------------------------------------------------------------------------
// This function parses the input and gets the 'a' and 'b' value
// Assumption: The input string matches the syntax "move a onto b" where 
// 'a' and 'b' are valid numbers
// ------------------------------------------------------------------------------------------------
void parseInput(const string& command, uint32_t& a, uint32_t& b)
{
    // Since the input will be on the exact format without incorrect commands
    // Assumption: Directly accessing the corresponding to the index
    // Command is of form "move a onto b"
    // Convert character to number
    a = command[5] - '0';
    b = command[command.length() - 1] - '0'; 
}

// ------------------------------------------------------------------------------------------------
// This function prints the final result. This pops the element of the Vector
// It prints and extra ',' at the end.
// ------------------------------------------------------------------------------------------------
void printBoard(vector< stack<uint32_t> >& robotWorld)
{
    DEBUG_MSG("Robot World" << endl);
    for (uint32_t i = 0; i < robotWorld.size(); i++)
    {
        cout << i << ": ";
        // Have to empty the stack for printing it
        
        // Taking care of the last ',' by print the first element and then adding
        // ',' to the front and print the rest of the elements
        if (!robotWorld[i].empty())
        {
            cout << robotWorld[i].top();
            robotWorld[i].pop();
        }

        while(!robotWorld[i].empty())
        {
            cout << ", " << robotWorld[i].top();
            robotWorld[i].pop();
        }

        cout << endl;
    }

    cout << endl;
}

// ------------------------------------------------------------------------------------------------
// This function checks whether 'a' and 'b' are on the same Stack to decide if it is No Op.
// ------------------------------------------------------------------------------------------------
bool isAandBonSameStack(unordered_map<uint32_t, uint32_t>& blockIndex,
                        uint32_t a,
                        uint32_t b,
                        uint32_t& aIdx,
                        uint32_t& bIdx)
{
    auto itr0 = blockIndex.find(a);
    if (itr0 != blockIndex.end())
    {
        aIdx = itr0->second;
    }
    else
    {
        blockIndex[a] = a;
        aIdx = a;
    }

    // TODO: Add a function for cleaner code
    auto itr1 = blockIndex.find(b);
    if (itr1 != blockIndex.end())
    {
        bIdx = itr1->second;
    }
    else
    {
        blockIndex[b] = b;
        bIdx = b;
    }

    return (aIdx == bIdx);
}

// ------------------------------------------------------------------------------------------------
// This function moves extra block back to their original position
// ------------------------------------------------------------------------------------------------
void moveOtherBlocksToInitialPosition(vector< stack<uint32_t> >& robotWorld,
                                      unordered_map<uint32_t, uint32_t>& blockIndex,
                                      uint32_t num,
                                      uint32_t numIdx)
{
    while (!robotWorld[numIdx].empty() > 0 && robotWorld[numIdx].top() != num)
    {
        // Move the element that is on the top of stack to its initial position
        uint32_t tmp = robotWorld[numIdx].top();
        robotWorld[tmp].push(tmp);
        blockIndex[tmp] = tmp;

        robotWorld[numIdx].pop();
    }
}

// ------------------------------------------------------------------------------------------------
// This function performs the actual moving of the blocks
// ------------------------------------------------------------------------------------------------
void moveBlock(vector< stack<uint32_t> >& robotWorld,
               unordered_map<uint32_t, uint32_t>& blockIndex,
               uint32_t a,
               uint32_t b,
               uint32_t aIdx,
               uint32_t bIdx)
{
    // Check if a and b are on top
    // If not on top, move to respective index and update hash till a and b comes to top
    // Once a and b are at the top, move a ontop b

    // Check if the Vector is empty before checking the top(). This could result in SEG Fault
    DEBUG_MSG("1. a: " << a << "; " << aIdx << "; b: " << b << "; bIdx: " << bIdx << endl);

    moveOtherBlocksToInitialPosition(robotWorld, blockIndex, a, aIdx);
    moveOtherBlocksToInitialPosition(robotWorld, blockIndex, b, bIdx);

    // We have made sure 'a' and 'b' are on the top of the stack
    // Time to move 'a' onto 'b'
    // Also update the hash table by Restting 'aIdx' and updating 'bIdx' with 'a'
    // Eg: move 4 onto 7
    //     1. Find where '7' is present and push 4 there
    //     2. Update '4's map to point to 7
    robotWorld[bIdx].push(a);
    blockIndex[a] = bIdx;

    if (!robotWorld[aIdx].empty())
    {
        robotWorld[aIdx].pop();
    }
    DEBUG_MSG("5. a: " << a << "; " << aIdx << "; b: " << b << "; bIdx: " << bIdx << endl);
}

// ------------------------------------------------------------------------------------------------
// This is the main functions that performs the Robot move of the blocks
// ------------------------------------------------------------------------------------------------
void startGame(const string& str,
               vector< stack<uint32_t> >& robotWorld,
               unordered_map<uint32_t, uint32_t>& blockIndex)
{
    uint32_t a;
    uint32_t b;
    uint32_t aIdx;
    uint32_t bIdx;
    bool isSameStack = false;

    // Get a and b from the command
    parseInput(str, a, b);

    // Check if 'a' and 'b' are on the same stack
    isSameStack = isAandBonSameStack(blockIndex, a, b, aIdx, bIdx);

    // If 'a' and 'b' are on the same stack, then it is a No Op
    if (!isSameStack)
    {
        moveBlock(robotWorld, blockIndex, a, b, aIdx, bIdx);
    }
}

// ------------------------------------------------------------------------------------------------
// This function initializes the Vector with initial values.
// ------------------------------------------------------------------------------------------------
void initializeRobotWorld(vector< stack<uint32_t> >& robotWorld,
                          unordered_map<uint32_t, uint32_t>& blockIndex)
{
    for (uint32_t i = 0; i < robotWorld.size(); i++)
    {
        robotWorld[i].push(i);
        blockIndex[i] = i;
    }
}

// ------------------------------------------------------------------------------------------------
// Main function 
// ------------------------------------------------------------------------------------------------
int main()
{
    string str;
    string line;

    // IMP: Give the size for the vector so that it can be accessed using Index
    vector< stack<uint32_t> > robotWorld (8);
    unordered_map<uint32_t, uint32_t> blockIndex;

    initializeRobotWorld(robotWorld, blockIndex);
    // Discard the leading whitespace
    while (getline(cin >> std::ws, line))
    {
        if (line != "quit")
        {
            startGame(line,  robotWorld, blockIndex);
            DEBUG_MSG("Done Game" << endl);
        }
        else
        {
            DEBUG_MSG("Quit Game" << endl);
            break;
        }
    }

    // Go through the Vector, format and print it as output
    printBoard(robotWorld);

    /*
    {
        // Test Case:
        // Change blockIndex robotWorld
        startGame("move 7 onto 1", robotWorld, blockIndex);
        startGame("move 4 onto 7", robotWorld, blockIndex);
        startGame("move 2 onto 3", robotWorld, blockIndex);
        startGame("move 7 onto 5", robotWorld, blockIndex);
        startGame("move 0 onto 5", robotWorld, blockIndex);
        startGame("move 6 onto 2", robotWorld, blockIndex);
        startGame("move 3 onto 6", robotWorld, blockIndex);
        startGame("move 5 onto 3", robotWorld, blockIndex);
    }
    */

    cout << endl;
    return 0;
}
