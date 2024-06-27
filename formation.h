#ifndef _CLIMBLIB_FORMATION_H_
#define _CLIMBLIB_FORMATION_H_

#include <stddef.h>

typedef struct Formation_ Formation;

Formation *Formation_new();
void Formation_free(Formation *);

void Formation_set_name(Formation *, const char *);
const char *Formation_name(const Formation *);

void Formation_set_description(Formation *, const char *);
const char *Formation_description(const Formation *);

void Formation_set_brief(Formation *, const char *);
const char *Formation_brief(const Formation *);

void Formation_add_alias(Formation *, const char *);
void Formation_remove_alias(Formation *, const char *);
const char **Formation_aliases(const Formation *, size_t *);

#endif
