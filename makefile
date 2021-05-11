all: program

program: f.o square.o
	gcc -m32 f.o square.o -o program

square.o: square.c
	gcc -m32 -c square.c -o square.o

f.o: f.asm
	nasm -g -f elf32 -DUNIX f.asm -o f.o
	
clean:
	rm -rf *.o program