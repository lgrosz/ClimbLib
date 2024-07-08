#ifndef _CLIMBLIB_GRAPH_H
#define _CLIMBLIB_GRAPH_H

#include "climb.h"

typedef struct ClimbGraph_ ClimbGraph;

ClimbGraph *ClimbGraph_new();
void ClimbGraph_free(ClimbGraph *);
void ClimbGraph_add_climb(ClimbGraph *, Climb *);
void ClimbGraph_remove_climb(ClimbGraph *, Climb *);
int ClimbGraph_has_climb(const ClimbGraph *, const Climb *);
void ClimbGraph_climbs(const ClimbGraph *, const Climb **, size_t *);

// Climb variations
void ClimbGraph_add_variation(ClimbGraph *, const Climb *, const Climb *);
void ClimbGraph_remove_variation(ClimbGraph *, const Climb *, const Climb *);
int ClimbGraph_has_variation(const ClimbGraph *, const Climb *, const Climb *);
void ClimbGraph_variations(const ClimbGraph *, const Climb *, const Climb **, size_t *);

// Climb link-ups
void ClimbGraph_add_linkup(ClimbGraph *, const Climb *, const Climb **, size_t);
void ClimbGraph_remove_linkup(ClimbGraph *, const Climb *);
int ClimbGraph_is_linkup(ClimbGraph *, const Climb *);
void ClimbGraph_linkup(ClimbGraph *, const Climb *, const Climb **, size_t *);
int ClimbGraph_is_of_linkup(ClimbGraph *, const Climb *);
void ClimbGraph_of_linkup(ClimbGraph *, const Climb *, const Climb **, size_t *);

#endif
