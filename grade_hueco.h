#ifndef _CLIMBLIB_GRADE_HUECO_H_
#define _CLIMBLIB_GRADE_HUECO_H_

#include <stddef.h>

typedef enum GradeHuecoModifier {
	GRADE_HUECO_MODIFIER_MINUS,
	GRADE_HUECO_MODIFIER_NONE,
	GRADE_HUECO_MODIFIER_PLUS,
	GRADE_HUECO_MODIFIER_MAX,
} GradeHuecoModifier;

typedef struct {
	unsigned int grade;
	GradeHuecoModifier modifier;
} GradeHueco;

int GradeHueco_cmp(const GradeHueco, const GradeHueco);
int GradeHueco_str(const GradeHueco, char *, size_t);
int GradeHueco_fromstr(const char *, GradeHueco *);

#endif
