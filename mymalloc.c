#include "mymalloc.h"
#define BLOCKSIZE 4096

static char myBlock[BLOCKSIZE] = {'\0'};

struct metadata* root = (struct metadata*)myBlock;
int initialized = 0;

struct metadata{
    unsigned short isFree: 4; //1 = free, 0 = in use
    unsigned short size: 12;
};
//short = 2 bytes = 16 bits; partition one short into status (isFree or not) and size of data needed
//we partition size into 12 bits because thats all we need (2^12 = 4096) rest of byte is status

int memoryLeft = 4096;

struct metadata* findMem(unsigned int size, char* file, int line){

    //start at root
    struct metadata* ptr = root;
    int currSize = 0;
    //printf("in findmem root: %d\n", root->size);
    while(ptr != NULL){
        //currSize = *(int*)(ptr+1);
        currSize = ptr->size;
        //printf("currSize compared to size: %d, %d\n", currSize,size);
        if(ptr->isFree == 1 && currSize >= size){
            //found it
            //memoryLeft -= size+1;
            return ptr;
        }
	    else{
		    if(ptr + currSize + size >= root + BLOCKSIZE - 1){ //there isnt enough space
                printf("saturation of dynamic memory in FILE: '%s' on LINE: '%d'\n", file, line);
                return NULL;
            }
	    }

        ptr = ptr + currSize + sizeof(struct metadata);
    }
    return ptr;


}

void split(struct metadata* block, unsigned int size){

    struct metadata* extra;
    int block_size = block->size;
    //printf("in split block size: %d\n", block_size);

    //extra block size
    int extra_block_size = block_size - size - sizeof(struct metadata);
    //printf("size of next extra: %d\n", extra_block_size);
	if (extra_block_size > 0){
	    extra = block + size + sizeof(struct metadata);
	    extra->isFree = 1;
	    extra->size = extra_block_size;
	    return;
	}
	else{ //idk what to do, there isnt enough space for metadata
		//printf("HERE\n");
		return;
	}
}

void* mymalloc(unsigned int size, char* file, int line){
    //printf("malloc is called!\n");
    if(size <= 0){
	//printf("Unable to allocate 0 bytes in FILE: '%s' on LINE: '%d'\n", file, line);
	 return NULL;
    }
	//printf("attemping to malloc %d bytes! Therefore we need at least %d bytes. We have about %d left.\n",size,size+2,memoryLeft);
    //check to see if root is initialized
    if(initialized == 0){ //FIRST USE, MUST INSTANTIATE MEMORY BLOCK
        //set metadata as free
        //printf("First use of malloc\n");
        initialized = 1;
        struct metadata rootMetadata;
		rootMetadata.isFree = 1;
		rootMetadata.size = BLOCKSIZE - sizeof(struct metadata);
		*(struct metadata*)root = rootMetadata;

        //update the size of the whole block next
        //*(int*)(root+1) = rootMetadata.size; //2 will be the min metadata we can use
    }

    //FIND A BLOCK OF MEM WITH GIVEN SIZE
    struct metadata* freeMem = findMem(size, file, line);
    //printf("freeMem is %d\n", freeMem->isFree);
    if(freeMem != NULL){
        //check if block has too much available space
        //printf("found memory\n");
        if(freeMem->size > size){
            //printf("leftover memory too big, splitting \n");
            split(freeMem,size);
        }

	    freeMem->isFree = 0;
	    freeMem->size = size; //assign the metadata
        memoryLeft -= size + 2;
        //printf("memory left after mallocing: %d\n",memoryLeft);
        //printf("memory in use at root: %d\n", root->size);
    }else{
        //printf("no memory found\n");
        return NULL;
    }

    //return the pointer after metadata
    //printf("freemem is: %d\n", freeMem->isFree);
    return  freeMem+sizeof(struct metadata);
}

void myfree(void* addr, char* file, int line){
   //check if addr is null or has already been freed
    if(addr == NULL){
        printf("Attempting to free memory that was not malloced in FILE: '%s' on LINE: '%d'\n", file, line);
        return;
    }

    struct metadata *ptr = root;
    //printf("root's size: %d\n", ptr->size);
    struct metadata *prev = NULL;
    int currSize = 0;

    while(ptr != NULL){
    //printf("addr is %p\n", addr);
    //printf("ptr is %p\n", ptr+sizeof(struct metadata));
       if(ptr + sizeof(struct metadata) == addr) {
            //printf("found pointer\n");
            break; //cuz we found the ptr
        }else{
	currSize = ptr->size;
        //printf("currsize: %d\n", currSize);

            prev = ptr;
            //printf("ptr size: %d\n", ptr->size);
            ptr = ptr + currSize + sizeof(struct metadata);
            if(ptr >= root + BLOCKSIZE - 1) break;
        }
    }

	//printf("out of the loop!\n");
    if(ptr >= root + BLOCKSIZE - 1){
        printf("Attempting to free memory that was not malloced in FILE: '%s' on LINE: '%d'\n", file, line);
        return;
    }
if (ptr->isFree == 1){
	printf("Redundant free of the same pointer in FILE: '%s' on LINE: '%d'\n", file, line);
	return;
}
    if(prev != NULL){
        if(prev->isFree == 1){
            //printf("prev is free\n");
            prev->size += ptr->size + sizeof(struct metadata);
            ptr = prev;
        }
    }


    struct metadata *next = ptr + ptr->size + sizeof(struct metadata);

    if(next != NULL){ //if next is past the array bounds

        if(next->isFree == 1){
            //printf("next is free\n");
            ptr->size += next->size + sizeof(struct metadata);
        }
    }

    ptr->isFree = 1;
    memoryLeft += ptr->size;
    //printf("free complete!\n");
}

