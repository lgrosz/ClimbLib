#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "verify.h"

#include <formation.h>

static void test_free_null()
{
	Formation_free(NULL);
	VERIFY(errno == EINVAL);
}

static void test_new()
{
	Formation *f = Formation_new();
	VERIFY(errno == 0);
	VERIFY(f != NULL);

	Formation_free(f);
	VERIFY(errno == 0);
}

static void test_name()
{
	Formation *f = Formation_new();
	VERIFY(errno == 0);
	VERIFY(f != NULL);

	VERIFY(strcmp(Formation_name(f), "") == 0);

	char name[] = "A Formation Name";
	Formation_set_name(f, name);
	VERIFY(errno == 0);
	VERIFY(strcmp(Formation_name(f), name) == 0);

	Formation_set_name(f, "");
	VERIFY(errno == 0);
	VERIFY(strcmp(Formation_name(f), "") == 0);

	Formation_free(f);
	VERIFY(errno == 0);
}

static void test_description()
{
	Formation *f = Formation_new();
	VERIFY(errno == 0);
	VERIFY(f != NULL);

	VERIFY(strcmp(Formation_description(f), "") == 0);

	char description[] = "A formation description...\nAnother line...";
	Formation_set_description(f, description);
	VERIFY(errno == 0);
	VERIFY(strcmp(Formation_description(f), description) == 0);

	Formation_set_description(f, "");
	VERIFY(errno == 0);
	VERIFY(strcmp(Formation_description(f), "") == 0);

	Formation_free(f);
	VERIFY(errno == 0);
}

static void test_brief()
{
	Formation *f = Formation_new();
	VERIFY(errno == 0);
	VERIFY(f != NULL);

	VERIFY(strcmp(Formation_brief(f), "") == 0);

	char brief[] = "A formation brief...";
	Formation_set_brief(f, brief);
	VERIFY(errno == 0);
	VERIFY(strcmp(Formation_brief(f), brief) == 0);

	Formation_set_brief(f, "");
	VERIFY(errno == 0);
	VERIFY(strcmp(Formation_brief(f), "") == 0);

	Formation_free(f);
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
	Formation *f = Formation_new();
	VERIFY(errno == 0);
	VERIFY(f != NULL);

	char alias1[] = "An alias";
	char alias2[] = "Another alias";

	Formation_add_alias(f, alias1);
	VERIFY(errno == 0);

	Formation_add_alias(f, alias2);
	VERIFY(errno == 0);

	size_t aliaseslen;
	const char **aliases = Formation_aliases(f, &aliaseslen);
	VERIFY(errno == 0);
	VERIFY(aliaseslen == 2);
	VERIFY(string_array_contains(aliases, aliaseslen, alias1));
	VERIFY(string_array_contains(aliases, aliaseslen, alias2));

	Formation_remove_alias(f, alias1);
	VERIFY(errno == 0);

	aliases = Formation_aliases(f, &aliaseslen);
	VERIFY(errno == 0);
	VERIFY(aliaseslen == 1);
	VERIFY(!string_array_contains(aliases, aliaseslen, alias1));
	VERIFY(string_array_contains(aliases, aliaseslen, alias2));

	Formation_add_alias(f, alias2);
	VERIFY(errno == 0);
	Formation_aliases(f, &aliaseslen);
	VERIFY(errno == 0);
	VERIFY(aliaseslen == 1);

	Formation_free(f);
	VERIFY(errno == 0);
}

int formation()
{
	test_free_null();
	test_new();
	test_name();
	test_description();
	test_brief();
	test_aliases();

	exit(EXIT_SUCCESS);
}
