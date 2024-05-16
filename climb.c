#include "climb.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct Climb_
{
	const char *name;
};

Climb Climb_new()
{
	Climb ret;

	if (NULL == (ret = malloc(sizeof(struct Climb_)))) {
		errno = ENOMEM;
		return NULL;
	}

	char *name;
	if (NULL == (name = malloc(strlen("")+1))) {
		errno = ENOMEM;
		free(ret);
		return NULL;
	}

	strcpy(name, "");
	ret->name = name;

	errno = 0;
	return ret;
}

void Climb_free(Climb climb)
{
	if (climb == NULL) {
		errno = EINVAL;
		return;
	}

	errno = 0;
	free((void*)climb->name);
	free(climb);
}

void Climb_set_name(Climb climb, const char *name)
{
	errno = 0;
	if (climb->name) {
		free((void*)climb->name);
	}

	char *result;
	if (NULL == (result = malloc(strlen(name)+1))) {
		errno = ENOMEM;
		return;
	}

	strcpy(result, name);
	climb->name = result;
}

const char *Climb_name(Climb climb)
{
	return climb->name;
}
