CC = gcc
CFLAGS = -Wall -g

all: main4

main4: main.o
	$(CC) $(CFLAGS) main.o -o main4

main.o: main.c huffman_codes.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o main4
