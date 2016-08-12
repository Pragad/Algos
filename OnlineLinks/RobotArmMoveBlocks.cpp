#include<iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>
using namespace std;

void parseInput(string command, uint32_t& a, uint32_t& b)
{
    // Since the input will be on the exact format without incorrect commands
    // Assumption: Directly accessing the corresponding to the index
    // Command is of form "move a onto b"
    // Convert character to number
    a = command[5] - '0';
    b = command[command.length() - 1] - '0'; 
}

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

    // TODO: Cleanup code in the form of a function
    cout << "Top A: " << robotWorld[aIdx].top() << "; a: " << a << endl;
    while (robotWorld[aIdx].top() != a)
    {
        uint32_t tmp = robotWorld[aIdx].top();
        robotWorld[tmp].push(tmp);

        blockIndex[tmp] = tmp;
    }

    cout << "Top B: " << robotWorld[bIdx].top() << "; b: " << b << endl;
    while (robotWorld[bIdx].top() != b)
    {
        uint32_t tmp = robotWorld[bIdx].top();
        robotWorld[tmp].push(tmp);

        blockIndex[tmp] = tmp;
    }

    // We have made sure A and B are on the top of the stack
    // Time to move A onto B
    cout << "Time to move" << endl;
}

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
    cout << "Str: " << str << "; a: " << str[5] << "; b: " << str[str.length() - 1] << "; aIdx: " << aIdx << "; bIdx: " << bIdx  << "; Same Stack: " << isSameStack << endl;
    if (!isSameStack)
    {
        cout << "Let's move" << endl;
        moveBlock(robotWorld, blockIndex, a, b, aIdx, bIdx);
        cout << "move over" << endl;
    }
    else
    {
        // 'a' and 'b' are on the same stack. So No Op
    }
    cout << "Done Move Fn" << endl;
}

int main()
{
    string str;
    unordered_map<uint32_t, uint32_t> blockIndex;
    vector< stack<uint32_t> > robotWorld;

    string line;
    while (getline(cin, line))
    {
        if (line != "quit")
        {
            cout << "Start Game" << endl;
            startGame(line,  robotWorld, blockIndex);
            cout << "Done Game" << endl;
        }
        else
        {
            cout << "Quit Game" << endl;
            break;
        }

        cin.clear();
        cin.ignore(10000,'\n'); 
    }

    // Go through the Vector, format and print it as output
    cout << endl;

    /*
    {
        // Test Case:
        // Change blockIndex robotWorld
        startGame("move 5 onto 1", blockIndex, robotWorld);
        startGame("move 7 onto 1", blockIndex, robotWorld);
        startGame("move 7 onto 1", blockIndex, robotWorld);
        startGame("move 7 onto 1", blockIndex, robotWorld);
        startGame("move 7 onto 1", blockIndex, robotWorld);
        startGame("move 7 onto 1", blockIndex, robotWorld);
        startGame("move 7 onto 1", blockIndex, robotWorld);
        startGame("move 7 onto 1", blockIndex, robotWorld);
    }
    */
}
