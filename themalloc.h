#ifndef _themalloc_h_
#define _themalloc_h_

#include <stdlib.h>
#include <stdio.h>

#define malloc( x ) mymalloc( x,__FILE__,__LINE__ )
#define free( x ) myfree( x,__FILE__,__LINE__ )

char memory[4096];

struct metadata{
    unsigned short isFree: 4; //1 = free, 0 = in use
    unsigned short size: 12;
};

struct metadata *base;

void initialize();
void* mymalloc(unsigned int size, char* file, int line);
void myfree(void* addr, char* file, int line);

#endif // _themalloc_h_
