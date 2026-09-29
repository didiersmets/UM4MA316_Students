#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"

void initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
    m->vtx_capacity = vtx_capacity;
    m->tri_capacity = tri_capacity;
    m->nv = 0;
    m->nt = 0;
    m->vert = malloc(sizeof(struct Vertex)*m->vtx_capacity);
    m->tri = malloc(sizeof(struct Triangle)*m->tri_capacity);
}

void reserve_vtx_mesh2D(struct Mesh2D* m, int vtx){
    if (m->vtx_capacity < vtx) {
        m->vert = realloc(m->vert, vtx*sizeof(struct Vertex));
        m->vtx_capacity = vtx;
    }
}

void reserve_tri_mesh2D(struct Mesh2D* m, int tri){
    if (m->tri_capacity < tri) {
        m->tri = realloc(m->tri, tri*sizeof(struct Triangle));
        m->tri_capacity = tri;
    }
}

void dispose_mesh2D(struct Mesh2D* m){
    free(m->vert);
    free(m->tri);
}

double area_mesh2D(struct Mesh2D* m){
    double sum = 0;
    for (int i = 0; i < m->nt; i++){
        struct Vertex A = m->vert[m->tri[i].nA];
        struct Vertex B = m->vert[m->tri[i].nB];
        struct Vertex C = m->vert[m->tri[i].nC];


        double v1x = B.x - A.x;
        double v1y = B.y - A.y;
        double v2x = C.x - A.x;
        double v2y = C.y - A.y;

        double det = v1x*v2y - v2x*v1y;
        
        sum += (1.0/2.0)*det;
    }

    return sum;
}

int read_mesh2D(struct Mesh2D* m, const char* filename){
    FILE* f = fopen(filename, "r");
    if (f == NULL){
        printf("error opening file\n");
        return 1;
    }
    
    while (fscanf(f,"Vertices %d", &(m->nv)) != 1){}
    
    reserve_vtx_mesh2D(m, m->nv);
    
    int vcount = 0;
    double x;
    double y;
    double z;
    int i;
   
    while(fscanf(f, "%lf %lf %lf %d", &x, &y, &z, &i)){
        struct Vertex newv;
        newv.x= x;
        newv.y= y;
        m->vert[vcount] = newv;
        vcount++;
    }

    fscanf(f,"Triangles %d", &(m->nt));
    reserve_tri_mesh2D(m, m->nt);
    
    int tcount = 0;
    int a;
    int b;
    int c;    
   
    while(fscanf(f, "%d %d %d %d", &a, &b, &c, &i)){
        struct Triangle newt;
        newt.nA= a-1;
        newt.nB= b-1;
        newt.nC= c-1;
        m->tri[tcount] = newt;
        tcount++;       
    }

    fclose(f);
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename){
    FILE *file = fopen("mesh.txt", "w");
    if (file == NULL) {
        printf("error opening file\n");
        return 1;
    }

    //print vertexs
    while(int i = m->nv; i > 0; i--){
        fprintf();
    }    

    //separation
    fprintf("\n");

    //print triangles
    while(int i = m->nt; i > 0; i--){
        fprintf();
    }
    
    fclose(file);


}


int main (int argc, char* argv[]){
    return 0;
}


