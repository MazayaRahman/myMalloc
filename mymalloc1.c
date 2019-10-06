#include "mymalloc.h"
#define BLOCKSIZE 4096

static char myBlock[BLOCKSIZE];

//char* root = myBlock;

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
    printf("in findmem root: %d\n", *root);
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

        ptr = ptr + currSize + 2;
    }
    return ptr;


}

void split(char* block, unsigned int size){

    char* extra;
    int block_size = *(int*)(block+1);
    printf("in split block size: %d\n", block_size);

    //extra block size
    int extra_block_size = block_size - size - 2;
    printf("size of next extra: %d\n", extra_block_size);
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
		printf("HERE\n");
		return;
	}
}

void* mymalloc(unsigned int size, char* file, int line){
    printf("malloc is called!\n");
    if(size <= 0 || memoryLeft<=size || memoryLeft <= 2) return NULL;
    printf("attemping to malloc %d bytes! Therefore we need at least %d bytes. We have about %d left.\n",size,size+2,memoryLeft);
    printf("at root is: %d\n", *root);
    printf("at myblock is: %c\n", myBlock[0]);
    //check to see if root is initialized
    if(!*root){ //FIRST USE, MUST INSTANTIATE MEMORY BLOCK
        //set metadata as free
        printf("First use of malloc\n");
        struct metadata rootMetadata;
		rootMetadata.isFree = 1;
		rootMetadata.size = BLOCKSIZE -2;
		*root = rootMetadata.isFree;
		printf("root: %d\n", *root);
        //update the size of the whole block next
        *(int*)(root+1) = rootMetadata.size; //2 will be the min metadata we can use
    }

    //FIND A BLOCK OF MEM WITH GIVEN SIZE
    printf("looking for memory\n");
    char* freeMem = findMem(size);
    printf("freeMem is %d\n", *freeMem);
    if(freeMem != NULL){
        //check if block has too much available space
        //printf("found memory\n");
	printf("freeMem+1 is %d\n",*(int*)(freeMem+1));
        if(*(int*)(freeMem+1) > size){
            printf("leftover memory too big, splitting \n");
            split(freeMem,size);
        }
        if(freeMem == root){
            printf("theyre equal\n");
        }
	    *(freeMem) = 0;
	    *(int*) (freeMem+1) = size; //assign the metadata
        memoryLeft -= size + 2;
        printf("memory left after mallocing: %d\n",memoryLeft);
        printf("memory in use at root: %d\n", *(int*)(root+1));
        printf("at root is: %d\n", *root);
    }else{
        printf("no memory found\n");
        return NULL;
    }

    //return the pointer after metadata
    return  freeMem+2;
}

void myfree(void* addr, char* file, int line){
    //root = myBlock;
    printf("memory in use at root: %d\n", *(int*)(root+1));


}
/*
void myfree(void* addr, char* file, int line){
    if(addr == NULL){
        printf("invalid free\n");
        return;
    }
    char* ptr = root;
    printf("root's size: %d\n", *(int*)(root+1));
    char* prev = NULL;
    int currSize = 0;
    while(ptr != NULL){
        currSize = *(int*)(ptr+1);
        printf("currsize: %d\n", currSize);
        if(ptr == addr - 2){
            printf("found pointer\n");
            break; //cuz we found the ptr
        }else{
            prev = ptr;
            ptr = ptr + currSize + 2;
            //next = ptr + *(int*)(ptr+1)+ 2;
        }
    }
    if(ptr == NULL){
        printf("Doesn't exits\n");
        return;
    }

    if(prev != NULL){
        printf("here~\n");
        if(*prev == 1){
            printf("prev is free\n");
            *(int*)(prev+1) += *(int*)(ptr+1)+2;
            ptr = prev;
        }
    }


    char* next = ptr + *(int*)(ptr+1) + 2;
    next = 1;
    printf("%d\n", next);
    if(next == 1){
        printf("%d\n", next);
    }



    if(next != NULL && next != '\0'){
        printf("next is not null\n");
        printf("%p\n", next);
        if(next == 0){
            printf("next is free\n");
            *(int*)(ptr+1) += *(int*)(next+1)+2;
        }else{
            printf("hereeee\n");
        }
    }

    *ptr = 1;
}
*/
