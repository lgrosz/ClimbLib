#include "graph.h"
#include "allocator.h"

struct Graph { };

struct Node { };

Graph *Graph_new()
{
	return climblib_malloc(sizeof(Graph));
}

void Graph_free(Graph *graph)
{
	climblib_free(graph);
}

Node *Node_new()
{
	return climblib_malloc(sizeof(Node));
}

void Node_free(Node *node)
{
	climblib_free(node);
}
