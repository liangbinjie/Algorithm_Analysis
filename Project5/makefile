CC = gcc
CFLAGS = -Wall -g

all: main

main: main.o
	$(CC) $(CFLAGS) main.o -o main

main.o: main.c huffman_tree.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o main

