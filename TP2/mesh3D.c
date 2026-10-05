#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mesh3D.h"

void initialize_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity){
    m->vtx_capacity = vtx_capacity;
    m->tri_capacity = tri_capacity;
    m->nv = 0;
    m->nt = 0;
    m->vert = malloc(sizeof(struct Vertex)*m->nv);
    m->tri = malloc(sizeof(struct Triangle)*m->nt);
}

void reserve_vtx_mesh3D(struct Mesh3D* m, int vtx){
    if (m->vtx_capacity < vtx) {
        m->vert = realloc(m->vert, vtx*sizeof(struct Vertex));
        m->vtx_capacity = vtx;
    }
}

void reserve_tri_mesh3D(struct Mesh3D* m, int tri){
    if (m->tri_capacity < tri) {
        m->tri = realloc(m->tri, tri*sizeof(struct Triangle));
        m->tri_capacity = tri;
    }
}

void dispose_mesh3D(struct Mesh3D* m){
    free(m->vert);
    free(m->tri);
}

// div(X) = 3 so left integral equal to 3V
// so V = 1/3 * ∫X*n dS, which, as said in pdf: for an affine vector field : 
// flux = triangle area * scalar product of the normal vector and the vector field at the barycentre


double volume_mesh3D(struct Mesh3D* m){
    double sum = 0;
    for (int i = 0; i < m->nt; i++){
        struct Vertex A = m->vert[m->tri[i].nA];
        struct Vertex B = m->vert[m->tri[i].nB];
        struct Vertex C = m->vert[m->tri[i].nC];
        
        // two vectors on the triangle
        double v1x = B.x - A.x;
        double v1y = B.y - A.y;
        double v1z = B.z - A.z;
        double v2x = C.x - A.x;
        double v2y = C.y - A.y;
        double v2z = C.z - A.z;

        // normal vector N = v1 x v2
        double nx = v1y*v2z - v1z*v2y;
        double ny = v1z*v2x - v1x*v2z;
        double nz = v1x*v2y - v1y*v2x;

        // norm of N
        double norm = sqrt(nx*nx + ny*ny + nz*nz);

        // area triangle ||N|| / 2
        double area = norm / 2.0;

        // n = N / ||N||
        double normalx = nx / norm;
        double normaly = ny / norm;
        double normalz = nz / norm;

        // triangle barycentre
        double baryx = (A.x + B.x + C.x)/3.0;
        double baryy = (A.y + B.y + C.y)/3.0;
        double baryz = (A.z + B.z + C.z)/3.0;

        // X(x,y,z) = (x,y,z) and X(G) = G
        // scalar product n · X(G)
        double scalar = normalx * baryx + normaly * baryy + normalz * baryz;

        // flux = triangle area * < normal | bary >
        double flux = area * scalar;

        // div(X) = 3, so V = total_flux / 3
        sum += flux / 3.0;

    }

    return sum;
}


int read_mesh3D(struct Mesh3D* m, const char* filename){
    FILE* f = fopen(filename, "r");
    if (f == NULL){
        printf("error opening file\n");
        return 1;
    }
    
    char word[256];

    while (fscanf(f, "%255s", word) == 1 && strcmp(word, "Vertices") != 0) {}

    fscanf(f, "%d", &(m->nv));

    reserve_vtx_mesh3D(m, m->nv);
    
    int vcount;
    double x;
    double y;
    double z;
    int i;
   

    for (vcount = 0; vcount < m->nv; vcount++) {
        fscanf(f, "%lf %lf %lf %d", &x, &y, &z, &i);

        m->vert[vcount].x = x;
        m->vert[vcount].y = y;
        m->vert[vcount].z = z;

    }

    fscanf(f, " Triangles %d", &m->nt);
    reserve_tri_mesh3D(m, m->nt);
    
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

int mesh3D_to_gnuplot(struct Mesh3D* m, const char* filename){
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("error opening file\n");
        return 1;
    }

    int i ;
    for(i = 0; i < m->nt; i++){
        fprintf(file, "%lf %lf %lf \n",m->vert[m->tri[i].nA].x, m->vert[m->tri[i].nA].y, m->vert[m->tri[i].nA].z);
        fprintf(file, "%lf %lf %lf \n",m->vert[m->tri[i].nB].x, m->vert[m->tri[i].nB].y, m->vert[m->tri[i].nB].z);
        fprintf(file, "%lf %lf %lf \n",m->vert[m->tri[i].nC].x, m->vert[m->tri[i].nC].y, m->vert[m->tri[i].nC].z);
        fprintf(file, "%lf %lf %lf \n",m->vert[m->tri[i].nA].x, m->vert[m->tri[i].nA].y, m->vert[m->tri[i].nA].z);
        fprintf(file, "\n");    
    }
    
    fclose(file);
    return 0;
}

int main (int argc, char* argv[]){
    struct Mesh3D m;
    initialize_mesh3D(&m, 0, 0);
    read_mesh3D(&m, argv[1]);
    mesh3D_to_gnuplot(&m, "mesh3D.txt");
    dispose_mesh3D(&m);

    return 0;
}



