all : asm main

asm: main.asm
	nasm -f elf64 main.asm -o asm.o

main: main2.c 
	gcc -Wall main2.c asm.o

clean:
	rm -f *.o a.out