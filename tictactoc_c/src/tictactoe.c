#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "../includes/tictactoe.h"
#include "/home/anupkodlekere/Documents/dev/utility/libs_c/klibc.h"

void clearBoard(Board* board) {
	for(int i = 0; i < BRD_SIZE; ++i)
		for(int j = 0; j < BRD_SIZE; ++j)
			board->board[i][j] = 0;
}

//TODO: Do it properly. 
void drawGrid() {
	printf("\n\n\n");
	for(int i = 0; i < GRD_SIZE; ++i) {
		for(int j = 0; j < GRD_SIZE; ++j) {
			// if(((i + 1) % 3 == 0)) {
			// 	printf("_");
			// } 

			// if((j + 1) % 3 == 0) {
			// 	printf("|");
			// } else printf(".");

			if(i % 3 != 0 || j % 3 != 0) printf(".");
			else {
				if(i % 3 == 0) printf("_");
				if(j % 3 == 0) printf("|");
			}
		}

		printf("\n");
	}
	printf("\n\n\n");
}

void drawBoard(const Board* board) {
	printf("\n\n\n");
	for(int i = 0; i < BRD_SIZE; ++i) {
		printf("\n");
		for(int j = 0; j < BRD_SIZE; ++j) {
			printf("%c ", board->board[i][j]);
		}
	}
	printf("\n\n\n");
}

// initPlayer function sets the playername and the player piece
// variables at startup
void initPlayers(Player* player) {
	char piece;

	for(int i = 0; i < PLAYER_COUNT; i++) {

		player[i].id = i;

		printf("\n Enter player %d name: ", i + 1);
		scanf("%s", player[i].name);

		printf("\n Enter player %d piece: ", i + 1);
		scanf(" %c", &piece);

		// TODO: Handle a case where the user does not enter X or O
		if(toupper(piece) == 'X') player[i].piece = X;
		else player[i].piece = O;
	}

}

void initBoard(Board* board) {
    for(int i = 0; i < BRD_SIZE; ++i)
        for(int j = 0; j < BRD_SIZE; ++j) {
            board->board[i][j] = '-';
            board->cell_used[i][j] = false;
        }
}

Pair translate(const int cell) {

	// is this a good design decision? REVIEW THIS
	Map map[] = {
		{ 0, { 0, 0 } }, { 1, { 0, 1 } }, { 2, { 0, 2 } },
        { 3, { 1, 0 } }, { 4, { 1, 1 } }, { 5, { 1, 2 } },
        { 6, { 2, 0 } }, { 7, { 2, 1 } }, { 8, { 2, 2 } }
	};

	Pair pair;
	pair.first = map[cell].value.first;
	pair.second = map[cell].value.second;
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
		int board_cell = -1; // maybe use your rangedinteger from your library?
		printf("\n Enter a number between 0 and 8, or -1 to quit: ");
		scanf("%d", &board_cell);

		// TODO: have a look at this 
		if(board_cell == -1) quit();

		board_index = translate(board_cell);
		illegal_move = board->cell_used[board_index.first][board_index.second];
		if(illegal_move) printf("\n Illegal Move: Try Again!\n");
	} while(illegal_move);

	placeOnBoard(board, board_index, player->piece);
}

int findPiecePlayer(const Player* player, PlayerToken piece) {
	for(int i = 0; i < PLAYER_COUNT; ++i) if(player[i].piece == piece) return i;
}

int generic_check(const Board* board, const Player* player,
	      bool (*condition)(int, int), bool columns, bool diags) {

	const int X_WIN = 264;
	const int O_WIN = 237;
	const int UNDETERMINED  = -2;

	int diag_sum = 0;
	int sum = 0;
	for(int row = 0; row < BRD_SIZE; ++row) {
		if(diags) sum = diag_sum; // this is a problem for diagonals
		else sum = 0;
		for(int col = 0; col < BRD_SIZE; ++col) {
			if((*condition)(row, col) && columns) sum += (int)board->board[col][row]; 
			else if((*condition)(row, col) && !columns) sum += (int)board->board[row][col]; 
		}
		//printf("\n SUM: %d\n", sum);
		diag_sum = sum;
		if(sum == X_WIN)      return findPiecePlayer(player, X);
		else if(sum == O_WIN) return findPiecePlayer(player, O);
	}

	return UNDETERMINED;
}

// utility function for checking left diagonal
bool left_diag_condition(const int i, const int j) { return i == j; }

// utility function for checking right diagonal
bool right_diag_condition(const int i, const int j) { return (i + j) == (BRD_SIZE - 1); } 

bool non_diag_condition(const int i , const int j) { return true; }

int checkGameOutcome(const Board* board, const Player* player) {
	// TODO: Will need to accept outcome as a parameter when AI is included
	const int UNDETERMINED  = -2;
	const int DRAW 			= -1; 

	if(boardFull(board)) return DRAW;

	bool (*non_diag)(int, int) = non_diag_condition;

	int row_check = generic_check(board, player, non_diag, false, false);
	if(row_check != UNDETERMINED) return row_check;

	int col_check = generic_check(board, player, non_diag, true, false);
	if(col_check != UNDETERMINED) return col_check;


	bool (*left_diag)(const int, const int) = left_diag_condition;
	int left_diag_check = generic_check(board, player, left_diag, false, true);
	//printf("\n LDSUM: %d\n", left_diag_check);
	if(left_diag_check != UNDETERMINED) return left_diag_check;

	bool (*right_diag)(const int, const int) = right_diag_condition;
	int right_diag_check = generic_check(board, player, right_diag, false, true);
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