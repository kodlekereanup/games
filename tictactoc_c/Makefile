CC := gcc
CFLAGS := -pedantic -Wextra -Wall -std=c11
#SRCS := src/game.c src/tetris.c 

game: game.o tictactoe.o
	$(CC) game.o tictactoe.o -o game 
	mv game.o build/
	mv tictactoe.o build/
	mv game build/

game.o: src/game.c
	$(CC) $(CFLAGS) -c src/game.c

tictactoe.o: src/tictactoe.c 
	$(CC) $(CFLAGS) -c src/tictactoe.c	

run:
	build/./game 

test:
	gcc tests/test.c -o test
	mv test tests/
	tests/./test 

.PHONY: clean

clean:
	rm build/*
	rm tests/test
