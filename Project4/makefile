CC = gcc
CFLAGS = -Wall -g

all: main4

main4: main4.o
	$(CC) $(CFLAGS) main4.o -o main4

main4.o: main4.c huffman_codes.h
	$(CC) $(CFLAGS) -c main4.c

clean:
	rm -f *.o main4
