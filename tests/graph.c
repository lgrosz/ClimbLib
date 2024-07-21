#include <check.h>
#include <stdlib.h>

#include "graph.h"

START_TEST(test_new)
{
	Graph *graph;

	graph = Graph_new();
	ck_assert_ptr_nonnull(graph);

	Graph_free(graph);
}
END_TEST

static Suite *suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Graph");

	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_new);

	suite_add_tcase(s, tc_core);

	return s;
}

void graph()
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
