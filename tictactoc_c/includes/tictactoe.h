#ifndef TICTACTOE_H
#define TICTACTOE_H

// -------------------------------------- MACROS ---------------------------------------------------
#define BRD_SIZE 3
#define GRD_SIZE BRD_SIZE * BRD_SIZE
#define PLAYER_COUNT 2

// -------------------------------------- ENUM DECLARATIONS --------------------------------------------
typedef enum { X = 88, O = 79 } PlayerToken;

// NOTE: I think this is a bad design decision
typedef enum { MO_UNDETERMINED = -2, MO_DRAW = -1, PLAYER1_WIN, PLAYER2_WIN }  MultiplayerOutcome;
typedef enum { CO_UNDETERMINED = -2, CO_DRAW = -1, PLAYER_WIN,  COMPUTER_WIN } ComputerOutcome;

/*
LastMove struct needs a bunch of player information to undo/redo the moves made by both players
*/

/*
typedef struct {
	PlayerMoves moves; 
	Player player;
} LastMove;
*/

// -------------------------------------- STRUCTURE DECLARATIONS  ----------------------------------------
typedef struct {
    PlayerToken board[BRD_SIZE][BRD_SIZE];
    bool cell_used[BRD_SIZE][BRD_SIZE];
} Board;

typedef struct {
	// TODO: Use char* name
	char name[10];
	int id;
    PlayerToken piece;
} Player;

typedef struct {
	MultiplayerOutcome MP_Outcome;
	ComputerOutcome CP_Outcome;
} Outcome;

typedef struct {
	int first;
	int second;
} Pair;

typedef struct {
	int key;
	Pair value;
} Map;

typedef struct {
	Player player[PLAYER_COUNT];
	Board board;
	// last move
    // TODO: How do I represent last move?
    // every player doesn't have a last move. The last move is updated to be whatever is the current move
    // of the game, not any individual player
	Outcome outcome;
	bool quit;
} Game;


// -------------------------------------- FUNCTION DECLARATIONS ---------------------------------------------
// NOTE: Do I need this function??
// void initGame(Board* board);
// void initMap(Map* map);
// int* free_moves_list(const Board* board, int* array_size);
// int recursive_binary_search(const int arr[], int l, int r, int x);
// int find(const int* array, const int free_cell_list_size, const int key);
// bool legalMove(const int cell, const Board* board);
// void selectPlayer();

/*


*/
void initPlayers(Player* player);

/*


*/
void initBoard(Board* board);

/*


*/
void clearBoard(Board* board);

/*


*/
void getPlayerInput(Board* board, const Player* player); // should take an input -- player id

/*


*/
void drawGrid();

/*
# Also check for draws
# return: If player is winning, returns the player which is winning else null

*/
int checkGameOutcome(const Board* board, const Player* player);

/*


*/
void showWinner(const Board* board);

/*


*/
bool rematch();

/*


*/
bool quit();

/*


*/
void drawBoard(const Board* board);

/*


*/
void placeOnBoard(Board* board, const Pair board_index, const PlayerToken piece);

/*


*/
bool boardFull(const Board* board);

/*


*/
int findPiecePlayer(const Player* player, PlayerToken piece);
/*


*/
Pair translate(const int cell);

// -------------------------------------- GLOBALS -------------------------------------------------------

#endif