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
	ClimbGraph g = ClimbGraph_new();
	VERIFY(errno == 0);
	VERIFY(g != NULL);

	ClimbGraph_free(g);
	VERIFY(errno == 0);
}

#define SETUP_GRAPH(a) \
	ClimbGraph (a) = ClimbGraph_new(); \
	VERIFY(errno == 0); \
	VERIFY((a) != NULL); \

#define CLEANUP_GRAPH(a) \
	ClimbGraph_free((a)); \
	VERIFY(errno == 0)

static void test_add_climb()
{
	SETUP_GRAPH(g);

	Climb c = Climb_new();
	ClimbNode cn = ClimbNode_new(c);
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

#define SETUP_CLIMB(a, b) \
	Climb (a) = Climb_new(); \
	VERIFY(errno == 0); \
	VERIFY((a) != NULL); \
	ClimbNode (b) = ClimbNode_new((a)); \
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

void graph()
{
	test_free_null();
	test_new();
	test_add_climb();
	test_add_variation();
	exit(EXIT_SUCCESS);
}
