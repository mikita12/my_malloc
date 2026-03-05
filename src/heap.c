#include "allocator.h"
#include "internal.h"

//| padding | prologue header | prologue footer | epilogue header |

static char *heap_listp;

int mm_init(){

    char *heap = sbrk(4*WSIZE);
    if(heap == (void *)-1)
        return -1;
    
    PUT(heap,0); //padding

    PUT(heap + (1 * WSIZE), PACK(DSIZE,1)); //prologue header

    PUT(heap + (2 * WSIZE), PACK(DSIZE,1)); //prologue footer

    PUT(heap + (3 * WSIZE), PACK(0,1)); //epilogue header

    heap_listp = heap  + (2 * WSIZE);

    return 0;
}

void *extend_heap(size_t size ){

    size = (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1); //damn

    char *bp = sbrk(size);
    if(bp == (void *)-1)
        return NULL;

    PUT(bp, PACK(size,0));

    PUT(bp + size - WSIZE, PACK(size,0));

    PUT(bp + size, PACK(0,1));

    return coalesce(bp + WSIZE);
}

void *coalesce(void *bp){
    
}