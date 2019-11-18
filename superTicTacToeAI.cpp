/***************************************************************************************
 Blake Hillier
 20 August 2018
 This file manages the implimentations of the functions prototyped in superTicTacToeAI.h
 ***************************************************************************************/

#ifndef superTicTacToeAI_cpp
#define superTicTacToeAI_cpp

#include "superTicTacToeAI.h"
#include <math.h>
#include <iostream>

// Creates the head Node and sets sims, wins, and visits to 0.
void SuperTicTacToeAI::initializeAI() {
    sims = 0;
    currentNode = new Node;
    currentNode->wins = 0;
    currentNode->visits = 0;
    Coordinates * newCoordinates = new Coordinates;
    newCoordinates->board = -1;
    newCoordinates->cell = -1;
    newCoordinates->symbol = 'B';
    currentNode->lastPlay = newCoordinates;
    currentNode->parent = NULL;
    
    // Creates Coordinates for all 81 first moves
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++){
            Coordinates * newMove = new Coordinates;
            newMove->board = i;
            newMove->cell = j;
            newMove->symbol = 'X';
            currentNode->availableMoves.push_back(newMove);
        }
    }
}

// Based off of the UCB1 algorithm for Monte-Carlo Tree Searchs
float SuperTicTacToeAI::nodeScore(Node * node) {
    return (node->wins / node->visits) + pow(2 * log(sims) / node->visits, 0.5);
}

Node * SuperTicTacToeAI::findBestNode(Node * bestNode) {
    // If the game is in progress
    char status = gameStatus(bestNode->mainBoard);
    if (status == 'P') {
        // If new moves can still be made
        if (!bestNode->availableMoves.empty()) {
            return expandTree(bestNode);
        // else all moves have already been made (fully expanded)
        } else {
           Node * bestChild = bestNode->children[0];

            int score = nodeScore(bestChild);
            // Find child with the best chance of success
            for (int i = 1; i < bestNode->children.size(); i++) {
                int tempScore = nodeScore(bestNode->children[i]);
                if (score < tempScore) {
                    score = tempScore;
                    bestChild = bestNode->children[i];
                } else if (score == tempScore) {
                    // Randomly switch if scores are equal
                    if (rand() % 2)
                        bestChild = bestNode->children[i];
                }
            }
            bestNode = bestChild;
            
            bestNode = findBestNode(bestNode);
            return bestNode;
        }
    }
    return bestNode;
}

Node * SuperTicTacToeAI::expandTree(Node * node) {
    // Pick a random move to play. This is going to be played in the new node
    int index = rand() % node->availableMoves.size();
    Coordinates * move = node->availableMoves[index];
    node->availableMoves.erase(node->availableMoves.begin() + index);
    
    // Create the new node and initialize its attributes
    return createChild(move, node);
}

float SuperTicTacToeAI::simulate(TicTacToe board[9], int nextBoard, char tempSymbol) {
    // Checks the status of the board
    char gameState = gameStatus(board);
    float score; // Holds the score of the board if terminal state
    
    // If the game is still in progress
    if (gameState == 'P') {
        // If the next move can be played on any board
        if (nextBoard == -1) {
            vector<int> openBoards;
            for (int i = 0; i < 9; i++) {
                if (board[i].currentState() == 'P') {
                    openBoards.push_back(i);
                }
            }
            // Pick random board
            int boardIndex = rand() % openBoards.size();
            nextBoard = openBoards[boardIndex];
        }
        
        // Pick random cell to play
        vector<int> emptyCells;
        board[nextBoard].getEmptyCells(emptyCells);
        int cellIndex = rand() % emptyCells.size();
        int nextCell = emptyCells[cellIndex];
        board[nextBoard].insertSymbol(nextCell, tempSymbol);
        board[nextBoard].updateBoardStatus(symbol);
        int previousCell;
        if (board[nextCell].currentState() != 'P') {
            previousCell = nextCell;
            nextCell = -1;
        } else
            previousCell = nextCell;
        
        if (tempSymbol == 'X')
            tempSymbol = 'O';
        else
            tempSymbol = 'X';
        
        // Simulate next move
        score = simulate(board, nextCell, tempSymbol);
        board[nextBoard].insertSymbol(previousCell, '#');
        return score;
    }
    else if (gameState == 'W')
        score = 2;
    else if (gameState == 'L')
        score = 0;
    else if (gameState == 'D')
        score = 0.5;
    else
        throw("Simulate function received unkown char from gameState function");
    return score;
}

// Updates the information on all nodes in the current tree traversal.
void SuperTicTacToeAI::backup(Node * node, float score) {
// This will go all the way back to head
    sims++;
    while (node->parent != NULL) {
            node->wins += score;
            node->visits++;
            node = node->parent;

    }
}

// Returns a character describing the current state of the game.
char SuperTicTacToeAI::gameStatus(TicTacToe board[9]) {
    if ((board[0].currentState() == symbol && board[1].currentState() == symbol && board[2].currentState() == symbol) ||
        (board[3].currentState() == symbol && board[4].currentState() == symbol && board[5].currentState() == symbol) ||
        (board[6].currentState() == symbol && board[7].currentState() == symbol && board[8].currentState() == symbol) ||
        (board[0].currentState() == symbol && board[3].currentState() == symbol && board[6].currentState() == symbol) ||
        (board[1].currentState() == symbol && board[4].currentState() == symbol && board[7].currentState() == symbol) ||
        (board[2].currentState() == symbol && board[5].currentState() == symbol && board[8].currentState() == symbol) ||
        (board[0].currentState() == symbol && board[4].currentState() == symbol && board[8].currentState() == symbol) ||
        (board[2].currentState() == symbol && board[4].currentState() == symbol && board[6].currentState() == symbol)) {
        return 'W';
    } else {
        changeSymbol();
        if ((board[0].currentState() == symbol && board[1].currentState() == symbol && board[2].currentState() == symbol) ||
            (board[3].currentState() == symbol && board[4].currentState() == symbol && board[5].currentState() == symbol) ||
            (board[6].currentState() == symbol && board[7].currentState() == symbol && board[8].currentState() == symbol) ||
            (board[0].currentState() == symbol && board[3].currentState() == symbol && board[6].currentState() == symbol) ||
            (board[1].currentState() == symbol && board[4].currentState() == symbol && board[7].currentState() == symbol) ||
            (board[2].currentState() == symbol && board[5].currentState() == symbol && board[8].currentState() == symbol) ||
            (board[0].currentState() == symbol && board[4].currentState() == symbol && board[8].currentState() == symbol) ||
            (board[2].currentState() == symbol && board[4].currentState() == symbol && board[6].currentState() == symbol)) {
            changeSymbol();
            return 'L';
        } else if (!areTurnsLeft(board)) {
            changeSymbol();
            return 'D';
        } else {
            changeSymbol();
            return 'P';
        }
    }
}

// Scans the game for any boards in progress.
bool SuperTicTacToeAI::areTurnsLeft(TicTacToe board[9]) {
    for (int i = 0; i < 9; i++) {
        if (board[i].currentState() == 'P') {
            return true;
        }
    }
    return false;
}

// Changes symbol to 'X' or 'O' based on previous turn.
void SuperTicTacToeAI::changeSymbol() {
    if (symbol == 'X')
        symbol = 'O';
    else
        symbol = 'X';
}

// Finds the best move for the AI to play and then move the current node to this child.
Coordinates SuperTicTacToeAI::findBestMove() {
    if (currentNode->children.size() < 1)
        throw("No Children when finding best move");

    Node * bestChild = currentNode->children[0];
    float bestScore = nodeScore(bestChild);
// Debug: Checking scores of each node
//cout << "Scores of nodes:" << endl;
    for (int i = 1; i < currentNode->children.size(); i++) {
        float tempScore = nodeScore(currentNode->children[i]);
//cout << tempScore << endl;
        if (bestScore < tempScore) {
            bestScore = tempScore;
            bestChild = currentNode->children[i];
        } else if (bestScore == tempScore) {
            if (rand() % 2)
                bestChild = currentNode->children[i];
        }
    }
//cout << "Best Score: " << bestScore << endl;
//cout << "Wins: " << bestChild->wins << "\nVisits: " << bestChild->visits << "\nSims: " << sims << endl;
// End Debug
    currentNode = bestChild;
    return *bestChild->lastPlay;
}

// Updates the AI of the opponents move.
void SuperTicTacToeAI::update(int board, int cell) {
    for (int i = 0; i < currentNode->children.size(); i++) {
        Node * child = currentNode->children[i];
        if ((child->lastPlay->board == board) && (child->lastPlay->cell == cell)) { // If the move matches a child, move currentNode to the child
            currentNode = child;
            return; // No need to check availableMoves
        }
    }
    
    for (int i = 0; i < currentNode->availableMoves.size(); i++) {
        Coordinates * move = currentNode->availableMoves[i];
        if ((move->board == board) && (move->cell == cell)) {
            currentNode->availableMoves.erase(currentNode->availableMoves.begin() + i); // Remove address of the move since it is no longer a potential move
            currentNode = createChild(move, currentNode); // move current node to represent players position
            break; // Leave the loop
        }
    }
}

// Creates a child, its attributes, and connects it to the parent.
Node * SuperTicTacToeAI::createChild(Coordinates * move, Node * parent) {
    Node * newNode = new Node;
    newNode->wins = 0;
    newNode->visits = 0;
    newNode->lastPlay = move;
    newNode->parent = parent;
    
    // Copy board over to new node and insert the next play
    for (int i = 0; i < 9; i++)
        newNode->mainBoard[i].copyBoard(parent->mainBoard[i]);
    newNode->mainBoard[move->board].insertSymbol(move->cell, move->symbol);
    
    // Check if next move won in the played board
    newNode->mainBoard[move->board].updateBoardStatus(move->symbol);
    
    char newSymbol;
    if (move->symbol == 'X')
        newSymbol = 'O';
    else
        newSymbol = 'X';
    
    vector<int> openBoards;
    // If the next board, cannot be played in, let the AI play anywhere
    char state = newNode->mainBoard[move->cell].currentState();
    if (state != 'P') {
        for (int i = 0; i < 9; i++) {
            if (newNode->mainBoard[i].currentState() == 'P') {
                openBoards.push_back(i);
            }
        }
    } else {
        openBoards.push_back(move->cell);
    }

    // Find the empty cells for each board and create a new coordinates object.
    vector<int> emptyCells;
    for (int i = 0; i < openBoards.size(); i++) {
        newNode->mainBoard[openBoards[i]].getEmptyCells(emptyCells);
        for (int j = 0; j < emptyCells.size(); j++) {
            Coordinates * newCoordinate = new Coordinates;
            newCoordinate->board = openBoards[i];
            newCoordinate->cell = emptyCells[j];
            newCoordinate->symbol = newSymbol;
            // Store new Coordinates object as possible move for newNode
            newNode->availableMoves.push_back(newCoordinate);
        }
        emptyCells.clear();
    }
    
    // Link the new Node to its parent
    parent->children.push_back(newNode);

    return newNode;
}

// Returns currentNode to the root of the tree.
void SuperTicTacToeAI::returnToRoot() {
    while (currentNode->parent != NULL)
        currentNode = currentNode->parent;
}

void SuperTicTacToeAI::clear(Node * node) {
    // Traverse the tree to find a leaf, clear it, and set to NULL
    int size = node->children.size();
    for (int i = 0; i < size; i++) {
        clear(node->children[i]);
        node->children[i] = NULL;
    }
    
    // Remove everything from the list
    node->children.clear();
    
    // Delete all Coordinates from available moves
    size = node->availableMoves.size();
    for (int i = 0; i < size; i++) {
        free(node->availableMoves[i]);
        node->availableMoves[i] = NULL;
    }
    // Remove everything from the list
    node->availableMoves.clear();
    // Free last play and set to NULL
    free(node->lastPlay);
    node->lastPlay = NULL;
    // Lose the link to node's parent
    node->parent = NULL;
    // Free the node since we are now done
    free(node);
}
#endif
