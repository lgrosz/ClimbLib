#ifndef _CLIMBLIB_GRADE_FONT_H_
#define _CLIMBLIB_GRADE_FONT_H_

typedef struct GradeFontainebleau_ GradeFontainebleau;
typedef enum GradeFontainebleauDivision {
	GRADE_FONT_DIVISION_A,
	GRADE_FONT_DIVISION_B,
	GRADE_FONT_DIVISION_C,
} GradeFontainebleauDivision;
typedef enum GradeFontainebleauModifier {
	GRADE_FONT_MODIFIER_NONE,
	GRADE_FONT_MODIFIER_PLUS,
} GradeFontainebleauModifier;

GradeFontainebleau *GradeFontainebleau_new(unsigned int, GradeFontainebleauDivision, GradeFontainebleauModifier);
void GradeFontainebleau_free(GradeFontainebleau *);
GradeFontainebleau *GradeFontainebleau_dup(const GradeFontainebleau *);
int GradeFontainebleau_cmp(const GradeFontainebleau *, const GradeFontainebleau *);
const char *GradeFontainebleau_str(const GradeFontainebleau *);
GradeFontainebleau *GradeFontainebleau_fromstr(const char *);

#endif
