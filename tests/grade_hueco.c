#include <errno.h>
#include <stdlib.h>
#include <check.h>

#include <grade_hueco.h>

START_TEST(test_cmp)
{
	GradeHueco *left, *right;

        ck_assert_int_eq(
            GradeHueco_cmp((GradeHueco){1, GRADE_HUECO_MODIFIER_NONE},
                           (GradeHueco){1, GRADE_HUECO_MODIFIER_NONE}),
            0);

        ck_assert_int_lt(
            GradeHueco_cmp((GradeHueco){1, GRADE_HUECO_MODIFIER_NONE},
                           (GradeHueco){2, GRADE_HUECO_MODIFIER_NONE}),
            0);

        ck_assert_int_lt(
            GradeHueco_cmp((GradeHueco){1, GRADE_HUECO_MODIFIER_NONE},
                           (GradeHueco){1, GRADE_HUECO_MODIFIER_PLUS}),
            0);
}
END_TEST

START_TEST(test_str)
{
	GradeHueco grade;

	// 4 characters is the largest string
	char str[5];
	size_t strlen;

	grade = (GradeHueco) { 0, GRADE_HUECO_MODIFIER_NONE};
	ck_assert_int_eq((strlen = GradeHueco_str(grade, NULL, 0)), 2);
	ck_assert_int_eq(GradeHueco_str(grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V0");

	grade = (GradeHueco) { 1, GRADE_HUECO_MODIFIER_MINUS };
	ck_assert_int_eq((strlen = GradeHueco_str(grade, NULL, 0)), 3);
	ck_assert_int_eq(GradeHueco_str(grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V1-");

	grade = (GradeHueco) { 2, GRADE_HUECO_MODIFIER_PLUS };
	ck_assert_int_eq((strlen = GradeHueco_str(grade, NULL, 0)), 3);
	ck_assert_int_eq(GradeHueco_str(grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V2+");

	grade = (GradeHueco) { 10, GRADE_HUECO_MODIFIER_NONE };
	ck_assert_int_eq((strlen = GradeHueco_str(grade, NULL, 0)), 3);
	ck_assert_int_eq(GradeHueco_str(grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V10");

	grade = (GradeHueco) { 11, GRADE_HUECO_MODIFIER_MINUS };
	ck_assert_int_eq((strlen = GradeHueco_str(grade, NULL, 0)), 4);
	ck_assert_int_eq(GradeHueco_str(grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V11-");

	grade = (GradeHueco) { 12, GRADE_HUECO_MODIFIER_PLUS };
	ck_assert_int_eq((strlen = GradeHueco_str(grade, NULL, 0)), 4);
	ck_assert_int_eq(GradeHueco_str(grade, str, strlen + 1), strlen);
	ck_assert_str_eq(str, "V12+");
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

static Suite *suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Hueco Grades");

	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_cmp);
	tcase_add_test(tc_core, test_str);
	tcase_add_test(tc_core, test_fromstr);

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
