#include <stdio.h>
#include "mesh3D.h"

int initialize_mesh3D(struct Mesh3D*, int vtx_capacity, int tri_capacity){

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


double volume_mesh3D(struct Mesh3D* m) {

    double sum = 0.0;
    double volume = 0.0;

    for (int tri = 0; tri < m->ntri; tri++) {
 
        struct Vertex a = m->vert[m->tri[tri].idx[0]];
        struct Vertex b = m->vert[m->tri[tri].idx[1]];
        struct Vertex c = m->vert[m->tri[tri].idx[2]];

        double x = (b.y - a.y) * (c.z - a.z) - (b.z - a.z) * (c.y - a.y);
        double y = (b.z - a.z) * (c.x - a.x) - (b.x - a.x) * (c.z - a.z);
        double z = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

        double barx = (a.x + b.x + c.x) / 3.0;
        double bary = (a.y + b.y + c.y) / 3.0;
        double barz = (a.z + b.z + c.z) / 3.0;

        sum += x * barx + y * bary + z * barz;
    
    }

    volume = (1.0/6.0) * sum;
    return volume;
}




