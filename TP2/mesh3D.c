#include <stdio.h>
#include <stdlib.h>
#include "mesh3D.h"

void initialize_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity){
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = malloc(sizeof(struct Vertex)*m->nv);
    m->tri = malloc(sizeof(struct Triangle)*m->nt);
    return 1;
}

void dispose_mesh3D(struct Mesh3D* m){
    free(m->vert);
    free(m->tri);
}


//div(X) = 3 so left integral equal to 3V
//so V = 1/3 * ∫X*n dS, which, as said in pdf: for an affine vector field : 
// flux = triangle area * scalar product of the normal vector and the vector field at the barycentre


double volume_mesh3D(struct Mesh3D* m){
    double sum = 0;
    for (int i=0; i < m->nt; i++){
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

        //norm of N
        double norm = sqrt(nx*nx + ny*ny + nz*nz);

        //area triangle ||N|| / 2
        double area = norm / 2.0;

        //n = N / ||N||
        double normalx = nx / norm;
        double normaly = ny / norm;
        double normalz = nz / norm;

        //triangle barycentre
        double baryx = (A.x + B.x + C.x)/3.0;
        double baryy = (A.y + B.y + C.y)/3.0;
        double baryz = (A.z + B.z + C.z)/3.0;

        //X(x,y,z) = (x,y,z) and X(G) = G
        //scalar product n · X(G)
        double scalar = normalx * baryx + normaly * baryy + normalz * baryz;

        // flux = triangle area * < normal | bary >
        double flux = area * scalar;

        // div(X) = 3, so V = total_flux / 3
        sum += flux / 3.0;

    }

    return sum;
}





int main (int argc, char* argv[]){
    return 0;
}


