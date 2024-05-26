#include "climb.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "str_util.h"

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

	ret->aliaseslen = 0;

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

	if (climb->aliases) {
		for (int i = 0; i < climb->aliaseslen; i++) {
			free((void*)climb->aliases[i]);
		}

		free(climb->aliases);
	}

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

void Climb_add_alias(Climb climb, const char *alias)
{
	if (climb == NULL) {
		errno = EINVAL;
		return;
	}

	if (contains(climb->aliases, climb->aliaseslen, alias)) {
		return;
	}

	const char **aliases;
	if (NULL == (aliases = malloc((climb->aliaseslen + 1) * sizeof(const char *)))) {
		errno = ENOMEM;
		return;
	}

	for (size_t i = 0; i < climb->aliaseslen; ++i) {
		aliases[i] = climb->aliases[i];
	}

	char *new_str;
	if (NULL == (new_str = malloc(strlen(alias) + 1))) {
		// TODO Cleanup
		errno = ENOMEM;
		return;
	}

	strcpy(new_str, alias);

	aliases[climb->aliaseslen] = new_str;

	if (climb->aliases) {
		free(climb->aliases);
	}

	errno = 0;
	climb->aliaseslen = climb->aliaseslen + 1;
	climb->aliases = aliases;
}

void Climb_remove_alias(Climb climb, const char *alias)
{
	if (climb == NULL) {
		errno = EINVAL;
		return;
	}

	size_t index = 0;
	int found = 0;

	for (index = 0; index < climb->aliaseslen; ++index) {
		if (strcmp(climb->aliases[index], alias) == 0) {
			found = 1;
			break;
		}
	}

	if (!found) {
		errno = 0;
		return;
	}

	const char **aliases;
	if (NULL == (aliases = malloc((climb->aliaseslen - 1) * sizeof(const char *)))) {
		errno = ENOMEM;
		return;
	}

	// Copy elements, skipping the element to remove
	for (size_t i = 0, j = 0; i < climb->aliaseslen; ++i) {
		if (i != index) {
			aliases[j++] = climb->aliases[i];
		}
	}

	if (climb->aliases) {
		free((void *)climb->aliases[index]);
		free(climb->aliases);
	}

	errno = 0;
	climb->aliaseslen = climb->aliaseslen - 1;
	climb->aliases = aliases;
}

const char **Climb_aliases(const Climb climb, size_t *len)
{
	if (len == NULL) {
		errno = EINVAL;
		return NULL;
	}

	*len = climb->aliaseslen;
	return climb->aliases;
}
