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

/*
int* free_moves_list(const Board* board, int* array_size) {
	int* list = malloc(sizeof(int) * 9);
	for(int i = 0; i < BRD_SIZE; ++i) {
		for(int j = 0; j < BRD_SIZE; ++j) {
			if(!board->cell_used[i][j]) {
				//vector_push_back(...)
				list[*array_size++] = board->board[i][j];
			}
		}
	}

	return list;
}

int recursive_binary_search(const int* arr, int l, int r, const int x) { 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle 
        // itself 
        if (arr[mid] == x) 
            return mid; 
  
        // If element is smaller than mid, then 
        // it can only be present in left subarray 
        if (arr[mid] > x) 
            return recursive_binary_search(arr, l, mid - 1, x); 
  
        // Else the element can only be present 
        // in right subarray 
        return recursive_binary_search(arr, mid + 1, r, x); 
    } 
  
    // We reach here when element is not 
    // present in array 
    return -1; 
} 

int find(const int* array, const int free_cell_list_size, const int key) {
	return recursive_binary_search(array, 0, free_cell_list_size, key);
}

bool legalMove(const int cell, const Board* board) {
	// if cell occurs in the !cell_used list, move is legal

	//Vector free_moves_list = extract(board->board, !board->cell_used);
	int free_cell_list_size = 0;
	int* free_cell_list = free_moves_list(board, &free_cell_list_size);

	// generalise this call and put in library
	// TODO: Replace -1 by library NOT_FOUND macro
	return (find(free_cell_list, free_cell_list_size, cell) == -1) ? false : true;
}
*/

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
		printf("\n Enter a number between 0 and 8: ");
		scanf("%d", &board_cell);
		board_index = translate(board_cell);
		illegal_move = board->cell_used[board_index.first][board_index.second];
		if(illegal_move) printf("\n Illegal Move: Try Again!\n");
	} while(illegal_move);

	placeOnBoard(board, board_index, player->piece);
}

int findPiecePlayer(const Player* player, PlayerToken piece) {
	for(int i = 0; i < PLAYER_COUNT; ++i) if(player[i].piece == piece) return i;
}

// how do I write this function in the best way possible
// TODO: Shitty function, find better ways
int checkGameOutcome(const Board* board, const Player* player) {
	
	// TODO: Will need to accept outcome as a parameter when AI is included

	const int X_WIN = 264;
	const int O_WIN = 237;
	const int DRAW  = -2;

	if(boardFull(board)) return -1;

	// check for X

	// checks all rows
	for(int row = 0; row < BRD_SIZE; ++row) {
		int row_sum = 0;
		for(int col = 0; col < BRD_SIZE; ++col) row_sum += (int)board->board[row][col]; 
		if(row_sum == X_WIN)      return findPiecePlayer(player, X);
		else if(row_sum == O_WIN) return findPiecePlayer(player, O);
	}

	// checks all columns
	for(int row = 0; row < BRD_SIZE; ++row) {
		int col_sum = 0;
		for(int col = 0; col < BRD_SIZE; ++col) col_sum += (int)board->board[col][row]; 
		if(col_sum == X_WIN) 	  return findPiecePlayer(player, X);
		else if(col_sum == O_WIN) return findPiecePlayer(player, O);
	}

	// check diagonals
	int left_diag_sum = 0;
	for(int row = 0; row < BRD_SIZE; ++row) {
		for(int col = 0; col < BRD_SIZE; ++col) 
			if(row == col) left_diag_sum += (int)board->board[row][col]; 
		if(left_diag_sum == X_WIN) 		return findPiecePlayer(player, X);
		else if(left_diag_sum == O_WIN) return findPiecePlayer(player, O);
	}

	int right_diag_sum = 0;
	for(int row = 0; row < BRD_SIZE; ++row) {
		for(int col = 0; col < BRD_SIZE; ++col) 
			if(row + col == BRD_SIZE - 1) right_diag_sum += (int)board->board[row][col]; 
		if(right_diag_sum == X_WIN) return findPiecePlayer(player, X);
		else if(right_diag_sum == O_WIN) return findPiecePlayer(player, O);
	}
	// should not return -1 until board is 
	return DRAW; // draw
}

// void showWinner(const Board* board) {

// }

bool boardFull(const Board* board) {
	for(int i = 0; i < BRD_SIZE; ++i)
		for(int j = 0; j < BRD_SIZE; ++j)
			if(!board->cell_used[i][j]) return false;

	return true;
}

bool rematch() { return false; }
bool quit() { return false; }
