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
GradeHueco GradeHueco_fromstr(const char *);

typedef struct GradeFontainebleau_* GradeFontainebleau;
typedef enum GradeFontainebleauDivision {
	GRADE_FONT_DIVISION_A,
	GRADE_FONT_DIVISION_B,
	GRADE_FONT_DIVISION_C,
} GradeFontainebleauDivision;
typedef enum GradeFontainebleauModifier {
	GRADE_FONT_MODIFIER_NONE,
	GRADE_FONT_MODIFIER_PLUS,
} GradeFontainebleauModifier;

GradeFontainebleau GradeFontainebleau_new(unsigned int, GradeFontainebleauDivision, GradeFontainebleauModifier);
void GradeFontainebleau_free(GradeFontainebleau);
GradeFontainebleau GradeFontainebleau_dup(const GradeFontainebleau);
int GradeFontainebleau_cmp(const GradeFontainebleau, const GradeFontainebleau);
char *GradeFontainebleau_str(const GradeFontainebleau);
