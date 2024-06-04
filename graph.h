#ifndef _CLIMBLIB_GRAPH_H
#define _CLIMBLIB_GRAPH_H

#include "node.h"

typedef struct ClimbGraph_* ClimbGraph;

ClimbGraph ClimbGraph_new();
void ClimbGraph_free(ClimbGraph);

#endif
