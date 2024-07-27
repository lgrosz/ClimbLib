#ifndef _CLIMBLIB_GRAPH_H_
#define _CLIMBLIB_GRAPH_H_

#include "formation.h"
#include "climb.h"

/**
 * @file graph.h
 *
 * @brief Header for entity-graphing
 *
 * A graph will map relationship between entities. Entities are physical things,
 * like areas, formations, and climbs.
 */

/**
 * @brief An opaque entity graph
 */
typedef struct Graph Graph;

/**
 * @brief An opaque entity node
 */
typedef struct Node Node;

/**
 * @brief Node types
 */
typedef enum {
	NodeType_UNDEFINED,
	NodeType_FORMATION,
	NodeType_CLIMB,
} NodeType ;

// TODO Edges should only make sense if the nodes are in the same graph

/**
 * @brief An opaque edge between two nodes
 */
typedef struct Edge Edge;

/**
 * @brief Creates a new graph
 */
Graph *Graph_new();

/**
 * @brief Frees a graph
 */
void Graph_free(Graph *);

/**
 * @brief Creates a new node
 */
Node *Node_new();

/**
 * @brief Creates a new formation node
 */
Node *Node_new_formation(Formation *);

/**
 * @brief Creates a new climb node
 */
Node *Node_new_climb(Climb *);

/**
 * @brief Frees a node
 */
void Node_free(Node *);

/**
 * @brief Adds node to graph
 *
 * @returns 0 on success, non-zero otherwise
 */
int Graph_add_node(Graph *, Node *);

/**
 * @brief Returns the first node of the graph
 */
Node *Graph_get_nodes(Graph *);

/**
 * @brief Returns the next node in the list
 */
Node *Node_get_next(Node *);

/**
 * @brief Adds edge to node
 */
int Node_add_edge(Node *, Node *);

/**
 * @brief Returns the edge-list of the node
 */
Edge *Node_get_edges(Node *);

/**
 * @brief Returns @ref NodeType of node
 */
NodeType Node_get_type(const Node *);

/**
 * @brief Returns node data as @ref Formation.
 */
Formation *Node_get_formation(const Node *);

/**
 * @brief Returns node data as @ref Climb.
 */
Climb *Node_get_climb(const Node *);

/**
 * @brief Gets the end-node of an edge
 */
Node *Edge_get_node(Edge *);

/**
 * @brief Gets the next edge in the edge-list
 */
Edge *Edge_get_next(Edge *);

#endif
