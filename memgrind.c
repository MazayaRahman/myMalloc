#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

struct testStruct{
    int testInt; //4 bytes
    char testChar; //1 bytes
}; //total size of struct should be 5 bytes

struct Node{
    int data; 
    Node* next;
};
  
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

    
    //TESTING WORKLOADS:
    //TESTING A: malloc and free 1 byte 150 times
    int i;
    for (i = 0; i <150; i++){
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
    int mallocs = 0, frees = 0;
    while(mallocs <= 50 ){ //while neither of them is not over 50
        if (mallocs == 50){ //free them all
            //TODO 
            break;
        }   

            
        int letsMalloc = rand() % 2; //either 1 or 0
        if (letsMalloc) {
            mallocs++;
            char* ptr = (char*) malloc(1); 
            //TODO insert into array?
        else{ //free
            if (mallocs == 0) //there is nothing to free
                continue;
            frees++;
            //TODO free something
        }
    }
    
    
    
    
    //OTHER WORKLOAD #1 - MALLOC A STRUCT    
    //OTHER WORKLOAD #2 - MALLOC A LINKED LIST
    return(0);
}
