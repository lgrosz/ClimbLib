#include "graph.h"
#include "hash_table.h"
#include <errno.h>
#include <stdlib.h>

#define CLIMBS_SIZE 100
#define FORMATIONS_SIZE 100

/**
 * @brief Removes @p ptr from @p arr with reallocation
 */
static void remove_ptr_from_arr(void ***arr, size_t *arrlen, void *ptr)
{
	int index = -1;

	for (int i = 0; i < *arrlen; i++) {
		if ((*arr)[i] == ptr) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		return;
	}

	// Case where the last variation was removed
	if (*arrlen == 1) {
		*arrlen = 0;
		free(*arr);
		*arr = NULL;
		return;
	}

	for (int i = index; i < *arrlen; i++) {
		(*arr)[i] = (*arr)[i + 1];
	}

	if (NULL == ((*arr) = realloc(*arr, sizeof(void*) * (*arrlen - 1)))) {
		return;
	}

	(*arrlen)--;
}

typedef struct ClimbNode {
	Climb *c;

        struct ClimbNode *var; //! Indicates node @ref c is a variation
	struct ClimbNode **vars; //! Variations of @ref c
	size_t varslen;

	struct ClimbNode **links; //! Links @ref c is made up from
	size_t linkslen;

	struct ClimbNode **link_of; //! Is a link of these climbs
	size_t link_oflen;
} ClimbNode;

typedef struct FormationNode {
	Formation *f;

	struct FormationNode *super_formation;
	struct FormationNode **sub_formations;
	size_t sub_formations_len;
} FormationNode;

struct ClimbGraph {
	HashTable *climbs;
	HashTable *formations;
};

ClimbNode *ClimbNode_new(Climb *climb)
{
	ClimbNode *node;

	if (NULL == (node = malloc(sizeof(ClimbNode)))) {
		return NULL;
	}

	node->c = climb;
	node->var = NULL;
	node->vars = NULL;
	node->varslen = 0;
	node->links = NULL;
	node->linkslen = 0;
	node->link_of = NULL;
	node->link_oflen = 0;

	return node;
}

void ClimbNode_free(ClimbNode *node)
{
	if(node->vars)	free(node->vars);
	if(node->links)	free(node->links);
	if(node->link_of)	free(node->link_of);
	free(node);
}

FormationNode *FormationNode_new(Formation *formation)
{
	FormationNode *node;

	if (NULL == (node = malloc(sizeof(FormationNode)))) {
		return NULL;
	}

	node->f = formation;
	node->super_formation = NULL;
	node->sub_formations = NULL;
	node->sub_formations_len = 0;

	return node;
}

void FormationNode_free(FormationNode *node)
{
	if (node) {
		if (node->sub_formations)	free(node->sub_formations);
		free(node);
	}
}

ClimbGraph *ClimbGraph_new()
{
	ClimbGraph *ret;

	if (NULL == (ret = malloc(sizeof(ClimbGraph)))) {
		return NULL;
	} else {
		ret->climbs = HashTable_create(CLIMBS_SIZE);
		ret->formations = HashTable_create(FORMATIONS_SIZE);
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

	if (NULL != graph->formations) {
		size_t formationslen;
		Formation **formations = (Formation**)HashTable_keys(graph->formations, &formationslen);

		for (int i = 0; i < formationslen; i++) {
			FormationNode *node = HashTable_search(graph->formations, formations[i]);
			FormationNode_free(node);
		}

		free(formations);

		HashTable_free(graph->formations);
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

	ClimbNode *cn = HashTable_search(g->climbs, c);

	if (!cn) {
		errno = EINVAL;
		return;
	}

	ClimbNode *vn = HashTable_search(g->climbs, v);

	if (!vn) {
		errno = EINVAL;
		return;
	}

	if (NULL == (cn->vars = realloc(cn->vars, sizeof(ClimbNode*) * (cn->varslen + 1)))) {
		return;
	} else {
		cn->vars[cn->varslen++] = vn;
		vn->var = cn;
	}

	errno = 0;
}

void ClimbGraph_remove_variation(ClimbGraph *g, const Climb *c, const Climb *v)
{
	if (g == NULL || c == NULL || v == NULL) {
		errno = EINVAL;
		return;
	}

	ClimbNode *cn = HashTable_search(g->climbs, c);

	if (!cn) {
		errno = EINVAL;
		return;
	}

	ClimbNode *vn = HashTable_search(g->climbs, v);

	if (!vn) {
		errno = EINVAL;
		return;
	}

	if (vn->var == cn) {
		vn->var = NULL;
	}

	int index = -1;

	for (int i = 0; i < cn->varslen; i++) {
		if (cn->vars[i] == vn) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		return;
	}

	// Case where the last variation was removed
	if (cn->varslen == 1) {
		cn->varslen = 0;
		free(cn->vars);
		cn->vars = NULL;
		return;
	}

	for (int i = index; i < cn->varslen; i++) {
		cn->vars[i] = cn->vars[i + 1];
	}

	if (NULL == (cn->vars = realloc(cn->vars, sizeof(ClimbNode*) * (cn->varslen - 1)))) {
		return;
	}

	cn->varslen--;
}

int ClimbGraph_has_variation(const ClimbGraph *g, const Climb *c, const Climb *v)
{
	if (g == NULL || c == NULL || v == NULL) {
		errno = EINVAL;
		return 0;
	}

	ClimbNode *cn = HashTable_search(g->climbs, c);

	if (!cn) {
		errno = EINVAL;
		return 0;
	}

	ClimbNode *vn = HashTable_search(g->climbs, v);

	if (!vn) {
		errno = EINVAL;
		return 0;
	}

	return vn->var == cn;
}

// TODO If vs is not null, and s is not null, then only populate vs with s nodes
void ClimbGraph_variations(const ClimbGraph *g, const Climb *climb, const Climb **vs, size_t *s)
{
	if (g == NULL || climb == NULL || s == NULL) {
		errno = EINVAL;
		return;
	}

	ClimbNode *node = HashTable_search(g->climbs, climb);

	if (node == NULL) {
		errno = EINVAL;
		return;
	}

	int count_only = vs == NULL;
	size_t max = count_only ? node->varslen : *s;
	*s = 0;

	for (int i = 0; i < node->varslen; i++) {
		if (!count_only) {
			vs[*s] = node->vars[i]->c;
		}

		(*s)++;

		if (*s > max) {
			break;
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

	ClimbNode *cn = HashTable_search(g->climbs, c);

	if (!cn) {
		errno = EINVAL;
		return;
	}

	if (NULL == (cn->links = malloc(sizeof(ClimbNode*) * llen))) {
		return;
	}

	cn->linkslen = llen;

	for (int i = 0; i < llen; i++) {
		ClimbNode *link_node;

		if (NULL != (link_node = HashTable_search(g->climbs, l[i]))) {
			cn->links[i] = link_node;

			link_node->link_of = realloc(link_node->link_of, sizeof(ClimbNode*) * (link_node->link_oflen + 1));
			link_node->link_of[link_node->link_oflen] = cn;
			link_node->link_oflen++;
		}
	}

	errno = 0;
}

void ClimbGraph_remove_linkup(ClimbGraph *g, const Climb *c)
{
	if (g == NULL || c == NULL) {
		errno = EINVAL;
		return;
	}

	ClimbNode *cn = HashTable_search(g->climbs, c);

	if (!cn) {
		errno = EINVAL;
		return;
	}

	if (cn->links) {
		for (int i = 0; i < cn->linkslen; i++) {
			ClimbNode *link = cn->links[i];
			remove_ptr_from_arr((void ***)&link->link_of, &link->link_oflen, cn);
		}

		free(cn->links);
	}

	cn->links = NULL;
	cn->linkslen = 0;
	errno = 0;
}

int ClimbGraph_is_linkup(ClimbGraph *g, const Climb *c)
{
	if (g == NULL || c == NULL) {
		errno = EINVAL;
		return 0;
	}

	ClimbNode *cn = HashTable_search(g->climbs, c);

	if (!cn) {
		errno = EINVAL;
		return 0;
	}

	errno = 0;

	return cn->links != NULL;
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

	ClimbNode *cn = HashTable_search(g->climbs, c);

	if (!cn) {
		errno = EINVAL;
		return;
	}

	if (llen != NULL) {
		*llen = cn->linkslen;
	}

	if (l != NULL) {
		for (int i = 0; i < cn->linkslen; i++) {
			l[i] = cn->links[i]->c;
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

	ClimbNode *cn = HashTable_search(g->climbs, c);

	if (!cn) {
		errno = EINVAL;
		return 0;
	}

	return cn->link_oflen > 0;
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

	ClimbNode *cn = HashTable_search(g->climbs, c);

	if (!cn) {
		errno = EINVAL;
		return;
	}

	if (llen != NULL) {
		*llen = cn->link_oflen;
	}

	if (l != NULL) {
		for (int i = 0; i < cn->link_oflen; i++) {
			l[i] = cn->link_of[i]->c;
		}
	}
}

void ClimbGraph_add_formation(ClimbGraph *graph, Formation *formation)
{
	if (graph == NULL || formation == NULL) {
		errno = EINVAL;
		return;
	}

	FormationNode *node;
	if (NULL == (node = FormationNode_new(formation))) {
		return;
	}

	HashTable_insert(graph->formations, formation, node);

	errno = 0;
}

void ClimbGraph_remove_formation(ClimbGraph *graph, Formation *formation)
{
	if (graph == NULL || formation == NULL) {
		errno = EINVAL;
		return;
	}

	FormationNode *node = HashTable_remove(graph->formations, formation);

	if (node) {
		FormationNode_free(node);
	}
}

int ClimbGraph_has_formation(ClimbGraph *graph, Formation *formation)
{
	if (graph == NULL || formation == NULL) {
		errno = EINVAL;
		return 0;
	}

	return NULL != HashTable_search(graph->formations, formation);
}

void ClimbGraph_add_subformation(ClimbGraph *graph, const Formation *formation, const Formation *subformation)
{
	if (graph == NULL || formation == NULL || subformation == NULL) {
		errno = EINVAL;
		return;
	}

	FormationNode *fn = HashTable_search(graph->formations, formation);

	if (!fn) {
		errno = EINVAL;
		return;
	}

	FormationNode *sfn = HashTable_search(graph->formations, subformation);

	if (!sfn) {
		errno = EINVAL;
		return;
	}

	sfn->super_formation = fn;

	if (NULL == (fn->sub_formations = realloc(fn->sub_formations, sizeof(FormationNode*) * (fn->sub_formations_len + 1)))) {
		return;
	}

	fn->sub_formations[fn->sub_formations_len] = sfn;
	fn->sub_formations_len++;
}

void ClimbGraph_remove_subformation(ClimbGraph *graph, const Formation *formation, const Formation *subformation)
{
	if (graph == NULL || formation == NULL || subformation == NULL) {
		errno = EINVAL;
		return;
	}

	FormationNode *fn = HashTable_search(graph->formations, formation);

	if (!fn) {
		errno = EINVAL;
		return;
	}

	FormationNode *sfn = HashTable_search(graph->formations, subformation);

	if (!sfn) {
		errno = EINVAL;
		return;
	}

	sfn->super_formation = NULL;

	remove_ptr_from_arr((void*)&fn->sub_formations, &fn->sub_formations_len, sfn);
}

int ClimbGraph_has_subformation(const ClimbGraph *graph, const Formation *formation, const Formation *subformation)
{
	if (graph == NULL || formation == NULL || subformation == NULL) {
		errno = EINVAL;
		return 0;
	}

	FormationNode *fn = HashTable_search(graph->formations, formation);

	if (!fn) {
		errno = EINVAL;
		return 0;
	}

	FormationNode *sfn = HashTable_search(graph->formations, subformation);

	if (!sfn) {
		errno = EINVAL;
		return 0;
	}

	return sfn->super_formation == fn;
}
