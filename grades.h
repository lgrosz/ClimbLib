typedef struct GradeHueco_* GradeHueco;
typedef enum GradeHuecoModifier {
	GRADE_HUECO_MODIFIER_MINUS,
	GRADE_HUECO_MODIFIER_NONE,
	GRADE_HUECO_MODIFIER_PLUS,
} GradeHuecoModifier;

GradeHueco GradeHueco_new(unsigned int, GradeHuecoModifier);
void GradeHueco_free(GradeHueco);
GradeHueco GradeHueco_dup(const GradeHueco);
int GradeHueco_cmp(const GradeHueco, const GradeHueco);
char *GradeHueco_str(const GradeHueco);
