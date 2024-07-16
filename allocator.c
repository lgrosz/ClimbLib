#include "allocator.h"
#include <stdlib.h>

static climblib_malloc_t fn_malloc = NULL;
static climblib_realloc_t fn_realloc = NULL;
static climblib_free_t fn_free = NULL;

void climblib_set_alloc(climblib_malloc_t malloc, climblib_realloc_t realloc, climblib_free_t free)
{
	fn_malloc = malloc;
	fn_realloc = realloc;
	fn_free = free;
}

void climblib_get_alloc(climblib_malloc_t *malloc, climblib_realloc_t *realloc, climblib_free_t *free)
{
	if (malloc) *malloc = fn_malloc;
	if (realloc) *realloc = fn_realloc;
	if (free) *free = fn_free;
}

void *climblib_malloc(size_t size)
{
	if (fn_malloc) {
		return fn_malloc(size);
	}

	return malloc(size);
}

void *climblib_realloc(void *ptr, size_t size)
{
	if (fn_realloc) {
		return fn_realloc(ptr, size);
	}

	return realloc(ptr, size);
}

void climblib_free(void *ptr)
{
	if (fn_free) {
		return fn_free(ptr);
	}

	return free(ptr);
}
