#include "internal.h"

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

}
