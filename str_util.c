#include "str_util.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Frees str_addr contents and replaces them with str. Sets errno accordingly
void free_allocate_and_assign_str(char const **str_addr, const char *str)
{
	errno = 0;

	*str_addr = realloc((void*)*str_addr, strlen(str) + 1);

	if (*str_addr != NULL) {
		strcpy((char*)*str_addr, str);
	}
}
