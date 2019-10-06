#include "mymalloc.h"
#define BLOCKSIZE 4096

static char myBlock[BLOCKSIZE] = {'\0'};

char* root = myBlock;

struct metadata{
    unsigned short isFree: 4; //1 = free, 0 = in use
    unsigned short size: 12;
}; 
//short = 2 bytes = 16 bits; partition one short into status (isFree or not) and size of data needed
//we partition size into 12 bits because thats all we need (2^12 = 4096) rest of byte is status

int memoryLeft = 4096;

char* findMem(unsigned int size){

    //start at root
    char* ptr = root;
    int currSize = 0;
    
    while(ptr != NULL){
        currSize = *(int*)(ptr+1);
        printf("currSize compared to size: %d, %d\n", currSize,size);
        if(*ptr == 1 && currSize >= size){ 
            //found it
            //memoryLeft -= size+1;
            return ptr;
        }
	    else{
		    if(ptr + currSize + size >= root + BLOCKSIZE - 1){ //there isnt enough space
                printf("HERE\n");
                return NULL;
            }
	    }   	
        
        ptr = ptr + currSize + 1;
    }
    return ptr;


}

void split(char* block, unsigned int size){

    char* extra;
    int block_size = *(int*)(block+1);

    //extra block size
    int extra_block_size = block_size - size - 2;
	if (extra_block_size > 0){
        struct metadata extraMetadata;
        extraMetadata.isFree = 1;
        extraMetadata.size = extra_block_size;
	    extra = block + size + 2;
	    *extra = extraMetadata.isFree;
	    *(int*)(extra+1) = extraMetadata.size;
	    return;
	}
	else{ //idk what to do, there isnt enough space for metadata
		
		return;
	}
}

void* mymalloc(unsigned int size, char* file, int line){
    printf("malloc is called!\n");
    if(size <= 0 || memoryLeft<=size) return NULL;
    printf("attemping to malloc %d bytes! Therefore we need at least %d bytes. We have about %d left.\n",size,size+2,memoryLeft);

    //check to see if root is initialized
    if(root[0] == '\0'){ //FIRST USE, MUST INSTANTIATE MEMORY BLOCK
        //set metadata as free
        printf("First use of malloc\n");
        struct metadata rootMetadata;
		rootMetadata.isFree = 1;
		rootMetadata.size = BLOCKSIZE -2;
		*root = rootMetadata.isFree;
        //update the size of the whole block next
        *(int*)(root+1) = rootMetadata.size; //2 will be the min metadata we can use 
    }

    //FIND A BLOCK OF MEM WITH GIVEN SIZE
    printf("looking for memory\n");
    char* freeMem = findMem(size);

    if(freeMem != NULL){
        //check if block has too much available space
        printf("found memory\n");
        printf("freeMem+1 is %d\n",*(int*)(freeMem+1));
        if(*(int*)(freeMem+1) > size-2){
            printf("leftover memory too big, splitting \n");
            split(freeMem,size);
        }

	    *(freeMem) = 0;
	    *(int*) (freeMem+1) = size; //assign the metadata
        memoryLeft -= size + 2;
        printf("memory left after mallocing: %d\n",memoryLeft);
    }else{
        printf("no memory found\n");
        return NULL;
    }

    //return the pointer after metadata
    return  freeMem+2;
}
