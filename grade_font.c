#include "grade_font.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int GradeFontainebleau_cmp(const GradeFontainebleau a, const GradeFontainebleau b)
{
	if (a.grade != b.grade) {
		return a.grade - b.grade;
	}

	// Grades less than F6A do not have divisions
	if (a.grade < 6) {
		return a.modifier - b.modifier;
	}

	if (a.division != b.division) {
		return a.division - b.division;
	}

	return a.modifier - b.modifier;
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

int GradeFontainebleau_fromstr(const char *str, GradeFontainebleau *grade)
{
	if (str == NULL || grade == NULL) {
		errno = EINVAL;
		return 1;
	}

	// TODO /^Fb/ is also a valid
	if (strlen(str) == 0 || str[0] != 'F') {
		errno = EINVAL;
		return 1;
	}

	char *the_rest;
	unsigned int value = strtoul(str + 1, &the_rest, 10);

	if (value > 5 && strlen(the_rest) < 1) {
		errno = EINVAL;
		return 1;
	}

	GradeFontainebleauDivision division = GRADE_FONT_DIVISION_A;

	// Divisions are only valid for grades > F5
	if (value > 5) {
		if (*the_rest == 'A') {
			division = GRADE_FONT_DIVISION_A;
		} else if (*the_rest == 'B') {
			division = GRADE_FONT_DIVISION_B;
		} else if (*the_rest == 'C') {
			division = GRADE_FONT_DIVISION_C;
		} else {
			errno = EINVAL;
			return 1;
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
		return 1;
	}

	grade->grade = value;
	grade->division = division;
	grade->modifier = modifier;
	return 0;
}
