#ifndef _CLIMBLIB_GRAPH_H_
#define _CLIMBLIB_GRAPH_H_

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
 * @brief Gets the end-node of an edge
 */
Node *Edge_get_node(Edge *);

/**
 * @brief Gets the next edge in the edge-list
 */
Edge *Edge_get_next(Edge *);

#endif
