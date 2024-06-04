#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "verify.h"

#include <grades.h>

static void test_free_null()
{
	GradeHueco_free(NULL);
	VERIFY(errno == EINVAL);
}

static void test_new()
{
	GradeHueco g = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeHueco_free(g);
	VERIFY(errno == 0);
}

static void test_new_grade_out_of_range()
{
	GradeHueco g = GradeHueco_new(100, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(errno == EINVAL);
	VERIFY(g == NULL);
}

static void test_dup_null()
{
	GradeHueco g = GradeHueco_dup(NULL);
	VERIFY(errno == EINVAL);
	VERIFY(g == NULL);
}

static void test_dup()
{
	GradeHueco g = GradeHueco_new(5, GRADE_HUECO_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeHueco h = GradeHueco_dup(g);
	VERIFY(errno == 0);
	VERIFY(h != NULL);

	VERIFY(GradeHueco_cmp(g, h) == 0);

	GradeHueco_free(g);
	VERIFY(errno == 0);

	GradeHueco_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_grade_eq()
{
	GradeHueco g = GradeHueco_new(3, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeHueco h = GradeHueco_new(3, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeHueco_cmp(g, h) == 0);

	GradeHueco_free(g);
	VERIFY(errno == 0);

	GradeHueco_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_grade_lt()
{
	GradeHueco g = GradeHueco_new(3, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeHueco h = GradeHueco_new(6, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeHueco_cmp(g, h) < 0);

	GradeHueco_free(g);
	VERIFY(errno == 0);

	GradeHueco_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_mod_eq()
{
	GradeHueco g = GradeHueco_new(4, GRADE_HUECO_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeHueco h = GradeHueco_new(4, GRADE_HUECO_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeHueco_cmp(g, h) == 0);

	GradeHueco_free(g);
	VERIFY(errno == 0);

	GradeHueco_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_mod_lt()
{
	GradeHueco g = GradeHueco_new(4, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeHueco h = GradeHueco_new(4, GRADE_HUECO_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeHueco_cmp(g, h) < 0);

	GradeHueco_free(g);
	VERIFY(errno == 0);

	GradeHueco_free(h);
	VERIFY(errno == 0);
}

static void test_cmp_grade_presc()
{
	GradeHueco g = GradeHueco_new(4, GRADE_HUECO_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeHueco h = GradeHueco_new(5, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(GradeHueco_cmp(g, h) < 0);

	GradeHueco_free(g);
	VERIFY(errno == 0);

	GradeHueco_free(h);
	VERIFY(errno == 0);
}

static void test_str()
{
	GradeHueco g = GradeHueco_new(4, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(strcmp(GradeHueco_str(g), "V4") == 0);

	GradeHueco_free(g);
	VERIFY(errno == 0);
}

static void test_str_mod()
{
	GradeHueco g = GradeHueco_new(10, GRADE_HUECO_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	VERIFY(strcmp(GradeHueco_str(g), "V10+") == 0);

	GradeHueco_free(g);
	VERIFY(errno == 0);
}

static void test_fromstr_empty()
{
	GradeHueco g = GradeHueco_fromstr("");
	VERIFY(errno == EINVAL);
	VERIFY(g == NULL);
}

static void test_fromstr_mess()
{
	GradeHueco g = GradeHueco_fromstr("adsfeg");
	VERIFY(errno == EINVAL);
	VERIFY(g == NULL);
}

static void test_fromstr()
{
	GradeHueco g = GradeHueco_fromstr("V5");
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeHueco h = GradeHueco_new(5, GRADE_HUECO_MODIFIER_NONE);
	VERIFY(errno == 0);
	VERIFY(h != NULL);

	VERIFY(GradeHueco_cmp(g, h) == 0);

	GradeHueco_free(g);
	VERIFY(errno == 0);

	GradeHueco_free(h);
	VERIFY(errno == 0);
}

static void test_fromstr_mod()
{
	GradeHueco g = GradeHueco_fromstr("V5+");
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	GradeHueco h = GradeHueco_new(5, GRADE_HUECO_MODIFIER_PLUS);
	VERIFY(errno == 0);
	VERIFY(h != NULL);

	VERIFY(GradeHueco_cmp(g, h) == 0);

	GradeHueco_free(g);
	VERIFY(errno == 0);

	GradeHueco_free(h);
	VERIFY(errno == 0);
}

void hueco()
{
	test_free_null();
	test_new();
	test_new_grade_out_of_range();
	test_dup_null();
	test_dup();
	test_cmp_grade_eq();
	test_cmp_grade_lt();
	test_cmp_mod_eq();
	test_cmp_mod_lt();
	test_cmp_grade_presc();
	test_str();
	test_str_mod();
	test_fromstr_empty();
	test_fromstr_mess();
	test_fromstr();
	test_fromstr_mod();

	exit(EXIT_SUCCESS);
}
