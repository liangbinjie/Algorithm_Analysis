all : asm main

asm: main.asm
	nasm -f elf64 main.asm -o asm.o

main: main.c 
	gcc -Wall main.c asm.o

clean:
	rm -f *.o a.out