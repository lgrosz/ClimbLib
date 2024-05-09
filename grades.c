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

GradeHueco GradeHueco_dup(const GradeHueco grade)
{
	GradeHueco ret;

	if (grade == NULL) {
		errno = EINVAL;
		return NULL;
	}

	if (NULL == (ret = malloc(sizeof(struct GradeHueco_)))) {
		errno = ENOMEM;
		return NULL;
	}

	ret->grade = grade->grade;
	ret->modifier = grade->modifier;

	return ret;
}

int normalize(int a)
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
