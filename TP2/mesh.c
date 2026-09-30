#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    
    char word[256];

    while (fscanf(f, "%255s", word) == 1 && strcmp(word, "Vertices") != 0) {}

    fscanf(f, "%d", &(m->nv));

    reserve_vtx_mesh2D(m, m->nv);
    
    int vcount;
    double x;
    double y;
    double z;
    int i;
   

    for (vcount = 0; vcount < m->nv; vcount++) {
        fscanf(f, "%lf %lf %lf %d", &x, &y, &z, &i);

        m->vert[vcount].x = x;
        m->vert[vcount].y = y;
    }

    fscanf(f, " Triangles %d", &m->nt);
    reserve_tri_mesh2D(m, m->nt);
    
    int tcount;
    int a;
    int b;
    int c;    
   
    for (tcount = 0; tcount < m->nt; tcount++) {
        fscanf(f, "%d %d %d %d", &a, &b, &c, &i);

        m->tri[tcount].nA = a - 1;
        m->tri[tcount].nB = b - 1;
        m->tri[tcount].nC = c - 1;
    }

    fclose(f);
    return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename){
    FILE *file = fopen("mesh.txt", "w");
    if (file == NULL) {
        printf("error opening file\n");
        return 1;
    }

    int i ;
    for(i = 0; i < m->nt; i++){
        fprintf(file, "%lf %lf \n",m->vert[m->tri[i].nA].x, m->vert[m->tri[i].nA].y);
        fprintf(file, "%lf %lf \n",m->vert[m->tri[i].nB].x, m->vert[m->tri[i].nB].y);
        fprintf(file, "%lf %lf \n",m->vert[m->tri[i].nC].x, m->vert[m->tri[i].nC].y);
        fprintf(file, "%lf %lf \n",m->vert[m->tri[i].nA].x, m->vert[m->tri[i].nA].y);
        fprintf(file, "\n");    
    }
    
    fclose(file);
    return 0;
}

int main (int argc, char* argv[]){
    struct Mesh2D m;
    initialize_mesh2D(&m, 0, 0);
    read_mesh2D(&m, argv[1]);
    mesh2D_to_gnuplot(&m, "mesh.txt");
    dispose_mesh2D(&m);

    return 0;
}


