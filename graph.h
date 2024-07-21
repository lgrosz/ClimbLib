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

#endif
