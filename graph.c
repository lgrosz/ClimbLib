#include "graph.h"
#include "allocator.h"

struct Graph {
	Node *head;
};

struct Node {
	Node *next;
	Edge *edges;
	NodeType type;
	union {
		Formation *formation;
		Climb *climb;
	} data;
};

struct Edge {
	Node *node;
	Edge *next;
};

Graph *Graph_new()
{
	Graph *graph;

	graph = climblib_malloc(sizeof(Graph));

	if (graph) {
		graph->head = NULL;
	}

	return graph;
}

void Graph_free(Graph *graph)
{
	climblib_free(graph);
}

Node *Node_new()
{
	return climblib_malloc(sizeof(Node));
}

Node *Node_new_formation(Formation *formation)
{
	Node *node;

	node = Node_new();
	node->type = NodeType_FORMATION;
	node->data.formation = formation;

	return node;
}

Node *Node_new_climb(Climb *climb)
{

	Node *node;

	node = Node_new();
	node->type = NodeType_CLIMB;
	node->data.climb = climb;

	return node;
}

void Node_free(Node *node)
{
	Edge *edge;

	edge = node->edges;

	while (edge != NULL) {
		Edge *fedge = edge;
		edge = fedge->next;
		climblib_free(fedge);
	}

	climblib_free(node);
}

int Graph_add_node(Graph *graph, Node *node)
{
	if (graph == NULL || node == NULL) {
		return 1;
	}

	if (graph->head) {
		Node *last = graph->head;
		while (last->next != NULL) {
			last = last->next;
		}

		last->next = node;
	} else {
		graph->head = node;
	}

	return 0;
}

Node *Graph_get_nodes(Graph *graph)
{
	if (!graph) {
		return NULL;
	}

	return graph->head;
}

Node *Node_get_next(Node *node)
{
	if (!node) {
		return NULL;
	}

	return node->next;
}

int Node_add_edge(Node *src, Node *dest)
{
	Edge *edge = climblib_malloc(sizeof(Edge));
	edge->node = dest;

	if (src->edges) {
		Edge *last = src->edges;
		while (last->next != NULL) {
			last = last->next;
		}

		last->next = edge;
	} else {
		src->edges = edge;
	}

	return 0;
}

Edge *Node_get_edges(Node *node)
{
	return node->edges;
}

NodeType Node_get_type(const Node *node)
{
	return node->type;
}

Formation *Node_get_formation(const Node *node)
{
	if (node->type == NodeType_FORMATION) {
		return node->data.formation;
	} else {
		return NULL;
	}
}

Climb *Node_get_climb(const Node *node)
{
	if (node->type == NodeType_CLIMB) {
		return node->data.climb;
	} else {
		return NULL;
	}
}

Node *Edge_get_node(Edge *edge)
{
	return edge->node;
}

Edge *Edge_get_next(Edge *edge)
{
	return edge->next;
}
