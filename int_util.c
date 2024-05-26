#include "int_util.h"

int clamp(int v, int l, int u)
{
	if (v < l) {
		return l;
	}

	if (v > u) {
		return u;
	}

	return v;
}
