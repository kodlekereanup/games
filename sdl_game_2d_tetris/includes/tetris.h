#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//------------------------------------------------------------DEFINES-----------------------------------------------------------
#define TETROMINO_SCALING_CONSTANT      5
#define TETROMINO_HORIZONTAL_SPAWN_ZONE 260
#define TETROMINO_VERTICAL_SPAWN_ZONE   150

int set_random_pos_within_bounds(unsigned int bounds); 

#endif

