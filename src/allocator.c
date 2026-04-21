#include "allocator.h"
#include "internal.h"
#include <stdio.h>

static int initialized = 0;

void *my_malloc(size_t size) {
  if (!initialized) {
    if (mm_init() == -1)
      return NULL;
    initialized = 1;
  }

  if (size == 0)
    return NULL;

  size_t asize = (size + OVERHEAD + (ALIGNMENT - 1)) &
                 ~(ALIGNMENT - 1); // zaokraglanie do 16

  void *bp = find_fit(asize);

  if (bp != NULL) {
    place(bp, asize);
    return bp;
  }

  size_t extendsize = (asize > CHUNKSIZE) ? asize : CHUNKSIZE;

  bp = extend_heap(extendsize);

  if (bp == NULL)
    return NULL;

  place(bp, asize);
  return bp;
}

void my_free(void *ptr) {
  if (ptr == NULL)
    return;

  size_t size = GET_SIZE(HDRP(ptr));

  PUT(HDRP(ptr), PACK(size, 0));
  PUT(FTRP(ptr), PACK(size, 0));

  coalesce(ptr);
}
