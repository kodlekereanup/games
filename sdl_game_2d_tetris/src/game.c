#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "../includes/tetris.h"

#define DEFAULT_WINDOW_DIMENSIONS 1

#if DEFAULT_WINDOW_DIMENSIONS == 1
#define WINDOW_WIDTH  480
#define WINDOW_HEIGHT 720
#else
#define SET_WINDOW_DIMENSIONS(W, H) \
#define WINDOW_WIDTH  W             \
#define WINDOW_HEIGHT H
#endif

int main(void) {

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("\n Error Initializing SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // If the user does not want to use the default window dimensions (480, 720) then they may use
    // a dimension that suits their liking by setting DEFAULT_WINDOW_DIMENSIONS to 0 and passing
    // suitable (WIDTH, HEIGHT) arguments to SET_WINDOW_DIMENSIONS(W, H) macro. 
    #if !DEFAULT_WINDOW_DIMENSIONS 
    SET_WINDOW_DIMENSIONS(1000, 1000);
    #endif

    SDL_Window* window = SDL_CreateWindow("Tetris",
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(!window) {
        printf("\n Could not create window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    Uint32 render_flags    = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);

    SDL_Surface* background_surface  = IMG_Load("assets/Mockup/background.jpg");
    SDL_Surface* tetromino_surface_L = IMG_Load("assets/L/L.png"); 
    //SDL_Surface* tetromino_surface_T = IMG_Load("assets/T/T.png");

    if(!background_surface) {
        printf("\n Could not create surface: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Texture* background_texture  = SDL_CreateTextureFromSurface(renderer, background_surface);
    SDL_Texture* tetromino_texture_L = SDL_CreateTextureFromSurface(renderer, tetromino_surface_L);

    SDL_Rect dest_rect;
    SDL_QueryTexture(tetromino_texture_L, NULL, NULL, &dest_rect.w, &dest_rect.h);
    //SDL_QueryTexture(tetromino_texture_L, NULL, NULL, &src_rect.w, &src_rect.h);

    dest_rect.w /= TETROMINO_SCALING_CONSTANT;
    dest_rect.h /= TETROMINO_SCALING_CONSTANT;

    // Decides where the image is loaded when the game starts.
    dest_rect.x = set_random_pos_within_bounds(TETROMINO_HORIZONTAL_SPAWN_ZONE);
    dest_rect.y = set_random_pos_within_bounds(TETROMINO_VERTICAL_SPAWN_ZONE);

    // This is where the tetromino spawned on the screen should start 
    // moving down with the default speed.
    bool close = false;
    int speed = 300;

    while(!close) {
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    close = true;
                    break;
                case SDL_KEYDOWN:
                    // (260, 40);
                    //SDL_Log("\nTetromino Positions : (%d, %d)", dest_rect.x, dest_rect.y);
                    switch(event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            dest_rect.y -= speed / 15;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            dest_rect.x -= speed / 15;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            dest_rect.y += speed / 15;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            dest_rect.x += speed / 15;
                            break;
                        default:
                            break;
                    }
            }
        }

        // Bound checking
        if(dest_rect.x + dest_rect.w > WINDOW_WIDTH) dest_rect.x = WINDOW_WIDTH - dest_rect.w;
        if(dest_rect.x < 0) dest_rect.x = 0;
        if(dest_rect.y + dest_rect.h > WINDOW_HEIGHT) dest_rect.y = WINDOW_HEIGHT - dest_rect.h;
        if(dest_rect.y < 0) dest_rect.y = 0;

        // Drawing
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, NULL);
        SDL_RenderCopy(renderer, tetromino_texture_L, NULL, &dest_rect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(tetromino_texture_L);
    SDL_DestroyTexture(background_texture);
    SDL_FreeSurface(tetromino_surface_L);
    SDL_FreeSurface(background_surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return EXIT_SUCCESS;
}
