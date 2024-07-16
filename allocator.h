#ifndef _CLIMBLIB_ALLOCATOR_H_
#define _CLIMBLIB_ALLOCATOR_H_

#include <stddef.h>

typedef void *(*climblib_malloc_t)(size_t);
typedef void *(*climblib_realloc_t)(void *, size_t);
typedef void (*climblib_free_t)(void *);

void climblib_set_alloc(climblib_malloc_t, climblib_realloc_t, climblib_free_t);
void climblib_get_alloc(climblib_malloc_t *, climblib_realloc_t *, climblib_free_t *);

void *climblib_malloc(size_t);
void *climblib_realloc(void *, size_t);
void climblib_free(void *);

#endif
