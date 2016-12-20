#include <iostream>
#include <iostream>
#include <cassert>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>        // std::fill_n, std::reverse, std::swap
#include <queue>            // Priority Queue
#include <typeinfo>         // typeid
#include <vector>
#include <cmath>            // ciel
#include <cstring>          // memset
#include <functional>       // std::function

using namespace std;

struct dirEntry
{
    uint8_t     dirType;                // Type of the sub directory.
    int8_t      fileName[9];            // Name of the sub directory.
    uint16_t    lastBlockUsedBytes;     // This will be 512 for a directory.
                                        // For a file it will range from 5 - 512 OR 0 - 504
                                        // For a file it will tell where the last entry of
                                        // the file is stored.
    uint32_t    actualBlockNumber;      // This will range between 1 to 100 to show the
                                        // block number that has the sub directory.
};

struct directory
{
    int32_t    prevBlock;
    int32_t    nextBlock;
    int32_t    firstUnusedBlock;
    uint32_t   fillerChar;
    dirEntry   dirEntries[31];
};

struct file
{
    int32_t    prevBlock;
    int32_t    nextBlock;
    uint8_t    fileData[504];
};

union block
{
    directory   blockDir;
    file        blockFile;
};

struct disk
{
    block blocks[100];
    //directory blocks[100];
} myDisk;

int main()
{
    cout << sizeof(int) << endl;
    cout << sizeof(char) << endl;

    int a = -1;
    if (a)
    {
        cout << "-1 is True" << endl;
    }
    else
    {
        cout << "-1 is False" << endl;
    }

    cout << "Struct Size" << endl;
    cout << sizeof(myDisk) << endl;
    cout << sizeof(file) << endl;
    cout << sizeof(directory) << endl;

    cout << endl;
    return 0;
}
