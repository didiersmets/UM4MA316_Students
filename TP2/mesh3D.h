#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



//fixed capacity but size can vary (starting w/ 0)

struct Vertex{
    double x;
    double y;
    double z;
};

struct Triangle{
    int nA;
    int nB;
    int nC;
};

struct Mesh3D{
    int nv;
    int nt;
    int vtx_capacity;
    int tri_capacity;
    struct Triangle* tri;
    struct Vertex* vert;

};


void reserve_vtx_mesh3D(struct Mesh3D* m, int vtx);

void reserve_tri_mesh3D(struct Mesh3D* m, int tri);

void initialize_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity);

void dispose_mesh3D(struct Mesh3D* m);

double volume_mesh3D(struct Mesh3D* m);

int read_mesh3D(struct Mesh3D* m, const char* filename);

int mesh3D_to_gnuplot(struct Mesh3D* m, const char* filename);


