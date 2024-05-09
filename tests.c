#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "grades.h"

#define VERIFY(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "Verification failed at %s:%d - %s\n", __FILE__, __LINE__, #expr); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

int main()
{
	// Test free function
	errno = 0;
	GradeHueco_free(NULL);
	VERIFY(errno == EINVAL);

	// Test new function
	GradeHueco a = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(a != NULL);
	GradeHueco_free(a);

	// Test duplicate function
	a = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	GradeHueco b = GradeHueco_dup(a);
	VERIFY(b != NULL);
	GradeHueco_free(a);
	GradeHueco_free(b);

	errno = 0;
	b = GradeHueco_dup(NULL);
	VERIFY(b == NULL);
	VERIFY(errno == EINVAL);

	// Test numerical comparisons
	a = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	b = GradeHueco_new(1, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(GradeHueco_cmp(a, b) < 0);
	GradeHueco_free(a);
	GradeHueco_free(b);

	// Test modifier comparisons
	a = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	b = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(GradeHueco_cmp(a, b) == 0);
	GradeHueco_free(b);

	b = GradeHueco_new(0, GRADE_HUECO_MODIFIER_MINUS);
	VERIFY(GradeHueco_cmp(a, b) > 0);
	GradeHueco_free(b);

	b = GradeHueco_new(0, GRADE_HUECO_MODIFIER_PLUS);
	VERIFY(GradeHueco_cmp(a, b) < 0);
	GradeHueco_free(a);

	a = GradeHueco_new(0, GRADE_HUECO_MODIFIER_MINUS);
	VERIFY(GradeHueco_cmp(a, b) < 0);
	GradeHueco_free(a);
	GradeHueco_free(b);

	// Test grade strings
	a = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(strcmp(GradeHueco_str(a), "V0") == 0);
	GradeHueco_free(a);

	a = GradeHueco_new(0, GRADE_HUECO_MODIFIER_MINUS);
	VERIFY(strcmp(GradeHueco_str(a), "V0-") == 0);
	GradeHueco_free(a);

	a = GradeHueco_new(0, GRADE_HUECO_MODIFIER_PLUS);
	VERIFY(strcmp(GradeHueco_str(a), "V0+") == 0);
	GradeHueco_free(a);

	return 0;
}
