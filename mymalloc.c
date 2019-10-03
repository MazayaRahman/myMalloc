#include "mymalloc.h"
#define BLOCKSIZE 4096

static char myBlock[BLOCKSIZE] = {'\0'};

char* root = myBlock;

const char isFree = 'f';
const char inUse = 'u';

char* findMem(unsigned int size){

    //start at root
    char* ptr = root;
    int currSize = 0;

    while(ptr != NULL){
        currSize = *(int*)(ptr+1);
        if(*ptr == isFree && currSize >= size + 5){
            //found it
            return ptr;
        }
        //deal with other cases like overflow
        ptr = ptr + currSize;


    }
    return ptr;


}

void split(char* block, unsigned int size){

    char* extra;
    int block_size = *(int*)(block+1);

    //extra block size
    block_size = block_size - size - 5;

    extra = block + size + 5;
    *extra = isFree;
    *(int*)(extra+1) = block_size;
    *(block) = inUse;
    *(int*)(block+1) = size+5;


}

void* mymalloc(unsigned int size, char* file, int line){
    printf("malloc is called!\n");
    if(size <= 0) return NULL;

    //check to see if root is initialized
    if(root[0] == '\0'){ //FIRST USE, MUST INSTANTIATE MEMORY BLOCK
        //set as free
        printf("First use of malloc\n");
        *root = isFree;
        //update the size of the whole block next
        *(int*)(root+1) = BLOCKSIZE - 5; //5 will be the min metadata we can use (1 bit for char, 4 bits for int size)
    }

    //FIND A BLOCK OF MEM WITH GIVEN SIZE
    printf("looking for memory\n");
    char* freeMem = findMem(size);

    if(freeMem != NULL){
        //check if block is too big
        printf("found memory\n");
        if(*(int*)(freeMem+1) > size){
            printf("memory too big, splitting \n");
            split(freeMem,size);
        }

    }else{
        printf("no memory found\n");
        return NULL;
    }

    //return the pointer after metadata
    return freeMem+5;


}
