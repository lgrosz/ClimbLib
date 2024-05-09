#include <assert.h>
#include <stdlib.h>
#include "grades.h"

int main()
{
	GradeHueco a = GradeHueco_new(0, GRADE_HUECO_MODIFIER_NONE);
	assert(a != NULL);

	free(a);

	return 0;
}
