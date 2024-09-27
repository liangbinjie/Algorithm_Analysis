CC = gcc
CFLAGS = -Wall -g

all: main

main: main.o huffman.o
	$(CC) $(CFLAGS) main.o huffman.o -o main

main.o: main.c huffman.h
	$(CC) $(CFLAGS) -c main.c

huffman.o: huffman.c huffman.h
	$(CC) $(CFLAGS) -c huffman.c

clean:
	rm -f *.o main
