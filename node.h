#ifndef _CLIMBLIB_NODE_H_
#define _CLIMBLIB_NODE_H_

/**
 * @file node.h
 * @brief Header prototyping nodes
 */

#include "climb.h"

/**
 * @class ClimbNode
 * @brief A node for @ref Climb [Climb]s
 */
typedef struct ClimbNode_* ClimbNode;

ClimbNode ClimbNode_new(Climb);
void ClimbNode_free(ClimbNode);
Climb ClimbNode_climb(const ClimbNode);

#endif
