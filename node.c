#include "node.h"
#include <errno.h>
#include <stdlib.h>

struct ClimbNode_ {
	Climb climb;
};

ClimbNode ClimbNode_new(Climb climb)
{
	ClimbNode ret;

	if (NULL == (ret = malloc(sizeof(ClimbNode)))) {
		return NULL;
	} else {
		ret->climb = climb;
	}

	errno = 0;
	return ret;
}

void ClimbNode_free(ClimbNode node)
{
	if (node == NULL) {
		errno = EINVAL;
		return;
	}

	free(node);
	errno = 0;
}

Climb ClimbNode_climb(const ClimbNode node)
{
	if (node == NULL) {
		errno = EINVAL;
		return NULL;
	}

	return node->climb;
}
