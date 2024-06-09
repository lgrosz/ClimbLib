#include "graph.h"
#include <errno.h>
#include <stdlib.h>

typedef struct VariationEdge_ {
	ClimbNode c;
	ClimbNode v;
} VariationEdge_;

struct ClimbGraph_ {
	ClimbNode *climbs;
	size_t climbslen;

	VariationEdge_ *variations;
	size_t variationslen;
};

ClimbGraph ClimbGraph_new()
{
	ClimbGraph ret;

	if (NULL == (ret = malloc(sizeof(struct ClimbGraph_)))) {
		return NULL;
	} else {
		ret->climbs = NULL;
		ret->climbslen = 0;
		ret->variations = NULL;
		ret->variationslen = 0;
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

	if (NULL != graph->variations) {
		free(graph->variations);
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

void ClimbGraph_add_variation(ClimbGraph g, const ClimbNode c, const ClimbNode v)
{
	if (g == NULL || c == NULL || v == NULL) {
		errno = EINVAL;
		return;
	}

	if (!ClimbGraph_has_climb(g, c) || !ClimbGraph_has_climb(g, v)) {
		errno = EINVAL;
		return;
	}

	if (NULL == (g->variations = realloc(g->variations, sizeof(VariationEdge_) * (g->variationslen + 1)))) {
		return;
	}

	VariationEdge_ edge = { c, v };

	g->variations[g->variationslen] = edge;
	g->variationslen = g->variationslen + 1;
	errno = 0;
}

void ClimbGraph_remove_variation(ClimbGraph g, const ClimbNode c, const ClimbNode v)
{
	if (g == NULL || c == NULL || v == NULL) {
		errno = EINVAL;
		return;
	}

	int index = -1;

	for (int i = 0; i < g->variationslen; i++) {
		if (g->variations[i].c == c && g->variations[i].v == v) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		return;
	}

	for (int i = index; i < g->variationslen - 1; i++) {
		g->variations[i] = g->variations[i + 1];
	}

	if (NULL == (g->variations = realloc(g->variations, sizeof(ClimbNode) * (g->variationslen - 1)))) {
		return;
	}

	g->variationslen = g->variationslen - 1;
}

int ClimbGraph_has_variation(const ClimbGraph g, const ClimbNode c, const ClimbNode v)
{
	if (g == NULL || c == NULL || v == NULL) {
		errno = EINVAL;
		return 0;
	}

	for (int i = 0; i < g->variationslen; i++) {
		if (g->variations[i].c == c && g->variations[i].v == v) {
			return 1;
		}
	}

	return 0;
}
