#include "themalloc.h"


void initialize(){
    printf("the size of metadata is: %d\n", sizeof(struct metadata));
    base->size = 4096 - sizeof(struct metadata);
    base->isFree = 1;
}

void* mymalloc(unsigned int size, char* file, int line){
    printf("malloc called!");
    if(!(base->size)){
        initialize();
        printf("memory initialized\n");
    }


}
