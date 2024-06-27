#include "climb.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "str_util.h"
#include "strarr_util.h"

struct Climb_
{
	const char *name;
	const char *description;
	const char *brief;
	const char **aliases;
	size_t aliaseslen;
};

static int contains(const char **strs, size_t len, const char *str)
{
	for (int i = 0; i < len; i++) {
		if (strcmp(strs[i], str) == 0) {
			return 1;
		}
	}

	return 0;
}

Climb *Climb_new()
{
	Climb *ret;

	if (NULL == (ret = malloc(sizeof(Climb)))) {
		return NULL;
	} else {
		ret->name = NULL;
		ret->description = NULL;
		ret->brief = NULL;
		ret->aliases = NULL;
	}

	Climb_set_name(ret, "");
	Climb_set_description(ret, "");
	Climb_set_brief(ret, "");

	ret->aliaseslen = 0;

	errno = 0;
	return ret;
}

void Climb_free(Climb *climb)
{
	if (climb == NULL) {
		errno = EINVAL;
		return;
	}

	errno = 0;
	if (climb->name)	free((void*)climb->name);
	if (climb->description)	free((void*)climb->description);
	if (climb->brief)	free((void*)climb->brief);

	if (climb->aliases) {
		for (int i = 0; i < climb->aliaseslen; i++) {
			free((void*)climb->aliases[i]);
		}

		free(climb->aliases);
	}

	free(climb);
}

void Climb_set_name(Climb *climb, const char *name)
{
	free_allocate_and_assign_str(&climb->name, name);
}

const char *Climb_name(const Climb *climb)
{
	return climb->name;
}

void Climb_set_description(Climb *climb, const char *description)
{
	free_allocate_and_assign_str(&climb->description, description);
}

const char *Climb_description(const Climb *climb)
{
	return climb->description;
}

void Climb_set_brief(Climb *climb, const char *description)
{
	free_allocate_and_assign_str(&climb->brief, description);
}

const char *Climb_brief(const Climb *climb)
{
	return climb->brief;
}

void Climb_add_alias(Climb *climb, const char *alias)
{
	if (climb == NULL) {
		errno = EINVAL;
		return;
	}

	errno = 0;

	if (contains(climb->aliases, climb->aliaseslen, alias)) {
		return;
	}

	add_str_to_strarr(alias, &climb->aliases, &climb->aliaseslen);
}

void Climb_remove_alias(Climb *climb, const char *alias)
{
	if (climb == NULL) {
		errno = EINVAL;
		return;
	}

	remove_str_from_strarr(alias, &climb->aliases, &climb->aliaseslen);
}

const char **Climb_aliases(const Climb *climb, size_t *len)
{
	if (len == NULL) {
		errno = EINVAL;
		return NULL;
	}

	*len = climb->aliaseslen;
	return climb->aliases;
}
