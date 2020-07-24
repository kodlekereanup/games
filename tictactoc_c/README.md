# ABOUT
A basic tic tac toe game written in C to test my C skills. 

# NOTES

The game will begin by asking the player to choose between a computer player and a human player.
Once the choice has been made the game loop will start running. 
At this stage there is a conditional input. If the player chooses to play againt another human, it makes sense to give him another choice: Whether to be 'X' or 'O'. 
Once the choice has been made, the otherPlayer defaults to the remaining piece.
However, if he/she chooses to play against a computer, the choice will not be asked, it will be assigned randomly, while retaining the idea of otherPlayer.

The first order of business is to draw the board. But actuallt before doing that, check if the player has pressed the "QUIT" button. If not, only then proceed to call drawBoard();

# WORKING 

## Last Move:

The last move struct keeps track of the last move that both players played. This is incase any one of them
want to undo the move. The state of the current board is stored in a global buffer. It is common to both the players.
If player1 makes a move and wants to undo, then it can be done. However, if player1 makes a move and player2 also makes a move,
then player1 cannot undo their move. The undo option is available only to the player who made the last move.

In case a player opts for undo, the state from the global buffer is pulled into the current buffer and redrawn 

# CELLS

	     0	        1          2
	|----------|----------|----------|
	|          |          |          |
  0	|    0     |    1     |    2     |
	|----------|----------|----------|
	|          |          |          |
  1	|    3     |    4     |    5     |
	|----------|----------|----------|
	|          |          |          |
  2	|    6     |    7     |    8     |
	|----------|----------|----------|

(index --> cell)

Option 1: Lookups
Use the map interface from klibc 
A map of integer to pair 

Option 2: Generate on-the-go
((i * column_size) + j) = index
(i = (index - (index % column_size)) / column_size)

Personally I feel Lookups are better since options are limited and eventually every number may be picked

(translated <-- userinput)
((i, j) <-- index)
((0, 0) <-- 0)
((0, 1) <-- 1)
((0, 2) <-- 2)

((1, 0) <-- 3)
((1, 1) <-- 4)
((1, 2) <-- 5)

((2, 0) <-- 6)
((2, 1) <-- 7)
((2, 2) <-- 8)

ASCII value of (X, O) = (88, 79)

# Winning Positions

There are multiple winning positions - 8 in total.

A player wins if his/her piece(s) are in following cells

HORIZONTAL:

(0 && 1 && 2) ||  
(3 && 4 && 5) || 
(6 && 7 && 8)  

VERTICAL:

(0 && 3 && 6) ||
(1 && 4 && 7) || 
(2 && 5 && 8) 

DIAGONAL

(0 && 4 && 8) ||
(2 && 4 && 6)

if sum == (88 * 3), Player with piece X wins
if sum == (79 * 3), Player with piece O wins

Lot of checks:

after every move, 16 checks need to be done (abstract).

X : 3 * HORIZONTAL + 3 * VERTICAL + 2 * DIAGONAL = 8
O : 3 * HORIZONTAL + 3 * VERTICAL + 2 * DIAGONAL = 8