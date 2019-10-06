#include <stdlib.h>
#include <stdio.h>
//#include "mymalloc.h"
#include "mymalloc.h"

//TESTING THIS NEW COMMIT

struct testStruct{
    char testChar; //1 bytes
    int testInt; //4 bytes

}; //total size of struct should be 5 bytes

typedef struct Node{
    int data;
    struct Node* next;
}Node;

int main(int argc, char* argv[]){

    printf("program initiated\n");
/*
    struct testStruct* test = malloc((sizeof(struct testStruct)));
    test->testChar = 'm';
    test->testInt = 13;

    free(test);
*/
    //char* ptr = (char*) malloc(sizeof(char)*12);
    //ptr[0] = 'm'; ptr[1] = 'p';
    //TODO: why does initializing thing change the address
    //int* arr = (int*) malloc(3*sizeof(int));
    //arr[0] = 3;
    //free(ptr);
    //free(arr);



//TESTING WORKLOADS:
    //TESTING A: malloc and free 1 byte 150 times
    /*
    int i;
    for (i = 0; i <150; i++){
        printf("iteration i: %d\n", i);
        char* test = (char*) malloc(1);
        free(test);
    }


    //TESTING B: malloc and store
    int counter = 0;
    char** pointers[50];
    for (i = 0; i < 150; i++){
        char* ptr = (char*) malloc(1);
        pointers[counter] = ptr;
        counter++;
        if (counter == 50){ //array is full
            int j;
            for (j = 0; j < 50; j++)
                free(pointers[j]);
            counter = 0;
        }
    }


    //TESTING C: random
    //TODO keep array of char pointers
    int mallocs = 0, i = 0;
    char** pointers[50];
    while(mallocs <= 50 ){ //while neither of them is not over 50
        if (mallocs == 50){ //free them all
            //TODO
            break;
        }


        int letsMalloc = rand() % 2; //either 1 or 0
        if (letsMalloc) {
            mallocs++;
            char* ptr = (char*) malloc(1);
            pointers[i] = ptr;
            i++;
            //TODO insert into array?
        }else{ //free
            if (i == 0) //there is nothing to free
                continue;
            else{
                free(pointers[i-1]);
                i--;
            }
            //frees++;
            //TODO free something
        }
    }
    //free rest of ptrs
    i--;
    while(i >= 0){
        free(pointers[i]);
        i--;
    }


    //TESTING D: random
    //TODO keep array of char pointers
    int mallocs = 0, i = 0;
    char** pointers[50];
    while(mallocs <= 50 ){ //while neither of them is not over 50
        if (mallocs == 50){ //free them all
            //TODO
            break;
        }


        int letsMalloc = rand() % 2; //either 1 or 0
        if (letsMalloc) {
            mallocs++;
            int size = rand() % 64 + 1;
            char* ptr = (char*) malloc(1*size);
            pointers[i] = ptr;
            i++;
            //TODO insert into array?
        }else{ //free
            if (i == 0) //there is nothing to free
                continue;
            else{
                free(pointers[i-1]);
                i--;
            }
            //frees++;
            //TODO free something
        }
    }
    //free rest of ptrs
    i--;
    while(i >= 0){
        free(pointers[i]);
        i--;
    }

    //OTHER WORKLOAD #1 - MALLOC A STRUCT

    int i;
    for (i = 0; i <150; i++){
        printf("iteration i: %d\n", i);
        struct testStruct* test = (struct testStruct*) malloc(1*sizeof(struct testStruct));
        free(test);
    }
*/
    //OTHER WORKLOAD #2 - MALLOC A LINKED LIST

    char* p = (char*)(malloc(4096-2));
    char* q = malloc(1);

    return(0);
}
