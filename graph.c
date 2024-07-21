#include "graph.h"
#include "allocator.h"

struct Graph { };

Graph *Graph_new()
{
	return climblib_malloc(sizeof(Graph));
}

void Graph_free(Graph *graph)
{
	climblib_free(graph);
}
