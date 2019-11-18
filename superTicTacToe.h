/**********************************************************************************
 Blake Hillier
 8 July 2018
 This file outlines the member variables and functions of the SuperTicTacToe class.
 **********************************************************************************/

#ifndef superTicTacToe_h
#define superTicTacToe_h

#include "superTicTacToeAI.h"

class SuperTicTacToe {
    TicTacToe board[9];
    int activeBoard;
    char turn; // Stores the symbol for the current turn
    char human; // Stores the symbol for the human player
    SuperTicTacToeAI AI;
    int AIThinkTime;

    public:

        /*******************************************************************************
         initializeGame
         Input: None
         Returns: None
         Asks the user which symbol they want, stores it in human, and initiates the AI.
         *******************************************************************************/
        void initializeGame();

        /****************************************
         display
         Input: None
         Returns: None
         Prints the main gameboard to the screen.
         ****************************************/
        void display();

        /**************************************************
         changeTurn
         Input: None
         Returns: None
         Changes turn to 'X' or 'O' based on previous turn.
         **************************************************/
        void changeTurn();

        /*****************************************************
         currentTurn
         Input: None
         Returns: char turn - the symbol of the active player.
         *****************************************************/
        char currentTurn() { return turn; };

        /*************************************************************
         gameStatus
         Input: None
         Returns: char - W if human won
                         L if human lost
                         D if draw
                         C if game in progress
         Returns a character describing the current state of the game.
         *************************************************************/
        char gameStatus();

        /************************************************************
         gameTurn
         Input: None
         Returns: None
         Decided whose turn it is and calls the appropriate function.
         ************************************************************/
        void gameTurn();

        /***********************************************************************************
         playerTurn
         Input: None
         Returns: None
         Informs the user which board they have to play in and asks where they want to play.
         ***********************************************************************************/
        void playerTurn();

        /****************************
         AITurn
         Input: None
         Returns: None
         Manages the computer's turn.
         ****************************/
        void AITurn();

       /************************************************
        reset
        Input: None
        Returns: None
        Reset's the main board and the AI.
        ************************************************/
       void reset();

       /**********************************************
        areTurnsLeft
        Input: None
        Returns: None
        Scans the game for any boards not in progress.
        **********************************************/
       bool areTurnsLeft();
    
       
};

#endif
