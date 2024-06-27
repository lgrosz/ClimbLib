#include "node.h"
#include <errno.h>
#include <stdlib.h>

struct ClimbNode_ {
	Climb climb;
};

struct FormationNode_ {
	Formation climb;
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

FormationNode FormationNode_new(Formation climb)
{
	FormationNode ret;

	if (NULL == (ret = malloc(sizeof(FormationNode)))) {
		return NULL;
	} else {
		ret->climb = climb;
	}

	errno = 0;
	return ret;
}

void FormationNode_free(FormationNode node)
{
	if (node == NULL) {
		errno = EINVAL;
		return;
	}

	free(node);
	errno = 0;
}

Formation FormationNode_climb(const FormationNode node)
{
	if (node == NULL) {
		errno = EINVAL;
		return NULL;
	}

	return node->climb;
}
