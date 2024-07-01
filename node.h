#ifndef _CLIMBLIB_NODE_H_
#define _CLIMBLIB_NODE_H_

#include "climb.h"

typedef struct ClimbNode_ ClimbNode;

ClimbNode *ClimbNode_new(Climb *);
void ClimbNode_free(ClimbNode *);
Climb *ClimbNode_climb(const ClimbNode *);

#endif
