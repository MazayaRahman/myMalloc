all: memgrind.c mymalloc1.o
	gcc -Wall -Werror -fsanitize=address -std=c99 -o memgrind memgrind.c mymalloc1.o

mymalloc1.o: mymalloc1.c
	gcc -c mymalloc1.c

clean:
	rm -f memgrind; rm mymalloc1.o
