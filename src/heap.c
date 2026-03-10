#include "allocator.h"
#include "internal.h"

//| padding | prologue header | prologue footer | epilogue header |

static char *heap_listp; //heap start

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

void *coalesce(void *bp){

    size_t size = GET_SIZE(HDRP(bp));
    size_t sizeBuf;

    bool prev = GET_ALLOC(HDRP(PREV_BLKP(bp)));
    bool next = GET_ALLOC(HDRP(NEXT_BLKP(bp)));

    if(prev && next){
        return bp;
    }else if(prev && !next){

        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp),PACK(size,0));
        PUT(FTRP(bp),PACK(size,0));

    }else if(!prev && next){

        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        bp = PREV_BLKP(bp);

        PUT(HDRP(bp),PACK(size,0));
        PUT(FTRP(bp),PACK(size,0));

    }else{

        char *bp_next;
        char *bp_prev;

        bp_next = NEXT_BLKP(bp);
        bp_prev = PREV_BLKP(bp);

        size += GET_SIZE(HDRP(bp_next)) + GET_SIZE(HDRP(bp_prev));

        PUT(HDRP(bp_prev),PACK(size,0));
        PUT(FTRP(bp_next),PACK(size,0));

        bp = bp_prev;
    }

    return (char *)(bp); //adres wskazujacy na payload polaczonego bloku
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

//|   FREE  |ALLOCATED|   FREE  |
//|ALLOCATED|ALLOCATED|   FREE  |
//|   FREE  |ALLOCATED|ALLOCATED|
//|ALLOCATED|ALLOCATED|ALLOCATED|

