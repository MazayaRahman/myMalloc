#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"


struct Node{
    int data;
    struct Node* next;
};


void workloadA(){
    int i;
    for (i = 0; i <150; i++){
        //printf("iteration i: %d\n", i);
        char* test = (char*) malloc(1);
        free(test);
    }
}

void workloadB(){
    int counter = 0, i;
    void* pointers[50];
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
    void* pointers[50];
    while(mallocs <= 50 ){ //while we havent reached 50 mallocs
        if (mallocs == 50){ //free them all
            
            break;
        }

        int letsMalloc = rand() % 2; //either 1 or 0
        if (letsMalloc) {
            mallocs++;
            char* ptr = (char*) malloc(1);
            pointers[i] = ptr;
            i++;
            
        }else{ //free
            if (i == 0) //there is nothing to free
                continue;
            else{
                free(pointers[i-1]);
                i--;
            }

            
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
    void* pointers[50];
    while(mallocs <= 50 ){ //while we havent reached 50 mallocs
        if (mallocs == 50){ //free them all
           
            break;
        }
        int letsMalloc = rand() % 2; //either 1 or 0
        if (letsMalloc) {
            mallocs++;
            int size = rand() % 64 + 1;
            char* ptr = (char*) malloc(1*size);
            pointers[i] = ptr;
            i++;
            
        }else{ //free
            if (i == 0) //there is nothing to free
                continue;
            else{
                free(pointers[i-1]);
                i--;
            }
       }
    }
    //free rest of ptrs
    i--;
    while(i >= 0){
        free(pointers[i]);
        i--;
    }
}

void createLL(struct Node** front){
    int i;
    for (i = 1; i<=50;i++){
        struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
       
        newNode->data = i;
        newNode->next = NULL;
         
        struct Node *ptr = *front;
        
        while(ptr->next != NULL){
            ptr = ptr->next;
            
        }
        ptr->next = newNode;
    }
}

void workloadE(){
    struct Node* front = (struct Node*) malloc(sizeof(struct Node));
    front->data = 0;
    front->next = NULL;
    //create LL
    createLL(&front);
    
    //free the LL
    struct Node* ptr = front;
    while(ptr!=NULL){
        
        struct Node* tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}

void workloadF(){
    char* str = "I love CS214 more than anything else!";
    
    int i;
    for (i = 0; i < 150; i++){
	    char* ptr = (char*) malloc(sizeof(char)*strlen(str));
            if (ptr != NULL){
		        strcpy(ptr,str);
		        free(ptr);
            }
    }
    


   
}

int main(int argc, char* argv[]){

    //printf("program initiated\n");
	
    //initialize total runtime
	float runtimeA = 0, runtimeB = 0, runtimeC = 0, runtimeD = 0,runtimeE = 0,runtimeF = 0;

    int workloads;
	for(workloads=1;workloads<=100;workloads++){

	    //initialize clock for each workload
	    struct timeval startA, startB, startC, startD, startE, startF, endA, endB, endC, endD, endE, endF;
	    //TESTING WORKLOADS:
    	
        //TESTING A: malloc and free 1 byte 150 times
    	gettimeofday(&startA,NULL);
	    workloadA();
		gettimeofday(&endA,NULL);
		runtimeA += (float)(endA.tv_usec-startA.tv_usec);
	    
        //TESTING B: malloc and store
	    gettimeofday(&startB,NULL);
	    workloadB();
		gettimeofday(&endB,NULL);
		runtimeB += (float)(endB.tv_usec-startB.tv_usec);
	    
        //TESTING C: random
		gettimeofday(&startC,NULL);
	    workloadC();
		gettimeofday(&endC,NULL);
		runtimeC += (float)(endC.tv_usec-startC.tv_usec);
   	    
        //TESTING D: random
   	 	gettimeofday(&startD,NULL);
	    workloadD();
		gettimeofday(&endD,NULL);
		runtimeD += (float)(endD.tv_usec-startD.tv_usec);
       	
        //OTHER WORKLOAD #1 - MALLOC A LL
       	gettimeofday(&startE,NULL);
	    workloadE();
		gettimeofday(&endE,NULL);
		runtimeE += (float)(endE.tv_usec-startE.tv_usec);
        
        //OTHER WORKLOAD #2 - STRCPY AND FREE
		gettimeofday(&startF,NULL);
	    workloadF();
		gettimeofday(&endF,NULL);
		runtimeF += (float)(endF.tv_usec-startF.tv_usec);
	
	}

    printf("totalA: %f\ntotalB: %f\ntotalC: %f\ntotalD: %f\ntotalE: %f\ntotalF: %f\n",runtimeA,runtimeB,runtimeC,runtimeD,runtimeE,runtimeF);

	//calculate avg
	float avgA = runtimeA/100, avgB = runtimeB/100, avgC = runtimeC/100, avgD = runtimeD/100, avgE = runtimeE/100, avgF = runtimeF/100;
	//print the mean runtime in order of workload? or in order of time? TODO
	printf("meanA: %f\nmeanB: %f\nmeanC: %f\nmeanD: %f\nmeanE: %f\nmeanF: %f\n",avgA,avgB,avgC,avgD,avgE,avgF);

    return(0);
}
