/********************************************************
 Blake Hillier
 August 19, 2018
 This file manages the AI for the super tic tac toe game.
 ********************************************************/

#ifndef superTicTacToeAI_h
#define superTicTacToeAI_h

#include "ticTacToe.h"
#include <vector>

using namespace std;
// This keeps track of the board and cell played in
struct Coordinates {
    int board; // Shows which board was played in
    int cell; // Shows which cell was played in
    char symbol; // Shows which symbol was used
};

// Represents a node in the search tree
struct Node {
    float wins; // Shows overall score for all terminal nodes linked to this node
    int visits; // Shows number of times this node was picked
    Coordinates * lastPlay;
    Node * parent; // Points to parent node
    TicTacToe mainBoard[9];
    vector<Node *> children;
    vector<Coordinates *> availableMoves;
};

class SuperTicTacToeAI {

    int sims;
    Node * currentNode;
    char symbol;

    public:
        /*************************************************************
         Constructor
         Input: none
         Returns: none
         Creates the currentNode and sets sims, wins, and visits to 0.
         *************************************************************/
        void initializeAI();

        /********************************************************
         getCurrentNode
         Input: none
         Returns: Node currentNode - pointer to the current node.
         ********************************************************/
        Node * getCurrentNode() { return currentNode; };

        /******************************************************************
         setSymbol
         Input: char newSymbol - the symbol used by the AI to play the game
         Returns: none
         ******************************************************************/
        void setSymbol(char newSymbol) { symbol = newSymbol; };

        /********************************************************
         getSymbol
         Input:
         Returns: char symbol - variable holding the AI's symbol.
         ********************************************************/
        char getSymbol() { return symbol; };

        /***************************************************************************
         nodeScore
         Input: Node node - the node being scored
         Returns: int - the score of the node being considered
         Based off of the UCB1 algorithm for Monte-Carlo Tree Searchs
         ***************************************************************************/
        float nodeScore(Node * node);

        /****************************************************************************************
         simulation
         Input: TicTacToe board - the state of the game being explored for a possible win
         Returns: float - the score of the terminal state. 1 for win, 0.5 for draw, and 0 for loss.
         Simulates random moves until the board reaches a terminal state and then returns the value of said state. ****************************************************************************************/
        float simulate(TicTacToe board[9], int nextBoard, char symbol);

        /******************************************************************************
         findBestNode
         Input: Node currentNode - the node containing the current position of the game
         Returns: Node - the Node at the end of the current best path
         Navigates the tree to the best leaf by either expanding or traversing.
         ******************************************************************************/
        Node * findBestNode(Node * bestNode);
    
        /*******************************************************************
         backup
         Input: Node node - the node currently being updated
                int score - the score of the most recent simulation
         Returns: None
         Updates the information on all nodes in the current tree traversal.
         *******************************************************************/
        void backup(Node * node, float score);
    
        /***********************************************************
         expandTree
         Input: Node node - the parent node with unexplored children
         Returns: Node - the new child node
         Creates a new child node for the best parent node.
         ***********************************************************/
        Node * expandTree(Node * node);
    
        /*************************************************************
         gameStatus
         Input: Node node - the node being checked
         Returns: char - W if human won
         L if human lost
         D if draw
         P if game in progress
         Returns a character describing the current state of the game.
         *************************************************************/
        char gameStatus(TicTacToe board[9]);
    
        /**********************************************
        areTurnsLeft
         Input: None
         Returns: None
         Scans the game for any boards not in progress.
         **********************************************/
        bool areTurnsLeft(TicTacToe board[9]);
    
        /****************************************************
         changeSymbol
         Input: None
         Returns: None
         Changes symbol to 'X' or 'O' based on previous turn.
         ****************************************************/
        void changeSymbol();
    
        /*************************************************
         findBestMove
         Input: None
         Returns: Coordinates - The move the AI will make.
         Finds the best move for the AI.
         *************************************************/
        Coordinates findBestMove();
    
        /******************************************************
         update
         Input: int board - the board played in by the opponent
                int cell - the cell played in by the opponent
         Returns: None
         Updates the AI of the opponents move.
         ******************************************************/
        void update(int board, int cell);
    
        /*****************************************************************
         createChild
         Input: Coordinates move - the game move to be played by the child
                Node parent - the parent of the new child
         Returns: None
         Creates a child, its attributes, and connects it to the parent.
         *****************************************************************/
        Node * createChild(Coordinates * move, Node * parent);
    
        /********************************************
         returnToHead
         Input: None
         Returns: None
         Returns currentNode to the root of the tree.
         ********************************************/
        void returnToRoot();
    
        /*******************************************************
         clear
         Input: Node node - the node being removed
         Returns: None
         Clears the Search tree and deallocates all used memory using the __ traversal method.
         *******************************************************/
        void clear(Node * node);
};

#endif

