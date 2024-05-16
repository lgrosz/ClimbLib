#ifndef _CLIMBLIB_CLIMB_H_
#define _CLIMBLIB_CLIMB_H_

typedef struct Climb_* Climb;

Climb Climb_new();
void Climb_free(Climb);

void Climb_set_name(Climb, const char *);
const char *Climb_name(const Climb);

#endif
