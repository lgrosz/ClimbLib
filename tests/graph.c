#include <errno.h>
#include <stdlib.h>
#include <check.h>

#include "climb.h"
#include "formation.h"
#include "verify.h"

#include <graph.h>

START_TEST(test_new)
{
	ClimbGraph *graph = ClimbGraph_new();
	ck_assert_ptr_nonnull(graph);
	ClimbGraph_free(graph);
}
END_TEST

START_TEST(test_free_null)
{
	ClimbGraph_free(NULL);
	ck_assert_int_eq(errno, EINVAL);
}
END_TEST

#define SETUP_GRAPH(a) \
	ClimbGraph *(a) = ClimbGraph_new(); \
	VERIFY(errno == 0); \
	VERIFY((a) != NULL); \

#define CLEANUP_GRAPH(a) \
	ClimbGraph_free((a)); \
	VERIFY(errno == 0)

static void test_add_climb()
{
	SETUP_GRAPH(g);

	Climb *c = Climb_new();
	ClimbGraph_add_climb(g, c);
	VERIFY(errno == 0);

	VERIFY(ClimbGraph_has_climb(g, c));
	VERIFY(errno == 0);

	ClimbGraph_remove_climb(g, c);
	VERIFY(errno == 0);

	VERIFY(!ClimbGraph_has_climb(g, c));
	VERIFY(errno == 0);

	CLEANUP_GRAPH(g);
	Climb_free(c);
}

static void test_climbs()
{
	SETUP_GRAPH(g);

	Climb *c = Climb_new();
	ClimbGraph_add_climb(g, c);
	VERIFY(errno == 0);

	size_t climbslen;
	ClimbGraph_climbs(g, NULL, &climbslen);
	VERIFY(errno == 0);
	VERIFY(climbslen == 1);

	Climb *c1 = Climb_new();
	ClimbGraph_add_climb(g, c1);
	VERIFY(errno == 0);

	ClimbGraph_climbs(g, NULL, &climbslen);
	VERIFY(errno == 0);
	VERIFY(climbslen == 2);

	CLEANUP_GRAPH(g);
	Climb_free(c);
	Climb_free(c1);
}

#define SETUP_CLIMB(a) \
	Climb *(a) = Climb_new(); \
	VERIFY(errno == 0); \
	VERIFY((a) != NULL);

#define CLEANUP_CLIMB(a) \
	Climb_free((a)); \
	VERIFY(errno == 0);

#define ADD_CLIMB(a, b) \
	ClimbGraph_add_climb((a), (b)); \
	VERIFY(errno == 0);

static void test_add_variation()
{
	SETUP_GRAPH(g);
	SETUP_CLIMB(a);
	SETUP_CLIMB(b);
	ADD_CLIMB(g, a);
	ADD_CLIMB(g, b);

	ClimbGraph_add_variation(g, a, b);
	VERIFY(errno == 0);

	VERIFY(ClimbGraph_has_variation(g, a, b));
	VERIFY(!ClimbGraph_has_variation(g, b, a));

	ClimbGraph_remove_variation(g, a, b);
	VERIFY(errno == 0);

	VERIFY(!ClimbGraph_has_variation(g, a, b));

	CLEANUP_CLIMB(a);
	CLEANUP_CLIMB(b);
	CLEANUP_GRAPH(g);
}

static void test_variations()
{
	SETUP_GRAPH(g);

	SETUP_CLIMB(a);
	SETUP_CLIMB(a1);
	SETUP_CLIMB(b);
	SETUP_CLIMB(b1);
	SETUP_CLIMB(b2);
	ADD_CLIMB(g, a);
	ADD_CLIMB(g, a1);
	ADD_CLIMB(g, b);
	ADD_CLIMB(g, b1);
	ADD_CLIMB(g, b2);

	ClimbGraph_add_variation(g, a, a1);
	VERIFY(errno == 0);
	ClimbGraph_add_variation(g, b, b1);
	VERIFY(errno == 0);
	ClimbGraph_add_variation(g, b, b2);
	VERIFY(errno == 0);

	size_t avarslen;
	ClimbGraph_variations(g, a, NULL, &avarslen);
	VERIFY(errno == 0);
	VERIFY(avarslen == 1);
	const Climb **avars;
	VERIFY(NULL != (avars = malloc(sizeof(Climb*) * avarslen)));
	ClimbGraph_variations(g, a, avars, &avarslen);
	VERIFY(errno == 0);
	VERIFY(avarslen == 1);
	free(avars);

	size_t bvarslen;
	ClimbGraph_variations(g, b, NULL, &bvarslen);
	VERIFY(errno == 0);
	VERIFY(bvarslen == 2);
	const Climb **bvars;
	VERIFY(NULL != (bvars = malloc(sizeof(Climb*) * bvarslen)));
	ClimbGraph_variations(g, b, bvars, &bvarslen);
	VERIFY(errno == 0);
	printf("%zu", bvarslen);
	VERIFY(bvarslen == 2);
	free(bvars);

	CLEANUP_GRAPH(g);

	CLEANUP_CLIMB(a);
	CLEANUP_CLIMB(a1);
	CLEANUP_CLIMB(b);
	CLEANUP_CLIMB(b1);
	CLEANUP_CLIMB(b2);
}

static void test_linkup()
{
	SETUP_GRAPH(g);
	SETUP_CLIMB(a);
	SETUP_CLIMB(b);
	SETUP_CLIMB(c);
	ADD_CLIMB(g, a);
	ADD_CLIMB(g, b);
	ADD_CLIMB(g, c);

	const Climb *links[] = { b, c };
	ClimbGraph_add_linkup(g, a, links, 2);
	VERIFY(errno == 0);

	VERIFY(ClimbGraph_is_linkup(g, a) == 1);
	VERIFY(errno == 0);

	size_t linkslen;
	ClimbGraph_linkup(g, a, NULL, &linkslen);
	VERIFY(errno == 0);
	VERIFY(linkslen == 2);

	const Climb **links_from_graph;
	links_from_graph = malloc(sizeof(Climb*) * linkslen);
	ClimbGraph_linkup(g, a, links_from_graph, &linkslen);
	VERIFY(errno == 0);
	VERIFY(linkslen == 2);
	free(links_from_graph);

	VERIFY(ClimbGraph_is_of_linkup(g, b));
	VERIFY(errno == 0);

	size_t linkupslen;
	ClimbGraph_of_linkup(g, b, NULL, &linkupslen);
	VERIFY(errno == 0);
	VERIFY(linkupslen == 1);

	const Climb **linkups;
	linkups = malloc(sizeof(Climb*) * linkupslen);
	ClimbGraph_of_linkup(g, b, linkups, &linkupslen);
	VERIFY(errno == 0);
	VERIFY(linkupslen == 1);
	free(linkups);

	ClimbGraph_remove_linkup(g, a);
	VERIFY(errno == 0);
	VERIFY(!ClimbGraph_is_linkup(g, a));
	VERIFY(!ClimbGraph_is_of_linkup(g, b));

	CLEANUP_GRAPH(g);
	CLEANUP_CLIMB(a);
	CLEANUP_CLIMB(b);
	CLEANUP_CLIMB(c);
}

START_TEST(test_add_formation)
{
	ClimbGraph *graph;
	Formation *formation;

	graph = ClimbGraph_new();
	formation = Formation_new();

	ClimbGraph_add_formation(graph, formation);
	ck_assert(ClimbGraph_has_formation(graph, formation));

	ClimbGraph_remove_formation(graph, formation);
	ck_assert(!ClimbGraph_has_formation(graph, formation));

	ClimbGraph_free(graph);
	Formation_free(formation);
}
END_TEST

START_TEST(test_add_subformation)
{
	ClimbGraph *graph;
	Formation *formation, *subformation;

	graph = ClimbGraph_new();
	formation = Formation_new();
	subformation = Formation_new();

	ClimbGraph_add_formation(graph, formation);
	ClimbGraph_add_formation(graph, subformation);

	ClimbGraph_add_subformation(graph, formation, subformation);
	ck_assert(ClimbGraph_has_subformation(graph, formation, subformation));

	ClimbGraph_remove_subformation(graph, formation, subformation);
	ck_assert(!ClimbGraph_has_subformation(graph, formation, subformation));

	ClimbGraph_free(graph);
	Formation_free(formation);
	Formation_free(subformation);
}
END_TEST

START_TEST(test_add_formation_climb)
{
	ClimbGraph *graph;
	Formation *formation;
	Climb *climb;

	graph = ClimbGraph_new();
	formation = Formation_new();
	climb = Climb_new();

	ClimbGraph_add_formation(graph, formation);
	ClimbGraph_add_climb(graph, climb);

	ClimbGraph_add_formation_climb(graph, formation, climb);
	ck_assert(ClimbGraph_has_formation_climb(graph, formation, climb));

	ClimbGraph_remove_formation_climb(graph, formation, climb);
	ck_assert(!ClimbGraph_has_formation_climb(graph, formation, climb));

	ClimbGraph_free(graph);
	Formation_free(formation);
	Climb_free(climb);
}
END_TEST

static Suite *suite()
{
	Suite *s;
	TCase *tc_core, *tc_formations;

	s = suite_create("Hueco Grades");

	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_new);
	tcase_add_test(tc_core, test_free_null);

	tc_formations = tcase_create("Formations");
	tcase_add_test(tc_formations, test_add_formation);
	tcase_add_test(tc_formations, test_add_subformation);
	tcase_add_test(tc_formations, test_add_formation_climb);

	suite_add_tcase(s, tc_core);
	suite_add_tcase(s, tc_formations);

	return s;
}
void graph()
{
	test_add_climb();
	test_climbs();
	test_add_variation();
	test_variations();
	test_linkup();

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
