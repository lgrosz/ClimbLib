#ifndef _CLIMBLIB_GRADE_FONT_H_
#define _CLIMBLIB_GRADE_FONT_H_

#include <stddef.h>

typedef enum {
	GRADE_FONT_DIVISION_A,
	GRADE_FONT_DIVISION_B,
	GRADE_FONT_DIVISION_C,
} GradeFontainebleauDivision;
typedef enum {
	GRADE_FONT_MODIFIER_NONE,
	GRADE_FONT_MODIFIER_PLUS,
} GradeFontainebleauModifier;

typedef struct {
	unsigned int grade;
	GradeFontainebleauDivision division;
	GradeFontainebleauModifier modifier;
} GradeFontainebleau;

int GradeFontainebleau_cmp(const GradeFontainebleau, const GradeFontainebleau);
int GradeFontainebleau_str(const GradeFontainebleau, char *, size_t);
int GradeFontainebleau_fromstr(const char *, GradeFontainebleau *);

#endif
