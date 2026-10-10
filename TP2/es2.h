#ifndef ES2_H
#define ES2_H

#include "es1.h"

// reads a 2D mesh from an INRIA .mesh file (Dimension 2 or 3, z ignored).
// m must not be initialized: the arrays are allocated here.
// returns 0 on success, 1 on error
int read_mesh2D(Mesh2D *m, const char *filename);

// writes one closed polygon per triangle, separated by blank lines,
// ready for gnuplot: plot "file" with lines
int mesh2D_to_gnuplot(Mesh2D *m, const char *filename);

// writes the mesh in the INRIA .mesh format (Dimension 2)
int write_mesh2D(Mesh2D *m, const char *filename);

#endif
