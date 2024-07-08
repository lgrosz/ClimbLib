#include "graph.h"
#include "hash_table.h"
#include <errno.h>
#include <stdlib.h>

#define CLIMBS_SIZE 100

typedef struct ClimbNode {
	Climb *c;
} ClimbNode;

typedef struct VariationEdge_ {
	const ClimbNode *c;
	const ClimbNode *v;
} VariationEdge_;

typedef struct LinkupEdge_ {
	const ClimbNode *c;
	const ClimbNode **l;
	size_t llen;
} LinkupEdge_;

struct ClimbGraph_ {
	HashTable *climbs;

	VariationEdge_ *variations;
	size_t variationslen;

	LinkupEdge_ *linkups;
	size_t linkupslen;
};

ClimbNode *ClimbNode_new(Climb *climb)
{
	ClimbNode *node;

	if (NULL == (node = malloc(sizeof(ClimbNode)))) {
		return NULL;
	}

	node->c = climb;

	return node;
}

void ClimbNode_free(ClimbNode *node)
{
	free(node);
}

ClimbGraph *ClimbGraph_new()
{
	ClimbGraph *ret;

	if (NULL == (ret = malloc(sizeof(struct ClimbGraph_)))) {
		return NULL;
	} else {
		ret->climbs = HashTable_create(CLIMBS_SIZE);
		ret->variations = NULL;
		ret->variationslen = 0;
		ret->linkups = NULL;
		ret->linkupslen = 0;
	}

	errno = 0;
	return ret;
}

void ClimbGraph_free(ClimbGraph *graph)
{
	if (graph == NULL) {
		errno = EINVAL;
		return;
	}

	if (NULL != graph->climbs) {
		size_t climbslen;
		Climb **climbs = (Climb**)HashTable_keys(graph->climbs, &climbslen);

		for (int i = 0; i < climbslen; i++) {
			ClimbNode *node = HashTable_search(graph->climbs, climbs[i]);
			ClimbNode_free(node);
		}

		free(climbs);

		HashTable_free(graph->climbs);
	}

	if (NULL != graph->variations) {
		free(graph->variations);
	}

	for (size_t i = 0; i < graph->linkupslen; i++) {
		if (NULL != graph->linkups[i].l) {
			free(graph->linkups[i].l);
		}
	}

	if (NULL != graph->linkups) {
		free(graph->linkups);
	}

	free(graph);
	errno = 0;
}

void ClimbGraph_add_climb(ClimbGraph *graph, Climb *climb) {
	if (graph == NULL || climb == NULL) {
		errno = EINVAL;
		return;
	}

	ClimbNode *node;
	if (NULL == (node = ClimbNode_new(climb))) {
		return;
	}

	HashTable_insert(graph->climbs, climb, node);

	errno = 0;
}

void ClimbGraph_remove_climb(ClimbGraph *graph, Climb *climb)
{
	if (graph == NULL || climb == NULL) {
		errno = EINVAL;
		return;
	}

	ClimbNode *node = HashTable_remove(graph->climbs, climb);

	if (node) {
		ClimbNode_free(node);
	}
}

int ClimbGraph_has_climb(const ClimbGraph *graph, const Climb *climb)
{
	if (graph == NULL || climb == NULL) {
		errno = EINVAL;
		return 0;
	}

	return NULL != HashTable_search(graph->climbs, climb);
}

void ClimbGraph_climbs(const ClimbGraph *graph, const Climb **climbs, size_t *size)
{
	if (graph == NULL || size == NULL) {
		errno = EINVAL;
		return;
	}

	Climb **keys = (Climb **)HashTable_keys(graph->climbs, size);

	if (climbs) {
		for (int i = 0; i < *size; i++) {
			climbs[i] = keys[i];
		}
	}

	free(keys);
}

void ClimbGraph_add_variation(ClimbGraph *g, const Climb *c, const Climb *v)
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

	VariationEdge_ edge = { HashTable_search(g->climbs, c), HashTable_search(g->climbs, v) };

	g->variations[g->variationslen] = edge;
	g->variationslen = g->variationslen + 1;
	errno = 0;
}

void ClimbGraph_remove_variation(ClimbGraph *g, const Climb *c, const Climb *v)
{
	if (g == NULL || c == NULL || v == NULL) {
		errno = EINVAL;
		return;
	}

	int index = -1;

	for (int i = 0; i < g->variationslen; i++) {
		if (g->variations[i].c == HashTable_search(g->climbs, c) && g->variations[i].v == HashTable_search(g->climbs, v)) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		return;
	}

	// Case where the last variation was removed
	if (g->variationslen == 1) {
		g->variationslen = 0;
		free(g->variations);
		g->variations = NULL;
		return;
	}

	for (int i = index; i < g->variationslen - 1; i++) {
		g->variations[i] = g->variations[i + 1];
	}

	if (NULL == (g->variations = realloc(g->variations, sizeof(Climb*) * (g->variationslen - 1)))) {
		return;
	}

	g->variationslen = g->variationslen - 1;
}

int ClimbGraph_has_variation(const ClimbGraph *g, const Climb *c, const Climb *v)
{
	if (g == NULL || c == NULL || v == NULL) {
		errno = EINVAL;
		return 0;
	}

	for (int i = 0; i < g->variationslen; i++) {
		if (g->variations[i].c == HashTable_search(g->climbs, c) && g->variations[i].v == HashTable_search(g->climbs, v)) {
			return 1;
		}
	}

	return 0;
}

// TODO If vs is not null, and s is not null, then only populate vs with s nodes
void ClimbGraph_variations(const ClimbGraph *g, const Climb *n, const Climb **vs, size_t *s)
{
	if (g == NULL || n == NULL || s == NULL) {
		errno = EINVAL;
		return;
	}

	int count_only = vs == NULL;
	size_t max = count_only ? g->variationslen : *s;
	*s = 0;

	for (int i = 0; i < g->variationslen; i++) {
		VariationEdge_ *var = &(g->variations[i]);

		if (var->c == HashTable_search(g->climbs, n)) {
			if (!count_only) {
				vs[*s] = var->v->c;
			}

			(*s)++;

			if (*s > max) {
				break;
			}
		}
	}

	return;
}

void ClimbGraph_add_linkup(ClimbGraph *g, const Climb *c, const Climb **l, size_t llen)
{
	if (g == NULL || c == NULL || l == NULL) {
		errno = EINVAL;
		return;
	}

	if (llen < 2) {
		errno = EINVAL;
		return;
	}

	for (size_t i = 0; i < llen; i++) {
		if (!ClimbGraph_has_climb(g, l[i])) {
			errno = EINVAL;
			return;
		}
	}

	LinkupEdge_ edge = { HashTable_search(g->climbs, c), malloc(sizeof(Climb*) * llen), llen };
	if (edge.l == NULL) {
		return;
	}

	for (int i = 0; i < llen; i++) {
		edge.l[i] = HashTable_search(g->climbs, l[i]);
	}

	if (NULL == (g->linkups = realloc(g->linkups, sizeof(LinkupEdge_) * (g->linkupslen + 1)))) {
		return;
	}

	g->linkups[g->linkupslen] = edge;
	g->linkupslen = g->linkupslen + 1;
	errno = 0;
}

void ClimbGraph_remove_linkup(ClimbGraph *g, const Climb *c)
{
	if (g == NULL || c == NULL) {
		errno = EINVAL;
		return;
	}

	int index = -1;

	for (int i = 0; i < g->linkupslen; i++) {
		if (g->linkups[i].c == HashTable_search(g->climbs, c)) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		return;
	}

	// Case where the last linkup was removed
	if (g->linkupslen == 1) {
		g->linkupslen = 0;
		free(g->linkups[0].l);
		free(g->linkups);
		g->linkups = NULL;
		return;
	}

	LinkupEdge_ linkup = g->linkups[index];
	free(linkup.l);

	for (int i = index; i < g->linkupslen - 1; i++) {
		g->linkups[i] = g->linkups[i + 1];
	}

	if (NULL == (g->linkups = realloc(g->linkups, sizeof(Climb*) * (g->linkupslen - 1)))) {
		return;
	}

	g->linkupslen = g->linkupslen - 1;
}

int ClimbGraph_is_linkup(ClimbGraph *g, const Climb *c)
{
	if (g == NULL || c == NULL) {
		errno = EINVAL;
		return 0;
	}

	errno = 0;
	for (int i = 0; i < g->linkupslen; i++) {
		if (g->linkups[i].c == HashTable_search(g->climbs, c)) {
			return 1;
		}
	}

	return 0;
}

// TODO If l is not null, and llen is not null, then only populate l with llen nodes
void ClimbGraph_linkup(ClimbGraph *g, const Climb *c, const Climb **l, size_t *llen)
{
	if (g == NULL || c == NULL) {
		errno = EINVAL;
		return;
	}

        // Expect at least one of the return references to be non-null.
        if (l == NULL && llen == NULL) {
		errno = EINVAL;
		return;
	}

        for (int i = 0; i < g->linkupslen; i++) {
		if (g->linkups[i].c == HashTable_search(g->climbs, c)) {
			LinkupEdge_ linkup = g->linkups[i];

			if (llen != NULL) {
				*llen = linkup.llen;
			}

			if (l != NULL) {
				for (int j = 0; j < g->linkups[i].llen; j++) {
					l[j] = linkup.l[j]->c;
				}
			}
		}

		return;
	}
}

int ClimbGraph_is_of_linkup(ClimbGraph *g, const Climb *c)
{
	if (g == NULL || c == NULL) {
		errno = EINVAL;
		return 0;
	}

	errno = 0;

	for (size_t i = 0; i < g->linkupslen; i++) {
		for (size_t j = 0; j < g->linkups[i].llen; j++) {
			if (HashTable_search(g->climbs, c) == g->linkups[i].l[j]) {
				return 1;
			}
		}
	}

	return 0;
}

// TODO If l is not null, and llen is not null, then only populate l with llen nodes
void ClimbGraph_of_linkup(ClimbGraph *g, const Climb *c, const Climb **l, size_t *llen)
{
	if (g == NULL || c == NULL) {
		errno = EINVAL;
		return;
	}

        // Expect at least one of the return references to be non-null.
        if (l == NULL && llen == NULL) {
		errno = EINVAL;
		return;
	}

	if (llen != NULL) {
		*llen = 0;
	}

        for (size_t i = 0; i < g->linkupslen; i++) {
		LinkupEdge_ linkup = g->linkups[i];
		for (size_t j = 0; j < linkup.llen; j++) {
			if (linkup.l[j] == HashTable_search(g->climbs, c)) {
				if (l != NULL) {
					l[*llen] = linkup.c->c;
				}

				if (llen != NULL) {
					(*llen)++;
				}

				break;
			}
		}
	}
}
