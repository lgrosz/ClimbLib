#include "grades.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct GradeHueco_
{
	unsigned int grade;
	GradeHuecoModifier modifier;
	char str[5];
};

static void update_str(GradeHueco grade)
{
	char mod_str;
	switch (grade->modifier) {
		case GRADE_HUECO_MODIFIER_MINUS:
			mod_str = '-';
			break;
		case GRADE_HUECO_MODIFIER_NONE:
			mod_str = '\0';
			break;
		case GRADE_HUECO_MODIFIER_PLUS:
			mod_str = '+';
			break;
	}

	snprintf(grade->str, sizeof(grade->str), "V%d%c", grade->grade, mod_str);
}

GradeHueco GradeHueco_new(unsigned int grade, GradeHuecoModifier modifier)
{
	GradeHueco ret;

	if (NULL == (ret = malloc(sizeof(struct GradeHueco_)))) {
		errno = ENOMEM;
		return NULL;
	}

	if (grade > 99) {
		/* Three digit numbers could overflow the string */
		errno = EINVAL;
		return NULL;
	}

	ret->grade = grade;
	ret->modifier = modifier;
	update_str(ret);

	return ret;
}

void GradeHueco_free(GradeHueco grade)
{
	if (grade == NULL) {
		errno = EINVAL;
		return;
	}

	free(grade);
}

GradeHueco GradeHueco_dup(const GradeHueco grade)
{
	if (grade == NULL) {
		errno = EINVAL;
		return NULL;
	}

	return GradeHueco_new(grade->grade, grade->modifier);
}

static int normalize(int a)
{
	if (a < 0) {
		return -1;
	} else if (a > 0) {
		return 1;
	} else {
		return 0;
	}
}

int GradeHueco_cmp(const GradeHueco a, const GradeHueco b)
{
	if (a->grade != b->grade) {
		return normalize(a->grade - b->grade);
	}

	if (a->modifier == b->modifier) {
		return 0;
	} else if (a->modifier < b->modifier) {
		return -1;
	} else {
		return 1;
	}
}

char *GradeHueco_str(const GradeHueco grade)
{
	return grade->str;
}

GradeHueco GradeHueco_fromstr(const char *str)
{
	int length = strlen(str);

	if (length == 0 || str[0] != 'V') {
		errno = EINVAL;
		return NULL;
	}

	char *potential_mod;
	unsigned int grade = strtoul(str + 1, &potential_mod, 10);

	GradeHuecoModifier modifier;

	if (strcmp(potential_mod, "") == 0) {
		modifier = GRADE_HUECO_MODIFIER_NONE;
	} else if (strcmp(potential_mod, "-") == 0) {
		modifier = GRADE_HUECO_MODIFIER_MINUS;
	} else if (strcmp(potential_mod, "+") == 0) {
		modifier = GRADE_HUECO_MODIFIER_PLUS;
	} else {
		errno = EINVAL;
		return NULL;
	}

	errno = 0;
	return GradeHueco_new(grade, modifier);
}
