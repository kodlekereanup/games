#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "../includes/tictactoe.h"

void clearBoard(Board* board) {
	for(int i = 0; i < BRD_SIZE; ++i)
		for(int j = 0; j < BRD_SIZE; ++j)
			board->board[i][j] = 0;
}

void drawBoard(const Board* board) {
	int count = 0;
	for(int j = 0; j < 13; j++) {
	  printf("\t\t");
	    for(int i = 0; i < 31; ++i) {
	        if(i % 10 == 0) printf("|");
	        else {
	            if( j % 4 == 0) printf("-");
	            else {
	                if((j == 2 || j == 6 || j == 10) && (i % 5 == 0)) {
	                	Pair pair = translate(count);
	                	printf("%c", board->board[pair.first][pair.second]);
	                	count++;
	                }
	                else printf(" ");
	            }
	        }
	    }
	    printf("\n");
	}
}

void chooseOpponent(Player* player) {
    printf("\n Press 0 to play against a Human\n");
    printf("\n Press 1 to play against a Computer\n");
    bool human;

    scanf("%d", &human);
    if(human) {

    } else {

    }
}

// initPlayer function sets the playername and the player piece
// variables at startup
// TODO: Handle a case where both players choose the same piece
void initPlayers(Player* player) {
	char piece;
	bool illegal_piece;
	//bool piece_already_chosen;

	for(int i = 0; i < PLAYER_COUNT; i++) {
		player[i].id = i;
		printf("\n Enter player %d name: ", i + 1);
		scanf("%s", player[i].name);
		printf("\n Enter player %d piece: ", i + 1);


    do {
			scanf(" %c", &piece);
			piece = toupper(piece);
			illegal_piece = !(piece == 'X' || piece == 'O');
			if(illegal_piece) printf("\n Invalid input. Please choose between X and O: \n");
		} while(illegal_piece);

		if(piece == 'X') player[i].piece = X;
		else player[i].piece = O;
	}
}

void initBoard(Board* board) {
	//int count = 49; // ASCII for '1'
    for(int i = 0; i < BRD_SIZE; ++i)
        for(int j = 0; j < BRD_SIZE; ++j) {
            board->board[i][j] = '-'; //count++;
            board->cell_used[i][j] = false;
        }
}

Pair translate(const unsigned int cell) {

	// Translates the cell inputted by the user
	// using an array that works like a map
	// The array is indexed by the cell and the
	// corresponding board index is retrieved.
    // TODO: Make map[] global??
	Pair map[] =
	{
		{ 0, 0 }, { 0, 1 }, { 0, 2 },
		{ 1, 0 }, { 1, 1 }, { 1, 2 },
		{ 2, 0 }, { 2, 1 }, { 2, 2 },
	};

	Pair pair;

	pair.first = map[cell].first;
	pair.second = map[cell].second;
	return pair;
}

void placeOnBoard(Board* board, const Pair board_index, const PlayerToken piece) {
	board->board[board_index.first][board_index.second] = piece;
	board->cell_used[board_index.first][board_index.second] = true;
}

void getPlayerInput(Board* board, const Player* player) {
	Pair board_index;
	bool illegal_move;
	// if translate(cell) is occupied, error and reinput

	do {
		int board_cell = -1; // maybe use your rangedinteger from my library?
		printf("\n Enter a number between 1 and 9 to make a move: \n");
		printf("\n Enter 0 for undo last move: \n");
		printf("\n Enter -1 to quit: \n\n Option: ");
		scanf("%d", &board_cell);

		// TODO: have a look at this
		if(board_cell == -1) quit();
		if(board_cell != 0) --board_cell;

		board_index = translate(board_cell);
		illegal_move = board->cell_used[board_index.first][board_index.second];
		if(illegal_move) printf("\n Illegal Move: Try Again!\n");
	} while(illegal_move);

	placeOnBoard(board, board_index, player->piece);
}

// Should display a warning saying control reaches end of a non-void
// function but that's okay since it's guaranteed that the player
// struct has the piece that we're looking for and it's simply unnecessary
// for us to create a temporary variable and have the for-loop break and
// have the function return that instead. 
int findPiecePlayer(const Player* player, PlayerToken piece) {
	for(int i = 0; i < PLAYER_COUNT; ++i) if(player[i].piece == piece) return i;
}

int gameStateCheck(const Board* board, const Player* player,
	                bool (*condition)(int, int), const bool columns, const bool diags) {

  const int X_WIN 		    = 264;
	const int O_WIN 		    = 237;
	const int UNDETERMINED  = -2;

	int diag_sum = 0; // edge case
	int sum = 0;
	for(int row = 0; row < BRD_SIZE; ++row) {
		if(diags) sum = diag_sum; // this is a problem for diagonals
		else sum = 0;
		for(int col = 0; col < BRD_SIZE; ++col) {
			if((*condition)(row, col) && columns) sum += (int)board->board[col][row];
			else if((*condition)(row, col) && !columns) sum += (int)board->board[row][col];
		}
		diag_sum = sum;
		if(sum == X_WIN) return findPiecePlayer(player, X);
		if(sum == O_WIN) return findPiecePlayer(player, O);
	}

	return UNDETERMINED;
}

// utility function for checking left diagonal
bool left_diag_condition(const int i, const int j) { return i == j; }

// utility function for checking right diagonal
bool right_diag_condition(const int i, const int j) { return (i + j) == (BRD_SIZE - 1); }

// utility function for checking non-diagonal
// obviously gcc will complain because the variables i and j are not being used.
// that's not a problem. However if thats annoying, then one could simply
// do a check that will always return true. A check that obviously depends
// on the value of i and j. So something like
// return (i >= 0 || j >=0); should do the trick.
bool non_diag_condition(const int i, const int j) { return true; }

int checkGameOutcome(const Board* board, const Player* player) {
	// TODO: Will need to accept outcome as a parameter when AI is included
	const int UNDETERMINED  = -2;
	const int DRAW 			    = -1;

	if(boardFull(board)) return DRAW;

	bool (*non_diag)(int, int) = non_diag_condition;

	int row_check = gameStateCheck(board, player, non_diag, false, false);
	if(row_check != UNDETERMINED) return row_check;

	int col_check = gameStateCheck(board, player, non_diag, true, false);
	if(col_check != UNDETERMINED) return col_check;

	bool (*left_diag)(const int, const int) = left_diag_condition;
	int left_diag_check = gameStateCheck(board, player, left_diag, false, true);
	if(left_diag_check != UNDETERMINED) return left_diag_check;

	bool (*right_diag)(const int, const int) = right_diag_condition;
	int right_diag_check = gameStateCheck(board, player, right_diag, false, true);
	if(right_diag_check != UNDETERMINED) return right_diag_check;

	// The current state of the board does not provide with enough information
	// to decide the outcome of the game, hence UNDETERMINED
	return UNDETERMINED;
}

bool boardFull(const Board* board) {
	for(int i = 0; i < BRD_SIZE; ++i)
		for(int j = 0; j < BRD_SIZE; ++j)
			if(!board->cell_used[i][j]) return false;

	return true;
}

bool rematch() { return false; }

bool quit() {
	char input;
	printf("\n Are you sure you want to quit? Y/N \n");
	scanf("%c", &input);
	return (toupper(input) == 'Y')? true : false;
}
