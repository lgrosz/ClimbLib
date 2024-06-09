#ifndef _CLIMBLIB_GRAPH_H
#define _CLIMBLIB_GRAPH_H

#include "node.h"

typedef struct ClimbGraph_* ClimbGraph;

ClimbGraph ClimbGraph_new();
void ClimbGraph_free(ClimbGraph);
void ClimbGraph_add_climb(ClimbGraph, const ClimbNode);
void ClimbGraph_remove_climb(ClimbGraph, const ClimbNode);
int ClimbGraph_has_climb(const ClimbGraph, const ClimbNode);

#endif
