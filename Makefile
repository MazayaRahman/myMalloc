all: memgrind.c themalloc.o
	gcc -Wall -Werror -std=c99 -o memgrind memgrind.c themalloc.o

themalloc.o: themalloc.c
	gcc -c themalloc.c

clean:
	rm -f memgrind; rm themalloc.o
