#include "grade_hueco.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int GradeHueco_cmp(const GradeHueco a, const GradeHueco b)
{
	return a.grade - b.grade;
}

int GradeHueco_str(const GradeHueco grade, char *str, size_t strlen)
{
	return snprintf(str, strlen, "V%d", grade.grade);
}

int GradeHueco_fromstr(const char *str, GradeHueco *grade)
{
	if (str == NULL || grade == NULL) {
		errno = EINVAL;
		return 1;
	}

	int ret;
	int nfilled = sscanf(str, "V%d", &grade->grade);

	if (nfilled < 1) {
		ret = 1;
	} else {
		ret = 0;
	}

	return ret;
}
