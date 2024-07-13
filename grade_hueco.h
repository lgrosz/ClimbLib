#ifndef _CLIMBLIB_GRADE_HUECO_H_
#define _CLIMBLIB_GRADE_HUECO_H_

typedef struct GradeHueco GradeHueco;
typedef enum GradeHuecoModifier {
	GRADE_HUECO_MODIFIER_MINUS,
	GRADE_HUECO_MODIFIER_NONE,
	GRADE_HUECO_MODIFIER_PLUS,
} GradeHuecoModifier;

GradeHueco *GradeHueco_new(unsigned int, GradeHuecoModifier);
void GradeHueco_free(GradeHueco *);
GradeHueco *GradeHueco_dup(const GradeHueco *);
int GradeHueco_cmp(const GradeHueco *, const GradeHueco *);
const char *GradeHueco_str(const GradeHueco *);
GradeHueco *GradeHueco_fromstr(const char *);

#endif
