#include <check.h>
#include <stdlib.h>

#include "graph.h"
#include "climb.h"
#include "formation.h"
#include "allocator.h"
#include "more_allocators.h"

START_TEST(test_new)
{
	Graph *graph;
	Node *node;

	climblib_set_alloc(bad_malloc, NULL, NULL);
	graph = Graph_new();
	ck_assert_ptr_null(graph);
	climblib_set_alloc(NULL, NULL, NULL);

	graph = Graph_new();
	ck_assert_ptr_nonnull(graph);

	node = Node_new();
	ck_assert_ptr_nonnull(node);

	Graph_free(graph);
	Node_free(node);
}
END_TEST

START_TEST(test_nodes)
{
	Graph *graph;
	Node *a, *b, *c, *n;

	climblib_set_alloc(bad_malloc, NULL, NULL);
	a = Node_new();
	ck_assert_ptr_null(a);
	climblib_set_alloc(NULL, NULL, NULL);

	graph = Graph_new();

	a = Node_new();

	ck_assert_ptr_nonnull(a);
	ck_assert_int_eq(Node_get_type(a), NodeType_UNDEFINED);

	b = Node_new();
	c = Node_new();

	ck_assert_ptr_null(Graph_get_nodes(NULL));
	ck_assert_ptr_null(Graph_get_nodes(graph));
	ck_assert_int_eq(!Graph_add_node(NULL, a), 0);
	ck_assert_int_eq(!Graph_add_node(graph, NULL), 0);

	ck_assert_int_eq(Graph_add_node(graph, a), 0);
	ck_assert_int_eq(Graph_add_node(graph, b), 0);
	ck_assert_int_eq(Graph_add_node(graph, c), 0);

	ck_assert_ptr_eq(n = Graph_get_nodes(graph), a);
	ck_assert_ptr_null(Node_get_next(NULL));
	ck_assert_ptr_eq(n = Node_get_next(n), b);
	ck_assert_ptr_eq(n = Node_get_next(n), c);
	ck_assert_ptr_null(n = Node_get_next(n));

	Graph_free(graph);
	Node_free(a);
	Node_free(b);
	Node_free(c);
}
END_TEST

START_TEST(test_formation_node)
{
	Formation *formation;
	Node *formation_node;

	climblib_set_alloc(bad_malloc, NULL, NULL);
	formation_node = Node_new_formation(NULL);
	ck_assert_ptr_null(formation_node);
	climblib_set_alloc(NULL, NULL, NULL);

	formation = Formation_new();
	ck_assert_ptr_nonnull(formation_node = Node_new_formation(formation));

	ck_assert_int_eq(Node_get_type(formation_node), NodeType_FORMATION);
	ck_assert_ptr_eq(Node_get_formation(formation_node), formation);
	ck_assert_ptr_null(Node_get_climb(formation_node));

	Node_free(formation_node);
	Formation_free(formation);
}
END_TEST

START_TEST(test_climb_node)
{
	Climb *climb;
	Node *climb_node;

	climblib_set_alloc(bad_malloc, NULL, NULL);
	climb_node = Node_new_climb(NULL);
	ck_assert_ptr_null(climb_node);
	climblib_set_alloc(NULL, NULL, NULL);

	climb = Climb_new();
	ck_assert_ptr_nonnull(climb_node = Node_new_climb(climb));

	ck_assert_int_eq(Node_get_type(climb_node), NodeType_CLIMB);
	ck_assert_ptr_eq(Node_get_climb(climb_node), climb);
	ck_assert_ptr_null(Node_get_formation(climb_node));

	Node_free(climb_node);
	Climb_free(climb);
}
END_TEST

START_TEST(test_edges)
{
	Graph *graph;
	Node *a, *b, *c, *d;
	Edge *e;

	graph = Graph_new();
	a = Node_new();

	ck_assert_ptr_null(Node_get_edges(a));

	b = Node_new();
	c = Node_new();
	d = Node_new();

	Graph_add_node(graph, a);
	Graph_add_node(graph, b);
	Graph_add_node(graph, c);
	Graph_add_node(graph, d);

	ck_assert_int_eq(Node_add_edge(a, b), 0);
	ck_assert_int_eq(Node_add_edge(a, c), 0);
	ck_assert_int_eq(Node_add_edge(a, d), 0);
	ck_assert_ptr_nonnull(e = Node_get_edges(a));
	ck_assert_ptr_eq(Edge_get_node(e), b);
	ck_assert_ptr_nonnull(e = Edge_get_next(e));
	ck_assert_ptr_eq(Edge_get_node(e), c);
	ck_assert_ptr_nonnull(e = Edge_get_next(e));
	ck_assert_ptr_eq(Edge_get_node(e), d);
	ck_assert_ptr_null(e = Edge_get_next(e));

	Graph_free(graph);
	Node_free(a);
	Node_free(b);
	Node_free(c);
	Node_free(d);
}
END_TEST

static Suite *suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Graph");

	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_new);
	tcase_add_test(tc_core, test_nodes);
	tcase_add_test(tc_core, test_formation_node);
	tcase_add_test(tc_core, test_climb_node);
	tcase_add_test(tc_core, test_edges);

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
