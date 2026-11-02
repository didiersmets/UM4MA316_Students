#include <stdlib.h>
#include <assert.h>
#include "mesh2D.h"

int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity){
    assert(m != NULL);

    m -> nv = 0;
    m -> nt = 0;

    m -> vert = malloc(vtx_capacity * sizeof(struct Vertex));
    m -> tri = malloc(tri_capacity * sizeof(struct Triangle));

    if (m -> vert == NULL || m -> tri == NULL){
        dispose_mesh2D(m);
        return -1;
    }
    return 0;

}


void dispose_mesh2D(struct Mesh2D* m) {
    if (m == NULL) { 
        return;
    }

    free(m -> vert);
    free(m -> tri);

    m -> vert = NULL;
    m -> tri = NULL;

    m -> nv = 0;
    m -> nt = 0;

}


double area_mesh2D(struct Mesh2D* m) {
    assert(m != NULL);

    double sum = 0.0;

    for (int tri = 0; tri < m->nt; tri++) {
 
        struct Vertex a = m->vert[m->tri[tri].idx[0]];
        struct Vertex b = m->vert[m->tri[tri].idx[1]];
        struct Vertex c = m->vert[m->tri[tri].idx[2]];


        sum += (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    
    }

    double area = 0.5 * sum;
    return area;
}

int read_mesh2D(struct Mesh2D *m, const char *filename);



