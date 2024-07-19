#include <check.h>
#include <stdlib.h>

#include "allocator.h"

static void *test_malloc(size_t size)
{
	return malloc(size);
}

static void *test_realloc(void *ptr, size_t size)
{
	return realloc(ptr, size);
}

static void test_free(void *ptr)
{
	return free(ptr);
}

START_TEST(test_set_alloc)
{
	climblib_malloc_t m = NULL;
	climblib_realloc_t r = NULL;
	climblib_free_t f = NULL;
	int ret;
	void *ptr;

	climblib_get_alloc(NULL, NULL, NULL);

	climblib_get_alloc(&m, &r, &f);
	ck_assert_ptr_null(m);
	ck_assert_ptr_null(r);
	ck_assert_ptr_null(f);

	ptr = climblib_malloc(1);
	ck_assert_ptr_nonnull(ptr);
	ptr = climblib_realloc(ptr, 2);
	ck_assert_ptr_nonnull(ptr);
	climblib_free(ptr);

	climblib_set_alloc(test_malloc, test_realloc, test_free);

	climblib_get_alloc(&m, &r, &f);
	ck_assert(m == test_malloc);
	ck_assert(r == test_realloc);
	ck_assert(f == test_free);

	ptr = climblib_malloc(1);
	ck_assert_ptr_nonnull(ptr);
	ptr = climblib_realloc(ptr, 2);
	ck_assert_ptr_nonnull(ptr);
	climblib_free(ptr);
}
END_TEST

static Suite *suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Allocator");

	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_set_alloc);

	suite_add_tcase(s, tc_core);

	return s;
}

void allocator()
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
