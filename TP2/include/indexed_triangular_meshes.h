#include <stddef.h>

struct Vertex {
    double x;
    double y;
};

struct Triangle {
    int vertex[3];
};

struct Mesh2D {
    int nv;                 // number of vertices in the mesh
    struct Vertex *vtx;     // array ov Vertex
    size_t vtx_capacity;
    int nt;                 // number of triangles in the mesh
    struct Triangle *tri;   // array of Triangle
    size_t tri_capacity;
};
    
int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity);

// free mesh
void dispose_mesh2D(struct Mesh2D *m);

// calculate mesh area
double area_mesh2D(struct Mesh2D *m);