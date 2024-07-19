#include "allocator.h"
#include "more_allocators.h"
#include <errno.h>
#include <stdlib.h>
#include <check.h>

#include <grade_hueco.h>

START_TEST(test_new)
{
	GradeHueco *grade;

	unsigned int grade_value = 5;
	GradeHuecoModifier grade_modifier = GRADE_HUECO_MODIFIER_NONE;
	grade = GradeHueco_new(grade_value, grade_modifier);

	ck_assert_ptr_nonnull(grade);
	ck_assert(GradeHueco_value(*grade) == grade_value);
	ck_assert(GradeHueco_modifier(*grade) == grade_modifier);

	GradeHueco_free(grade);
}
END_TEST

START_TEST(test_new_invalid)
{
	GradeHueco *grade;

	grade = GradeHueco_new(0, -1);
	ck_assert_ptr_null(grade);
	ck_assert_int_eq(errno, EINVAL);

	grade = GradeHueco_new(0, GRADE_HUECO_MODIFIER_MAX);
	ck_assert_ptr_null(grade);
	ck_assert_int_eq(errno, EINVAL);
}
END_TEST

START_TEST(test_free_null)
{
	GradeHueco_free(NULL);
	ck_assert_int_eq(errno, EINVAL);
}
END_TEST

START_TEST(test_new_bad_malloc)
{
	climblib_set_alloc(bad_malloc, NULL, NULL);
	ck_assert_ptr_null(GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE));
}
END_TEST

START_TEST(test_cmp)
{
	GradeHueco *left, *right;

	left = GradeHueco_new(1, GRADE_HUECO_MODIFIER_NONE);
	right = GradeHueco_new(1, GRADE_HUECO_MODIFIER_NONE);
	ck_assert_int_eq(GradeHueco_cmp(*left, *right), 0);
	GradeHueco_free(left);
	GradeHueco_free(right);

	left = GradeHueco_new(1, GRADE_HUECO_MODIFIER_NONE);
	right = GradeHueco_new(2, GRADE_HUECO_MODIFIER_NONE);
	ck_assert_int_lt(GradeHueco_cmp(*left, *right), 0);
	GradeHueco_free(left);
	GradeHueco_free(right);

	left = GradeHueco_new(1, GRADE_HUECO_MODIFIER_NONE);
	right = GradeHueco_new(1, GRADE_HUECO_MODIFIER_PLUS);
	ck_assert_int_lt(GradeHueco_cmp(*left, *right), 0);
	GradeHueco_free(left);
	GradeHueco_free(right);
}
END_TEST

START_TEST(test_str)
{
	GradeHueco *grade;

	// 4 characters is the largest string
	char str[5];
	size_t strlen;

	grade = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	ck_assert_int_eq((strlen = GradeHueco_str(*grade, NULL, 0)), 2);
	ck_assert_int_eq(GradeHueco_str(*grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V0");
	GradeHueco_free(grade);

	grade = GradeHueco_new(1, GRADE_HUECO_MODIFIER_MINUS);
	ck_assert_int_eq((strlen = GradeHueco_str(*grade, NULL, 0)), 3);
	ck_assert_int_eq(GradeHueco_str(*grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V1-");
	GradeHueco_free(grade);

	grade = GradeHueco_new(2, GRADE_HUECO_MODIFIER_PLUS);
	ck_assert_int_eq((strlen = GradeHueco_str(*grade, NULL, 0)), 3);
	ck_assert_int_eq(GradeHueco_str(*grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V2+");
	GradeHueco_free(grade);

	grade = GradeHueco_new(10, GRADE_HUECO_MODIFIER_NONE);
	ck_assert_int_eq((strlen = GradeHueco_str(*grade, NULL, 0)), 3);
	ck_assert_int_eq(GradeHueco_str(*grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V10");
	GradeHueco_free(grade);

	grade = GradeHueco_new(11, GRADE_HUECO_MODIFIER_MINUS);
	ck_assert_int_eq((strlen = GradeHueco_str(*grade, NULL, 0)), 4);
	ck_assert_int_eq(GradeHueco_str(*grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V11-");
	GradeHueco_free(grade);

	grade = GradeHueco_new(12, GRADE_HUECO_MODIFIER_PLUS);
	ck_assert_int_eq((strlen = GradeHueco_str(*grade, NULL, 0)), 4);
	ck_assert_int_eq(GradeHueco_str(*grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V12+");
	GradeHueco_free(grade);
}
END_TEST

START_TEST(test_fromstr)
{
	GradeHueco grade;

	ck_assert_int_eq(!GradeHueco_fromstr(NULL, &grade), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(!GradeHueco_fromstr("V10", NULL), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(!GradeHueco_fromstr("Not a valid grade-string", &grade), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(!GradeHueco_fromstr("V5/", &grade), 0);
	ck_assert_int_eq(errno, EINVAL);

	ck_assert_int_eq(GradeHueco_fromstr("V0", &grade), 0);
	ck_assert_int_eq(GradeHueco_cmp(grade, (GradeHueco) { 0, GRADE_HUECO_MODIFIER_NONE }), 0);

	ck_assert_int_eq(GradeHueco_fromstr("V7-", &grade), 0);
	ck_assert_int_eq(GradeHueco_cmp(grade, (GradeHueco) { 7, GRADE_HUECO_MODIFIER_MINUS }), 0);

	ck_assert_int_eq(GradeHueco_fromstr("V11+", &grade), 0);
	ck_assert_int_eq(GradeHueco_cmp(grade, (GradeHueco) { 11, GRADE_HUECO_MODIFIER_PLUS }), 0);
}
END_TEST

static void default_allocators()
{
	climblib_set_alloc(NULL, NULL, NULL);
}

static Suite *suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Hueco Grades");

	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_new);
	tcase_add_test(tc_core, test_new_invalid);
	tcase_add_test(tc_core, test_new_bad_malloc);
	tcase_add_test(tc_core, test_free_null);
	tcase_add_test(tc_core, test_cmp);
	tcase_add_test(tc_core, test_str);
	tcase_add_test(tc_core, test_fromstr);
	tcase_add_checked_fixture(tc_core, NULL, default_allocators);

	suite_add_tcase(s, tc_core);

	return s;
}

void grade_hueco()
{
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
