/********************************************************************
 Blake Hillier
 8 July 2018
 This file manages the member functions for the SuperTicTacToe class.
 ********************************************************************/

#ifndef superTicTacToe_cpp
#define superTicTacToe_cpp

#include "superTicTacToe.h"
#include <iostream>
#include <ctime>

using namespace std;

// Prints the main gameboard to the screen.
void SuperTicTacToe::display() {
    for (int i = 1; i < 4; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            board[j].displayRow(i);
            if (j < 2)
                cout << " | ";
            else
                cout << endl;
        }
    }

    for (int i = 0; i < 17; i++)
        cout << "-";

    cout << endl;
    
    for (int i = 1; i < 4; i++) {
        cout << " ";
        for (int j = 3; j < 6; j++) {
            board[j].displayRow(i);
            if (j < 5)
                cout << " | ";
            else
                cout << endl;
        }
    }

    for (int i = 0; i < 17; i++)
        cout << "-";

    cout << endl;

    for (int i = 1; i < 4; i++) {
        cout << " ";
        for (int j = 6; j < 9; j++) {
            board[j].displayRow(i);
            if (j < 8)
                cout << " | ";
            else
                cout << endl;
        }
    }
}

// Asks the user what symbol they want and sets activeBoard to -1.
void SuperTicTacToe::initializeGame() {
    AI.initializeAI();
    // Asks the player which symbol they want
    cout << "X or O? ";
    cin >> human;
    // Relates the board to numbers for the user
    cout << "\nThe board is set up as\n1 2 3\n4 5 6\n7 8 9" << endl << endl;

    // Makes user's symbol capitalized and gives the computer the other symbol
    if (human == 'x' || human == 'X') {
        human = 'X';
        AI.setSymbol('O');
    } else if (human == 'o' || human == 'O') {
        human = 'O';
        AI.setSymbol('X');
    } else
        throw("Unkown data in variable 'human'.");

    activeBoard = -1;
    AIThinkTime = 1.5;
    turn = 'O';
}

// Changes turn to 'X' or 'O' based on previous turn.
void SuperTicTacToe::changeTurn() {
    if (turn == 'X')
        turn = 'O';
    else
        turn = 'X';
}

// Calls the appropriate function depending on the active player
void SuperTicTacToe::gameTurn() {
    if (currentTurn() == human)
        playerTurn();
    else
        AITurn();
}

// Informs the user which board they have to play in and asks where they want to play.
void SuperTicTacToe::playerTurn() {
    if (activeBoard == -1) {
        cout << "\nWhich board do you want to play in (1-9)? ";
        cin >> activeBoard;
        activeBoard -= 1;
        while (board[activeBoard].currentState() != 'P') {
            cout << "\nERROR: You must select an unfinished board.\n Which board do you want to play in? ";
            cin >> activeBoard;
            activeBoard -= 1;
        }
    } else if (activeBoard < 9 && activeBoard > -1) {
        cout << "\nYou must play in board " << activeBoard + 1 << endl;
    } else
        throw("activeBoard set at " + to_string(activeBoard));

    // Ask the user where they want to play, and subtract one for index
    int index;
    cout << "Enter the index of an empty square to play your piece (1-9): ";
    cin >> index;
    index = index - 1;

    // Check if space is blank
    while (!board[activeBoard].isEmptySpot(index)) {
        cout << "\nERROR: SPACE NOT EMPTY!" << endl;
        cout << "Enter the index of an empty square to play your piece (1-9): ";
        cin >> index;
        index = index - 1;
    }

    // Assing the players symbol to the square
    board[activeBoard].assignSymbol(index, turn);
    // Update the board's status
    board[activeBoard].updateBoardStatus(turn);

    // send move to AI
    AI.update(activeBoard, index);
    
    // Check if the next board is playable and assign activeBoard accordingly    
    if (board[index].currentState() == 'P')
        activeBoard = index;
    else
        activeBoard = -1;
}

void SuperTicTacToe::AITurn() {
    time_t startTime;
    time_t currentTime;
    double timer = 0.0;
    time(&startTime);
    // While time is not up, run simulations
     do {
        Node * bestNode = AI.findBestNode(AI.getCurrentNode());
         TicTacToe tempBoard[9];
         for (int i = 0; i < 9; i++) {
             tempBoard[i].copyBoard(bestNode->mainBoard[i]);
         }
        float score = AI.simulate(tempBoard, bestNode->lastPlay->cell, bestNode->lastPlay->symbol);
        AI.backup(bestNode, score);
        time(&currentTime);
         timer = difftime(currentTime, startTime);
     } while (timer < AIThinkTime);
    
    Coordinates nextMove = AI.findBestMove();
    board[nextMove.board].assignSymbol(nextMove.cell, nextMove.symbol);
    // Checks if the AI's play one that board
    board[nextMove.board].updateBoardStatus(nextMove.symbol);
    // if the next board is not playable, then mark the active board with -1
    if (board[nextMove.cell].currentState() != 'P')
        activeBoard = -1;
    else
        activeBoard = nextMove.cell;
}

// Returns a character describing the current game state
char SuperTicTacToe::gameStatus() {
    if ((board[0].currentState() == turn && board[1].currentState() == turn && board[2].currentState() == turn) ||
       (board[3].currentState() == turn && board[4].currentState() == turn && board[5].currentState() == turn) ||
       (board[6].currentState() == turn && board[7].currentState() == turn && board[8].currentState() == turn) ||
       (board[0].currentState() == turn && board[3].currentState() == turn && board[6].currentState() == turn) ||
       (board[1].currentState() == turn && board[4].currentState() == turn && board[7].currentState() == turn) ||
       (board[2].currentState() == turn && board[5].currentState() == turn && board[8].currentState() == turn) ||
       (board[0].currentState() == turn && board[4].currentState() == turn && board[8].currentState() == turn) ||
       (board[2].currentState() == turn && board[4].currentState() == turn && board[6].currentState() == turn)) {
        return 'W';
    } else {
	changeTurn();
        if ((board[0].currentState() == turn && board[1].currentState() == turn && board[2].currentState() == turn) ||
        (board[3].currentState() == turn && board[4].currentState() == turn && board[5].currentState() == turn) ||
        (board[6].currentState() == turn && board[7].currentState() == turn && board[8].currentState() == turn) ||
        (board[0].currentState() == turn && board[3].currentState() == turn && board[6].currentState() == turn) ||
        (board[1].currentState() == turn && board[4].currentState() == turn && board[7].currentState() == turn) ||
        (board[2].currentState() == turn && board[5].currentState() == turn && board[8].currentState() == turn) ||
        (board[0].currentState() == turn && board[4].currentState() == turn && board[8].currentState() == turn) ||
        (board[2].currentState() == turn && board[4].currentState() == turn && board[6].currentState() == turn)) {
            changeTurn();
            return 'L';
        } else if (!areTurnsLeft()) {
            changeTurn();
            return 'D';
        } else { 
            changeTurn();
            return 'C';
        }
    }
}

// Scans the game for any boards in progress.
bool SuperTicTacToe::areTurnsLeft() {
    for (int i = 0; i < 9; i++) {
        if (board[i].currentState() == 'P') {
            return true;
        }
    }
    return false;
}

// Reset's the main board and the AI.
void SuperTicTacToe::reset() {
    for (int i = 0; i < 9; i++)
        board[i].reset();
    
    // Find root node of AI tree before clearing
    AI.returnToRoot();
    AI.clear(AI.getCurrentNode());
}


#endif
