CC := gcc
CFLAGS := -pedantic -Wextra -Wall -std=c11
#SRCS := src/game.c src/tetris.c 

game: game.o tictactoe.o
	$(CC) game.o tictactoe.o -o game 

game.o: src/game.c
	$(CC) $(CFLAGS) -c src/game.c

tictactoe.o: src/tictactoe.c 
	$(CC) $(CFLAGS) -c src/tictactoe.c	

run:
	./game 

.PHONY: clean

clean:
	rm *.o game
