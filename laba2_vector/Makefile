all: main

main: main.o IntVector.o
	gcc -Wall main.o IntVector.o -o main

main.o: main.c
	gcc -Wall -c main.c

IntVector.o: IntVector.c
	gcc -Wall -c IntVector.c

clean:
	rm -rf *.o main