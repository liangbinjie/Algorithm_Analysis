CC = gcc
CFLAGS = -Wall -g

all: main5

main5: main5.o
	$(CC) $(CFLAGS) main5.o -o main5

main5.o: main5.c huffman_tree.h
	$(CC) $(CFLAGS) -c main5.c

clean:
	rm -f *.o main5

