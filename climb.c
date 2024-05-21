#include "climb.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct Climb_
{
	const char *name;
	const char *description;
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

	char *description;
	if (NULL == (description = malloc(strlen("")+1))) {
		errno = ENOMEM;
		free(ret);
		free(name);
		return NULL;
	}

	strcpy(description, "");
	ret->description = description;

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
	free((void*)climb->description);
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

void Climb_set_description(Climb climb, const char *description)
{
	errno = 0;
	if (climb->description) {
		free((void*)climb->description);
	}

	char *result;
	if (NULL == (result = malloc(strlen(description)+1))) {
		errno = ENOMEM;
		return;
	}

	strcpy(result, description);
	climb->description = result;
}

const char *Climb_description(Climb climb)
{
	return climb->description;
}
