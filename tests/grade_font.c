#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <check.h>
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

	VERIFY(GradeFontainebleau_cmp(*g, *h) == 0);

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

	VERIFY(GradeFontainebleau_cmp(*g, *h) < 0);

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

	VERIFY(GradeFontainebleau_cmp(*g, *h) == 0);

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

	VERIFY(GradeFontainebleau_cmp(*g, *h) < 0);

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

	VERIFY(GradeFontainebleau_cmp(*g, *h) == 0);

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

	VERIFY(GradeFontainebleau_cmp(*g, *h) < 0);

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

	VERIFY(GradeFontainebleau_cmp(*g, *h) < 0);

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

	VERIFY(GradeFontainebleau_cmp(*g, *h) < 0);

	GradeFontainebleau_free(g);
	VERIFY(errno == 0);

	GradeFontainebleau_free(h);
	VERIFY(errno == 0);
}

START_TEST(test_str)
{
	GradeFontainebleau g;
	char str[10];
	size_t strlen;

	g = (GradeFontainebleau) { 5, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE };
	ck_assert_int_eq(strlen = GradeFontainebleau_str(g, NULL, 0), 2);
	ck_assert_int_eq(GradeFontainebleau_str(g, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "F5");

	g = (GradeFontainebleau) { 5, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS };
	ck_assert_int_eq(strlen = GradeFontainebleau_str(g, NULL, 0), 3);
	ck_assert_int_eq(GradeFontainebleau_str(g, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "F5+");

	g = (GradeFontainebleau) { 7, GRADE_FONT_DIVISION_C, GRADE_FONT_MODIFIER_NONE };
	ck_assert_int_eq(strlen = GradeFontainebleau_str(g, NULL, 0), 3);
	ck_assert_int_eq(GradeFontainebleau_str(g, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "F7C");

	g = (GradeFontainebleau) { 8, GRADE_FONT_DIVISION_B, GRADE_FONT_MODIFIER_NONE };
	ck_assert_int_eq(strlen = GradeFontainebleau_str(g, NULL, 0), 3);
	ck_assert_int_eq(GradeFontainebleau_str(g, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "F8B");

	g = (GradeFontainebleau) { 9, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE };
	ck_assert_int_eq(strlen = GradeFontainebleau_str(g, NULL, 0), 3);
	ck_assert_int_eq(GradeFontainebleau_str(g, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "F9A");

	g = (GradeFontainebleau) { 7, GRADE_FONT_DIVISION_C, GRADE_FONT_MODIFIER_PLUS };
	ck_assert_int_eq(strlen = GradeFontainebleau_str(g, NULL, 0), 4);
	ck_assert_int_eq(GradeFontainebleau_str(g, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "F7C+");
}
END_TEST

START_TEST(test_fromstr)
{
	GradeFontainebleau grade;

	ck_assert_int_eq(!GradeFontainebleau_fromstr(NULL, &grade), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(!GradeFontainebleau_fromstr("F7A", NULL), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(!GradeFontainebleau_fromstr("", &grade), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(!GradeFontainebleau_fromstr("F6", &grade), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(!GradeFontainebleau_fromstr("V0", &grade), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(!GradeFontainebleau_fromstr("F6D", &grade), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(!GradeFontainebleau_fromstr("F5/", &grade), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(GradeFontainebleau_fromstr("F5", &grade), 0);
	ck_assert_int_eq(GradeFontainebleau_cmp(grade, (GradeFontainebleau) { 5, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE }), 0);

	ck_assert_int_eq(GradeFontainebleau_fromstr("F5+", &grade), 0);
	ck_assert_int_eq(GradeFontainebleau_cmp(grade, (GradeFontainebleau) { 5, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS }), 0);

	ck_assert_int_eq(GradeFontainebleau_fromstr("F7C", &grade), 0);
	ck_assert_int_eq(GradeFontainebleau_cmp(grade, (GradeFontainebleau) { 7, GRADE_FONT_DIVISION_C, GRADE_FONT_MODIFIER_NONE }), 0);

	ck_assert_int_eq(GradeFontainebleau_fromstr("F8B", &grade), 0);
	ck_assert_int_eq(GradeFontainebleau_cmp(grade, (GradeFontainebleau) { 8, GRADE_FONT_DIVISION_B, GRADE_FONT_MODIFIER_NONE }), 0);

	ck_assert_int_eq(GradeFontainebleau_fromstr("F9A", &grade), 0);
	ck_assert_int_eq(GradeFontainebleau_cmp(grade, (GradeFontainebleau) { 9, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE }), 0);

	ck_assert_int_eq(GradeFontainebleau_fromstr("F7C+", &grade), 0);
	ck_assert_int_eq(GradeFontainebleau_cmp(grade, (GradeFontainebleau) { 7, GRADE_FONT_DIVISION_C, GRADE_FONT_MODIFIER_PLUS }), 0);
}
END_TEST

static Suite *suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Fontainebleau Grades");

	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_str);
	tcase_add_test(tc_core, test_fromstr);

	suite_add_tcase(s, tc_core);

	return s;
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

	int number_failed;
	Suite *s;
	SRunner *sr;

	s = suite();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	exit((number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}
