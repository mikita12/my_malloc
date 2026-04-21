#ifndef ALLOCATOR_H
#define ALLOCATOR_H


#include <stddef.h>

int mm_init(void);
void* my_malloc(size_t size);
void my_free(void* ptr);
void *coalesce(void *bp);
void *find_fit(size_t asize);
void place(void* bp, size_t asize);
void *extend_heap(size_t size);

#endif