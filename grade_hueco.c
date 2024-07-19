#include "grade_hueco.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

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
