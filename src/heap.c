#include "allocator.h"

//| padding | prologue header | prologue footer | epilogue header |

int mm_init(){

    char *heap = sbrk(4*WSIZE);
    if(heap == (void *)-1)
        return -1;
    
    PUT(heap,0); //padding

    PUT(heap + (1 * WSIZE), PACK(DSIZE,1)); //prologue header

    PUT(heap + (2 * WSIZE), PACK(DSIZE,1)); //prologue footer

    PUT(heap + (3 * WSIZE), PACK(0,1)); //epilogue header

    return 0;

}