#ifndef _CLIMBLIB_GRAPH_H
#define _CLIMBLIB_GRAPH_H

/**
 * @file graph.h
 * @brief Header prototyping ClimbGraph_* methods
 */

#include "node.h"

/**
 * @class ClimbGraph
 * @brief An referential type for a graph of climbs
 *
 * An opaque, referential, type that details climbs in a graph relationship.
 */
typedef struct ClimbGraph_* ClimbGraph;

/**
 * @brief Creates a new @ref ClimbGraph
 * @memberof ClimbGraph
 *
 * @return A new @ref ClimbGraph
 */
ClimbGraph ClimbGraph_new();

/**
 * @brief Frees @p graph
 * @memberof ClimbGraph
 *
 * @param graph The @ref ClimbGraph to free
 */
void ClimbGraph_free(ClimbGraph);

/**
 * @brief Adds an @p node to the @p graph.
 * @memberof ClimbGraph
 *
 * @param graph The @ref ClimbGraph which to add @p node
 * @param node The @ref ClimbNode which to add to @p graph
 */
void ClimbGraph_add_climb(ClimbGraph, const ClimbNode);

/**
 * @brief Removes @p node from @p graph
 * @memberof ClimbGraph
 *
 * @param graph The @ref ClimbGraph which to remove @p node
 * @param node The @ref ClimbNode to remove from @p graph
 */
void ClimbGraph_remove_climb(ClimbGraph, const ClimbNode);

/**
 * @brief Checks whether @p graph contains @p node
 * @memberof ClimbGraph
 *
 * @param graph The @ref ClimbGraph to check
 * @param node The @ref ClimbNode to check for
 * @return `1` if @p graph contains @p node, `0` otherwise
 */
int ClimbGraph_has_climb(const ClimbGraph, const ClimbNode);

/**
 * @brief All the @ref ClimbNode ["(ClimbNode)"]s contained in @p graph
 * @memberof ClimbGraph
 *
 * @param graph @ref ClimbGraph to read from
 * @param size Address to load with the size of the returned array
 * @return An array of size @p size
 */
ClimbNode *ClimbGraph_climbs(const ClimbGraph, size_t *);

// Climb variations
void ClimbGraph_add_variation(ClimbGraph, const ClimbNode, const ClimbNode);
void ClimbGraph_remove_variation(ClimbGraph, const ClimbNode, const ClimbNode);
int ClimbGraph_has_variation(const ClimbGraph, const ClimbNode, const ClimbNode);
void ClimbGraph_variations(const ClimbGraph, const ClimbNode, ClimbNode *, size_t *);

// Climb link-ups
void ClimbGraph_add_linkup(ClimbGraph, const ClimbNode, const ClimbNode *, size_t);
void ClimbGraph_remove_linkup(ClimbGraph, const ClimbNode);
int ClimbGraph_is_linkup(ClimbGraph, const ClimbNode);
void ClimbGraph_linkup(ClimbGraph, const ClimbNode, ClimbNode *, size_t *);
int ClimbGraph_is_of_linkup(ClimbGraph, const ClimbNode);
void ClimbGraph_of_linkup(ClimbGraph, const ClimbNode, ClimbNode *, size_t *);

#endif
