CC := gcc
# clang src/game.c -o main `pkg-config --libs --cflags SDL2_image sdl2`
#CFLAGS :=
#SRCS :=
#OBJS :=

game: game.o tetris.o
	$(CC) game.o tetris.o -o game -lSDL2 -lSDL2_image 
	@mv game build/
	@mv tetris.o build/
	@mv game.o build/

game.o: src/game.c
	$(CC) src/game.c -c 

tetris.o: src/tetris.c includes/tetris.h
	$(CC) src/tetris.c -c

run:
	build/./game

.PHONY: clean

clean:
	rm build/* 
