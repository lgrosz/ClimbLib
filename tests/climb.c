#include <errno.h>
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
	Climb *c = Climb_new();
	VERIFY(errno == 0);
	VERIFY(c != NULL);

	Climb_free(c);
	VERIFY(errno == 0);
}

static void test_name()
{
	Climb *c = Climb_new();
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

static void test_description()
{
	Climb *c = Climb_new();
	VERIFY(errno == 0);
	VERIFY(c != NULL);

	VERIFY(strcmp(Climb_description(c), "") == 0);

	char description[] = "A problem description...\nAnother line...";
	Climb_set_description(c, description);
	VERIFY(errno == 0);
	VERIFY(strcmp(Climb_description(c), description) == 0);

	Climb_set_description(c, "");
	VERIFY(errno == 0);
	VERIFY(strcmp(Climb_description(c), "") == 0);

	Climb_free(c);
	VERIFY(errno == 0);
}

static void test_brief()
{
	Climb *c = Climb_new();
	VERIFY(errno == 0);
	VERIFY(c != NULL);

	VERIFY(strcmp(Climb_brief(c), "") == 0);

	char brief[] = "A problem brief...";
	Climb_set_brief(c, brief);
	VERIFY(errno == 0);
	VERIFY(strcmp(Climb_brief(c), brief) == 0);

	Climb_set_brief(c, "");
	VERIFY(errno == 0);
	VERIFY(strcmp(Climb_brief(c), "") == 0);

	Climb_free(c);
	VERIFY(errno == 0);
}

static int string_array_contains(const char **arr, unsigned int len, const char *str)
{
	for (int i = 0; i < len; i++) {
		if (strcmp(arr[i], str) == 0) {
			return 1;
		}
	}

	return 0;
}

static void test_aliases()
{
	Climb *c = Climb_new();
	VERIFY(errno == 0);
	VERIFY(c != NULL);

	char alias1[] = "An alias";
	char alias2[] = "Another alias";

	Climb_add_alias(c, alias1);
	VERIFY(errno == 0);

	Climb_add_alias(c, alias2);
	VERIFY(errno == 0);

	size_t aliaseslen;
	const char **aliases = Climb_aliases(c, &aliaseslen);
	VERIFY(errno == 0);
	VERIFY(aliaseslen == 2);
	VERIFY(string_array_contains(aliases, aliaseslen, alias1));
	VERIFY(string_array_contains(aliases, aliaseslen, alias2));

	Climb_remove_alias(c, alias1);
	VERIFY(errno == 0);

	aliases = Climb_aliases(c, &aliaseslen);
	VERIFY(errno == 0);
	VERIFY(aliaseslen == 1);
	VERIFY(!string_array_contains(aliases, aliaseslen, alias1));
	VERIFY(string_array_contains(aliases, aliaseslen, alias2));

	Climb_add_alias(c, alias2);
	VERIFY(errno == 0);
	Climb_aliases(c, &aliaseslen);
	VERIFY(errno == 0);
	VERIFY(aliaseslen == 1);

	Climb_free(c);
	VERIFY(errno == 0);
}

int climb()
{
	test_free_null();
	test_new();
	test_name();
	test_description();
	test_brief();
	test_aliases();

	exit(EXIT_SUCCESS);
}
