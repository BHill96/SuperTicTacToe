/***********************************************************************************
 Blake Hillier
 8 July 2018
 This file simulates a tic tac toe game on a 9x9 grid to test the different classes.
 ***********************************************************************************/

#include "superTicTacToe.h"
#include <iostream>

using namespace std;

int main() {
    SuperTicTacToe game;
    bool run = false; // Indicates wether the program should keep running
    srand(time(NULL));
 
    try { 
        do {
            game.initializeGame();

            // This loop manages the actual game
            do {
                // Displays current game information each turn
                game.changeTurn();
                cout << game.currentTurn() << "'s turn:" << endl;
                game.display();
                cout << endl;
                game.gameTurn();
            } while (game.gameStatus() == 'C');

            // Tells the user who won or the game was a draw
            switch (game.gameStatus()) {
                case 'W':
                    cout << game.currentTurn() << " won!" << endl;
                    game.display();
                    break;
                case 'D':
                    cout << "It's a draw!" << endl;
                    game.display();
                    break;
                case 'C':
                    game.display();
                    throw("Game loop ended while game was still in progress.");
                default:
                    throw("Unkown error with gameStatus after game loop.");
            }

            // Asks user if they want to play again
            char choice;
            cout << "Again? (y/n) ";
            cin >> choice;

            // Resets the board if the user wants to play
            if (choice == 'y') {
                game.reset();
                run = true;
            } else // Finish running the loop
                run = false;

        } while (run);

        cout << "\nCreated by Blake Hillier.\nStarted on June 28, 2018." << endl;
    }
    catch (const char* message) {
        cout << "ERROR: " << message << "\nTerminating program";
    }
    catch (...) {
        throw;
   }
}
