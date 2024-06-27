#include "strarr_util.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_str_to_strarr(const char *str, const char ***arr, size_t *arrlen)
{
	if (NULL == (*arr = realloc(*arr, sizeof(const char *) * (*arrlen + 1)))) {
		return;
	}

	if (NULL == ((*arr)[*arrlen] = malloc(strlen(str) + 1))) {
		return;
	}

	strcpy((char *)(*arr)[*arrlen], str);
	*arrlen = *arrlen + 1;
}

void remove_str_from_strarr(const char *str, const char ***arr, size_t *arrlen)
{

	size_t index = 0;
	int found = 0;

	for (index = 0; index < *arrlen; ++index) {
		if (strcmp((*arr)[index], str) == 0) {
			found = 1;
			break;
		}
	}

	if (!found) {
		return;
	}

	const char **newarr;
	if (NULL == (newarr = malloc((*arrlen - 1) * sizeof(const char *)))) {
		return;
	}

	// Copy elements, skipping the element to remove
	for (size_t i = 0, j = 0; i < *arrlen; ++i) {
		if (i != index) {
			newarr[j++] = (*arr)[i];
		}
	}

	if (*arr) {
		free((void *)(*arr)[index]);
		free(*arr);
	}

	errno = 0;
	*arrlen = *arrlen - 1;
	*arr = newarr;
}
