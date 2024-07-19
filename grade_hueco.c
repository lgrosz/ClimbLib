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
	if (str == NULL || grade == NULL) {
		errno = EINVAL;
		return 1;
	}

	int ret;
	char mod_char;
	int nfilled = sscanf(str, "V%d%c", &grade->grade, &mod_char);

	if (nfilled < 1) {
		ret = 1;
	} else if (nfilled == 1) {
		grade->modifier = GRADE_HUECO_MODIFIER_NONE;
		ret = 0;
	} else {
		switch (mod_char) {
			case '-':
				grade->modifier = GRADE_HUECO_MODIFIER_MINUS;
				ret = 0;
				break;
			case '+':
				grade->modifier = GRADE_HUECO_MODIFIER_PLUS;
				ret = 0;
				break;
			default:
				ret = 1;
				break;
		}
	}

	return ret;
}
