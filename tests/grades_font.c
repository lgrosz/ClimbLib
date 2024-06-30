#include <stdlib.h>
#include <check.h>
#include <errno.h>
#include <grades.h>

START_TEST(test_GradeFontainebleau_new)
{
	GradeFontainebleau *g;

	g = GradeFontainebleau_new(10, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	ck_assert_ptr_null(g);
	ck_assert_int_eq(errno, EINVAL);

	g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	ck_assert_ptr_nonnull(g);
	ck_assert_int_eq(errno, 0);

	GradeFontainebleau_free(g);
}
END_TEST

START_TEST(test_GradeFontainebleau_dup)
{
	GradeFontainebleau *g, *h;

	g = GradeFontainebleau_dup(NULL);
	ck_assert_ptr_null(g);
	ck_assert_int_eq(errno, EINVAL);

	g = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	ck_assert_ptr_nonnull(g);
	ck_assert_int_eq(errno, 0);

	h = GradeFontainebleau_dup(g);
	ck_assert_ptr_nonnull(h);
	ck_assert_int_eq(errno, 0);

	ck_assert_int_eq(GradeFontainebleau_cmp(g, h), 0);

	GradeFontainebleau_free(g);
	GradeFontainebleau_free(h);
}
END_TEST

START_TEST(test_GradeFontainebleau_cmp_grade)
{
	GradeFontainebleau *g1 = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	GradeFontainebleau *g2 = GradeFontainebleau_new(7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE);
	GradeFontainebleau *g3 = GradeFontainebleau_new(6, GRADE_FONT_DIVISION_B, GRADE_FONT_MODIFIER_NONE);
	GradeFontainebleau *g4 = GradeFontainebleau_new(8, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_PLUS);

	ck_assert_int_eq(GradeFontainebleau_cmp(g1, g2), 0);
	ck_assert_int_gt(GradeFontainebleau_cmp(g1, g3), 0);
	ck_assert_int_lt(GradeFontainebleau_cmp(g1, g4), 0);
}
END_TEST

START_TEST(test_GradeFontainebleau_cmp_division)
{
}
END_TEST

START_TEST(test_GradeFontainebleau_cmp_modifier)
{
}
END_TEST

START_TEST(test_GradeFontainebleau_cmp_low_grade)
{
}
END_TEST

static Suite *climblib_suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("ClimbLib Fontainebleau Grades");

	tc_core = tcase_create("grades_font");
	tcase_add_test(tc_core, test_GradeFontainebleau_new);
	tcase_add_test(tc_core, test_GradeFontainebleau_dup);
	tcase_add_test(tc_core, test_GradeFontainebleau_cmp_grade);

	suite_add_tcase(s, tc_core);

	return s;
}

int grades_font(int argc, char *argv[])
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = climblib_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
