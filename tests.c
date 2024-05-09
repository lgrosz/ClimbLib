#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "grades.h"

int main()
{
	// Test free function
	errno = 0;
	GradeHueco_free(NULL);
	assert(errno == EINVAL);

	// Test new function
	GradeHueco a = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	assert(a != NULL);
	GradeHueco_free(a);

	// Test duplicate function
	GradeHueco b = GradeHueco_dup(a);
	assert(b != NULL);
	GradeHueco_free(b);

	errno = 0;
	b = GradeHueco_dup(NULL);
	assert(b == NULL);
	assert(errno == EINVAL);

	return 0;
}
