#include "climb.h"
#include <errno.h>
#include <stdlib.h>

struct Climb_
{
};

Climb Climb_new()
{
	Climb ret;

	if (NULL == (ret = malloc(sizeof(struct Climb_)))) {
		errno = ENOMEM;
		return NULL;
	}

	errno = 0;
	return ret;
}

void Climb_free(Climb climb)
{
	if (climb == NULL) {
		errno = EINVAL;
		return;
	}

	errno = 0;
	free(climb);
}
