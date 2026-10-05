#include <stdio.h>

typedef struct Vertex{
    double x;
    double y;
}Vertex;

typedef struct Triangle{
    int idx[3];
}Triangle;

typedef struct Mesh2D{
    int nv;
    Vertex* vtx;
    int vtx_capacity;
    int nt;
    Triangle* tri;
    int tri_capacity;
}Mesh2D;

int initialize_mesh2D(Mesh2D* m, int vtx_capacity, int tri_capacity){
    Vertex* vtx = malloc(vtx_capacity*sizeof(Vertex));
    Triangle* tri = malloc(tri_capacity*sizeof(Triangle));

    if(vtx==NULL || tri==NULL){
        printf("Error allocating memory!\n");
        return -1;
    }

    m->nv = 0;
    m->vtx = vtx;
    m->vtx_capacity = vtx_capacity;
    m->nt = 0;
    m->tri = tri;
    m->tri_capacity = tri_capacity;

    return 0;
}

void dispose_mesh2D(Mesh2D* m){
    free(m->vtx);
    free(m->tri);
    free(m);
}

double area_mesh2D(Mesh2D* m){

    Vertex* vtx = m->vtx;
    double tot_area = 0;

    for(int i=0;i<m->tri_capacity;i++){

        int idx[3] = m->tri[i].idx;

        double xa = vtx[idx[0]].x;
        double ya = vtx[idx[0]].y;

        double xb = vtx[idx[1]].x;
        double yb = vtx[idx[1]].y;

        double xc = vtx[idx[2]].x;
        double yc = vtx[idx[2]].y;

        double area = 1/2*((xb-xa)*(yc-ya)-(xc-xa)*(yb-ya));
        tot_area += area;
    }

    return tot_area;
}

int main(int argc, char* argv[]){

    return 0;
}