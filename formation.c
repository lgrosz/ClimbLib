#include "formation.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "str_util.h"
#include "strarr_util.h"

struct Formation_
{
	const char *name;
	const char *description;
	const char *brief;
	const char **aliases;
	size_t aliaseslen;
};

Formation *Formation_new()
{
	Formation *ret;

	if (NULL == (ret = malloc(sizeof(Formation)))) {
		return NULL;
	} else {
		ret->name = NULL;
		ret->description = NULL;
		ret->brief = NULL;
		ret->aliases = NULL;
	}

	Formation_set_name(ret, "");
	Formation_set_description(ret, "");
	Formation_set_brief(ret, "");

	ret->aliaseslen = 0;

	errno = 0;
	return ret;
}

void Formation_free(Formation *formation)
{
	if (formation == NULL) {
		errno = EINVAL;
		return;
	}

	errno = 0;
	if (formation->name)	free((void*)formation->name);
	if (formation->description)	free((void*)formation->description);
	if (formation->brief)	free((void*)formation->brief);

	if (formation->aliases) {
		for (int i = 0; i < formation->aliaseslen; i++) {
			free((void*)formation->aliases[i]);
		}

		free(formation->aliases);
	}

	free(formation);
}

void Formation_set_name(Formation *formation, const char *name)
{
	free_allocate_and_assign_str(&formation->name, name);
}

const char *Formation_name(const Formation *formation)
{
	return formation->name;
}

void Formation_set_description(Formation *formation, const char *description)
{
	free_allocate_and_assign_str(&formation->description, description);
}

const char *Formation_description(const Formation *formation)
{
	return formation->description;
}

void Formation_set_brief(Formation *formation, const char *description)
{
	free_allocate_and_assign_str(&formation->brief, description);
}

const char *Formation_brief(const Formation *formation)
{
	return formation->brief;
}

void Formation_add_alias(Formation *formation, const char *alias)
{
	if (formation == NULL) {
		errno = EINVAL;
		return;
	}

	errno = 0;

	if (strarr_contains(formation->aliases, formation->aliaseslen, alias)) {
		return;
	}

	add_str_to_strarr(alias, &formation->aliases, &formation->aliaseslen);
}

void Formation_remove_alias(Formation *formation, const char *alias)
{
	if (formation == NULL) {
		errno = EINVAL;
		return;
	}

	remove_str_from_strarr(alias, &formation->aliases, &formation->aliaseslen);
}

const char **Formation_aliases(const Formation *formation, size_t *len)
{
	if (len == NULL) {
		errno = EINVAL;
		return NULL;
	}

	*len = formation->aliaseslen;
	return formation->aliases;
}
