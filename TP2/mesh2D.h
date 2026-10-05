#define MESH2D_H

struct Vertex {
    double x ;
    double y ;
};

struct Triangle {
    int idx[3] ;
};

struct Mesh2D {
    int nv;
    struct Vertex *vert;
    int nt;
    struct Triangle *tri;
}

int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity);
void dispose_mesh2D(struct Mesh2D *m);
double area_mesh2D(struct Mesh2D *m);


