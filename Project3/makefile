CC = gcc
CFLAGS = -Wall -g

all: main3

main3: main3.o huffman.o
	$(CC) $(CFLAGS) main3.o huffman.o -o main3

main.o: main.c huffman.h
	$(CC) $(CFLAGS) -c main.c

huffman.o: huffman.c huffman.h
	$(CC) $(CFLAGS) -c huffman.c

clean:
	rm -f *.o main3
