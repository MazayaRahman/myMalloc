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
	else{
		if(ptr + currSize + size >= root + BLOCKSIZE -1) //there isnt enough space
			return NULL;
	}	
        
        ptr = ptr + currSize + 5;


    }
    return ptr;


}

void split(char* block, unsigned int size){

    char* extra;
    int block_size = *(int*)(block+1);

    //extra block size
    int extra_block_size = block_size - size -5;
	if (extra_block_size > 0){

	    extra = block + size + 5;
	    *extra = isFree;
	    *(int*)(extra+1) = block_size;
	    return;
	}
	else{ //idk what to do, there isnt enough space for metadata
		//TODO can we do anything? or just leave empty
		
	}
 

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
        //check if block has too much available space
        printf("found memory\n");
        if(*(int*)(freeMem+1) > size-5){
            printf("memory too big, splitting \n");
            split(freeMem,size);
        }
	*(freeMem) = inUse;
	*(int*) (freeMem+1) = size+5; //initialize the metadata

    }else{
        printf("no memory found\n");
        return NULL;
    }

    //return the pointer after metadata
    return freeMem+5;
}
