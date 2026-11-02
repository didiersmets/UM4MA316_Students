#include <stdlib.h>

struct Vertex {
    double x, y, z; // Coordinates of the vertex in 2D space
    int ref;
};

struct Triangle {
    int iA;
    int iB;
    int iC;
    int ref;
};

struct Mesh{
    int nv; // Number of vertices in the mesh
    struct Vertex *vert; // Array of vertices that are to be found or loaded
    int nt; // Number of triangles in the mesh. 
    struct Triangle *tri; // Array of triangles that are to be found or loaded
};

int edge_pos_in_tri(int v1, int v2, struct Triangle t);

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m);

int *build_adjacency_table1(const struct Mesh *m);