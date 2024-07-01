#include <errno.h>
#include <stdlib.h>

#include "climb.h"
#include "node.h"
#include "verify.h"

#include <graph.h>

static void test_free_null()
{
	ClimbGraph_free(NULL);
	VERIFY(errno == EINVAL);
}

static void test_new()
{
	ClimbGraph *g = ClimbGraph_new();
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	ClimbGraph_free(g);
	VERIFY(errno == 0);
}

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
	ClimbNode *cn = ClimbNode_new(c);
	ClimbGraph_add_climb(g, cn);
	VERIFY(errno == 0);

	VERIFY(ClimbGraph_has_climb(g, cn));
	VERIFY(errno == 0);

	ClimbGraph_remove_climb(g, cn);
	VERIFY(errno == 0);

	VERIFY(!ClimbGraph_has_climb(g, cn));
	VERIFY(errno == 0);

	CLEANUP_GRAPH(g);
	ClimbNode_free(cn);
	Climb_free(c);
}

static void test_climbs()
{
	SETUP_GRAPH(g);

	Climb *c = Climb_new();
	ClimbNode *cn = ClimbNode_new(c);
	ClimbGraph_add_climb(g, cn);
	VERIFY(errno == 0);

	size_t climbslen;
	ClimbNode **climbs = ClimbGraph_climbs(g, &climbslen);
	VERIFY(errno == 0);
	VERIFY(climbslen == 1);
	VERIFY(climbs[0] == cn);

	Climb *c1 = Climb_new();
	ClimbNode *cn1 = ClimbNode_new(c1);
	ClimbGraph_add_climb(g, cn1);
	VERIFY(errno == 0);

	climbs = ClimbGraph_climbs(g, &climbslen);
	VERIFY(errno == 0);
	VERIFY(climbslen == 2);
	VERIFY(climbs[1] == cn1);

	CLEANUP_GRAPH(g);
	ClimbNode_free(cn);
	Climb_free(c);
	ClimbNode_free(cn1);
	Climb_free(c1);
}

#define SETUP_CLIMB(a, b) \
	Climb *(a) = Climb_new(); \
	VERIFY(errno == 0); \
	VERIFY((a) != NULL); \
	ClimbNode *(b) = ClimbNode_new((a)); \
	VERIFY(errno == 0); \
	VERIFY((b) != NULL);

#define CLEANUP_CLIMB(a, b) \
	ClimbNode_free((b)); \
	VERIFY(errno == 0); \
	Climb_free((a)); \
	VERIFY(errno == 0);

#define ADD_CLIMB(a, b) \
	ClimbGraph_add_climb((a), (b)); \
	VERIFY(errno == 0);

static void test_add_variation()
{
	SETUP_GRAPH(g);
	SETUP_CLIMB(a, an);
	SETUP_CLIMB(b, bn);
	ADD_CLIMB(g, an);
	ADD_CLIMB(g, bn);

	ClimbGraph_add_variation(g, an, bn);
	VERIFY(errno == 0);

	VERIFY(ClimbGraph_has_variation(g, an, bn));
	VERIFY(!ClimbGraph_has_variation(g, bn, an));

	ClimbGraph_remove_variation(g, an, bn);
	VERIFY(errno == 0);

	VERIFY(!ClimbGraph_has_variation(g, an, bn));

	CLEANUP_CLIMB(a, an);
	CLEANUP_CLIMB(b, bn);
	CLEANUP_GRAPH(g);
}

static void test_variations()
{
	SETUP_GRAPH(g);

	SETUP_CLIMB(a, an);
	SETUP_CLIMB(a1, a1n);
	SETUP_CLIMB(b, bn);
	SETUP_CLIMB(b1, b1n);
	SETUP_CLIMB(b2, b2n);
	ADD_CLIMB(g, an);
	ADD_CLIMB(g, a1n);
	ADD_CLIMB(g, bn);
	ADD_CLIMB(g, b1n);
	ADD_CLIMB(g, b2n);

	ClimbGraph_add_variation(g, an, a1n);
	VERIFY(errno == 0);
	ClimbGraph_add_variation(g, bn, b1n);
	VERIFY(errno == 0);
	ClimbGraph_add_variation(g, bn, b2n);
	VERIFY(errno == 0);

	size_t avarslen;
	ClimbGraph_variations(g, an, NULL, &avarslen);
	VERIFY(errno == 0);
	VERIFY(avarslen == 1);
	const ClimbNode **avars;
	VERIFY(NULL != (avars = malloc(sizeof(ClimbNode*) * avarslen)));
	ClimbGraph_variations(g, an, avars, &avarslen);
	VERIFY(errno == 0);
	VERIFY(avarslen == 1);
	VERIFY(avars[0] == a1n);
	free(avars);

	size_t bvarslen;
	ClimbGraph_variations(g, bn, NULL, &bvarslen);
	VERIFY(errno == 0);
	VERIFY(bvarslen == 2);
	const ClimbNode **bvars;
	VERIFY(NULL != (bvars = malloc(sizeof(ClimbNode*) * bvarslen)));
	ClimbGraph_variations(g, bn, bvars, &bvarslen);
	VERIFY(errno == 0);
	printf("%zu", bvarslen);
	VERIFY(bvarslen == 2);
	VERIFY(bvars[0] == b1n);
	VERIFY(bvars[1] == b2n);
	free(bvars);

	CLEANUP_GRAPH(g);

	CLEANUP_CLIMB(a, an);
	CLEANUP_CLIMB(a1, a1n);
	CLEANUP_CLIMB(b, bn);
	CLEANUP_CLIMB(b1, b1n);
	CLEANUP_CLIMB(b2, b2n);
}

static void test_linkup()
{
	SETUP_GRAPH(g);
	SETUP_CLIMB(a, an);
	SETUP_CLIMB(b, bn);
	SETUP_CLIMB(c, cn);
	ADD_CLIMB(g, an);
	ADD_CLIMB(g, bn);
	ADD_CLIMB(g, cn);

	const ClimbNode *links[] = { bn, cn };
	ClimbGraph_add_linkup(g, an, links, 2);
	VERIFY(errno == 0);

	VERIFY(ClimbGraph_is_linkup(g, an) == 1);
	VERIFY(errno == 0);

	size_t linkslen;
	ClimbGraph_linkup(g, an, NULL, &linkslen);
	VERIFY(errno == 0);
	VERIFY(linkslen == 2);

	const ClimbNode **links_from_graph;
	links_from_graph = malloc(sizeof(ClimbNode*) * linkslen);
	ClimbGraph_linkup(g, an, links_from_graph, &linkslen);
	VERIFY(errno == 0);
	VERIFY(linkslen == 2);
	VERIFY(links_from_graph[0] == bn);
	VERIFY(links_from_graph[1] == cn);
	free(links_from_graph);

	VERIFY(ClimbGraph_is_of_linkup(g, bn));
	VERIFY(errno == 0);

	size_t linkupslen;
	ClimbGraph_of_linkup(g, bn, NULL, &linkupslen);
	VERIFY(errno == 0);
	VERIFY(linkupslen == 1);

	const ClimbNode **linkups;
	linkups = malloc(sizeof(ClimbNode*) * linkupslen);
	ClimbGraph_of_linkup(g, bn, linkups, &linkupslen);
	VERIFY(errno == 0);
	VERIFY(linkupslen == 1);
	VERIFY(linkups[0] == an);
	free(linkups);

	ClimbGraph_remove_linkup(g, an);
	VERIFY(errno == 0);
	VERIFY(!ClimbGraph_is_linkup(g, an));
	VERIFY(!ClimbGraph_is_of_linkup(g, bn));

	CLEANUP_GRAPH(g);
	CLEANUP_CLIMB(a, an);
	CLEANUP_CLIMB(b, bn);
	CLEANUP_CLIMB(c, cn);
}

void graph()
{
	test_free_null();
	test_new();
	test_add_climb();
	test_climbs();
	test_add_variation();
	test_variations();
	test_linkup();
	exit(EXIT_SUCCESS);
}
