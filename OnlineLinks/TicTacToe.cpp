/* 
 * By Pragadheeshwaran Thirumurthi
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
using namespace std;

// Global Variables;
static const char PLAYER_COMPUTER = 'O';
static const char PLAYER_HUMAN  = 'X';
static const char TIE_GAME  = 'T';

char activePlayer = PLAYER_COMPUTER;
static int DEFAULT_SCORE = -1;
static int SCORE_CURRENT = 1;
static int NUM_TRIALS = 10; // Incresing this will increase the chances of computer winning
static int NUM_CELLS = 3;


// This function initialized the Tic Tac Toe Board
void initClearBoard(char** board, int num)
{
    for (unsigned int i = 0; i < num; i++)
    {
        for (unsigned int j = 0; j < num; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// Utility function to print the Tic Tac Toe Board
void printBoard(char** board, int num)
{
    cout << endl << "Board: " << endl;
    for (unsigned int i = 0; i < num; i++)
    {
        for (unsigned int j = 0; j < num; j++)
        {
            cout << board[i][j] << " | ";
        }
        cout << endl << "-----------" <<endl;
    }
    cout << endl;
}

// Utility function to print the Score Matrix
void printScoresMat(int** scoreMat, int num)
{
    cout << endl << "Scores Matrix: " << endl;
    for (unsigned int i = 0; i < num; i++)
    {
        for (unsigned int j = 0; j < num; j++)
        {
            cout << scoreMat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// For a given player, this function returns the other player
char getSwitchedPlayer(char player)
{
    if (player == PLAYER_COMPUTER)
    {
        return PLAYER_HUMAN; 
    }
    else if (player == PLAYER_HUMAN)
    {
        return PLAYER_COMPUTER; 
    }

    return ' ';
}

// This function changes the active player
void switchActivePlayer(char& activePlayer)
{
    if (activePlayer == PLAYER_COMPUTER)
    {
        activePlayer = PLAYER_HUMAN;
    }
    else
    {
        activePlayer = PLAYER_COMPUTER;
    }
}

// Check if any Cells are empty in the board. If so the game is still on.
bool isAnyCellEmptyInBoard(char** board, int num)
{
    for (unsigned int i = 0; i < num; i++)
    {
        for (unsigned int j = 0; j < num; j++)
        {
            if (board[i][j] != PLAYER_COMPUTER &&
                board[i][j] != PLAYER_HUMAN)
            {
                return true;
            }
        }
    }

    return false;
}

// Check if a given cell is empty
bool checkIsCellEmpty(char** board, int row, int col)
{
    if (board[row][col] == PLAYER_COMPUTER ||
        board[row][col] == PLAYER_HUMAN)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Update a given position with a player
void updateBoardWithPlayer(char** board, int row, int col, char player)
{
    if (checkIsCellEmpty(board, row, col))
    {
        board[row][col] = player;
    }
    else
    {
        cout << "The desired cell is not empty" << endl;
    }
}

// Check if any Cells are empty in the board. If so the game is still on.
void getEmptyCells(char** board, int num, vector<int>& empRows, vector<int>& empCols)
{
    for (unsigned int i = 0; i < num; i++)
    {
        for (unsigned int j = 0; j < num; j++)
        {
            if (board[i][j] != PLAYER_COMPUTER &&
                board[i][j] != PLAYER_HUMAN)
            {
                empRows.push_back(i);
                empCols.push_back(j);
            }
        }
    }
}

// Given a 2D Board, this finds who the winner is.
char findWinner(char** board, int num)
{
    char winner = TIE_GAME;
    num = 3;

    // Check for O O O:
    for (unsigned int i = 0; i < num; i++)
    {
        if (board[i][0] == board[i][1] and board[i][1] == board[i][2] and
            board[i][0] != ' ')
        {
            winner = board[i][0];
            return winner;
        }
    }

    // Check for 
    // 0
    // 0
    // 0
    for (unsigned int i = 0; i < num; i++)
    {
        if (board[0][i] == board[1][i] and board[1][i] == board[2][i] and
            board[i][0] != ' ')
        {
            winner = board[0][i];
            return winner;
        }
    }

    // Check for diagnol like
    // 0
    //   0
    //     0
    if ((board[0][0] == board[1][1] and board[1][1] == board[2][2] and board[0][0] != ' ') ||
        (board[0][2] == board[1][1] and board[1][1] == board[2][0] and board[0][2] != ' '))
    {
        winner = board[1][1];
        return winner;
    }
 
    return winner;
}

// This is a function that runs a Trial Game till we get a winner or tie
// Later based on this game, we compute a score on the OPTIMUM cells where chances of winning
// is high. Computer will select this cell.
void runTrialGame(char** board, int num, char& player)
{
    while (isAnyCellEmptyInBoard(board, num) &&
           findWinner(board, num) != PLAYER_HUMAN&&
           findWinner(board, num) != PLAYER_COMPUTER)
    {
        int randomCell;
        vector<int> emptyRows;
        vector<int> emptyCols;
        getEmptyCells(board, num, emptyRows, emptyCols);

        srand (time(NULL));
        randomCell = rand() % emptyRows.size();
        
        updateBoardWithPlayer(board, emptyRows[randomCell], emptyCols[randomCell], player);

        switchActivePlayer(player);
    }
}

// The following function updates the score matrix
// Score matrix is used to find the OPTIMUM cell form a winning board.
void updateScoreMatrix(char** board,
                       int num,
                       char player,
                       int** scoreMat)
{
    char playerWon = findWinner(board, num);

    if (playerWon == TIE_GAME)
    {
        return ;
    }

    if (playerWon == player)
    {
        for (unsigned int i = 0; i < num; i++)
        {
            for (unsigned int j = 0; j < num; j++)
            {
                if (board[i][j] == player)
                {
                    scoreMat[i][j] += SCORE_CURRENT;
                }
                else if(board[i][j] == getSwitchedPlayer(player))
                {
                    scoreMat[i][j] -= SCORE_CURRENT;
                }
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < num; i++)
        {
            for (unsigned int j = 0; j < num; j++)
            {
                if (board[i][j] == player)
                {
                    scoreMat[i][j] -= SCORE_CURRENT;
                }
                else if (board[i][j] == getSwitchedPlayer(player))
                {
                    scoreMat[i][j] += SCORE_CURRENT;
                }
            }
        }
    }
}

// This function gets the best move for a given score matrix
void getBestMove(char** board,
                 int** scoreMat,
                 int num,
                 int& row = DEFAULT_SCORE,
                 int& col = DEFAULT_SCORE)
{
    int maxVal = INT_MIN;
    vector<int> maxValRow;
    vector<int> maxValCol;

    // Find the Max Val in the score matrix by traversing it.
    for (unsigned int i = 0; i < num; i++)
    {
        for (unsigned int j = 0; j < num; j++)
        {
            if (scoreMat[i][j] > maxVal &&
                checkIsCellEmpty(board, i , j))
            {
                maxVal = scoreMat[i][j];
            }
        }
    }

    // Add the Best Moves Row and Col to corresponding vectors.
    for (unsigned int i = 0; i < num; i++)
    {
        for (unsigned int j = 0; j < num; j++)
        {
            if (scoreMat[i][j] == maxVal)
            {
                maxValRow.push_back(i);
                maxValCol.push_back(j);
            }
        }
    }

    // Generate a random number if we have multiple bestMoves
    // Initialize Random Seed
    int randomNum;
    srand (time(NULL));

    // Repeat till you get an empty cell
    do
    {
        randomNum = rand() % maxValRow.size();

        row = maxValRow[randomNum];
        col = maxValCol[randomNum];
    } while (!(checkIsCellEmpty(board, row, col)));
}


// This function plays tic tac toe by itself until the game is over. Once the game is over,
// it find the best position by using a Scoring matrix.
void repeatTrialGameAndFindBestMove(char** board, int num, char player, int& targRow, int& targCol)
{
    // Initialize a Score Matrix to play the trial game.
    int** scoresMat = new int* [num];
    for (unsigned int i = 0; i < num; i++)
    {
        scoresMat[i] = new int[num];
    }

    // Intialize Scores Matrix to all INT_MIN;
    for (unsigned int i = 0; i < num; i++)
    {
        for (unsigned int j = 0; j < num; j++)
        {
            scoresMat[i][j] = 0;
        }
    }


    for (unsigned int i = 0; i < NUM_TRIALS; i++)
    {
        // Initialize a temp board to play the trial game.
        char** tmpBoard = new char* [num];
        for (unsigned int it = 0; it < num; it++)
        {
            tmpBoard[it] = new char[num];
        }

        // Copy current board to temp Board
        for (unsigned int ii = 0; ii < num; ii++)
        {
            for (unsigned int jj = 0; jj < num; jj++)
            {
                tmpBoard[ii][jj] = board[ii][jj];
            }
        }

        // Run a trial game
        runTrialGame(tmpBoard,
                     num,
                     player);

        // Update the score matrix
        updateScoreMatrix(tmpBoard,
                          num,
                          player,
                          scoresMat);

        // Cleanup the temp board
        for(unsigned int i = 0; i < num; i++)
        {
            delete[] tmpBoard[i];
        }
        delete[] tmpBoard;
    }

    // Find the best position
    getBestMove(board,
                scoresMat,
                num,
                targRow,
                targCol);
}

// Play Tic Tac Toe Game
void playTicTacToe(char** board, int num, char& player)
{
    // Continue till we have a winner or at least one cell is empty
    while (isAnyCellEmptyInBoard(board, num) &&
           findWinner(board, num) != PLAYER_HUMAN&&
           findWinner(board, num) != PLAYER_COMPUTER)
    {
        if (player == PLAYER_HUMAN)
        {
            unsigned int rowPos;
            unsigned int colPos;
            printBoard(board, num);
            cout << "Enter Your Row Position: ";
            cin >> rowPos;

            cout << "Enter Your Col Position: ";
            cin >> colPos;

            updateBoardWithPlayer(board, rowPos, colPos, player);

            if (isAnyCellEmptyInBoard(board, num))
            {
                switchActivePlayer(player);
                printBoard(board, num);
            }
        }

        // If player is Computer, we try to find the optimum cell for placement.
        // This is found by running TRIAL games multiple times and find the best position
        // where the chances of winning is high.
        if (findWinner(board, num) != PLAYER_HUMAN &&
            player == PLAYER_COMPUTER)
        {
            int targRow;
            int targCol;

            // Run the trail game and find best move
            repeatTrialGameAndFindBestMove(board, num, player, targRow, targCol);

            // Place the position in the identified cell
            updateBoardWithPlayer(board, targRow, targCol, player);

            // Give back to the other player
            switchActivePlayer(player);
        }
    }

    cout << endl << endl;
    cout << "Game Complete. Winner: " << findWinner(board, num) << endl;
    printBoard(board, num);
}

int main()
{
    // Num of cells for Tic Tac Toe Game
    unsigned int numGrids = 3;

    char** grid = new char* [numGrids];
    for (unsigned int i = 0; i < numGrids; i++)
    {
        grid[i] = new char[numGrids];
    }

    char startPlayer = PLAYER_HUMAN;
    initClearBoard(grid, numGrids);

    playTicTacToe(grid, numGrids, startPlayer);

    cout << endl;
    return 0;
}
