#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

int main(void) {

    SDL_Window* window;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Window", 
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              1280, 720,
                              SDL_WINDOW_OPENGL);

    if(!window) {
        printf("\n Could not create window");
        return -1;
    }

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);

    if(!window_surface) {
        printf("\n Could not retrieve surface from the window");
        return -1;
    }

    SDL_Surface* image = IMG_Load("assets/Mockup/background.jpg");
    if(!image) {
        printf("\n Failed to load image\n");
        printf("\n SDL2 Error: %s", SDL_GetError());
        return -1;
    }
    
    bool keep_window_open = true;
    while(keep_window_open) {
        SDL_Event event;

        while(SDL_PollEvent(&event) > 0) {
            switch(event.type) {
                case SDL_QUIT: {
                                   keep_window_open = false;
                               } break;
            }

            int new_width = image->w;
            int new_height = image->h;

            SDL_SetWindowSize(window, new_width, new_height);
            window_surface = SDL_GetWindowSurface(window);
            SDL_BlitSurface(image, NULL, window_surface, NULL);
            SDL_UpdateWindowSurface(window);
        }
    }

    return 0;
}
