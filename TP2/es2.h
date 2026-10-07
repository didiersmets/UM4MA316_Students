#ifndef ES2_H
#define ES2_H

#include "es1.h"

// reads a 2D mesh from an INRIA .mesh file (Dimension 2 or 3, z ignored).
// m must not be initialized: the arrays are allocated here.
// returns 0 on success, 1 on error
int read_mesh2D(Mesh2D *m, const char *filename);


#endif
