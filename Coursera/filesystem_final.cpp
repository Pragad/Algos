#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#ifdef _WIN32
typedef char 	                int8_t;
typedef unsigned char 	        uint8_t;
typedef unsigned short int 	    uint16_t;
typedef int 	                int32_t;
typedef unsigned int 	        uint32_t;
typedef unsigned long long int 	uint64_t;
#include <strstream>
#else
#include <stdint.h>
#include <sstream>
#endif

//-------------------------------------------------------------------------------------------------
bool checkIfFullPathExists(string strFileName,
                           int& tmpBlockNum,
                           int& retParentBlockNum);

void printList(struct node* head);
int32_t pop(struct node** head);
void insert(struct node* &head, uint32_t value);
void buildUnusedBlocksList();
std::vector<std::string> &strSplit(const std::string &s,
                                   char delim,
                                   std::vector<std::string> &elems);
std::vector<std::string> strSplit(const std::string &s,
                                  char delim);
int getUnusedBlockFromList();
int getParentsLastSubFileBlock(uint32_t blockNum);
int getParentsLastSubdirBlock(uint32_t blockNum);
bool doesDirHaveAnyFiles(uint32_t blockNum);
bool doesDirHaveAnyDirs(uint32_t blockNum);
bool isDirAllFree(uint32_t blockNum);
void updateParentBlock(uint32_t parentBlockNum,
                       uint8_t  availableIndex,
                       uint32_t childBlockNum,
                       uint8_t  fileDirType,
                       string   strFileDirName);
void updateNextBlock(uint32_t lastBlockNum, uint32_t newBlockNum);
int getBlockNumber(uint32_t blockNum, const char* name);
bool countIfParentHas31(uint32_t blockNum);
bool isIndexFree(uint32_t blockNum, uint8_t index);
int getFirstFreeFrom31(uint32_t blockNum);
void updategDetails(int k,
                    int blockNumber,
                    string blockName,
                    int parentBlockNum,
                    string parentBlockName);
void createRootDirectory();
void createDirectoryEntry(uint32_t blkNum, uint32_t prevBlk = 0);
bool checkIfFilePresentInDir(uint32_t blockNum, string strDirFileName);
bool checkIfDirPathExists(string strDirFileName);
int getIndexFromGlobalList(int curBlockNum);
void printGlobalList();
int getFirstFreeInGlobalList();
string getGlobalCurrName (int currBlockNum);
string getGlobalParentName (int parentBlockNum);
int getGlobalParentNumFromChild (int currBlockNum);
int getGlobalBlockNum (string name, string parentName);
int getGlobalParentBlockNum (string &name, string &parentName);
int createDirectoryEntrySupplements(int currBlockNum,
                                    string currBlockName,
                                    int parentBlockNumber,
                                    string parentBlockName,
                                    string targetBlockName);
int traversePathFindCurrAndParentBlkNum(string strFileName,
                                        int& tempBlockNumber,
                                        int& parentBlockNumber,
                                        string& tempChild);
void createFileOrDirectoryEntry(uint32_t blkNum, uint32_t prevBlk, uint8_t fileDirType);
void createDirPreProcess(string strFileName);
void createFileEntry(uint32_t blkNum, uint32_t prevBlk);
void createFilePreProcess(string strDirFileName);
void createFileOrDirectory(string strType, string strFileName);
void openFile(string strMode, string strFileName);
void closeFile();
void readFile(string strNumBytes);
void writeFile(string strNumBytes, string strData);
void seekFile(string strBase, string strOffset);
int getIndexOfBlockFromParent(int curBlockNum, int parBlockNum);
uint8_t checkIfFileOrDir(int curBlockNum, int parBlockNum);
bool checkIfFullPathExists(string strFileName,
                           int& tmpBlockNum,
                           int& retParentBlockNum);
bool checkIfFullPathExistsIncNext(string strFileName,
                                  int& tmpBlockNum,
                                  int& retParentBlockNum);

int deleteUpdateParent(uint32_t parentBlockNum, uint32_t curBlockNum);
int deleteUpdateGlobalList(uint32_t curBlockNum);
void deleteUpdateLinkedList(uint32_t curBlockNum);
void deleteDirPreProcess(int parentBlockNum, int curBlockNum);
void deleteFilePreProcess(int parentBlockNum, int curBlockNum);
void deleteFileOrDirectory(string strFileName);
void parseInputCommand(string inputCmd);
void getInputCommand();
bool isEntryAtLeaf(int curBlockNum);
bool isEntryHasNext(uint32_t curBlockNum);
void getChildBlockNumbers(int& curBlockNum, int& parentBlockNum);
void getNextPtrBlockNumbers(int& curBlockNum, int& parentBlockNum);

// Read Write Funtions:

void write(int blockno, int noOfBytes, int readPointer, char input[], int startIndex);
int findFreeParent (int pBlockNum);
int findPointerBlock (int quotient, int blockNum);
void createFileParentDirEntry (int blockNum, int freeindex, int fBlockNum);
void updateFileParentDirEntry (int blockNum, int iEntry, int usedBytes);
int findEntryFromParent(int pBlockNum, int blockno);
int findFileMaxBytes (int pBlockNum, int finalSize, int i);
int findIteration (int remain, int toUpdate);
void updateFileNext (int iBlock, int tempBlockNum);

//-------------------------------------------------------------------------------------------------
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
} myDisk;

struct trackCurrent
{
    int parentBlockNumber;
    int currentBlockNumber;
    int numberOfBytesUsed;
    int seekPointer;
    int readPointer;
    int writePointer;
    bool status;
    
    trackCurrent()
    {
        parentBlockNumber = -1;
        currentBlockNumber = -1;
        numberOfBytesUsed = -1;
        seekPointer = -1;
        readPointer = -1;
        writePointer = -1;
        status = false;
    }
} readStruct;

struct generalBlockDetails
{
    int currentBlockNum;
    int parentBlockNum;
    string currentName;
    string parentName;
    bool isUsed;

    generalBlockDetails()
    {
        isUsed = false;
    }
} gDetails[100]; 

uint32_t globalConstant;

static const uint32_t MAX_DIR_ENTRIES = 3;

//-------------------------------------------------------------------------------------------------
//                  LINKED LIST OF UNUSED BLOCKS
//-------------------------------------------------------------------------------------------------
struct node
{
    int data;
    struct node* next;
} *head;

void printList(struct node* head)
{
    cout << endl << "LINKED LIST OF FREE BLOCKS" << endl;
    if(head == nullptr)
    {
        cout<<"No elements present right now"<<endl;
    }
    while(head != nullptr)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
    cout << endl;
}

int32_t pop(struct node** head)
{
    if (*head != NULL)
    {
        uint32_t value = (*head)->data;
        struct node *temp;
        temp = *head;
        free (*head);
        *head = temp->next;
        return value;
    }
    return -1;
}

void insert(struct node* &head, uint32_t value)
{
    struct node* newNode;
    newNode = new node();
    newNode->data = value;
    newNode->next = nullptr;
    struct node* prev;
    struct node* temphead;
    temphead = head;
    prev = temphead;
    if(temphead != nullptr)
    {
        temphead = temphead->next;
    }
    if(prev == nullptr)
    {
        head = newNode;
    }
    else if(prev->data > value)
    {
        newNode->next = prev;
        head = newNode;
    }
    else if(prev->data < value)
    {
        while(prev->next != nullptr)
        {
            if(temphead->data > value)
            {
                newNode->next = prev->next;
                prev->next = newNode;
                break;
            }
            else if(temphead->data < value)
            {
                prev = prev->next;
                temphead = temphead->next;
            }
        }
        if(prev->next == nullptr)
        {
            prev->next = newNode;
        }
    }
}

void buildUnusedBlocksList()
{
    head = nullptr;
    for (uint8_t i = 1; i < 100; i++)
    {
        insert(head, i);
    }
}

// END OF LINKED LIST
//-------------------------------------------------------------------------------------------------

// strSplit()
//      This functions splits the input name by '\' and put it in a char array.
//
//      Input: String, delimitor
std::vector<std::string> &strSplit(const std::string &s,
                                   char delim,
                                   std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> strSplit(const std::string &s,
                                  char delim)
{
    std::vector<std::string> elems;
    strSplit(s, delim, elems);
    return elems;
}

int getUnusedBlockFromList()
{
    return (pop(&head));
}

// TRAVERSAL:
// We need to search only the first level inside a directory. We will always have the
// full path starting from the ROOT.
// getBlockNumber(name) - Given a name of a child directory, return its block number
//      by searching thourgh the 31 entries.
//
// create Child. So at the point parent will know what values the child is going to take 
// Parent should get the block number by checked the Global Unused block list.
//
// countIfParentHas31 - this will check if the parent directory has room to create a child
// getFirstFreeFrom31 - This is get the first index where we can put the child directory 
//      isIndexFree - Have a helper function to tell if an index is free or not just by
//      looking at that index.
// getFirstUnusedBlock() - Traverse the global list and get the first unused block.
// getParentsLastSubdirBlock() - Get the block number of the last sub directory in the
// parent.
// update nextBlock() in the block got from above.
// createChild(blockNumber, prevBlock, nextBlock); - Next block will be 0 or -1.
//        PrevBlock will point to the block number got from getParentsLastSubdirBlock()


// getParentsLastSubdirBlock()
//      This function returns the last subdirectory block inside a parent directory.
//      This is used to update the next field of the last subdirectory block.
//
//      Input   :  Block number of the parent directory
//      Output  :  Block number of the child whose nextBlock is 0.
int getParentsLastSubFileBlock(uint32_t blockNum)
{
    int32_t childBlockNum = -1;
    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        // Check for child block only if the dirType is not FREE and dirType is
        // NOT a directory.
        if ((myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'F') &&
           (myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'D'))
        {
            childBlockNum = myDisk.blocks[blockNum].blockDir.dirEntries[i].actualBlockNumber;
            if (myDisk.blocks[childBlockNum].blockDir.nextBlock == 0)
            {
                break;
            }
        }
    }

    return childBlockNum;
}

// getParentsLastSubdirBlock()
//      This function returns the last subdirectory block inside a parent directory.
//      This is used to update the next field of the last subdirectory block.
//
//      Input   :  Block number of the parent directory
//      Output  :  Block number of the child whose nextBlock is 0.
int getParentsLastSubdirBlock(uint32_t blockNum)
{
    int32_t childBlockNum = -1;
    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        // Check for child block only if the dirType is not FREE.
        if ((myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'F') &&
           (myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'U'))
        {
            childBlockNum = myDisk.blocks[blockNum].blockDir.dirEntries[i].actualBlockNumber;
            if (myDisk.blocks[childBlockNum].blockDir.nextBlock == 0)
            {
                break;
            }
        }
    }

    return childBlockNum;
}

// doesDirHaveAnyFiles()
//      This function checks and tells if a directory is completely free.
//
//      Input   :
//      Output  :
bool doesDirHaveAnyFiles(uint32_t blockNum)
{
    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        // Check for child block only if the dirType is not FREE.
        if ((myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'F') &&
           (myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'D'))
        {
            return true;
        }
    }

    return false;
}

// doesDirHaveAnyDirs()
//      This function checks and tells if a directory is completely free.
//
//      Input   :
//      Output  :
bool doesDirHaveAnyDirs(uint32_t blockNum)
{
    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        // Check for child block only if the dirType is not FREE.
        if ((myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'F') &&
           (myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'U'))
        {

            return true;
        }
    }
    return false;
 }
// isDirAllFree()
//      This function checks and tells if a directory is completely free.
//      This can be deleted.
//
//      Input   :
//      Output  :
bool isDirAllFree(uint32_t blockNum)
{
    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        // Check for child block only if the dirType is not FREE.
        if (myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'F')
        {

            return false;
        }
    }
    return true;
 }


// updateParentBlock()
//      This function updates the parent when a child directory is created.
//
//      Input   :
//      Output  :
void updateParentBlock(uint32_t parentBlockNum,
                       uint8_t  availableIndex,
                       uint32_t childBlockNum,
                       uint8_t  fileDirType,
                       string   strFileDirName)
{
    myDisk.blocks[parentBlockNum].blockDir.dirEntries[availableIndex].actualBlockNumber = childBlockNum;
    myDisk.blocks[parentBlockNum].blockDir.dirEntries[availableIndex].dirType = fileDirType;
    strFileDirName.copy((char *)myDisk.blocks[parentBlockNum].blockDir.dirEntries[availableIndex].fileName, 9);

    if (fileDirType == 'D')
    {
        myDisk.blocks[parentBlockNum].blockDir.dirEntries[availableIndex].lastBlockUsedBytes = 512;
    }
    else
    {
        myDisk.blocks[parentBlockNum].blockDir.dirEntries[availableIndex].lastBlockUsedBytes = 0;
    }
}

// ()
//      This function
//
//      Input   :
//      Output  :
void updateNextBlock(uint32_t lastBlockNum, uint32_t newBlockNum)
{
    myDisk.blocks[lastBlockNum].blockDir.nextBlock = newBlockNum;
}

// ()
//      This function get the block number of the child directory given the block number
//      of the parent directory.
//
//      Input   :
//      Output  :
int getBlockNumber(uint32_t blockNum, const char* name)
{
    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        // Check for file names only if the dirType is not FREE.
        if (myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'F')
        {
            if (strcmp((char *)myDisk.blocks[blockNum].blockDir.dirEntries[i].fileName, name) == 0)
            {
                return myDisk.blocks[blockNum].blockDir.dirEntries[i].actualBlockNumber;
            }
        }
    }

    // Error Case: 
    return -1;
}

// ()
//      This function returns False if Parent has even one space available.
//
//      Input   :
//      Output  :
bool countIfParentHas31(uint32_t blockNum)
{
    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        if (myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType == 'F')
        {
            return false;
        }
    }
    return true;
}

// isIndexFree()
//      This function tells if the index pointed by the sub directory is free or not.
//
//      Input:   Block number of the current (parent directory).
//      Input:   Index of the sub directory that needs to be checked.
//      Output:  If sub directory pointed by Index is free or not.
bool isIndexFree(uint32_t blockNum, uint8_t index)
{
    return (myDisk.blocks[blockNum].blockDir.dirEntries[index].dirType == 'F');
}

// getFirstFreeFrom31()
//      This function returns the first available index where the child directory can
//      be created.
//
//      Input   :
//      Output  :
int getFirstFreeFrom31(uint32_t blockNum)
{
    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        if (isIndexFree(blockNum, i))
        {
            return i;
        }
    }

    // Error Case:
    return -1;
}

void updategDetails(int k,
                    int blockNumber,
                    string blockName,
                    int parentBlockNum,
                    string parentBlockName)
{
    gDetails[k].currentBlockNum = blockNumber;
    gDetails[k].currentName = blockName;

    gDetails[k].parentBlockNum = parentBlockNum;
    gDetails[k].parentName = parentBlockName;
    gDetails[k].isUsed = true;
}

// createRootDirectory()
//      This function creates a root directory to start the program.
//      It also assigns all blocks inside it to F.
//
//      Input   : None
//      Output  : None
void createRootDirectory()
{
    myDisk.blocks[0].blockDir.prevBlock = 0;
    myDisk.blocks[0].blockDir.nextBlock = 0;
    myDisk.blocks[0].blockDir.firstUnusedBlock = 0;
    myDisk.blocks[0].blockDir.fillerChar = 0;

    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        // Set all entires inside this directory to be Free.
        myDisk.blocks[0].blockDir.dirEntries[i].dirType = 'F';

        // The below number should be got when creating the sub directory.
        // It should get updated when the sub directory is created. 
        // This number is the block[INDEX] where the sub directory is created.
        //myDisk.blocks[0].blockDir.dirEntries[i].actualBlockNumber = 1;
    }

    // Also update the global table for root entry.
    updategDetails(0, // block num
                   0,
                   "root",
                   -1,
                   "-");
    globalConstant = globalConstant + 1;

}

void createFileOrDirectoryEntry(uint32_t blkNum, uint32_t prevBlk, uint8_t fileDirType)
{
    if (fileDirType == 'D')
    {
        createDirectoryEntry(blkNum, prevBlk);
    }
    else if (fileDirType == 'U')
    {
        createFileEntry(blkNum, prevBlk);
    }
    else
    {
        cout << "Invalid Type Given" << endl;
    }
}

// createDirectoryEntry()
//      This function creates a directory entry to start the program.
//      It also assigns all blocks inside it to F.
//
//      Input   : prevBlk is a default parameter with 0
//      Output  : None
void createDirectoryEntry(uint32_t blkNum, uint32_t prevBlk)
{
    myDisk.blocks[blkNum].blockDir.prevBlock = prevBlk;
    myDisk.blocks[blkNum].blockDir.nextBlock = -1;
    myDisk.blocks[blkNum].blockDir.firstUnusedBlock = 0;
    myDisk.blocks[blkNum].blockDir.fillerChar = 0;

    for (uint8_t i = 0; i < 32; i++)
    {
        // Set all entires inside this directory to be Free.
        myDisk.blocks[blkNum].blockDir.dirEntries[i].dirType = 'F';
    }
}

// checkIfFilePresentInDir()
//      This function check if the given file name already exists in this block
//
//      Input   : 
//      Output  : 
bool checkIfFilePresentInDir(uint32_t blockNum, string strDirFileName)
{
    for (uint8_t i = 0; i < 32; i++)
    {
        if (myDisk.blocks[blockNum].blockDir.dirEntries[i].dirType != 'F')
        {
            if (strcmp((char *)myDisk.blocks[blockNum].blockDir.dirEntries[i].fileName, strDirFileName.c_str()) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

// checkIfDirPathExists()
//      This function check if the given path (excluding last token) exists
//
//      Input   : None
//      Output  : None
bool checkIfDirPathExists(string strDirFileName)
{
    std::vector<std::string> vecFileNameTokens;

    vecFileNameTokens = strSplit(strDirFileName, '/');

    int32_t  tmpBlockNum = 0;
    uint32_t parentBlockNum = 0;

    // Give size()-1 to exlude to last token
    for (uint8_t i = 0; i < vecFileNameTokens.size() - 1; i++)
    {
        tmpBlockNum = getBlockNumber(parentBlockNum, vecFileNameTokens[i].c_str()); 

        // If -1 is returned then the directory does not exist. Return false.
        if (tmpBlockNum == -1)
        {
            return false;
        }
        else
        {
            parentBlockNum = tmpBlockNum;
        }
    }

    return true;
}

int getIndexFromGlobalList(int curBlockNum)
{
    for (uint32_t i = 0; i < 100; i++)
    {
        if (gDetails[i].isUsed)
        {
            if (gDetails[i].currentBlockNum == curBlockNum)
            {
                return i;
            }
        }
    }

    return -1;
}

void printGlobalList()
{
    cout << "GLOBAL LIST THAT TRACKS ALL ELEMENTS" << endl;
    for (uint32_t i = 0; i < 100; i++)
    {
        if (gDetails[i].isUsed)
        {
            int tmpIndex = getIndexOfBlockFromParent(gDetails[i].currentBlockNum, gDetails[i].parentBlockNum);

            cout << i << ": " << "CBN: " << setw(2) << gDetails[i].currentBlockNum \
            << " - " << setw(9) << gDetails[i].currentName << "; Type: " << \
            myDisk.blocks[gDetails[i].parentBlockNum].blockDir.dirEntries[tmpIndex].dirType << \
            "; Index: " << setw(3) << tmpIndex << \
            " ; Prev: " << setw(3) << \
            myDisk.blocks[gDetails[i].currentBlockNum].blockDir.prevBlock << \
            " ; Next: " << setw(3) << \
            myDisk.blocks[gDetails[i].currentBlockNum].blockDir.nextBlock << \
            " ; PBN: " <<  setw(2) << gDetails[i].parentBlockNum << " - " << \
            setw(9) << gDetails[i].parentName << endl;
        }
    }
    cout << endl;
}

void printTrackStruct()
{
    cout << "TRACKING STRUCT Pbn: " << readStruct.parentBlockNumber << "; Cbn: " << \
         readStruct.currentBlockNumber  << "; # Bytes: " << readStruct.numberOfBytesUsed << "; SkPtr: " << readStruct.seekPointer << "; RdPtr: " << readStruct.readPointer << "; WrPtr: " << readStruct.writePointer << "; Stat: " << readStruct.status << endl;
}

void printFile(int blockNum, int numBytes)
{
    /*
    cout << "***FILE DATA***" << endl;
    for (uint32_t i = 0; i < numBytes; i++)
    {
        cout << myDisk.blocks[blockNum].blockFile.fileData[i] << " ";
    }
    cout << endl;
    */
}

int getFirstFreeInGlobalList()
{
    for (uint32_t i = 0; i < 100; i++)
    {
        if (!gDetails[i].isUsed)
        {
            return i;
        }
    }

    return -1;
}

string getGlobalCurrName (int currBlockNum)
{
    for (uint32_t i = 0; i < globalConstant; i++)
    {
        if(gDetails[i].currentBlockNum == currBlockNum)
        {
            return gDetails[i].currentName;
        }
    }

    return "";
}

string getGlobalParentName (int parentBlockNum)
{
    for (uint32_t i = 0; i < globalConstant; i++)
    {
        if(gDetails[i].parentBlockNum == parentBlockNum)
        {
            return gDetails[i].parentName;
        }
    }

    return "";
}

int getGlobalParentNumFromChild (int currBlockNum)
{
    for (uint32_t i = 0; i < globalConstant; i++)
    {
        if (gDetails[i].isUsed &&
            gDetails[i].currentBlockNum == currBlockNum)
        {
            return gDetails[i].parentBlockNum;
        }
    }

    return -1;
}

int getGlobalBlockNum (string name, string parentName)
{
    for(uint32_t i = 0; i < globalConstant; i++)
    {
        if (gDetails[i].currentName == name && gDetails[i].parentName == parentName)
        {
            return gDetails[i].currentBlockNum;
        }
    }
    return -1;
}

int getGlobalParentBlockNum (string &name, string &parentName)
{
    for (uint32_t i = 0; i < globalConstant; i++)
    {
        if (gDetails[i].currentName == name && gDetails[i].parentName == parentName)
        {
            return gDetails[i].parentBlockNum;
        }
    }

    return -1;
}

int createFileOrDirEntrySupplements(int currBlockNum,
                                    string currBlockName,
                                    int parentBlockNumber,
                                    string parentBlockName,
                                    string targetBlockName,
                                    uint8_t fileDirType)
{
    bool condition = true;
    int targetBlockNum;
    int availIndex;

    if (currBlockNum != -1)
    {
        availIndex = getFirstFreeFrom31(currBlockNum);
        targetBlockNum = getUnusedBlockFromList();
        if (targetBlockNum != -1)
        {
            while (condition)
            {
                //cout << "ANUP: 3. TarBlk: " << targetBlockNum << "; AvailIdx: " << availIndex << endl;
                if (availIndex != -1)
                {
                    createFileOrDirectoryEntry(targetBlockNum,
                                               -1, // Don't have to update the previous pointer.
                                               fileDirType);

                    updateParentBlock(currBlockNum,
                                      (uint8_t)availIndex,
                                      targetBlockNum,
                                      fileDirType,
                                      targetBlockName);

                    // k will have the first free entry in the Global table.
                    int k = getFirstFreeInGlobalList();
                    //cout << "ANUP: 4. k: " << k << "; tbName: " << targetBlockName \
                         << "; cbn: " << currBlockNum << "; cbname: " << currBlockName \
                         << endl;

                    // "k == -1" is unlikely to happen. So once we are here,
                    // while will EXIT for sure.
                    if (k != -1)
                    {
                        updategDetails(k,
                                       targetBlockNum,
                                       targetBlockName,
                                       currBlockNum,
                                       getGlobalCurrName(currBlockNum));
//                                       currBlockName);

                        globalConstant = globalConstant + 1;
                        condition = false;

                        // Print the global list for verification.
                        //printGlobalList();
                    }
                }
                else
                {
                    // Over here we have more than MAX DIR ENTRIES.
                    // 1. So we should try creating in a parent directory or Next dir
                    // 2. Update Curren't Next
                    // TempBlockNumber got updated to a new number that has available
                    // space for 31 entries.

                    //cout << "ANUP: 5. Cbn: " << currBlockNum << "; nxtBlk: " << myDisk.blocks[currBlockNum].blockDir.nextBlock << endl;
                    if ((myDisk.blocks[currBlockNum].blockDir.nextBlock) == -1)
                    {
                        // First we should create a DUMMY directory
                        int tempCurrBlkNum = currBlockNum;
                        if (getGlobalParentNumFromChild(currBlockNum) != -1)
                        {
                            //cout << "ANUP: 6. Par: " << parentBlockNumber << endl;
                            parentBlockNumber = getGlobalParentNumFromChild(currBlockNum);
                        }
                        else
                        {
                            cout << "Exit the program as parent dir does not exist" <<endl;
                            return -1;
                        }

                        // We have a targetblock number already. So use it for the dummy directory.
                        currBlockNum = targetBlockNum;
                        availIndex = getFirstFreeFrom31(parentBlockNumber);

                        // We are NOT recursively going to the parent to create another
                        // directory that will hold our target dir/file.
                        if (availIndex == -1)
                        {
                            cout << "Parent has no available space" << endl;
                            return -1;
                        }

                        createDirectoryEntry(targetBlockNum,
                                             tempCurrBlkNum); // Update the previous pointer.

                        updateParentBlock(parentBlockNumber,
                                          (uint8_t)availIndex,
                                          targetBlockNum,
                                          'D',
                                          "NULL");

                        // k will have the first free entry in the Global table.
                        int k = getFirstFreeInGlobalList();
                        //cout << "ANUP: 7. Cbn: " << currBlockNum << "; Idx: " << availIndex << "; k: " << k << endl;

                        // This is unlikely to happen. So once we are here, while will 
                        // EXIT for sure.
                        if (k != -1)
                        {
                            updategDetails(k,
                                           targetBlockNum,
                                           "NULL",
                                           parentBlockNumber,
                                           getGlobalCurrName(parentBlockNumber));

                            globalConstant = globalConstant + 1;
                            //cout << "Dummy Directory has been created"<<endl;
                        }

                        // Update the Curren't next to point to the dummy directory created.
                        myDisk.blocks[tempCurrBlkNum].blockDir.nextBlock = currBlockNum;

                        // Get new values for the directory.
                        targetBlockNum = getUnusedBlockFromList();
                        currBlockName = "NULL";

                        //cout << "ANUP: 8: " << "TmpCbn: " << tempCurrBlkNum << "; Cbn: " << currBlockNum << "; Pbn: " << parentBlockNumber << "; Tbnanme: " << targetBlockName << "; Tbnum: " << targetBlockNum << endl;
                    }
                    else
                    {
                        currBlockName = "NULL";
                        currBlockNum = myDisk.blocks[currBlockNum].blockDir.nextBlock;
                        //cout << "ANUP 9. Cbn: " << currBlockNum << "; Pbn: " << \
                            getGlobalParentNumFromChild(currBlockNum) << endl;
                        if (getGlobalParentNumFromChild(currBlockNum) != -1)
                        {
                            parentBlockNumber = getGlobalParentNumFromChild(currBlockNum);
                            availIndex = getFirstFreeFrom31(currBlockNum);
                        }
                        else
                        {
                            cout << "Exit the program as parent dir does not exist" << endl;
                        }
                    }
                }
            }
        }
        else 
        {
            cout << "Cannot create. The File System memory is full!!"<<endl;
            return -1;
        }
    }
    
    //cout << "ANUP: 99: " << "Cbn: " << currBlockNum << "; CbnIdx: " << availIndex \
         << "; Pbn: " << parentBlockNumber << "; Tbnum: " << targetBlockNum \
          << "; Tbn: " << targetBlockName << endl;
    return 0;
}

int createDirectoryEntrySupplements(int currBlockNum,
                                    string currBlockName,
                                    int parentBlockNumber,
                                    string parentBlockName,
                                    string targetBlockName)
{
    return createFileOrDirEntrySupplements(currBlockNum,
                                           currBlockName,
                                           parentBlockNumber,
                                           parentBlockName,
                                           targetBlockName,
                                           'D');
}

int traversePathFindCurrAndParentBlkNum(string strFileName,
                                        int& tempBlockNumber,
                                        int& parentBlockNumber,
                                        string& tempChild)
{
    std::vector<std::string> vecFileNameTokens;

    vecFileNameTokens = strSplit(strFileName, '/');
    uint32_t size = vecFileNameTokens.size();
    tempChild = vecFileNameTokens[size - 1];
    string tempParent = vecFileNameTokens[0];

    tempBlockNumber = 0;
    parentBlockNumber = 0;
    int parentTempBlockNumber = 0;
    int nextPtr;
    int nextParentPtr;

    // By the end of the for loop we will have tempBlock and parentBlockNumbers
    // parentTempBlockNumber is used for Iterating. It gets equated to tempBlockNumber.
    // parentBlockNumber will have the actual block number of the parent.
    for (uint32_t i = 0; i < size-1; i++)
    {
        if(parentTempBlockNumber == tempBlockNumber)
        {
            tempBlockNumber = getBlockNumber(parentTempBlockNumber, vecFileNameTokens[i].c_str());
            nextParentPtr = parentTempBlockNumber;
            while(tempBlockNumber == -1)
            {
                // nextPtr will point to the Next Block that could possible have the
                // directory that we are looking for.
                nextPtr = myDisk.blocks[nextParentPtr].blockDir.nextBlock;
                if(nextPtr != -1)
                {
                    // Get the block number where the Directory we are looking for 
                    // is saved.
                    tempBlockNumber = getBlockNumber(nextPtr, vecFileNameTokens[i].c_str());
                    nextParentPtr = nextPtr;
                }
                else
                {
                    // Path doesn't exist in the Next ptr. But it can be present
                    // elsewhere
                    cout << "Path doesn't exist over here."<<endl;
                    break;
                }
            }

            if(tempBlockNumber != -1)
            {
                parentBlockNumber = parentTempBlockNumber;
                // Preparing for next iteration.
                parentTempBlockNumber = tempBlockNumber;
            }
        }
        else
        {
            // Path doesn't exist. So we can error out.
            return -1;
            break;
        }
    }

    // Success
    return 0;
}

void createDirPreProcess(string strFileName)
{
    // a/b/c/d
    // cbn: c
    // pbn: b
    // tbn: d
    int currBlockNumber = 0;
    int parentBlockNumber = 0;
    string currBlockName = "";
    string parentBlockName = "";
    string targetBlockName;

    // Traverse and Find if the parent path exists.
    if (traversePathFindCurrAndParentBlkNum(strFileName, // I/p
                                            currBlockNumber, // O/p
                                            parentBlockNumber, // O/p
                                            targetBlockName) == -1) // O/p
    {
        cout << "Direcotry Path Doesn't Exist" << endl;
        //cout << "ANUP: 1.: " << "Cbn: " << currBlockNumber << "; Pbn: " << parentBlockNumber << "; Tbn: " << targetBlockName << endl;
    }
    else
    {
        if (currBlockNumber >= 0)
        {
            currBlockName = getGlobalCurrName(currBlockNumber);
        }

        if (parentBlockNumber >= 0)
        {
            parentBlockName = getGlobalCurrName(parentBlockNumber);
            //parentBlockName = getGlobalParentName(parentBlockNumber);
        }

        //cout << "ANUP: 2.: " << "Cbn: " << currBlockNumber << ": " \
             << currBlockName << "; Pbn: " << parentBlockNumber << ": " \
             << parentBlockName << "; Tbn: " << targetBlockName << endl;
        createDirectoryEntrySupplements(currBlockNumber,
                                        currBlockName,
                                        parentBlockNumber,
                                        parentBlockName,
                                        targetBlockName);

        cout << "Create Directory: Success" << endl;
        printGlobalList();
    }
}

// createFileEntry()
//      This function creates a directory entry to start the program.
//      It also assigns all blocks inside it to F.
//
//      Input   : None
//      Output  : None
void createFileEntry(uint32_t blkNum, uint32_t prevBlk)
{
    myDisk.blocks[blkNum].blockFile.prevBlock = prevBlk;
    myDisk.blocks[blkNum].blockFile.nextBlock = -1;
}

void createFilePreProcess(string strDirFileName)
{
    std::vector<std::string> vecFileNameTokens;

    vecFileNameTokens = strSplit(strDirFileName, '/');

    int32_t  tmpBlockNum = 0;
    uint32_t parentBlockNum = 0;
    bool     isPathExist = true;
    string   strFileName = vecFileNameTokens[vecFileNameTokens.size() - 1];

    // If strDirFileName.length is greater than strFileName.length(), proceed
    // Else we are creating in the root itself.
    uint32_t remainDirLen = strDirFileName.length() - (strFileName.length() + 1);
    string   remainDirPath = strDirFileName.substr (0, remainDirLen);

    int curBlockNum = 0;
    int parBlockNum = 0;
    string currBlockName = "";
    string parentBlockName = "";

    if (strDirFileName.length() > strFileName.length() && 
        !checkIfFullPathExists(remainDirPath, curBlockNum, parBlockNum))
    {
        //cout << "Path Does NOT Exist; Cbn: " << curBlockNum << "; Pbn: " << parBlockNum << endl;
        cout << "Path Does NOT Exist" <<  endl;
        return;
    }
    else
    {
        // If Length is same we have to check and create in root
        if (strDirFileName.length() == strFileName.length())
        {
            parentBlockNum = 0;
            curBlockNum = 0;
        }

        // Proceed only if this file is not present already
        if (!checkIfFilePresentInDir(parentBlockNum, strFileName))
        {
            if (curBlockNum >= 0)
            {
                currBlockName = getGlobalCurrName(curBlockNum);
            }

            if (parBlockNum >= 0)
            {
                parentBlockName = getGlobalCurrName(parBlockNum);
            }

            createFileOrDirEntrySupplements(curBlockNum,
                                            currBlockName,
                                            parBlockNum,
                                            parentBlockName,
                                            strFileName,
                                            'U');

            cout << "Create File: Success" << endl;
            printGlobalList();
        }
        else
        {
            cout << "The given file name already exists!" << endl;
        }
    }
}

void createFileOrDirectory(string strType, string strFileName)
{
    string inputString;
    char createType;
    int curBlockNum;
    int parBlockNum;

    if (checkIfFullPathExists(strFileName, curBlockNum, parBlockNum))
    {
        //cout << "Path Already Exists; Cbn: " << curBlockNum << "; Pbn: " << parBlockNum << endl;
        cout << "Path Already Exists" << endl;
        return;
    }

    if (strType.compare("U") == 0)
    {
        createType = 'U';
        createFilePreProcess(strFileName);
    }
    else if (strType.compare("D") == 0)
    {
        createType = 'D';
        createDirPreProcess(strFileName);
    }
    else
    {
        cout << " Wrong User Type " << endl;
    }
}

void openFile(string strMode, string strFileName)
{
    int currBlockNumber = 0;
    int parentBlockNumber = 0;
    int noOfBytes = 0;
    string currBlockName = "";
    string parentBlockName = "";
    string targetBlockName;

    // Traverse and Find if the parent path exists.
    if (!checkIfFullPathExistsIncNext(strFileName, currBlockNumber, parentBlockNumber))
    {
        cout << " Path is not found!!!!" << endl;
        return;
    }

    //cout << "ANUP: 1.: " << "Cbn: " << currBlockNumber << ": " \
         << currBlockName << "; Pbn: " << parentBlockNumber << ": " \
         << parentBlockName << "; Tbn: " << targetBlockName << endl;

    // If trying to open a Dir, fail here
    int tmpIndex = getIndexOfBlockFromParent(currBlockNumber, parentBlockNumber);
    if (tmpIndex == -1)
    {
        return;
    }

    if (myDisk.blocks[parentBlockNumber].blockDir.dirEntries[tmpIndex].dirType != 'U')
    {
        cout << "Trying to open a dir" << endl;
        return;
    }

    noOfBytes = myDisk.blocks[parentBlockNumber].blockDir.dirEntries[tmpIndex].lastBlockUsedBytes;

   if (strcmp((char *)strMode.c_str(), "I") == 0)
   {
       readStruct.readPointer = 0;
       readStruct.seekPointer = 0;
       readStruct.writePointer = -1;
   }
   else if (strcmp((char *)strMode.c_str(), "O") == 0)
   {
       readStruct.readPointer = -1;
       readStruct.seekPointer = -1;
       readStruct.writePointer = 0;
   }
   else if (strcmp((char *)strMode.c_str(), "U") == 0)
   {
       readStruct.readPointer = 0;
       readStruct.seekPointer = 0;
       readStruct.writePointer = 0;
   }
   else
   {
       cout<<"You have to give I or O or U for mode"<<endl;
   }
     
    readStruct.parentBlockNumber = parentBlockNumber; 
    readStruct.currentBlockNumber = currBlockNumber;
    readStruct.numberOfBytesUsed = noOfBytes;
    readStruct.status = true;
   
    // to check openFile
    printTrackStruct();
    cout << "File has been Successfully Opened!" << endl;
    cout << endl;
}

void closeFile()
{
    readStruct.parentBlockNumber = -1;
    readStruct.currentBlockNumber = -1;
    readStruct.numberOfBytesUsed = -1;
    readStruct.seekPointer = -1;
    readStruct.readPointer = -1;
    readStruct.writePointer = -1;
    readStruct.status = false;
}

void read(int blockno, int iteration, int startIndex)
{
    //cout << "ACTUAL READ: " << endl;
    cout << "ACTUAL READ: sIdx: " << startIndex << "; Iter: " << iteration << endl;
    for (int i = startIndex; i < startIndex + iteration; i++)
    {
        cout << myDisk.blocks[blockno].blockFile.fileData[i] << " ";
    }

    cout << endl;
}

void readFile(string strNumBytes)
{
    int blockno = readStruct.currentBlockNumber;
    int pointer = readStruct.seekPointer;
    int noOfBytes = std::stoi(strNumBytes);
    int finalSize = pointer + noOfBytes;
    int pBlockNum, iIndex;
    int quotient, remainder;
    int startIndex = pointer;
    int toRead = noOfBytes;
    int remain, iteration;
    int tempBlockNum = blockno;


    pBlockNum = getGlobalParentNumFromChild (blockno);
    iIndex = getIndexOfBlockFromParent (blockno, pBlockNum);
    //cout << "iIdx: " << iIndex << "; pblock: " << pBlockNum << "; stIdx: " << startIndex << endl;
    int availBytes = myDisk.blocks[pBlockNum].blockDir.dirEntries[iIndex].lastBlockUsedBytes;

    //cout <<"Ptr + NumBytes: " << pointer + noOfBytes << "; AvailBytes: " << availBytes << endl;

    // Proceed only if the pointer + User's Input number of bytes is less than 504.
    if (pointer + noOfBytes <= availBytes) 
    {
        if (startIndex < 504)
        {
            remain = 504 - startIndex;
            iteration = findIteration (remain, toRead);  
            read(blockno, iteration, startIndex);
            toRead = toRead - iteration;
        }

        else
        {
            int quotient = pointer / 504;
            startIndex = pointer % 504;
            tempBlockNum = findPointerBlock(quotient, blockno);

            remain = 504 - startIndex;
            iteration = findIteration (remain, toRead);  
            read (tempBlockNum, iteration, startIndex);
            toRead = toRead - iteration;
        }

        while (toRead != 0)
        {
            tempBlockNum = myDisk.blocks[tempBlockNum].blockDir.nextBlock;
            if (tempBlockNum != -1)
            {
                startIndex = 0;
                remain = 504;
                iteration = findIteration (remain, toRead);  
                read(tempBlockNum, iteration, startIndex);
                toRead = toRead - iteration;
            }
            else
            {
                cout << "You are accessing the memory that is not yours"<<endl;
            }
        }
    }
    else
    {
        cout << "You are accessing the memory that is not yours"<<endl;
    }

    // cout << "BlkNo. : " << blockno << "; NumByte: " << std::stoi( strNumBytes ) << endl;
    printFile(blockno, 504);
    printTrackStruct();
    cout << endl;
}

void write(int blockno, int noOfBytes, int readPointer, const char* input, int startIndex)
{
    int totSize = readPointer + noOfBytes;
    //cout << "INP: " << input << endl;
    cout << "ACTUAL WRITE: rdPtr: " << readPointer << "; nuBytes: " << noOfBytes << "; sIdx: " << startIndex << "; tot: " << totSize << "; blNo. : " << blockno << endl;

    for (int i = readPointer, j = startIndex; i < totSize; i++, j++)
    {
        myDisk.blocks[blockno].blockFile.fileData[i] = input[j];
    }

    cout << endl;
}

int findFreeParent (int pBlockNum)
{
    bool cond = true;

    while (cond)
    {
        for (uint32_t i = 0; i < MAX_DIR_ENTRIES; i++)
        {
            if (myDisk.blocks[pBlockNum].blockDir.dirEntries[i].dirType == 'F')
            {
                cond = false;
                return pBlockNum;
            }
        }
        
        pBlockNum = getGlobalParentNumFromChild (pBlockNum);
    }
    return -1;
}

int findPointerBlock (int quotient, int blockNum)
{
    for (int i = 0; i < quotient; i++)
    {
        if (myDisk.blocks[blockNum].blockFile.nextBlock != -1)
        {
            blockNum = myDisk.blocks[blockNum].blockFile.nextBlock;
        }
        else
        {
            return -1;
        }
    }
    return blockNum;
}

void createFileParentDirEntry (int blockNum, int freeIndex, int fBlockNum)
{
   myDisk.blocks[blockNum].blockDir.dirEntries[freeIndex].dirType = 'U'; 
   std::string tmpStr ("NULL");
   tmpStr.copy((char *)myDisk.blocks[blockNum].blockDir.dirEntries[freeIndex].fileName, 9);
   myDisk.blocks[blockNum].blockDir.dirEntries[freeIndex].lastBlockUsedBytes = 0;
   myDisk.blocks[blockNum].blockDir.dirEntries[freeIndex].actualBlockNumber = fBlockNum;
}

void updateFileParentDirEntry (int blockNum, int iEntry, int usedBytes)
{
   myDisk.blocks[blockNum].blockDir.dirEntries[iEntry].lastBlockUsedBytes = usedBytes;
}

int findEntryFromParent (int pBlockNum, int blockno)
{
    for (int i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        if (myDisk.blocks[pBlockNum].blockDir.dirEntries[i].actualBlockNumber == blockno)
        {
            return i;
        }
    }
    return -1;
}

int findFileMaxBytes (int pBlockNum, int finalSize, int i)
{
    if(myDisk.blocks[pBlockNum].blockDir.dirEntries[i].lastBlockUsedBytes < finalSize)
    {
        return finalSize;
    }
    else
    {
        return myDisk.blocks[pBlockNum].blockDir.dirEntries[i].lastBlockUsedBytes; 
    }
}

int findIteration (int remain, int toUpdate)
{
    if (remain >= toUpdate)
    {
        return toUpdate;
    }
    else
    {
        return remain;
    }
}

void updateFileNext (int iBlock, int tempBlockNum)
{
    myDisk.blocks[iBlock].blockDir.nextBlock = tempBlockNum;
}

void writeFile(string strNumBytes, string strData)
{
    int blockno = readStruct.currentBlockNumber;
    int pointer;
    if (readStruct.seekPointer != -1)
    {
        pointer = readStruct.seekPointer;
    }
    else
    {
        pointer = readStruct.writePointer;
    }

    // Extra ONE character for NULL Termination
    const char* input = strData.c_str();

    int finalSize = pointer + std::stoi( strNumBytes );
    int startIndex = pointer;
    
    // Convert string to int.
    int toUpdate = std::stoi( strNumBytes );
    int remain, iteration;
    int inputIndex = 0;
    int pBlockNum, pTempBlockNum, iBlock;
    int tempBlockNum = blockno;

    if (startIndex < 504)
    {
        remain = 504 - startIndex;
        iteration = findIteration (remain, toUpdate);
        write (blockno, iteration, startIndex, input, inputIndex); 
        inputIndex = inputIndex + iteration; 
        toUpdate = toUpdate - iteration;
    }

    else
    {
        int quotient = pointer / 504;
        startIndex = pointer % 504;
        tempBlockNum = findPointerBlock (quotient, blockno);

        remain = 504 - startIndex;
        iteration = findIteration (remain, toUpdate);
        write (blockno, iteration, startIndex, input, inputIndex); 
        inputIndex = inputIndex + iteration; 
        toUpdate = toUpdate - iteration;
    }

    while (toUpdate != 0)
    {
        iBlock = tempBlockNum;
        tempBlockNum = myDisk.blocks[tempBlockNum].blockDir.nextBlock;
        if (tempBlockNum != -1)
        {
            startIndex = 0;
            remain = 504;
            iteration = findIteration (remain, toUpdate);
            write (blockno, iteration, startIndex, input, inputIndex); 
            inputIndex = inputIndex + iteration; 
            toUpdate = toUpdate - iteration;
        }
        else
        {
            pTempBlockNum = findFreeParent (blockno);
            tempBlockNum = getUnusedBlockFromList();
            int i = getFirstFreeFrom31 (pTempBlockNum);
            createFileEntry (tempBlockNum, iBlock);
            createFileParentDirEntry (pTempBlockNum, i, tempBlockNum);
            updateFileNext (iBlock, tempBlockNum);

            // Time to update the global table.
            int gTableIdx = getFirstFreeInGlobalList();

            // "k == -1" is unlikely to happen.
            if (gTableIdx != -1)
            {
                updategDetails(gTableIdx, // Index
                               tempBlockNum, // Target Block Number
                               "NULL", // Target Block Name
                               pTempBlockNum, // Target Parent's Block Number
                               getGlobalCurrName(pTempBlockNum));
            }

            // Print the global list for verification.
            printGlobalList();

            startIndex = 0;
            remain = 504;
            iteration = findIteration (remain, toUpdate);
            write (tempBlockNum, iteration, startIndex, input, inputIndex); 
            inputIndex = inputIndex + iteration; 
            toUpdate = toUpdate - iteration;

            //update global table for the new entry. find k, parentBlockName
            /*
            int k = getFirstFreeInGlobalList();
            string parentBlockName = getGlobalParentName (pBlockNum);
            updategDetails(k, blockno, "NULL", pBlockNum, parentBlockName);
            */

        }
    }
    
    pBlockNum = readStruct.parentBlockNumber;
    //int iEntry = findEntryFromParent (pBlockNum, blockno);
    int iEntry = getIndexOfBlockFromParent (blockno, pBlockNum);
    int maxBytes = findFileMaxBytes (pBlockNum, finalSize, iEntry);

    // cout << "iEntry: " << iEntry << "parentBlock: " << pBlockNum << "MAX BYTES: " << maxBytes << endl;
    updateFileParentDirEntry (pBlockNum, iEntry, maxBytes); 
    readStruct.numberOfBytesUsed = maxBytes;
    //find k, parentBlockName

    int k = getFirstFreeInGlobalList();
    string parentBlockName = getGlobalParentName (pBlockNum);
    updategDetails(k, blockno, "NULL", pBlockNum, parentBlockName);

    //cout << "BlkNo. : " << blockno << "; NumByte: " << std::stoi( strNumBytes ) << endl;
    //printFile(blockno, std::stoi( strNumBytes ));
    printFile(blockno, 504);
    printTrackStruct();
    cout << endl;
}

void seekFile(string strBase, string strOffset)
{
    int one = std::stoi(strBase);
    int two = std::stoi(strOffset);
    int sPointer = readStruct.seekPointer;
    int availBytes = readStruct.numberOfBytesUsed;

    if (one == -1)
    {
        if (two == 0)
        {
           sPointer = 0; 
        }
        else if (two > 0)
        {
            if (two <= availBytes)
            {
                sPointer = two;
            }
            else
            {
                cout << "1. Memory not found" <<endl;
            }
        }
        else
        {
            cout << "2. Memory not found" << endl;
        }
    }
    else if (one == 0)
    {
        if (two == 0)
        {
            sPointer = sPointer;
        }
        else if (two > 0)
        {
            if (sPointer + two <= availBytes)
            {
                sPointer = sPointer + two;
            }
            else
            {
                cout << "3. Memory not found" << endl;
            }
        }
        else if (two < 0)
        {
            if (sPointer + two >= 0)
            {
                sPointer = sPointer + two;
            }
            else
            {
                cout << "4. Memory not found" << endl;
            }
        }

    }
    else if (one == 1)
    {
        if (two == 0)
        {
            sPointer = availBytes;
        }
        else if (two > 0)
        {
            cout << "Memory not found" << endl;
        }
        else if (two < 0)
        {
            if (availBytes + two >= 0)
            {
                sPointer = availBytes + two;
            }
            else
            {
                cout << "Memory not found" << endl;
            }
        }

    }
    else
    {
        cout << "The base you have given is not right" << endl;
    }
    
    readStruct.seekPointer = sPointer;

    printTrackStruct();
    cout << endl;
}

// Current Block Number should be Present
int getIndexOfBlockFromParent(int curBlockNum,
                              int parBlockNum)
{
    if (curBlockNum >= 0 && parBlockNum >= 0)
    {
        for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
        {
            if (myDisk.blocks[parBlockNum].blockDir.dirEntries[i].actualBlockNumber == curBlockNum)
            {
                return i;
            }
        }
    }

    return -1;
}

// Current Block Number should be Present
uint8_t checkIfFileOrDir(int curBlockNum,
                         int parBlockNum)
{
    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        if (myDisk.blocks[parBlockNum].blockDir.dirEntries[i].actualBlockNumber == curBlockNum)
        {
            return myDisk.blocks[parBlockNum].blockDir.dirEntries[i].dirType;
        }
    }

    return ' ';
}

// checkIfFullPathExists()
//      This function check if the given path exists
//
//      Input   : None
//      Output  : Block number of the last file or directory and Parent block num
bool checkIfFullPathExists(string strFileName,
                           int& tmpBlockNum,
                           int& retParentBlockNum)
{
    std::vector<std::string> vecFileNameTokens;

    vecFileNameTokens = strSplit(strFileName, '/');

    tmpBlockNum = 0;
    retParentBlockNum = 0;
    uint32_t parentBlockNum = 0;

    for (uint8_t i = 0; i < vecFileNameTokens.size(); i++)
    {
        tmpBlockNum = getBlockNumber(parentBlockNum, vecFileNameTokens[i].c_str()); 

        // If -1 is returned then the directory does not exist. Return false.
        if (tmpBlockNum == -1)
        {
            return false;
        }
        else
        {
            retParentBlockNum = parentBlockNum;
            parentBlockNum = tmpBlockNum;
        }
    }

    return true;
}

// checkIfFullPathExistsIncNext()
//      This function check if the given path exists
//
//      Input   : None
//      Output  : Block number of the last file or directory and Parent block num
bool checkIfFullPathExistsIncNext(string strFileName,
                                  int& tmpBlockNum,
                                  int& retParentBlockNum)
{
    std::vector<std::string> vecFileNameTokens;

    vecFileNameTokens = strSplit(strFileName, '/');

    tmpBlockNum = 0;
    retParentBlockNum = 0;
    uint32_t parentBlockNum = 0;

    for (uint8_t i = 0; i < vecFileNameTokens.size(); i++)
    {
        tmpBlockNum = getBlockNumber(parentBlockNum, vecFileNameTokens[i].c_str()); 
        //cout << "98. cbn: " << tmpBlockNum << "; pbn: " << parentBlockNum << endl;

        // If -1 is returned then the directory does not exist. Return false.
        while (tmpBlockNum == -1)
        {
            // nextPtr will point to the Next Block that could possible have the
            // directory that we are looking for.
            int nextPtr = myDisk.blocks[parentBlockNum].blockDir.nextBlock;
            //cout << "99. nxt: " << nextPtr << endl;
            if (nextPtr != -1)
            {
                // Get the block number where the Directory we are looking for 
                // is saved.
                parentBlockNum = nextPtr;
                tmpBlockNum = getBlockNumber(nextPtr, vecFileNameTokens[i].c_str());
                if (tmpBlockNum != -1)
                {
                    break;
                }
            }
            else
            {
                // Next Pointer does not exist.
                return false;
            }
        }

        if (tmpBlockNum != -1)
        {
            retParentBlockNum = parentBlockNum;
            parentBlockNum = tmpBlockNum;
        }
    }
    //cout << "100. cbn: " << tmpBlockNum << "; pbd: " << retParentBlockNum << endl;

    return true;
}

int deleteUpdateParent(uint32_t parentBlockNum, uint32_t curBlockNum)
{
    //cout << "ANUP: 205. pbn: " << parentBlockNum << "; cbe: " \
         << curBlockNum << endl;
    int parentIdx = getIndexOfBlockFromParent(curBlockNum, parentBlockNum);
    if (parentIdx != -1)
    {
        //cout << "ANUP: 210. pIdx: " << parentIdx << endl;
        myDisk.blocks[parentBlockNum].blockDir.dirEntries[parentIdx].actualBlockNumber = 0;
        myDisk.blocks[parentBlockNum].blockDir.dirEntries[parentIdx].dirType = 'F';
        // Zero out the file name in the parent entry.
        // memset(&myDisk.blocks[parentBlockNum].blockDir.dirEntries[availableIndex].fileName, 0, 9);
        return 0;
    }

    return -1;
}

int deleteUpdateGlobalList(uint32_t curBlockNum)
{
    int gListIdx = getIndexFromGlobalList(curBlockNum);
    if (gListIdx != -1)
    {
        gDetails[gListIdx].currentBlockNum = -1;
        gDetails[gListIdx].parentBlockNum = -1;
        gDetails[gListIdx].currentName = "";
        gDetails[gListIdx].parentName = "";
        gDetails[gListIdx].isUsed = false;

        return 0;
    }
    return -1;
}

void deleteUpdateLinkedList(uint32_t curBlockNum)
{
    insert(head, curBlockNum);
}

void deleteUpdatePreviousBlockNext(uint32_t curBlockNum)
{
    int tmpPrevBlkNum = myDisk.blocks[curBlockNum].blockDir.prevBlock;

    if (tmpPrevBlkNum != -1)
    {
        myDisk.blocks[tmpPrevBlkNum].blockDir.nextBlock = -1;
    }
}

bool isEntryAtLeaf(uint32_t curBlockNum)
{
    for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
    {
        if (!isIndexFree(curBlockNum, i))
        {
            return false;
        }
    }

    return true;
}

bool isEntryHasNext(uint32_t curBlockNum)
{
    return (myDisk.blocks[curBlockNum].blockDir.nextBlock != -1);
}

void deleteDirPreProcess(int curBlockNum, int parentBlockNum)
{
    //cout << "ANUP. 201.a : cbn: " << curBlockNum << "; pbn: " << parentBlockNum << endl;
    if (curBlockNum > 0 && parentBlockNum >= 0)
    {
        // If it is a file then just delete it as it will be the last entry.
        // Else If the directory is at Leaf and has NO next ptr, the good to delete.
        if ((checkIfFileOrDir(curBlockNum, parentBlockNum) == 'U') ||
            (isEntryAtLeaf((uint32_t)curBlockNum) &&
            !isEntryHasNext((uint32_t)curBlockNum)))
        {
            if (deleteUpdateParent(parentBlockNum, curBlockNum) == -1)
            {
                return;
            }

            if (deleteUpdateGlobalList(curBlockNum) == -1)
            {
                return;
            }

            // Update the current dir's previous dir's next pointer to -1 when
            // current dir is deleted.
            deleteUpdatePreviousBlockNext(curBlockNum);
            deleteUpdateLinkedList(curBlockNum);

            // Deleting of leaf directory is successful.
            //cout << "After Deleting" << endl;
            //printList(head);
            //printGlobalList();
        }
        else
        {
            // Storing two separate variable for Leaf and Next.
            int grLfParBlkNum;
            int grNxtParBlkNum;
            int nxtParentBlockNum;
            int nxtCurBlockNum;
            bool hasLeaf = false;
            bool hasNext = false;
            // If the directory has sub directories then delete them first.
            if (!isEntryAtLeaf((uint32_t)curBlockNum))
            {
                hasLeaf = true;
                for (uint8_t i = 0; i < MAX_DIR_ENTRIES; i++)
                {
                    if(!isIndexFree(curBlockNum, i))
                    {
                        grLfParBlkNum = parentBlockNum;
                        parentBlockNum = curBlockNum;
                        curBlockNum = myDisk.blocks[curBlockNum].blockDir.dirEntries[i].actualBlockNumber;

                        // Delete all the sub directories.
                        //cout << "Has Leaf: cbn: " << curBlockNum << "; pbn: " << parentBlockNum << endl;
                        deleteDirPreProcess(curBlockNum, parentBlockNum);
                    }
                }
            }

            if (isEntryHasNext((uint32_t)curBlockNum))
            {
                hasNext = true;
                // Storing the parent in case we need it for anything. This is not
                // use for now.
                grNxtParBlkNum = parentBlockNum;
                
                // We use the below two entries to finally delete the block.
                grLfParBlkNum = parentBlockNum;
                parentBlockNum = curBlockNum;

                nxtCurBlockNum = myDisk.blocks[curBlockNum].blockDir.nextBlock;
                nxtParentBlockNum = getGlobalParentNumFromChild(nxtCurBlockNum);

                //cout << "Has Next: cbn: " << nxtCurBlockNum << "; pbn: " << nxtParentBlockNum << endl;
                deleteDirPreProcess(nxtCurBlockNum, nxtParentBlockNum);
            }

            deleteDirPreProcess(parentBlockNum, grLfParBlkNum);
        }
    }
    else
    {
        cout << "Invalid Block Numbers" << endl;
        return;
    }
}

void deleteFileOrDirectory(string strFileName)
{
    int curBlockNum;
    int parBlockNum;
    if (!checkIfFullPathExistsIncNext(strFileName, curBlockNum, parBlockNum))
    {
        curBlockNum = 0;
        parBlockNum = 0;
        cout << "Invalid Path to Delete" << endl;
        return;
    }
    else
    {
        //cout << "ANUP: 200. Path Exists; Cbn: " << curBlockNum << "; Pbn: " << parBlockNum << endl;
    }

    cout << "Before Deleting" << endl;
    printList(head);
    printGlobalList();

    deleteDirPreProcess(curBlockNum, parBlockNum);

    cout << "After Deleting" << endl;
    printList(head);
    printGlobalList();
}

void parseInputCommand(string inputCmd)
{
    std::vector<std::string> vecUserCmd;

    vecUserCmd = strSplit(inputCmd, ' ');

    /*
    for (uint8_t i = 0; i < vecUserCmd.size(); i++)
    {
        cout << vecUserCmd[i] << endl;
    }
    */

    if (vecUserCmd[0].compare("CREATE") == 0)
    {
        createFileOrDirectory(vecUserCmd[1], vecUserCmd[2]);
    }

    else if (vecUserCmd[0].compare("OPEN") == 0)
    {
        openFile(vecUserCmd[1], vecUserCmd[2]);
    }

    else if (vecUserCmd[0].compare("CLOSE") == 0)
    {
        closeFile();
    }

    else if (vecUserCmd[0].compare("READ") == 0)
    {
        if (readStruct.readPointer != -1)
        {
            readFile(vecUserCmd[1]);
        }
        else
        {
            cout << "You do not have Read permission" << endl;
        }
    }

    else if (vecUserCmd[0].compare("WRITE") == 0)
    {
        if (readStruct.writePointer != -1)
        {
            writeFile(vecUserCmd[1], vecUserCmd[2]);
        }
        else
        {
            cout << "You do not have Write permission" << endl;
        }
    }

    else if (vecUserCmd[0].compare("SEEK") == 0)
    {
        if ((readStruct.writePointer != -1 && readStruct.readPointer == -1) || 
            (readStruct.writePointer == -1 && readStruct.readPointer == -1))
        {
            cout << "You do not have Seek permission" << endl;
        }
        else
        {
            seekFile(vecUserCmd[1], vecUserCmd[2]);
        }
    }

    else if (vecUserCmd[0].compare("DELETE") == 0)
    {
        deleteFileOrDirectory(vecUserCmd[1]);
    }
    else
    {
        cout << "Invalid Command" << endl;
    }
}

void getInputCommand()
{
    string inputCmd;
    cout << endl << "Enter the command: " << endl;

    // In order to avoid reading '\n'
    cin.ignore();

    // Get the command from the user. "cin" will read only one word
    getline(cin, inputCmd);

    parseInputCommand(inputCmd);
}

int main()
{
    createRootDirectory();
    buildUnusedBlocksList();

    uint32_t input;
    do
    {
        cout << endl << "Enter your choice: " << endl;
        cout << "1. If you want to enter the command, type 1"<<endl;
        cout << "2. To exit, type 2" << endl;
        cin >> input;

        switch (input)
        {
            case 1:
                getInputCommand();
                break;

            case 2:
                break;

            default:
                break;
        }
    } while (input == 1);

    cout << endl;
    return 0;
}
