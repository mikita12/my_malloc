#include "internal.h"
#include <stddef.h>
#include <stdio.h>

extern char *heap_listp;

void *find_fit(size_t asize){ //first fit

    char *bp = NEXT_BLKP(heap_listp);
    
    while(GET_SIZE(HDRP(bp))){

        if(GET_ALLOC(HDRP(bp)) == 0 && GET_SIZE(HDRP(bp)) >= asize){
            return bp;
        }

        bp = NEXT_BLKP(bp);
    }

    return NULL;
}

void place(void* bp, size_t asize){
    size_t csize = GET_SIZE(HDRP(bp));

    if(csize - asize >= DSIZE){
        
        PUT(HDRP(bp),PACK(asize,1));
        PUT(FTRP(bp),PACK(asize,1));
        
        char* bp2 = NEXT_BLKP(bp);
        
        PUT(HDRP(bp2),PACK(csize-asize,0));
        PUT(FTRP(bp2),PACK(csize-asize,0));

        return;
    }

    PUT(HDRP(bp),PACK(csize,1));
    PUT(FTRP(bp),PACK(csize,1));

    return;
}
