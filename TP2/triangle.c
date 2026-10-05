#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"


int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity) {
    m->nv = vtx_capacity;
    m->nt = tri_capacity;

    m->vert = malloc(vtx_capacity * sizeof(struct Vertex));
    m->tri  = malloc(tri_capacity * sizeof(struct Triangle));
    return 0;
}

void dispose_mesh2D(struct Mesh2D* m) {
    // TODO: free memory from each Triangle
    free(m);
}

double dist_euclidian(struct Vertex *v1, struct Vertex *v2) {
    return sqrt(POW2(v1->x - v2->x) + POW2(v1->y - v2->y));
}

double area_mesh2D(struct Mesh2D* m) {
    struct Triangle *tri = NULL;
    tri = m->tri;
    double area = 0;
    struct Vertex *vert;
    vert = m->vert;
    double vect_prod = 0;
    for (size_t i = 0 ; i < m->nt ; i++) {

	tri = &tri[i];
	printf("%d\n", tri->v3);
	vect_prod = vert[tri->v3].y * vert[tri->v2].x - vert[tri->v3].x * vert[tri->v2].y;
	vect_prod /= abs(vect_prod);
	area += vect_prod * dist_euclidian(&vert[tri->v1], &vert[tri->v3]) * dist_euclidian(&vert[tri->v1], &vert[tri->v2]) / 2;
    }
    return area;
}
