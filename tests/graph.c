#include <errno.h>
#include <stdlib.h>

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

void graph()
{
	test_free_null();
	test_new();
	exit(EXIT_SUCCESS);
}
