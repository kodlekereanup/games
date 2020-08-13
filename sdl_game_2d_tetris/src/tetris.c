#include "../includes/tetris.h"

int set_random_pos_within_bounds(unsigned int bounds) {
    srand(time(0));
    return rand() % bounds; 
}

