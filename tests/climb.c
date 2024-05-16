#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static void test_name()
{
	Climb c = Climb_new();
	VERIFY(errno == 0);
	VERIFY(c != NULL);

	VERIFY(strcmp(Climb_name(c), "") == 0);

	char name[] = "A Problem Name";
	Climb_set_name(c, name);
	VERIFY(errno == 0);
	VERIFY(strcmp(Climb_name(c), name) == 0);

	Climb_set_name(c, "");
	VERIFY(errno == 0);
	VERIFY(strcmp(Climb_name(c), "") == 0);

	Climb_free(c);
	VERIFY(errno == 0);
}

int climb()
{
	test_free_null();
	test_new();
	test_name();

	exit(EXIT_SUCCESS);
}
