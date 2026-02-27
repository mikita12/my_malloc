#ifndef INTERNAL_H
#define INTERNAL_H

#include <unistd.h>
#include <stdint.h>

#define WSIZE       8
#define DSIZE       16
#define ALIGNMENT   16

#define CHUNKSIZE   (1 << 12)

#define OVERHEAD    (2 * WSIZE)

#define PACK(size, alloc)   ((size) | (alloc))

#define GET(p)              (*(size_t *)(p))
#define PUT(p, val)         (*(size_t *)(p) = (val))

#define GET_SIZE(p)         (GET(p) & ~0xF)
#define GET_ALLOC(p)        (GET(p) & 0x1)

#define HDRP(bp)            ((char *)(bp) - WSIZE)
//#define FTRP(bp)            ((