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

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity) {
    m = malloc(sizeof(struct Mesh2D));
    m->nv = vtx_capacity;
    m->nt = tri_capacity;

    return 0;
}

void dispose_mesh2D(struct Mesh2D* m) {
    // TODO: free memory from each Triangle
    free(m);
}

double dist_euclidian(struct Vertex *v1, struct Vertex *v2) {
    return sqrt(POW2(v1->x - v2->x) + POW2(v1->y - v2->y))
}

double area_mesh2D(struct Mesh2D* m) {
    struct Triangle *tri = NULL;
    double area = 0;
    int vect_prod = 0;
    for (size_t i = 0 ; i < nt ; i++) {
	tri = tri[i];
	vect_prod = vert[tri.v3].y * vert[tri.v2].x - vert[tri.v3].x * vert[tri.v2].y;
	vect_prod /= abs(vect_prod);
	area += vect_prod * dist_euclidian(vert[tri.v1], vert[tri.v3]) * dist_euclidian(vert[tri.v1], vert[tri.v2]) / 2;
    }
    return area;
}
