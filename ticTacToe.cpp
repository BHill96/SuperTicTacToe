#ifndef ticTacToe_cpp
#define ticTacToe_cpp

#include "ticTacToe.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Creates the array and fills it with '#' as a blank space.
TicTacToe::TicTacToe() {
    status = 'P';
    for (int i = 0; i < 9; i++)
        board[i] = '#';
}

// Copies another objects board and status.
void TicTacToe::copyBoard(const TicTacToe &origional) {
    for (int i = 0; i < 9; i++)
        board[i] = origional.board[i];
    status = origional.status;
}

// Returns true if there is empty space, or false.
bool TicTacToe::areTurnsLeft() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == '#') {
            return true;
        }
    }
    return false;
}

// Displays the board on the screen.
void TicTacToe::displayRow(int row) {
    for (int i = 0; i < 3; i++) {
        cout << board[3 * (row - 1) + i];
    }
}

// Sets every index to '#' and set status to 'P'.
void TicTacToe::reset() {
    status = 'P';
    for (int i = 0; i < 9; i++)
        board[i] = '#';
}

// Places the player's symbol on the board.
void TicTacToe::assignSymbol(int index, char symbol) {
    board[index] = symbol;
}

// True if empty, false if filled
bool TicTacToe::isEmptySpot(int index) {
    if (board[index] == '#')
        return true;
    else
        return false;
}

// Checks to see if the player won the board, if it's a draw, or if it's still in progress.
void TicTacToe::updateBoardStatus(char turn) {
    if ((board[0] == turn && board[1] == turn && board[2] == turn) ||
       (board[3] == turn && board[4] == turn && board[5] == turn) ||
       (board[6] == turn && board[7] == turn && board[8] == turn) ||
       (board[0] == turn && board[3] == turn && board[6] == turn) ||
       (board[1] == turn && board[4] == turn && board[7] == turn) ||
       (board[2] == turn && board[5] == turn && board[8] == turn) ||
       (board[0] == turn && board[4] == turn && board[8] == turn) ||
       (board[2] == turn && board[4] == turn && board[6] == turn)) {
        status = turn;
        displayWinningSymbol();
    } else if (!areTurnsLeft()) {
        status = 'D';
        displayWinningSymbol();
    }
}

// If the board reached a final state, then it shows an X, O, or D depending on who won/draw.
void TicTacToe::displayWinningSymbol() {
    switch (status) {
        case 'X':
            for (int i = 0; i < 9; i++) {
                if (i % 2 == 0)
                    board[i] = 'X';
                else
                    board[i] = '#';
             }
             break;
        case 'O':
            for (int i = 0; i < 9; i++) {
                if (i != 4)
                    board[i] = 'O';
                else
                    board[i] = '#';
            }
            break;
        case 'D':
            for (int i = 0; i < 9; i++) {
                if (i != 2 && i != 4 && i != 8)
                    board[i] = 'D';
                else
                    board[i] = '#';
            }
            break;
        default:
            throw("Board is trying to display winning symbol without winner.");
    }
}

// Takes an array and stores the indices in the array.
void TicTacToe::getEmptyCells(vector<int>& list) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == '#')
            list.push_back(i);
    }
}

// Inserts the players symbol into the appropriate cell.
void TicTacToe::insertSymbol(int cell, char symbol) {
    board[cell] = symbol;
}

#endif
