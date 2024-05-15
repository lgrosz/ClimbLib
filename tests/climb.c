#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "verify.h"

#include <climb.h>

static void test_free_null()
{
	Climb_free(NULL);
	VERIFY(errno == EINVAL);
}

static void test_new()
{
	Climb c = Climb_new();
	VERIFY(errno == 0);
	VERIFY(c != NULL);

	Climb_free(c);
	VERIFY(errno == 0);
}

int climb()
{
	test_free_null();
	test_new();

	exit(EXIT_SUCCESS);
}
