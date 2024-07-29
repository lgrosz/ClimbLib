#ifndef _CLIMBLIB_CLIMB_H_
#define _CLIMBLIB_CLIMB_H_

#include <stddef.h>

typedef struct GradeItem GradeItem;
typedef struct Climb Climb;

Climb *Climb_new();
void Climb_free(Climb *);

void Climb_set_name(Climb *, const char *);
const char *Climb_name(const Climb *);

void Climb_set_description(Climb *, const char *);
const char *Climb_description(const Climb *);

void Climb_set_brief(Climb *, const char *);
const char *Climb_brief(const Climb *);

void Climb_add_alias(Climb *, const char *);
void Climb_remove_alias(Climb *, const char *);
const char **Climb_aliases(const Climb *, size_t *);

/**
 * @brief Sets grades for climb
 *
 * @returns Previous grades for climb
 */
GradeItem *Climb_set_grades(Climb *, GradeItem *);

/**
 * @brief Grades for climb
 *
 * @returns Grades for climb
 */
GradeItem *Climb_grades(Climb *);

#endif
