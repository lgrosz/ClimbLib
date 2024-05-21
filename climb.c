#include "climb.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct Climb_
{
	const char *name;
	const char *description;
	const char *brief;
};

// Frees str_addr contents and replaces them with str. Sets errno accordingly
static void free_allocate_and_assign_str(char const **str_addr, const char *str)
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
		Climb_free(ret);
		return NULL;
	} else {
		strcpy(name, "");
		ret->name = name;
	}

	char *description;
	if (NULL == (description = malloc(strlen("")+1))) {
		errno = ENOMEM;
		Climb_free(ret);
		return NULL;
	} else {
		strcpy(description, "");
		ret->description = description;
	}

	char *brief;
	if (NULL == (brief = malloc(strlen("")+1))) {
		errno = ENOMEM;
		Climb_free(ret);
		return NULL;
	} else {
		strcpy(brief, "");
		ret->brief = brief;
	}

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
	if (climb->name)	free((void*)climb->name);
	if (climb->description)	free((void*)climb->description);
	if (climb->brief)	free((void*)climb->brief);
	free(climb);
}

void Climb_set_name(Climb climb, const char *name)
{
	free_allocate_and_assign_str(&climb->name, name);
}

const char *Climb_name(Climb climb)
{
	return climb->name;
}

void Climb_set_description(Climb climb, const char *description)
{
	free_allocate_and_assign_str(&climb->description, description);
}

const char *Climb_description(Climb climb)
{
	return climb->description;
}

void Climb_set_brief(Climb climb, const char *description)
{
	free_allocate_and_assign_str(&climb->brief, description);
}

const char *Climb_brief(Climb climb)
{
	return climb->brief;
}
