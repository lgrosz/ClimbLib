#include <check.h>
#include <stdlib.h>

#include "grade_item.h"
#include "grade_font.h"
#include "allocator.h"

#include "grade_hueco.h"
#include "more_allocators.h"

START_TEST(bad_free)
{
	// Shouldn't crash
	GradeItem_free(NULL);
}
END_TEST

START_TEST(test_fontainebleau)
{
	GradeItem *item;
	GradeFontainebleau grade, result;

	grade = (GradeFontainebleau){ 7, GRADE_FONT_DIVISION_A, GRADE_FONT_MODIFIER_NONE };

	climblib_set_alloc(bad_malloc, NULL, NULL);
	ck_assert_ptr_null(item = GradeItem_new_fontainebleau(grade));
	climblib_set_alloc(NULL, NULL, NULL);

	ck_assert_ptr_nonnull(item = GradeItem_new_fontainebleau(grade));

	ck_assert_int_eq(GradeItem_fontainebleau(item, &result), 0);
	ck_assert_int_eq(GradeFontainebleau_cmp(grade, result), 0);

	ck_assert_int_ne(GradeItem_hueco(item, NULL), 0);

	GradeItem_free(item);
}
END_TEST

START_TEST(test_hueco)
{
	GradeItem *item;
	GradeHueco grade, result;

	grade = (GradeHueco){ 7, GRADE_HUECO_MODIFIER_NONE };

	climblib_set_alloc(bad_malloc, NULL, NULL);
	ck_assert_ptr_null(item = GradeItem_new_hueco(grade));
	climblib_set_alloc(NULL, NULL, NULL);

	ck_assert_ptr_nonnull(item = GradeItem_new_hueco(grade));

	ck_assert_int_eq(GradeItem_hueco(item, &result), 0);
	ck_assert_int_eq(GradeHueco_cmp(grade, result), 0);

	ck_assert_int_ne(GradeItem_fontainebleau(item, NULL), 0);

	GradeItem_free(item);
}
END_TEST

static Suite *suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Grade Items");

	tc_core = tcase_create("Core");

	suite_add_tcase(s, tc_core);
	tcase_add_test(tc_core, bad_free);
	tcase_add_test(tc_core, test_fontainebleau);
	tcase_add_test(tc_core, test_hueco);

	return s;
}

void grade_item()
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

