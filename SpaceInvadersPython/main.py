#!/usr/bin/python3.8

import pygame
import os
import time
import random

# initialize the font to draw text inside thw window
pygame.font.init()

# Initialize WIndow Size and Window properties 
WIDTH, HEIGHT = 800, 600
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Space Invaders")

# Load game assets
RED_SPACE_SHIP    = pygame.image.load(os.path.join("assets", "pixel_ship_red_small.png"))
GREEN_SPACE_SHIP  = pygame.image.load(os.path.join("assets", "pixel_ship_green_small.png"))
BLUE_SPACE_SHIP   = pygame.image.load(os.path.join("assets", "pixel_ship_blue_small.png"))
YELLOW_SPACE_SHIP = pygame.image.load(os.path.join("assets", "pixel_ship_yellow.png"))

RED_LASER    = pygame.image.load(os.path.join("assets", "pixel_laser_red.png"))
GREEN_LASER  = pygame.image.load(os.path.join("assets", "pixel_laser_green.png"))
BLUE_LASER   = pygame.image.load(os.path.join("assets", "pixel_laser_blue.png"))
YELLOW_LASER = pygame.image.load(os.path.join("assets", "pixel_laser_yellow.png"))

BG = pygame.transform.scale(pygame.image.load(os.path.join("assets", "background-black.png")), (WIDTH, HEIGHT))

def main():
    run = True
    FPS = 60
    level = 1
    lives = 5
    main_font = pygame.font.SysFont('consolas', 30)

    # Why is this clock needed? 
    clock = pygame.time.Clock()

    def redraw_window():
        # blit on the surface, at 60 fps
        WIN.blit(BG, (0, 0))
        # draw font
        lives_label = main_font.render(f"Lives : {lives}", 1, (255, 255, 255))
        level_label = main_font.render(f"Level : {level}", 1, (255, 255, 255))

        WIN.blit(lives_label,  (10, 10))
        WIN.blit(level_label,  (WIDTH - level_label.get_width() - 10, 10))
        pygame.display.update()
    while run:
        clock.tick(FPS)
        redraw_window()

        # check if the user has pressed quit
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False


main()