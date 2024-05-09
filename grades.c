#include "grades.h"
#include <stdlib.h>
#include <errno.h>

struct GradeHueco_
{
	unsigned int grade;
	GradeHuecoModifier modifier;
};

GradeHueco GradeHueco_new(unsigned int grade, GradeHuecoModifier modifier)
{
	GradeHueco ret;

	if (NULL == (ret = malloc(sizeof(struct GradeHueco_)))) {
		errno = ENOMEM;
		return NULL;
	}

	ret->grade = grade;
	ret->modifier = modifier;

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

int foo()
{
	return 1;
}
