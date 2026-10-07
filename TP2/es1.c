#include <stdio.h>
#include <stdlib.h>
#include "es1.h"

// returns 1 if malloc fails. 0 otherwise
int initialize_mesh2D(Mesh2D *m, int vtx_capacity, int tri_capacity) {
    m->nv = 0;
    m->nt = 0;

    m->vtx = malloc(vtx_capacity * sizeof(Vertex));
    if (m->vtx == NULL) {
        printf("Vertex array allocation failed\n");
        return 1;
    }
    m->vtx_capacity = vtx_capacity;

    m->tri = malloc(tri_capacity * sizeof(Triangle));
    if (m->tri == NULL) {
        printf("Triangle array allocation failed\n");
        free(m->vtx);
        m->vtx = NULL;
        m->vtx_capacity = 0;
        return 1;
    }
    m->tri_capacity = tri_capacity;

    return 0;
}

void dispose_mesh2D(Mesh2D *m) {
    free(m->vtx);
    free(m->tri);

    m->vtx = NULL;
    m->tri = NULL;

    m->nv = 0;
    m->nt = 0;
    m->vtx_capacity = 0;
    m->tri_capacity = 0;
}

double area_mesh2D(Mesh2D *m) {
    double area = 0;
    for (int i = 0; i < m->nt; i++) {
        Vertex A = m->vtx[m->tri[i].a];
        Vertex B = m->vtx[m->tri[i].b];
        Vertex C = m->vtx[m->tri[i].c];

        area += 0.5 * ((B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y));
    }

    return area;
}
