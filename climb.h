#ifndef _CLIMBLIB_CLIMB_H_
#define _CLIMBLIB_CLIMB_H_

typedef struct Climb_* Climb;

Climb Climb_new();
void Climb_free(Climb);

void Climb_set_name(Climb, const char *);
const char *Climb_name(const Climb);

void Climb_set_description(Climb, const char *);
const char *Climb_description(const Climb);

void Climb_set_brief(Climb, const char *);
const char *Climb_brief(const Climb);

#endif
