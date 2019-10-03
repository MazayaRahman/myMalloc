#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

int main(int argc, char* argv[]){

    printf("program initiated\n");


    char* one = malloc(8);
    one = "hello";
    char* two = malloc(10);
    two = "HOLAAA";

    printf("8 %p \n", one);
    printf("%s\n", one);

    printf("10 %p \n", two);
    printf("%s\n", two);

    one = "Bye";
    printf("%s\n", one);

    return(0);
}
