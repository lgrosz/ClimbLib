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

void ClimbGraph_add_climb(ClimbGraph graph, const ClimbNode node) {
	if (graph == NULL || node == NULL) {
		errno = EINVAL;
		return;
	}

	if (NULL == (graph->climbs = realloc(graph->climbs, sizeof(ClimbNode) * (graph->climbslen + 1)))) {
		return;
	}

	graph->climbs[graph->climbslen] = node;
	graph->climbslen = graph->climbslen + 1;
	errno = 0;
}

void ClimbGraph_remove_climb(ClimbGraph graph, const ClimbNode node)
{
	if (graph == NULL || node == NULL) {
		errno = EINVAL;
		return;
	}

	int index = -1;

	for (int i = 0; i < graph->climbslen; i++) {
		if (graph->climbs[i] == node) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		return;
	}

	for (int i = index; i < graph->climbslen - 1; i++) {
		graph->climbs[i] = graph->climbs[i + 1];
	}

	if (NULL == (graph->climbs = realloc(graph->climbs, sizeof(ClimbNode) * (graph->climbslen - 1)))) {
		return;
	}

	graph->climbslen = graph->climbslen - 1;
}

int ClimbGraph_has_climb(ClimbGraph graph, ClimbNode node)
{
	if (graph == NULL || node == NULL) {
		errno = EINVAL;
		return 0;
	}

	for (size_t i = 0; i < graph->climbslen; i++) {
		if (graph->climbs[i] == node) {
			return 1;
		}
	}

	return 0;
}
