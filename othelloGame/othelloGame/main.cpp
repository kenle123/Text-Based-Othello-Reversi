/*
 * Ken Le
 * Last Updated: 5-26-17
 * Copyright © 2017 Ken Le. All rights reserved.
 */

#include <iostream>
#include <iomanip>
using namespace std;

/*
 * Displays the board
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 */
void displayBoard(char board[8][8], int row, int col)
{
    int numCordinate = 0;  //Format number coordinates
    cout << " ";
    
    //Letter Coordinates
    for(char a = 'A'; a < 'I'; a++)
    {
        cout << setw(3) << a;  //Format letter coordinates
    }
    cout << endl;
    //Displays new board with number coordinates
    for(int i = 0; i < row; i ++)
    {
        cout << numCordinate << "  ";
        for(int j = 0; j < col; j++)
        {
            cout <<  board[i][j] << "  ";
        }
        numCordinate++;  //Iterate number coordinates
        cout << endl;
    }
}

/*
 * Resets the board with the pieces in the middle
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 */
void resetBoard(char board[8][8], int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            board[i][j] = '-';
        }
    }
    
    board[3][3] = 'X';
    board[3][4] = 'O';
    board[4][3] = 'O';
    board[4][4] = 'X';
}

/*
 * Checks which turn it is
 * @param[out] playerTurn the corresponding player's move
 */
void playerTurn(int& playerTurn)
{
    cout << endl;
    if(playerTurn == 0)
    {
        cout << "       Player O Move \n";
        playerTurn++;
    }
    
    else
    {
        cout << "       Player X Move \n";
        playerTurn = 0;
    }
}

/*
 * Prompts user to enter a row number and validates it
 * @param[out] row a row number to be validated
 * @return a valid row number inputted by user
 */
void getRow(int& row)
{
    bool fail = true;
    
    //Keeps looping until the user inputs a valid row number
    while(fail)
    {
        cout << "Enter a Row Number(0-7): ";
        
        //Checks to see if user enters an integer
        if(cin >> row)
        {
            //User correctly enters a valid row number
            if(row >= 0 && row <= 7)
            {
                fail = false;
            }
            
            //User enters a number < 0 or > 7
            else
            {
                cout << "Please Input a Number 0-7 inclusive" << endl;
            }
        }
        
        //User enters a string, clears the bad input
        else
        {
            cin.clear();
            string invalid;
            cin >> invalid;
            cout << "Invalid Input" << endl;
        }
    }
}

/*
 * Prompts user to enter a column number and validates it. Converts to integer
 * @param[out] col a column number to be validated
 * @return a valid column number inputted by user
 */
void getColumn(int& col)
{
    string colString = "";
    
    cout << " Enter a Column Number(A-H): ";
    cin >> colString;
    
    //User does not input a character A-E inclusive
    while(!(colString == "A" || colString == "B" || colString == "C"
            || colString == "D"|| colString == "E" || colString == "F" ||
            colString == "G" || colString == "H"))
    {
        cout << "Please Input a Character A-H inclusive" << endl;
        cout << "Enter a Column Number: ";
        cin >> colString;
    }
    
    //Converts the character to an integer
    if(colString == "A")
    {
        col = 0;
    }
    
    else if(colString == "B")
    {
        col = 1;
    }
    
    else if(colString == "C")
    {
        col = 2;
    }
    
    else if(colString == "D")
    {
        col = 3;
    }
    
    else if(colString == "E")
    {
        col = 4;
    }
    
    else if (colString == "F")
    {
        col = 5;
    }
    
    else if (colString == "G")
    {
        col = 6;
    }
    
    else
    {
        col = 7;
    }
}

/*
 * Checks if the user move is a valid move
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 * @param userRow the user inputted row
 * @param userCol the user inputted column
 * @param playerTurn the corresponding player's move
 */
void checkIfValidMove(char board[8][8], int row, int col, int userRow, int userCol, int playerTurn)
{
    //Player O Turn
    if(playerTurn == 1)
    {
        //Invalid move since userRow/userCol is on the edge
        if(!(userRow+1 > 7 || userCol+1 > 7 || userRow-1 < 0 || userCol-1 < 0))
        {
            //Check up, down, left, right, diag up left, diag up right, diag down left, diag down right to check if empty, therefore invalid
            if(board[userRow-1][userCol] == '-' || board[userRow+1][userCol] == '-' ||board[userRow][userCol-1] == '-' ||
               board[userRow][userCol+1] == '-' || board[userRow-1][userCol-1] == '-' ||board[userRow-1][userCol+1] == '-'||
               board[userRow+1][userCol-1] == '-' ||board[userRow+1][userCol+1] == '-')
            {
                cout << "GGEZ";
            }

        }
        
        else
        {
            cout << "FML";
        }
    }
    
    //Player X turn
    else
    {
        
    }
}


int main()
{
    #define ROWS 8
    #define COLS 8
    
    //Main board for game
    char board[ROWS][COLS];
    
    //Resets the board
    resetBoard(board, ROWS, COLS);
    
    bool gameOnGoing = true;
    int playerMove = 0;
    
    do
    {
        //Checks which player turn it is
        playerTurn(playerMove);
        
        cout << endl;
        
        //Displays the board
        displayBoard(board, ROWS, COLS);
        
        int userInputRow = 0;
        int userInputCol = 0;
        
        //Get/Validate user input for row and column input
        getRow(userInputRow);
        getColumn(userInputCol);
        cout << "PlayeMove is: " << playerMove << endl;
        checkIfValidMove(board, ROWS, COLS, userInputRow, userInputCol, playerMove);
        
        
        
        
        
    }while(gameOnGoing);
    return 0;
}
