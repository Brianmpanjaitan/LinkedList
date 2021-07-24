output: main.o list.o
	gcc -g -w main.o list.o -o print

main.o: main.c
	gcc -c main.c

List.o: List.c list.h
	gcc -c list.c

clean:
	rm *.o print
