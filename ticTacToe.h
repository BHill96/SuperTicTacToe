#ifndef ticTacToe_h
#define ticTacToe_h

#include <vector>

using namespace std;

class TicTacToe {
    char board[9];
    char status; // Stores the winning symbol or P for in progress 

    public:
        /*********************************************************
         Constructor
         Input: None
         Returns: None
         Creates the array and fills it with '#' as a blank space.
         *********************************************************/
        TicTacToe();
    
        /*********************************************************
        Copy Constructor
        Input: const TicTacToe &origional
        Returns: None
        Copies another objects board and status.
        *********************************************************/
        void copyBoard(const TicTacToe &origional);
    
        /*****************************
         areTurnsLeft
         Input: None
         Returns: true if '#' is found
                  false otherwise 
         *****************************/
        bool areTurnsLeft();
      
        /*********************************
         display
         Input: None
         Returns: None
         Displays the board on the screen.
         *********************************/
        void displayRow(int row);
        
        /******************************************
         reset
         Input: None
         Returns: None
         Sets every index to '#' and status to 'P'.
         ******************************************/
        void reset();
        
        /****************************************************
         currentState
         Input: None
         Returns: char status - indicates if the game is over
         ****************************************************/
        char currentState() { return status; };

        /*************************************************************
         assignSymbol
         Input: int index - the location in the array
                char symbol - the player symbol being put in the board
         Returns: None
         Manages the AI's turn.
         *************************************************************/
        void assignSymbol(int index, char symbol);

        /**********************************************************
         isEmptySpot
         Input: int index - the location in the array being checked
         Returns: bool true - spot is empty
                  bool false - spot is not empty
         **********************************************************/
        bool isEmptySpot(int index);

        /****************************************************************************************
         updateBoardStatus
         Input: char turn - the symbol used to see if the board's status has changed
         Returns: None
         Checks to see if the player won the board, if it's a draw, or if it's still in progress.
         ****************************************************************************************/
        void updateBoardStatus(char turn);

        /******************************************************************************************
         displayWinningSymbol
         Input: None
         Returns: None
         If the board reached a final state, then it shows an X, O, or D depending on who won/draw.
         ******************************************************************************************/
        void displayWinningSymbol();
    
        /****************************************************************
         getEmptyCells
         Input: int [] list - the list storing the indices to empty cells
         Returns: None
         Takes an array and stores the indices in the array.
         ****************************************************************/
        void getEmptyCells(vector<int>& list);
    
        /********************************************************
         insertSymbol
         Input: int cell - index to the cell being filled
                char symbol - the symbol being inserted into cell
         Returns: None
         Inserts the players symbol into the appropriate cell.
         ********************************************************/
        void insertSymbol(int cell, char symbol);
};



#endif
