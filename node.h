#ifndef _CLIMBLIB_NODE_H_
#define _CLIMBLIB_NODE_H_

#include "climb.h"
#include "formation.h"

typedef struct ClimbNode_* ClimbNode;
typedef struct FormationNode_* FormationNode;

ClimbNode ClimbNode_new(Climb);
void ClimbNode_free(ClimbNode);
Climb ClimbNode_climb(const ClimbNode);

FormationNode FormationNode_new(Formation);
void FormationNode_free(FormationNode);
Formation FormationNode_climb(const FormationNode);

#endif
