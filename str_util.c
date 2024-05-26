#include "str_util.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Frees str_addr contents and replaces them with str. Sets errno accordingly
void free_allocate_and_assign_str(char const **str_addr, const char *str)
{
	errno = 0;

	if (*str_addr) {
		free((void*)*str_addr);
	}

	char *result;
	if (NULL == (result = malloc(strlen(str)+1))) {
		errno = ENOMEM;
		return;
	}

	strcpy(result, str);
	*str_addr = result;
}
