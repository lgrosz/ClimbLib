#include "grade_hueco.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "allocator.h"

GradeHueco *GradeHueco_new(unsigned int grade, GradeHuecoModifier modifier)
{
	GradeHueco *ret;

	if (NULL == (ret = climblib_malloc(sizeof(GradeHueco)))) {
		return NULL;
	} else {
		ret->grade = 0;
		ret->modifier = GRADE_HUECO_MODIFIER_NONE;
	}

	if (GradeHueco_set_value(ret, grade) != 0) {
		GradeHueco_free(ret);
		errno = EINVAL;
		return NULL;
	}

	if (GradeHueco_set_modifier(ret, modifier) != 0) {
		GradeHueco_free(ret);
		errno = EINVAL;
		return NULL;
	}

	errno = 0;
	return ret;
}

unsigned int GradeHueco_value(const GradeHueco grade)
{
	return grade.grade;
}

GradeHuecoModifier GradeHueco_modifier(const GradeHueco grade)
{
	return grade.modifier;
}

int GradeHueco_set_value(GradeHueco *grade, unsigned int value)
{
	grade->grade = value;

	return 0;
}

int GradeHueco_set_modifier(GradeHueco *grade, GradeHuecoModifier modifier)
{
	if (modifier < GRADE_HUECO_MODIFIER_MINUS || modifier >= GRADE_HUECO_MODIFIER_MAX) {
		errno = EINVAL;
		return 1;
	}

	grade->modifier = modifier;

	return 0;
}

void GradeHueco_free(GradeHueco *grade)
{
	if (grade == NULL) {
		errno = EINVAL;
		return;
	}

	errno = 0;
	climblib_free(grade);
}

int GradeHueco_cmp(const GradeHueco a, const GradeHueco b)
{
	if (a.grade != b.grade) {
		return a.grade - b.grade;
	}

	return a.modifier - b.modifier;
}

int GradeHueco_str(const GradeHueco grade, char *str, size_t strlen)
{
	if (grade.modifier == GRADE_HUECO_MODIFIER_NONE) {
		return snprintf(str, strlen, "V%d", grade.grade);
	} else {
		char mod_str;
		switch (grade.modifier) {
			case GRADE_HUECO_MODIFIER_MINUS:
				mod_str = '-';
				break;
			default:
				mod_str = '+';
				break;
		}

		return snprintf(str, strlen, "V%d%c", grade.grade, mod_str);
	}
}

int GradeHueco_fromstr(const char *str, GradeHueco *grade)
{
	size_t length = strlen(str);

	if (length == 0 || str[0] != 'V' || grade == NULL) {
		errno = EINVAL;
		return 1;
	}

	char *potential_mod;
	unsigned int value = strtoul(str + 1, &potential_mod, 10);

	GradeHuecoModifier modifier;

	if (strcmp(potential_mod, "") == 0) {
		modifier = GRADE_HUECO_MODIFIER_NONE;
	} else if (strcmp(potential_mod, "-") == 0) {
		modifier = GRADE_HUECO_MODIFIER_MINUS;
	} else if (strcmp(potential_mod, "+") == 0) {
		modifier = GRADE_HUECO_MODIFIER_PLUS;
	} else {
		errno = EINVAL;
		return 1;
	}

	grade->grade = value;
	grade->modifier = modifier;
	return 0;
}
