#include "mesh2D.h"

int initialize_mesh2D(struct Mesh2D*, int vtx_capacity, int tri_capacity){
    assert(m != NULL);

    m -> nv = 0;
    m -> nt = 0;

    m -> vert = malloc(vtx_capacity * sizeof(struct Vertex));
    m -> tri = malloc(vtx_capacity * sizeof(struct Triangle));

}


void dispose_mesh2D(struct Mesh2D* m) {
    if m == NULL { 
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

    for (int tri = 0; tri < m->ntri; tri++) {
 
        struct Vertex a = m->vert[m->tri[tri].idx[0]];
        struct Vertex b = m->vert[m->tri[tri].idx[1]];
        struct Vertex c = m->vert[m->tri[tri].idx[2]];


        sum += (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    
    }

    area = 0.5 * sum;
    return area;
}




