all: prog

prog: avl.o main.o compare.o
	gcc -g -Wall -std=c99 -o prog avl.o compare.o main.o 

compare.o: compare.c
	gcc -g -Wall -std=c99 -c compare.c 
		
main.o: main.c avl.h
	gcc -g -Wall -std=c99 -c main.c 
	
avl.o: avl.c avl.h
	gcc -g -Wall  -std=c99 -c avl.c 

clean:	
	rm avl.o
	rm main.o
	rm compare.o
	rm prog
