#include "graph.h"
#include <errno.h>
#include <stdlib.h>

struct ClimbGraph_ {
	ClimbNode *climbs;
	size_t climbslen;
};

ClimbGraph ClimbGraph_new()
{
	ClimbGraph ret;

	if (NULL == (ret = malloc(sizeof(struct ClimbGraph_)))) {
		return NULL;
	} else {
		ret->climbs = NULL;
		ret->climbslen = 0;
	}

	errno = 0;
	return ret;
}

void ClimbGraph_free(ClimbGraph graph)
{
	if (graph == NULL) {
		errno = EINVAL;
		return;
	}

	if (NULL != graph->climbs) {
		free(graph->climbs);
	}

	free(graph);
	errno = 0;
}
