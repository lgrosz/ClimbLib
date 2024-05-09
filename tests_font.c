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
	GradeFontainebleau_free(NULL);
	VERIFY(errno == EINVAL);

	// Test new function
	GradeFontainebleau a_f = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(a_f != NULL);
	GradeFontainebleau_free(a_f);

	// Test duplicate function
	a_f = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	GradeFontainebleau b_f = GradeFontainebleau_dup(a_f);
	VERIFY(b_f != NULL);
	GradeFontainebleau_free(a_f);
	GradeFontainebleau_free(b_f);

	errno = 0;
	b_f = GradeFontainebleau_dup(NULL);
	VERIFY(b_f == NULL);
	VERIFY(errno == EINVAL);

	// Test numerical comparisons
	a_f = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	b_f = GradeFontainebleau_new(8, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(GradeFontainebleau_cmp(a_f, b_f) < 0);
	GradeFontainebleau_free(a_f);
	GradeFontainebleau_free(b_f);

	// Test division comparisons
	a_f = GradeFontainebleau_new(0, GRADE_FONT_DIVISION_B, GRADE_FONT_MODIFIER_NONE);
	b_f = GradeFontainebleau_new(0, GRADE_FONT_DIVISION_B, GRADE_FONT_MODIFIER_NONE);
	VERIFY(GradeFontainebleau_cmp(a_f, b_f) == 0);
	GradeFontainebleau_free(b_f);

	b_f = GradeFontainebleau_new(0, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(GradeFontainebleau_cmp(a_f, b_f) > 0);
	GradeFontainebleau_free(b_f);

	b_f = GradeFontainebleau_new(0, GRADE_FONT_DIVISION_C, GRADE_FONT_MODIFIER_NONE);
	VERIFY(GradeFontainebleau_cmp(a_f, b_f) < 0);
	GradeFontainebleau_free(a_f);
	GradeFontainebleau_free(b_f);

	// Test modifier comparisons
	a_f = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	b_f = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(GradeFontainebleau_cmp(a_f, b_f) == 0);
	GradeFontainebleau_free(b_f);

	b_f = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(GradeFontainebleau_cmp(a_f, b_f) < 0);
	GradeFontainebleau_free(a_f);
	GradeFontainebleau_free(b_f);

	// Test grade strings
	a_f = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(strcmp(GradeFontainebleau_str(a_f), "F7A") == 0);
	GradeFontainebleau_free(a_f);

	a_f = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(strcmp(GradeFontainebleau_str(a_f), "F7A+") == 0);
	GradeFontainebleau_free(a_f);

	return 0;
}
