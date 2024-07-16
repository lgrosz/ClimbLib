#include "allocator.h"
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
	ck_assert(GradeHueco_value(grade) == grade_value);
	ck_assert(GradeHueco_modifier(grade) == grade_modifier);

	GradeHueco_free(grade);
}
END_TEST

START_TEST(test_new_invalid)
{
	unsigned int grade_value = 100;
	GradeHueco *grade = GradeHueco_new(100, GRADE_HUECO_MODIFIER_NONE);
	ck_assert_ptr_null(grade);
	ck_assert_int_eq(errno, EINVAL);

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

static void *bad_malloc(size_t size)
{
	return NULL;
}

START_TEST(test_new_bad_malloc)
{
	climblib_set_alloc(bad_malloc, NULL, NULL);
	ck_assert_ptr_null(GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE));
}
END_TEST

START_TEST(test_cmp)
{
	GradeHueco *left, *right;

	GradeHueco_cmp(NULL, NULL);
	ck_assert_int_eq(errno, EINVAL);

	left = GradeHueco_new(1, GRADE_HUECO_MODIFIER_NONE);
	right = GradeHueco_new(1, GRADE_HUECO_MODIFIER_NONE);
	ck_assert_int_eq(GradeHueco_cmp(left, right), 0);
	GradeHueco_free(left);
	GradeHueco_free(right);

	left = GradeHueco_new(1, GRADE_HUECO_MODIFIER_NONE);
	right = GradeHueco_new(2, GRADE_HUECO_MODIFIER_NONE);
	ck_assert_int_lt(GradeHueco_cmp(left, right), 0);
	GradeHueco_free(left);
	GradeHueco_free(right);

	left = GradeHueco_new(1, GRADE_HUECO_MODIFIER_NONE);
	right = GradeHueco_new(1, GRADE_HUECO_MODIFIER_PLUS);
	ck_assert_int_lt(GradeHueco_cmp(left, right), 0);
	GradeHueco_free(left);
	GradeHueco_free(right);
}
END_TEST


START_TEST(test_dup)
{
	unsigned int value;
	GradeHuecoModifier modifier;
	GradeHueco *grade, *duped;

	duped = GradeHueco_dup(NULL);
	ck_assert_ptr_null(duped);
	ck_assert_int_eq(errno, EINVAL);

	value = 5;
	modifier = GRADE_HUECO_MODIFIER_NONE;

	grade = GradeHueco_new(value, modifier);
	duped = GradeHueco_dup(grade);

	ck_assert_ptr_nonnull(duped);
	ck_assert_int_eq(GradeHueco_cmp(grade, duped), 0);

	GradeHueco_free(grade);
	GradeHueco_free(duped);
}
END_TEST

START_TEST(test_str)
{
	GradeHueco *grade;

	grade = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	ck_assert_str_eq(GradeHueco_str(grade), "V0");
	GradeHueco_free(grade);

	grade = GradeHueco_new(1, GRADE_HUECO_MODIFIER_MINUS);
	ck_assert_str_eq(GradeHueco_str(grade), "V1-");
	GradeHueco_free(grade);

	grade = GradeHueco_new(2, GRADE_HUECO_MODIFIER_PLUS);
	ck_assert_str_eq(GradeHueco_str(grade), "V2+");
	GradeHueco_free(grade);

	grade = GradeHueco_new(10, GRADE_HUECO_MODIFIER_NONE);
	ck_assert_str_eq(GradeHueco_str(grade), "V10");
	GradeHueco_free(grade);

	grade = GradeHueco_new(11, GRADE_HUECO_MODIFIER_MINUS);
	ck_assert_str_eq(GradeHueco_str(grade), "V11-");
	GradeHueco_free(grade);

	grade = GradeHueco_new(12, GRADE_HUECO_MODIFIER_PLUS);
	ck_assert_str_eq(GradeHueco_str(grade), "V12+");
	GradeHueco_free(grade);
}
END_TEST

START_TEST(test_fromstr)
{
	GradeHueco *grade, *grade_from_str;
	char *str;

	grade_from_str = GradeHueco_fromstr("Not a valid grade-string");
	ck_assert_ptr_null(grade_from_str);
	ck_assert_int_eq(errno, EINVAL);

	grade_from_str = GradeHueco_fromstr("V5/");
	ck_assert_ptr_null(grade_from_str);
	ck_assert_int_eq(errno, EINVAL);

	str = "V0";
	grade = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	grade_from_str = GradeHueco_fromstr(str);
	ck_assert_ptr_nonnull(grade_from_str);
	ck_assert_int_eq(GradeHueco_cmp(grade, grade_from_str), 0);
	GradeHueco_free(grade);
	GradeHueco_free(grade_from_str);

	str = "V7-";
	grade = GradeHueco_new(7, GRADE_HUECO_MODIFIER_MINUS);
	grade_from_str = GradeHueco_fromstr(str);
	ck_assert_ptr_nonnull(grade_from_str);
	ck_assert_int_eq(GradeHueco_cmp(grade, grade_from_str), 0);
	GradeHueco_free(grade);
	GradeHueco_free(grade_from_str);

	str = "V11+";
	grade = GradeHueco_new(11, GRADE_HUECO_MODIFIER_PLUS);
	grade_from_str = GradeHueco_fromstr(str);
	ck_assert_ptr_nonnull(grade_from_str);
	ck_assert_int_eq(GradeHueco_cmp(grade, grade_from_str), 0);
	GradeHueco_free(grade);
	GradeHueco_free(grade_from_str);
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
	tcase_add_test(tc_core, test_dup);
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
