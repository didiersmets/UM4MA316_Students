#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Vertex {
    double x;
    double y;
};

struct Triangle {
    size_t v1;
    size_t v2;
    size_t v3;
};

struct Mesh2D {
    int nv;
    struct Vertex *vert;
    int nt;
    struct Triangle *tri;
};

int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity); 

void dispose_mesh2D(struct Mesh2D *m);

double triangle_area(struct Triangle *tri, struct Vertex *vert);

double mesh_area2D(struct Mesh2D *m); 

int read_mesh2D(struct Mesh2D *m, const char *filename); 
