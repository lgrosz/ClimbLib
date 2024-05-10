#include "grades.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct GradeFontainebleau_
{
	unsigned int grade;
	GradeFontainebleauDivision division;
	GradeFontainebleauModifier modifier;
	char str[5];
};

static void update_str(GradeFontainebleau grade)
{
	char div_str;
	switch (grade->division) {
		case GRADE_FONT_DIVISION_A:
			div_str = 'A';
			break;
		case GRADE_FONT_DIVISION_B:
			div_str = 'B';
			break;
		case GRADE_FONT_DIVISION_C:
			div_str = 'C';
			break;
	}

	char mod_str;
	switch (grade->modifier) {
		case GRADE_FONT_MODIFIER_NONE:
			mod_str = '\0';
			break;
		case GRADE_FONT_MODIFIER_PLUS:
			mod_str = '+';
			break;
	}

	snprintf(grade->str, sizeof(grade->str), "F%d%c%c", grade->grade, div_str, mod_str);
}

GradeFontainebleau GradeFontainebleau_new(unsigned int grade, GradeFontainebleauDivision division, GradeFontainebleauModifier modifier)
{
	GradeFontainebleau ret;

	if (NULL == (ret = malloc(sizeof(struct GradeFontainebleau_)))) {
		errno = ENOMEM;
		return NULL;
	}

	if (grade > 9) {
		/* Two digit numbers could overflow the string */
		errno = EINVAL;
		return NULL;
	}

	ret->grade = grade;
	ret->division = division;
	ret->modifier = modifier;
	update_str(ret);

	return ret;
}

void GradeFontainebleau_free(GradeFontainebleau grade)
{
	if (grade == NULL) {
		errno = EINVAL;
		return;
	}

	free(grade);
}

GradeFontainebleau GradeFontainebleau_dup(const GradeFontainebleau grade)
{
	if (grade == NULL) {
		errno = EINVAL;
		return NULL;
	}

	return GradeFontainebleau_new(grade->grade, grade->division, grade->modifier);
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

int GradeFontainebleau_cmp(const GradeFontainebleau a, const GradeFontainebleau b)
{
	if (a == NULL || b == NULL) {
		errno = EINVAL;
		return 0;
	} else {
		errno = 0;
	}

	if (a->grade != b->grade) {
		return normalize(a->grade - b->grade);
	}

	if (a->division < b->division) {
		return -1;
	} else if (a->division > b->division){
		return 1;
	}

	if (a->modifier == b->modifier) {
		return 0;
	} else if (a->modifier < b->modifier) {
		return -1;
	} else {
		return 1;
	}
}

char *GradeFontainebleau_str(const GradeFontainebleau grade)
{
	return grade->str;
}
