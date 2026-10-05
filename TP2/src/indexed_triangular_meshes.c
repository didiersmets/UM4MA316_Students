#include "../include/indexed_triangular_meshes.h"
#include <stdlib.h>
#include <stdio.h>



int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity) {

    m -> nv = 0;
    m -> nt = 0;

    m -> vtx = malloc(vtx_capacity * sizeof(struct Vertex));
    if(m -> vtx == NULL) {
        printf("Vertex array allocation failed\n");
        return 1;
    }
    m -> vtx_capacity = vtx_capacity;

    m -> tri = malloc(tri_capacity * sizeof(struct Triangle));
    if(m -> tri == NULL) {
        printf("Triangle array allocation failed\n");
        return 1;
    }
    m -> tri_capacity = tri_capacity;

    return 0;   
}

void dispose_mesh2D(struct Mesh2D *m) {
    free(m -> vtx);
    free(m -> tri);
}

double area_mesh2D(struct Mesh2D *m) {

    double area = 0.0;

    struct Vertex a;
    struct Vertex b;
    struct Vertex c;

    for (int i = 0; i < m->nt; i++) {
        a = m->vtx[m->tri[i].vertex[0]];
        b = m->vtx[m->tri[i].vertex[1]];
        c = m->vtx[m->tri[i].vertex[2]];

        area += 0.5 * ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
    }

    return area;
}