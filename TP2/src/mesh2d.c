#include <stdlib.h>


struct Vertex {
    double x;
    double y;
};


struct Triangle {
    int v[3];
};


struct Mesh2D {
    int nv;
    struct Vertex *vert;

    int nt;
    struct Triangle *tri;
};

int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity)
{
    if(m == NULL || vtx_capacity<0 || tri_capacity<0){
        return 0;
    }
    m->nv=0;
    m->nt=0;
    m->vert=NULL;
    m->tri=NULL;

    if (vtx_capacity > 0) {
        m->vert = malloc(vtx_capacity * sizeof(struct Vertex));

        if (m->vert == NULL) {
            return 0;
        }
    } 
    
    if (tri_capacity > 0) {
        m->tri = malloc(tri_capacity * sizeof(struct Triangle));

        if (m->tri == NULL) {
            free(m->vert);
            m->vert = NULL;
            return 0;
        }
    }

    m->nv=vtx_capacity;
    m->nt=tri_capacity;
   
    return 1;
}



void dispose_mesh2D(struct Mesh2D *m)
{
    if (m == NULL) {
        return;
    }

    free(m->vert);
    free(m->tri);

    m->vert = NULL;
    m->tri = NULL;

    m->nv = 0;
    m->nt = 0;
}

double area_mesh2D(struct Mesh2D *m)
{
    if (m == NULL){
        return 0.0;
    }

    double area = 0.0;

    for (int i=0; i<m->nt; i++){

        struct Vertex A = m->vert[m->tri[i].v[0]];
        struct Vertex B = m->vert[m->tri[i].v[1]];
        struct Vertex C = m->vert[m->tri[i].v[2]];

        area += 0.5 * ((B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y));
    }

    return area;
}

