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
    int numCordinate = 1;  //Format number coordinates
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
        
        return 0;
        
        
        
        
        
        
    }while(gameOnGoing);
    return 0;
}
