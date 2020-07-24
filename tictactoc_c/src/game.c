#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../includes/tictactoe.h"

int main() {
    
    /*
     *  Create all the game entities in here. 
     *  Instance of a game, the board(?) and the players.
     *  NOTE: Do I need seperate structs for the Game and the Board? 
     *
     *  Game game;
     *  Player player1, player2;
     *
     *  while the game is running, check if any one player has pressed quit, if no then 
     *  proceed to draw the board. If yes then there are multiple possibilities. 
     *  
     *  One being, the game has not finished yet and one of the players has quit. In this case
     *  the otherPlayer wins the game irrespective of the board position. 
     *  
     *  The second one being, if the game has finished and instead of a 'restart' someone is pissed
     *  off and doesn't want to continue anymore and in this case we normally quit the game and bring
     *  back the main menu of the game. 
     *
     *  while (game.running()) {
     *      if (player.quit()) {
     *
     *      } else {
     *          drawBoard();
     *      }
     *  }
     */

    Game game;

    clearBoard(&game.board);
    initBoard(&game.board);
    drawGrid();
    initPlayers(game.player);
    drawBoard(&game.board);

    int player_turn = 0;
    while(!game.quit) {

        // if(quit()) game.quit = true;
        // TODO: Check if game is quit
        // If quit mid declare other player as winner
        // and bring back main menu. 
        // to completely quit they must exit the game.

        // quit - exits current game and brings back main menu
        // exit - out of game.

        // TODO: add functionality to quit here 

        getPlayerInput(&game.board, &game.player[player_turn % PLAYER_COUNT]);

        int result = checkGameOutcome(&game.board, game.player);
        if(result != MO_UNDETERMINED) {
            if(result == MO_DRAW) {
                drawBoard(&game.board);
                printf("\n GAME TIED \n");
                game.quit = true;
                //continue;
            } else {
                drawBoard(&game.board);
                printf("\n %s Wins \n", game.player[result].name);
                game.quit = true;
                //continue
            }
        }

        if(!game.quit) drawBoard(&game.board);

        // int result = isPlayerWinning(&game.board, game.player, game.outcome);
        // if(result == game.outcome.MP_Outcome.PLAYER1_WIN) {

        // } else if(result == PLAYER2_WIN) {

        // } else if(result == MO_DRAW) {

        // }

        // /*  - Save current state
        //     - Clear board
        //     - Update Board with new input
        //     - Draw Board
        // */

        // if(isPlayerWinning()) {
        //     showWinner();
        //     if(rematch())  {
        //         // do something ...
        //     } else if(quit()) {
        //         // do something ...
        //     }
        // }
        // getPlayerInput();
        player_turn++;

    } 

    return 0;
}