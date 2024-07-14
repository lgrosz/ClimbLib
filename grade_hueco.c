#include "grade_hueco.h"
#include "int_util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct GradeHueco
{
	unsigned int grade;
	GradeHuecoModifier modifier;
	char str[5];
};

static void update_str(GradeHueco *grade)
{
	char mod_str;
	switch (grade->modifier) {
		case GRADE_HUECO_MODIFIER_MINUS:
			mod_str = '-';
			break;
		case GRADE_HUECO_MODIFIER_PLUS:
			mod_str = '+';
			break;
		default:
			mod_str = '\0';
			break;
	}

	snprintf(grade->str, sizeof(grade->str), "V%d%c", grade->grade, mod_str);
}

GradeHueco *GradeHueco_new(unsigned int grade, GradeHuecoModifier modifier)
{
	GradeHueco *ret;

	if (NULL == (ret = malloc(sizeof(struct GradeHueco)))) {
		return NULL;
	}

	if (GradeHueco_set_value(ret, grade) != 0) {
		errno = EINVAL;
		return NULL;
	}

	if (GradeHueco_set_modifier(ret, modifier) != 0) {
		errno = EINVAL;
		return NULL;
	}

	errno = 0;
	return ret;
}

unsigned int GradeHueco_value(const GradeHueco *grade)
{
	return grade->grade;
}

GradeHuecoModifier GradeHueco_modifier(const GradeHueco *grade)
{
	return grade->modifier;
}

int GradeHueco_set_value(GradeHueco *grade, unsigned int value)
{
	if (value > 99) {
		/* Three digit numbers could overflow the string */
		return 1;
	}

	grade->grade = value;
	update_str(grade);

	return 0;
}

int GradeHueco_set_modifier(GradeHueco *grade, GradeHuecoModifier modifier)
{
	if (modifier < GRADE_HUECO_MODIFIER_MINUS || modifier >= GRADE_HUECO_MODIFIER_MAX) {
		errno = EINVAL;
		return 1;
	}

	grade->modifier = modifier;
	update_str(grade);

	return 0;
}

void GradeHueco_free(GradeHueco *grade)
{
	if (grade == NULL) {
		errno = EINVAL;
		return;
	}

	errno = 0;
	free(grade);
}

GradeHueco *GradeHueco_dup(const GradeHueco *grade)
{
	if (grade == NULL) {
		errno = EINVAL;
		return NULL;
	}

	return GradeHueco_new(grade->grade, grade->modifier);
}

int GradeHueco_cmp(const GradeHueco *a, const GradeHueco *b)
{
	if (a == NULL || b == NULL) {
		errno = EINVAL;
		return 0;
	} else {
		errno = 0;
	}

	if (a->grade != b->grade) {
		return a->grade - b->grade;
	}

	return a->modifier - b->modifier;
}

const char *GradeHueco_str(const GradeHueco *grade)
{
	return grade->str;
}

GradeHueco *GradeHueco_fromstr(const char *str)
{
	size_t length = strlen(str);

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
