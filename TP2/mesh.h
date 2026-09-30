#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//fixed capacity but size can vary (starting w/ 0)

struct Vertex{
    double x;
    double y;
};


struct Triangle{
    int nA;
    int nB;
    int nC;
};

struct Mesh2D{
    int nv;
    int nt;
    int vtx_capacity;
    int tri_capacity;
    struct Triangle* tri;
    struct Vertex* vert;

};

void initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity);

void reserve_vtx_mesh2D(struct Mesh2D* m, int vtx);

void reserve_tri_mesh2D(struct Mesh2D* m, int tri);

void dispose_mesh2D(struct Mesh2D* m);

double area_mesh2D(struct Mesh2D* m);

int read_mesh2D(struct Mesh2D* m, const char* filename);

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename);


