# supertictactoe
This repo contains the code to play a 9x9 version of tictactoe on the terminal against an AI using the Monte Carlo Tree Search Algorithm.
# Game Play
9x9 Tic-Tac-Toe consists of a tic-tac-toe grid where each space contains another tic-tac-toe grid. When each of these sub-grids are won, the space it occupies becomes marked with your symbol. When you win three of these spaces in a single line, you have won the game. However, the placement of your symbols differs from the typical 3x3 game. The person to start the game gets to play in any of the 81 spaces. Now, wherever you put your symbol in a subgrid forces your opponent to play their turn the corresponding main grid. For example, if x played in the top right square of the middle board, then o must play in the top right board. The only exception is when you are forced to play on a board that has already been won. In this case, you can play on any open space.
# Files
1. SuperTicTacToe - Controls how the user/AI can interact with the game being played
2. SuperTicTacToeAI - Manages the AI's strategy
3. TicTacToe - Manages the board for each space in the main grid
4. Driver - Runs the game in the terminal
