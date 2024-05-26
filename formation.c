#include "formation.h"
#include "str_util.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct Formation_
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

Formation Formation_new()
{
	Formation ret;

	if (NULL == (ret = malloc(sizeof(struct Formation_)))) {
		errno = ENOMEM;
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

void Formation_free(Formation formation)
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

void Formation_set_name(Formation formation, const char *name)
{
	free_allocate_and_assign_str(&formation->name, name);
}

const char *Formation_name(Formation formation)
{
	return formation->name;
}

void Formation_set_description(Formation formation, const char *description)
{
	free_allocate_and_assign_str(&formation->description, description);
}

const char *Formation_description(Formation formation)
{
	return formation->description;
}

void Formation_set_brief(Formation formation, const char *description)
{
	free_allocate_and_assign_str(&formation->brief, description);
}

const char *Formation_brief(Formation formation)
{
	return formation->brief;
}

void Formation_add_alias(Formation formation, const char *alias)
{
	if (formation == NULL) {
		errno = EINVAL;
		return;
	}

	if (contains(formation->aliases, formation->aliaseslen, alias)) {
		return;
	}

	const char **aliases;
	if (NULL == (aliases = malloc((formation->aliaseslen + 1) * sizeof(const char *)))) {
		errno = ENOMEM;
		return;
	}

	for (size_t i = 0; i < formation->aliaseslen; ++i) {
		aliases[i] = formation->aliases[i];
	}

	char *new_str;
	if (NULL == (new_str = malloc(strlen(alias) + 1))) {
		// TODO Cleanup
		errno = ENOMEM;
		return;
	}

	strcpy(new_str, alias);

	aliases[formation->aliaseslen] = new_str;

	if (formation->aliases) {
		free(formation->aliases);
	}

	errno = 0;
	formation->aliaseslen = formation->aliaseslen + 1;
	formation->aliases = aliases;
}

void Formation_remove_alias(Formation formation, const char *alias)
{
	if (formation == NULL) {
		errno = EINVAL;
		return;
	}

	size_t index = 0;
	int found = 0;

	for (index = 0; index < formation->aliaseslen; ++index) {
		if (strcmp(formation->aliases[index], alias) == 0) {
			found = 1;
			break;
		}
	}

	if (!found) {
		errno = 0;
		return;
	}

	const char **aliases;
	if (NULL == (aliases = malloc((formation->aliaseslen - 1) * sizeof(const char *)))) {
		errno = ENOMEM;
		return;
	}

	// Copy elements, skipping the element to remove
	for (size_t i = 0, j = 0; i < formation->aliaseslen; ++i) {
		if (i != index) {
			aliases[j++] = formation->aliases[i];
		}
	}

	if (formation->aliases) {
		free((void *)formation->aliases[index]);
		free(formation->aliases);
	}

	errno = 0;
	formation->aliaseslen = formation->aliaseslen - 1;
	formation->aliases = aliases;
}

const char **Formation_aliases(const Formation formation, size_t *len)
{
	if (len == NULL) {
		errno = EINVAL;
		return NULL;
	}

	*len = formation->aliaseslen;
	return formation->aliases;
}
