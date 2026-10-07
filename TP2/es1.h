#ifndef ES1_H
#define ES1_H

typedef struct Vertex {
    double x;
    double y;
} Vertex;

// indexed triangle: a, b, c are positions in the vertex array (0-based)
typedef struct Triangle {
    int a;
    int b;
    int c;
} Triangle;

typedef struct Mesh2D {
    int nv;
    Vertex *vtx;
    int vtx_capacity;
    int nt;
    Triangle *tri;
    int tri_capacity;
} Mesh2D;

// returns 1 if an allocation fails, 0 otherwise
int initialize_mesh2D(Mesh2D *m, int vtx_capacity, int tri_capacity);

// releases the arrays (not the Mesh2D itself)
void dispose_mesh2D(Mesh2D *m);

// signed area: positive if triangles are oriented counter-clockwise
double area_mesh2D(Mesh2D *m);

#endif
