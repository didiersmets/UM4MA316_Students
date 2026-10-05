#include <math.h>
#include <stdlib.h>


#define POW2(x) ((x)*(x))

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

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity);


void dispose_mesh2D(struct Mesh2D* m);

double dist_euclidian(struct Vertex *v1, struct Vertex *v2);

double area_mesh2D(struct Mesh2D* m);
