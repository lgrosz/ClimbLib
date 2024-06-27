#ifndef _CLIMBLIB_GRAPH_H
#define _CLIMBLIB_GRAPH_H

#include "node.h"

typedef struct ClimbGraph_* ClimbGraph;

ClimbGraph ClimbGraph_new();
void ClimbGraph_free(ClimbGraph);
void ClimbGraph_add_climb(ClimbGraph, const ClimbNode);
void ClimbGraph_remove_climb(ClimbGraph, const ClimbNode);
int ClimbGraph_has_climb(const ClimbGraph, const ClimbNode);
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

// Formation operations
void ClimbGraph_add_formation(ClimbGraph, const FormationNode);
void ClimbGraph_remove_formation(ClimbGraph, const FormationNode);
int ClimbGraph_has_formation(ClimbGraph, const FormationNode);
FormationNode *ClimbGraph_formations(const ClimbGraph, size_t *);
void ClimbGraph_add_subformation(ClimbGraph, const FormationNode, const FormationNode);
void ClimbGraph_remove_subformation(ClimbGraph, const FormationNode, const FormationNode);
int ClimbGraph_has_subformation(ClimbGraph, const FormationNode, const FormationNode);
void ClimbGraph_formation_add_climb(ClimbGraph, const FormationNode, const ClimbNode);
void ClimbGraph_formation_remove_climb(ClimbGraph, const FormationNode, const ClimbNode);
int ClimbGraph_formation_has_climb(ClimbGraph, const FormationNode, const ClimbNode);

#endif
