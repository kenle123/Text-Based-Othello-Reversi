/*
 * Ken Le
 * Last Updated: 5-31-17
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
    board[3][1] = 'O';
    board[3][3] = 'X';
    board[3][4] = 'X';
    board[4][3] = 'O';
    board[4][4] = 'X';
}

/*
 * Checks if move is valid, if true then next player, else output invalid move
 * @param[out] playerTurn the corresponding player's move
 * @param valid either a valid or invalid move
 */
void ifValidMove(int& playerTurn, int& validMoves, bool valid)
{
    if(valid)
    {
        validMoves++;
        
        cout << endl;
        if(playerTurn == 0)
        {
            playerTurn++;
        }
        
        else
        {
            playerTurn = 0;
        }
    }
    
    else
    {
        cout << "Invalid Move!" << endl;
        cout << endl;
    }
}

/*
 * Displays which player's turn it is
 * @param playerTurn 0 if player O 1 if player X
 */
void displayWhichPlayerTurn(int playerTurn)
{
    if(playerTurn == 0)
    {
        cout << "       Player O Move \n";
    }
    
    else
    {
        cout << "       Player X Move \n";
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
 * Checks if the user move left is a valid move and switches pieces if it is
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 * @param userRow the user inputted row
 * @param userCol the user inputted column
 * @param playerTurn the corresponding player's move
 * @param[out] left true if left is valid move, else false
 */
void checkLeftSide(char board[8][8], int row, int col, int userRow, int userCol, int playerTurn, bool& left)
{
    //Player O Turn / Check left side to see if valid move
    if(playerTurn == 0)
    {
        int numTilesToFlip = 1;
        
        //Left is same piece, space, wall, or one more space so no more room for same piece, then move is invalid on left side
        if(board[userRow][userCol-1] == 'O' || board[userRow][userCol-1] == '-' || userCol == 0 || userCol == 1)
        {
            left = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow][userCol-1] == 'X')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow][userCol-i] == '-')
                {
                    left = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow][userCol-i] == 'O')
                {
                    left = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow][userCol-i] = 'O';
                    }
                    return;
                }
                
                //If hits leftmost wall, then stop searching for same piece and return false
                else if(userCol-i == 0)
                {
                    left = false;
                    return;
                }
                numTilesToFlip++;
            }
        }
        
        else
        {
            left = false;
        }
    }
    
    //Player X Turn / Check left side to check if valid move
    else
    {
        int numTilesToFlip = 1;
        
        //Left is same piece, space, wall, or one more space so no more room for same piece, then move is invalid on left side
        if(board[userRow][userCol-1] == 'X' || board[userRow][userCol-1] == '-' || userCol == 0 || userCol == 1)
        {
            left = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow][userCol-1] == 'O')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow][userCol-i] == '-')
                {
                    left = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow][userCol-i] == 'X')
                {
                    left = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow][userCol-i] = 'X';
                    }
                    return;
                }
                
                //If hits leftmost wall, then stop searching for same piece and return false
                else if(userCol == 0)
                {
                    left = false;
                    return;
                }

                numTilesToFlip++;
            }
            left = false;
        }
       
        else
        {
            left = false;
        }
    }
}

/*
 * Checks if the user move right is a valid move and switches pieces if it is
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 * @param userRow the user inputted row
 * @param userCol the user inputted column
 * @param playerTurn the corresponding player's move
 * @param[out] right true if right is valid move, else false
 */
void checkRightSide(char board[8][8], int row, int col, int userRow, int userCol, int playerTurn, bool& right)
{
    //Player O Turn / Check right side to see if valid move
    if(playerTurn == 0)
    {
        int numTilesToFlip = 1;
        
        //Right is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow][userCol+1] == 'O' || board[userRow][userCol+1] == '-' || userCol == 6 || userCol == 7)
        {
            right = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow][userCol+1] == 'X')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow][userCol+i] == '-')
                {
                    right = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow][userCol+i] == 'O')
                {
                    right = true;
                    
                    //Swap the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow][userCol+i] = 'O';
                    }
                    return;
                }
                
                //If hits rightmost wall, then stop searching for same piece and return false
                else if(userCol+i == 7)
                {
                    right = false;
                    return;
                }

                numTilesToFlip++;
            }
            right = false;
        }
        
        else
        {
            right = false;
        }
    }
    
    //Player X Turn / Check right side to check if valid move
    else
    {
        int numTilesToFlip = 1;
        
        //Right is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow][userCol+1] == 'X' || board[userRow][userCol+1] == '-' || userCol == 6 || userCol == 7)
        {
            right = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow][userCol+1] == 'O')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow][userCol+i] == '-')
                {
                    right = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow][userCol+i] == 'X')
                {
                    right = true;
                    
                    //Swap the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow][userCol+i] = 'X';
                    }
                    return;
                }
                
                //If hits rightmost wall, then stop searching for same piece and return false
                else if(userCol+i == 7)
                {
                    right = false;
                    return;
                }
                numTilesToFlip++;
            }
            right = false;
        }
        
        else
        {
            right = false;
        }
    }
}

/*
 * Checks if the user move up is a valid move and switches pieces if it is
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 * @param userRow the user inputted row
 * @param userCol the user inputted column
 * @param playerTurn the corresponding player's move
 * @param[out] up true if up is valid move, else false
 */
void checkUpSide(char board[8][8], int row, int col, int userRow, int userCol, int playerTurn, bool& up)
{
    //Player O Turn / Check up side to see if valid move
    if(playerTurn == 0)
    {
        int numTilesToFlip = 1;
        
        //Up is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow-1][userCol] == 'O' || board[userRow-1][userCol] == '-' || userRow == 0 || userRow == 1)
        {
            up = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow-1][userCol] == 'X')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow-i][userCol] == '-')
                {
                    up = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow-i][userCol] == 'O')
                {
                    up = true;
                    
                    //Swap the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow-i][userCol] = 'O';
                    }
                    return;
                }
                
                //If hits upmost wall, then stop searching for same piece and return false
                else if(userRow-i == 0)
                {
                    up = false;
                    return;
                }
                numTilesToFlip++;
            }
            up = false;
        }
        
        else
        {
            up = false;
        }
    }
    
    //Player X Turn / Check up side to check if valid move
    else
    {
        int numTilesToFlip = 1;
        
        //Up is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow-1][userCol] == 'X' || board[userRow-1][userCol] == '-' || userRow == 0 || userRow == 1)
        {
            up = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow-1][userCol] == 'O')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow-i][userCol] == '-')
                {
                    up = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow-i][userCol] == 'X')
                {
                    up = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow-i][userCol] = 'X';
                    }
                    return;
                }
                
                //If hits upmost wall, then stop searching for same piece and return false
                else if(userRow-i == 0)
                {
                    up = false;
                    return;
                }
                numTilesToFlip++;
            }
            up = false;
        }
        
        else
        {
            up = false;
        }
    }
}

/*
 * Checks if the user move down is a valid move and switches pieces if it is
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 * @param userRow the user inputted row
 * @param userCol the user inputted column
 * @param playerTurn the corresponding player's move
 * @param[out] down true if down is valid move, else false
 */
void checkDownSide(char board[8][8], int row, int col, int userRow, int userCol, int playerTurn, bool& down)
{
    //Player O Turn / Check down side to see if valid move
    if(playerTurn == 0)
    {
        int numTilesToFlip = 1;
        
        //Down is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow+1][userCol] == 'O' || board[userRow+1][userCol] == '-' || userRow == 6 || userRow == 7)
        {
            down = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow+1][userCol] == 'X')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow+i][userCol] == '-')
                {
                    down = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow+i][userCol] == 'O')
                {
                    down = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow+i][userCol] = 'O';
                    }
                    return;
                }
                
                //If hits downmost wall, then stop searching for same piece and return false
                else if(userRow+i == 7)
                {
                    down = false;
                    return;
                }
                numTilesToFlip++;
            }
            down = false;
        }
        
        else
        {
            down = false;
        }
    }
    
    //Player X Turn / Check down side to check if valid move
    else
    {
        int numTilesToFlip = 1;
        
        //Down is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow+1][userCol] == 'X' || board[userRow+1][userCol] == '-' || userRow == 6 || userRow == 7)
        {
            down = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow+1][userCol] == 'O')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow+i][userCol] == '-')
                {
                    down = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow+i][userCol] == 'X')
                {
                    down = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow+i][userCol] = 'X';
                    }
                    return;
                }
                
                //If hits downmost wall, then stop searching for same piece and return false
                else if(userRow+i == 7)
                {
                    down = false;
                    return;
                }
                numTilesToFlip++;
            }
            down = false;
        }
        
        else
        {
            down = false;
        }
    }
}

/*
 * Checks if the user move diagonal up left is a valid move and switches pieces if it is
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 * @param userRow the user inputted row
 * @param userCol the user inputted column
 * @param playerTurn the corresponding player's move
 * @param[out] diagUpLeft true if diagonal up left is valid move, else false
 */
void checkDiagonalUpLeftSide(char board[8][8], int row, int col, int userRow, int userCol, int playerTurn, bool& diagUpLeft)
{
    //Player O Turn / Check diagonal up left side to see if valid move
    if(playerTurn == 0)
    {
        int numTilesToFlip = 1;
        
        //Diagonal up left is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow-1][userCol-1] == 'O' || board[userRow-1][userCol-1] == '-' || (userRow == 1 && userCol == 1)
           || (userRow == 0 && userCol == 0))
        {
            diagUpLeft = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow-1][userCol-1] == 'X')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow-i][userCol-i] == '-')
                {
                    diagUpLeft = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow-i][userCol-i] == 'O')
                {
                    diagUpLeft = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow-i][userCol-i] = 'O';
                    }
                    return;
                }
                
                //If hits leftmost wall, then stop searching for same piece and return false
                else if(userCol-i == 0)
                {
                    diagUpLeft = false;
                    return;
                }
                numTilesToFlip++;
            }
            diagUpLeft = false;
        }
        
        else
        {
            diagUpLeft = false;
        }
    }
    
    //Player X Turn / Check diagonal up left side to check if valid move
    else
    {
        int numTilesToFlip = 1;
        
        //Diagonal Up Left is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow-1][userCol-1] == 'X' || board[userRow-1][userCol-1] == '-' || (userRow == 1 && userCol == 1)
           || (userRow == 0 && userCol == 0))
        {
            diagUpLeft = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow-1][userCol-1] == 'O')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow-i][userCol-i] == '-')
                {
                    diagUpLeft = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow-i][userCol-i] == 'X')
                {
                    diagUpLeft = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow-i][userCol-i] = 'X';
                    }
                    return;
                }
                
                //If hits leftmost wall, then stop searching for same piece and return false
                else if(userCol-i == 0)
                {
                    diagUpLeft = false;
                    return;
                }
                numTilesToFlip++;
            }
            diagUpLeft = false;
        }
        
        else
        {
            diagUpLeft = false;
        }
    }
}

/*
 * Checks if the user move diagonal up right is a valid move and switches pieces if it is
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 * @param userRow the user inputted row
 * @param userCol the user inputted column
 * @param playerTurn the corresponding player's move
 * @param[out] diagUpRight true if diagonal up right is valid move, else false
 */
void checkDiagonalUpRightSide(char board[8][8], int row, int col, int userRow, int userCol, int playerTurn, bool& diagUpRight)
{
    //Player O Turn / Check diagonal up right side to see if valid move
    if(playerTurn == 0)
    {
        int numTilesToFlip = 1;
        
        //Diagonal up right is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow-1][userCol+1] == 'O' || board[userRow-1][userCol+1] == '-' || (userRow == 1 && userCol == 6)
           || (userRow == 0 && userCol == 7))
        {
            diagUpRight = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow-1][userCol+1] == 'X')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow-i][userCol+i] == '-')
                {
                    diagUpRight = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow-i][userCol+i] == 'O')
                {
                    diagUpRight = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow-i][userCol+i] = 'O';
                    }
                    return;
                }
                
                //If hits rightmost wall, then stop searching for same piece and return false
                else if(userCol+i == 7)
                {
                    diagUpRight = false;
                    return;
                }
                numTilesToFlip++;
            }
            diagUpRight = false;
        }
        
        else
        {
            diagUpRight = false;
        }
    }
    
    //Player X Turn / Check diagonal up right side to check if valid move
    else
    {
        int numTilesToFlip = 1;
        
        //Diagonal Up Right is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow-1][userCol+1] == 'X' || board[userRow-1][userCol+1] == '-' || (userRow == 1 && userCol == 6)
           || (userRow == 0 && userCol == 7))
        {
            diagUpRight = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow-1][userCol+1] == 'O')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow-i][userCol+i] == '-')
                {
                    diagUpRight = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow-i][userCol+i] == 'X')
                {
                    diagUpRight = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow-i][userCol+i] = 'X';
                    }
                    return;
                }
                
                //If hits rightmost wall, then stop searching for same piece and return false
                else if(userCol+i == 7)
                {
                    diagUpRight = false;
                    return;
                }
                numTilesToFlip++;
            }
            diagUpRight = false;
        }
        
        else
        {
            diagUpRight = false;
        }
    }
}

/*
 * Checks if the user move diagonal down left is a valid move and switches pieces if it is
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 * @param userRow the user inputted row
 * @param userCol the user inputted column
 * @param playerTurn the corresponding player's move
 * @param[out] diagDownLeft true if diagonal down left is valid move, else false
 */
void checkDiagonalDownLeftSide(char board[8][8], int row, int col, int userRow, int userCol, int playerTurn, bool& diagDownLeft)
{
    //Player O Turn / Check diagonal down left side to see if valid move
    if(playerTurn == 0)
    {
        int numTilesToFlip = 1;
        
        //Diagonal down left is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow+1][userCol-1] == 'O' || board[userRow+1][userCol-1] == '-' || (userRow == 6 && userCol == 1)
           || (userRow == 7 && userCol == 0))
        {
            diagDownLeft = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow+1][userCol-1] == 'X')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow+i][userCol-i] == '-')
                {
                    diagDownLeft = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow+i][userCol-i] == 'O')
                {
                    diagDownLeft = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow+i][userCol-i] = 'O';
                    }
                    return;
                }
                
                //If hits leftmost wall, then stop searching for same piece and return false
                else if(userCol-i == 0)
                {
                    diagDownLeft = false;
                    return;
                }
                numTilesToFlip++;
            }
            diagDownLeft = false;
        }
        
        else
        {
            diagDownLeft = false;
        }
    }
    
    //Player X Turn / Check diagonal down left side to check if valid move
    else
    {
        int numTilesToFlip = 1;
        
        //Diagonal Down Left is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow+1][userCol-1] == 'X' || board[userRow+1][userCol-1] == '-' || (userRow == 6 && userCol == 1)
           || (userRow == 7 && userCol == 0))
        {
            diagDownLeft = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow+1][userCol-1] == 'O')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow+i][userCol-i] == '-')
                {
                    diagDownLeft = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow+i][userCol-i] == 'X')
                {
                    diagDownLeft = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow+i][userCol-i] = 'X';
                    }
                    return;
                }
                
                //If hits leftmost wall, then stop searching for same piece and return false
                else if(userCol-i == 0)
                {
                    diagDownLeft = false;
                    return;
                }
                numTilesToFlip++;
            }
            diagDownLeft = false;
        }
        else
        {
            diagDownLeft = false;
        }
    }
}

/*
 * Checks if the user move diagonal down right is a valid move and switches pieces if it is
 * @param board[][] the main board game
 * @param row the number of rows
 * @param col the number of columns
 * @param userRow the user inputted row
 * @param userCol the user inputted column
 * @param playerTurn the corresponding player's move
 * @param[out] diagDownRight true if diagonal up left is valid move, else false
 */
void checkDiagonalDownRightSide(char board[8][8], int row, int col, int userRow, int userCol, int playerTurn, bool& diagDownRight)
{
    //Player O Turn / Check diagonal up left side to see if valid move
    if(playerTurn == 0)
    {
        int numTilesToFlip = 1;
        
        //Diagonal down right is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow+1][userCol+1] == 'O' || board[userRow+1][userCol+1] == '-' || (userRow == 6 && userCol == 6)
           || (userRow == 7 && userCol == 7))
        {
            diagDownRight = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow+1][userCol+1] == 'X')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow+i][userCol+i] == '-')
                {
                    diagDownRight = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow+i][userCol+i] == 'O')
                {
                    diagDownRight = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow+i][userCol+i] = 'O';
                    }
                    return;
                }
                
                //If hits rightmost wall, then stop searching for same piece and return false
                else if(userCol+i == 7)
                {
                    diagDownRight = false;
                    return;
                }
                numTilesToFlip++;
            }
            diagDownRight = false;
        }
        
        else
        {
            diagDownRight = false;
        }
    }
    
    //Player X Turn / Check diagonal down right side to check if valid move
    else
    {
        int numTilesToFlip = 1;
        
        //Diagonal Down Right is same piece, space, wall, or one more space so no more room for same piece, then move is invalid
        if(board[userRow+1][userCol+1] == 'X' || board[userRow+1][userCol+1] == '-' || (userRow == 6 && userCol == 6)
           || (userRow == 7 && userCol == 7))
        {
            diagDownRight = false;
        }
        
        //First interaction is different player's piece, therefore possible valid move
        else if(board[userRow+1][userCol+1] == 'O')
        {
            for(int i = 2; i < 7; i++)
            {
                //Has to have no spaces in between pieces
                if(board[userRow+i][userCol+i] == '-')
                {
                    diagDownRight = false;
                    return;
                }
                
                //There is a same player's piece next to different players' piece
                if(board[userRow+i][userCol+i] == 'X')
                {
                    diagDownRight = true;
                    
                    //Swaps the different pieces
                    for(int i = 1; i < numTilesToFlip+1; i++)
                    {
                        board[userRow+i][userCol+i] = 'X';
                    }
                    return;
                }
                
                //If hits leftmost wall, then stop searching for same piece and return false
                else if(userCol+i == 7)
                {
                    diagDownRight = false;
                    return;
                }
                numTilesToFlip++;
            }
            diagDownRight = false;
        }
        
        else
        {
            diagDownRight = false;
        }
    }
}

/*
 * Test to see if the user has won
 * @param board[][] the playing board
 */
void displayWinner(char board[8][8])
{
    int oCount = 0;
    int xCount = 0;
    
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(board[i][j] == 'O')
            {
                oCount++;
            }
            
            else
            {
                xCount++;
            }
        }
    }
    
    if(oCount < xCount)
    {
        cout << "Player X Wins with " << xCount << " pieces." << endl;
    }
    
    else if(xCount < oCount)
    {
        cout << "Player O Wins with " << oCount << " pieces." << endl;
    }
    
    else
    {
        cout << "It's A Tie with " << oCount << " pieces." << endl;
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
    bool flip = true;
    
    //Counts how many valid moves as occured, if 64, then whole board is filled
    int validMoveCount = 4;
    
    //Player O starts, 0 = O, 1 = X
    int playerMove = 0;
    
    do
    {
        //Checks which player turn it is
        displayWhichPlayerTurn(playerMove);
        
        cout << endl;
        
        //Displays the board
        displayBoard(board, ROWS, COLS);
        
        int userInputRow = 0;
        int userInputCol = 0;
        
        //Get/Validate user input for row and column input
        getRow(userInputRow);
        getColumn(userInputCol);
        
        //Boolean values to check each side
        bool left = true;
        bool right = true;
        bool up = true;
        bool down = true;
        bool diagonalUpLeft = true;
        bool diagonalUpRight = true;
        bool diagonalDownLeft = true;
        bool diagonalDownRight = true;
        
        //Checks each position to see if valid, if it is, then swap the pieces
        checkLeftSide(board, ROWS, COLS, userInputRow, userInputCol, playerMove, left);
        checkRightSide(board, ROWS, COLS, userInputRow, userInputCol, playerMove, right);
        checkUpSide(board, ROWS, COLS, userInputRow, userInputCol, playerMove, up);
        checkDownSide(board, ROWS, COLS, userInputRow, userInputCol, playerMove, down);
        checkDiagonalUpLeftSide(board, ROWS, COLS, userInputRow, userInputCol, playerMove, diagonalUpLeft);
        checkDiagonalUpRightSide(board, ROWS, COLS, userInputRow, userInputCol, playerMove, diagonalUpRight);
        checkDiagonalDownLeftSide(board, ROWS, COLS, userInputRow, userInputCol, playerMove, diagonalDownLeft);
        checkDiagonalDownRightSide(board, ROWS, COLS, userInputRow, userInputCol, playerMove, diagonalDownRight);
        
        flip = left || right || up || down || diagonalUpLeft || diagonalUpRight || diagonalDownLeft || diagonalDownRight;
        
        cout << "Left is: " << left << endl;
        cout << "Right is: " << right << endl;
        cout << "Up is: " << up << endl;
        cout << "Down is: " << down << endl;
        cout << "Diagonal Up Left is: " << diagonalUpLeft << endl;
        cout << "Diagonal Up Right is: " << diagonalUpRight << endl;
        cout << "Diagonal Down Left is: " << diagonalDownLeft << endl;
        cout << "Diagonal Down Right is: " << diagonalDownRight << endl;
        
        //If the move is valid, then increment playerMove so goes to next player's turn
        ifValidMove(playerMove, validMoveCount ,flip);
        
        //A valid move
        if(flip)
        {
            //Player O turn
            if(playerMove == 1)
            {
                board[userInputRow][userInputCol] = 'O';
            }
            
            //Player X turn
            else
            {
                board[userInputRow][userInputCol] = 'X';
            }

        }
        
        if(validMoveCount == 64)
        {
            displayBoard(board, ROWS, COLS);
            displayWinner(board);
            return 0;
        }
        
    }while(gameOnGoing);
    return 0;
}
