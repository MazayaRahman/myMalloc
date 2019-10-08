#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
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



void workloadA(){
    int i;
    for (i = 0; i <150; i++){
        printf("iteration i: %d\n", i);
        char* test = (char*) malloc(1);
        free(test);
    }
}

void workloadB(){
    int counter = 0, i;
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

}

void workloadC(){

    int mallocs = 0, i = 0;
    char** pointers[50];
    while(mallocs <= 50 ){ //while we havent reached 50 mallocs
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
}

void workloadD(){

    int mallocs = 0, i = 0;
    char** pointers[50];
    while(mallocs <= 50 ){ //while we havent reached 50 mallocs
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
}

void workloadE(){

    int i;
    for (i = 0; i <150; i++){
        printf("iteration i: %d\n", i);
        struct testStruct* test = (struct testStruct*) malloc(1*sizeof(struct testStruct));
        free(test);
    }
}

void workloadF(){
    char* p = (char*)(malloc(4096-2));
    char* q = malloc(1);

}

int main(int argc, char* argv[]){

    printf("program initiated\n");


    //TODO: memcpy
    char* testPointer = (char*) malloc(12*sizeof(char));
    testPointer = "Mazaya&Priya";
    //strcpy(testPointer,str);

    printf("value at ptr in our heap: %s\n", testPointer);

    free(testPointer);

/*
    //initialize total runtime
	float runtimeA = 0, runtimeB = 0, runtimeC = 0, runtimeD = 0,runtimeE = 0,runtimeF = 0;

    int workloads = 0;
	while (workloads < 100){

	    //initialize clock for each workload
	    struct timeval startA, startB, startC, startD, startE, startF, endA, endB, endC, endD, endE, endF;
	    //TESTING WORKLOADS:
    	//TESTING A: malloc and free 1 byte 150 times
    	gettimeofday(&startA,NULL);
	    workloadA();
		gettimeofday(&endA,NULL);
		runtimeA += (float)(endA.tv_sec-startA.tv_sec);
	    //TESTING B: malloc and store
	    gettimeofday(&startB,NULL);
	    workloadB();
		gettimeofday(&endB,NULL);
		runtimeB += (float)(endB.tv_sec-startB.tv_sec);
	    //TESTING C: random
		gettimeofday(&startC,NULL);
	    workloadC();
		gettimeofday(&endC,NULL);
		runtimeC += (float)(endC.tv_sec-startC.tv_sec);
   	    //TESTING D: random
   	 	gettimeofday(&startD,NULL);
	    workloadD();
		gettimeofday(&endD,NULL);
		runtimeD += (float)(endD.tv_sec-startD.tv_sec);
       	//OTHER WORKLOAD #1 - MALLOC A STRUCT
       	gettimeofday(&startE,NULL);
	    workloadE();
		gettimeofday(&endE,NULL);
		runtimeE += (float)(endE.tv_sec-startE.tv_sec);
        //OTHER WORKLOAD #2 - MALLOC A LINKED LIST
		gettimeofday(&startF,NULL);
	    workloadF();
		gettimeofday(&endF,NULL);
		runtimeF += (float)(endF.tv_sec-startF.tv_sec);

		workloads++;
	}

    printf("totalA: %f\ntotalB: %f\ntotalC: %f\ntotalD: %f\ntotalE: %f\ntotalF: %f\n",runtimeA,runtimeB,runtimeC,runtimeD,runtimeE,runtimeF);


	//calculate avg
	float avgA = runtimeA/100, avgB = runtimeB/100, avgC = runtimeC/100, avgD = runtimeD/100, avgE = runtimeE/100, avgF = runtimeF/100;
	//print the mean runtime in order of workload? or in order of time? TODO
	printf("mean A: %f\nmeanB: %f\nmeanC: %f\nmeanD: %f\nmeanE: %f\nmeanF: %f\n",avgA,avgB,avgC,avgD,avgE,avgF);

*/
    return(0);
}
