#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "verify.h"

#include <grade_font.h>

static void test_free_null()
{
	GradeFontainebleau_free(NULL);
	VERIFY(errno == EINVAL);
}

static void test_new()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);
}

static void test_new_grade_out_of_range()
{
	GradeFontainebleau *g = GradeFontainebleau_new(10, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == EINVAL);
	VERIFY(g == NULL);
}

static void test_dup_null()
{
	GradeFontainebleau *g = GradeFontainebleau_dup(NULL);
	VERIFY(errno == EINVAL);
	VERIFY(g == NULL);
}

static void test_dup()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_dup(g);
	VERIFY(errno == 0);
	VERIFY(h != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_grade()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(8, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) < 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_division_eq()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_division_lt()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_C, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) < 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_mod_eq()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_mod_lt()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) < 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_grade_presc()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_B, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(8, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) < 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_division_presc()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_B, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) < 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_str()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(strcmp(GradeFontainebleau_str(g), "F7A") == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);
}

static void test_str_mod()
{
	GradeFontainebleau *g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(strcmp(GradeFontainebleau_str(g), "F7A+") == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);
}

static void test_str_lt_6()
{
	GradeFontainebleau *g = GradeFontainebleau_new(5, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(strcmp(GradeFontainebleau_str(g), "F5") == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);
}

static void test_str_lt_6_mod()
{
	GradeFontainebleau *g = GradeFontainebleau_new(5, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(strcmp(GradeFontainebleau_str(g), "F5+") == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);
}

static void test_fromstr_empty()
{
	GradeFontainebleau *g = GradeFontainebleau_fromstr("");
	VERIFY(errno == EINVAL);
	VERIFY(g == NULL);
}

static void test_fromstr_mess()
{
	GradeFontainebleau *g = GradeFontainebleau_fromstr("abcdefg");
	VERIFY(errno == EINVAL);
	VERIFY(g == NULL);
}

static void test_fromstr()
{
	GradeFontainebleau *g = GradeFontainebleau_fromstr("F7A");
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_fromstr_mod()
{
	GradeFontainebleau *g = GradeFontainebleau_fromstr("F7A+");
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_fromstr_lt_6()
{
	GradeFontainebleau *g = GradeFontainebleau_fromstr("F5");
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(5, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

static void test_fromstr_lt_6_division()
{
	GradeFontainebleau *g = GradeFontainebleau_fromstr("F5A");
	VERIFY(errno == EINVAL);
	VERIFY(g == NULL);
}

static void test_fromstr_lt_6_mod()
{
	GradeFontainebleau *g = GradeFontainebleau_fromstr("F5+");
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeFontainebleau *h = GradeFontainebleau_new(5, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeFontainebleau_cmp(g, h) == 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

void grade_font()
{
	test_free_null();
	test_new();
	test_new_grade_out_of_range();
	test_dup();
	test_dup_null();
	test_cmp_grade();
	test_cmp_division_eq();
	test_cmp_division_lt();
	test_cmp_mod_eq();
	test_cmp_mod_lt();
	test_cmp_grade_presc();
	test_cmp_division_presc();
	test_str();
	test_str_mod();
	test_str_lt_6();
	test_str_lt_6_mod();
	test_fromstr_empty();
	test_fromstr_mess();
	test_fromstr();
	test_fromstr_mod();
	test_fromstr_lt_6();
	test_fromstr_lt_6_division();
	test_fromstr_lt_6_mod();

	exit(EXIT_SUCCESS);
}
