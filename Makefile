all: memgrind.c mymalloc.o
	gcc -fsanitize=address -std=c99 -o memgrind memgrind.c mymalloc.o

mymalloc.o: mymalloc.c
	gcc -c mymalloc.c

clean:
	rm -f memgrind; rm mymalloc.o
