#include "grade_font.h"
#include "int_util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

GradeFontainebleau *GradeFontainebleau_new(unsigned int grade, GradeFontainebleauDivision division, GradeFontainebleauModifier modifier)
{
	GradeFontainebleau *ret;

	if (grade > 9) {
		/* Two digit numbers could overflow the string */
		errno = EINVAL;
		return NULL;
	}

	if (NULL == (ret = malloc(sizeof(GradeFontainebleau)))) {
		return NULL;
	}

	ret->grade = grade;
	ret->division = division;
	ret->modifier = modifier;

	errno = 0;
	return ret;
}

void GradeFontainebleau_free(GradeFontainebleau *grade)
{
	if (grade == NULL) {
		errno = EINVAL;
		return;
	}

	errno = 0;
	free(grade);
}

GradeFontainebleau *GradeFontainebleau_dup(const GradeFontainebleau *grade)
{
	if (grade == NULL) {
		errno = EINVAL;
		return NULL;
	}

	errno = 0;
	return GradeFontainebleau_new(grade->grade, grade->division, grade->modifier);
}

int GradeFontainebleau_cmp(const GradeFontainebleau a, const GradeFontainebleau b)
{
	if (a.grade != b.grade) {
		return clamp(a.grade - b.grade, -1, 1);
	}

	// Divisions only matter in F6 or higher
	if (a.grade > 5) {
		if (a.division < b.division) {
			return -1;
		} else if (a.division > b.division){
			return 1;
		}
	}

	if (a.modifier == b.modifier) {
		return 0;
	} else if (a.modifier < b.modifier) {
		return -1;
	} else {
		return 1;
	}
}

int GradeFontainebleau_str(const GradeFontainebleau grade, char *str, size_t strlen)
{
	if (grade.grade < 6) {
		if (grade.modifier == GRADE_FONT_MODIFIER_NONE) {
			return snprintf(str, strlen, "F%d", grade.grade);
		} else {
			return snprintf(str, strlen, "F%d+", grade.grade);
		}
	}

	char div_char;
	switch (grade.division) {
		case GRADE_FONT_DIVISION_A:
			div_char = 'A';
			break;
		case GRADE_FONT_DIVISION_B:
			div_char = 'B';
			break;
		default:
			div_char = 'C';
			break;
        }

        if (grade.modifier == GRADE_FONT_MODIFIER_NONE) {
		return snprintf(str, strlen, "F%d%c", grade.grade, div_char);
	} else {
		return snprintf(str, strlen, "F%d%c+", grade.grade, div_char);
	}
}

GradeFontainebleau *GradeFontainebleau_fromstr(const char *str)
{
	// TODO /^Fb/ is also a valid
	if (strlen(str) == 0 || str[0] != 'F') {
		errno = EINVAL;
		return NULL;
	}

	char *the_rest;
	unsigned int grade = strtoul(str + 1, &the_rest, 10);

	if (grade > 5 && strlen(the_rest) < 1) {
		errno = EINVAL;
		return NULL;
	}

	GradeFontainebleauDivision division = GRADE_FONT_DIVISION_A;

	// Divisions are only valid for grades > F5
	if (grade > 5) {
		if (*the_rest == 'A') {
			division = GRADE_FONT_DIVISION_A;
		} else if (*the_rest == 'B') {
			division = GRADE_FONT_DIVISION_B;
		} else if (*the_rest == 'C') {
			division = GRADE_FONT_DIVISION_C;
		} else {
			errno = EINVAL;
			return NULL;
		}

		the_rest = the_rest + 1;
	}

	GradeFontainebleauModifier modifier;

	if (strcmp(the_rest, "") == 0) {
		modifier = GRADE_FONT_MODIFIER_NONE;
	} else if (strcmp(the_rest, "+") == 0) {
		modifier = GRADE_FONT_MODIFIER_PLUS;
	} else {
		errno = EINVAL;
		return NULL;
	}

	errno = 0;
	return GradeFontainebleau_new(grade, division, modifier);
}
