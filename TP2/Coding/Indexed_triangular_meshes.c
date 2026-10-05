#include<stdio.h>
#include<stdlib.h>

struct Vertex {
    double x;
    double y;
};

struct Vertex_3D{
    double x;
    double y;
    double z;
}


struct Triangle {
    int idx[3];
};

struct Mesh2D {
    int nv;
    int vtx_capacity;
    int tri_capacity;
    struct Vertex * vert;
    int nt;
    struct Triangle * tri; 
};

struct Mesh3D {
    int nv;
    int vtx_capacity;
    int tri_capacity;
    struct Vertex_3D * vert;
    int nt;
    struct Triangle * tri; 
};

int initialize_mesh2D(struct Mesh2D * m, int vtx_capacity, int tri_capacity){
    m -> nv = 0;
    m -> nt = 0;
    m -> vtx_capacity = vtx_capacity;
    m -> tri_capacity = tri_capacity;
    m -> vert = malloc(vtx_capacity * sizeof(struct Vertex));
    m -> tri = malloc(tri_capacity * sizeof(struct Triangle));
    return 0;
}


void dispose_mesh2D(struct Mesh2D * m){
    free(m->vert);
    free(m->tri);
    free(m);
}


double area_mesh2D(struct Mesh2D * m){
    double S = 0.0;
    for (int it = 0; it < m->nt; it++){
        struct Triangle curr_trgle = m->tri[it]; 
        struct Vertex A = m->vert[curr_trgle->idx[0]];
        struct Vertex B = m->vert[curr_trgle->idx[1]];
        struct Vertex C = m->vert[curr_trgle->idx[2]];
        double area = ((B.x - A.x)*(C.y - A.y)) - ((B.y - A.y)*(C.x - A.x));
        S += 0.5 * area;
    }
    return S;
}


double area_mesh3D(struct Mesh3D * m){
    double Volume = 0.0;
    for (int it = 0; it < m->nt; it++){
        struct Triangle curr_trgle = m->tri[it];
        struct Vertex_3D A = m->vert[curr_trgle->idx[0]];
        struct Vertex_3D B = m->vert[curr_trgle->idx[1]];
        struct Vertex_3D C = m->vert[curr_trgle->idx[2]];

        double gx = (A.x + B.x + C.x)/3;      
        double gy = (A.y + B.y + C.y)/3;
        double gz = (A.z + B.z + C.z)/3;

        double Nx = (B.y - A.y) * (C.z - A.z) - (B.z - A.z) * (C.y - A.y);
        double Ny = (B.z - A.z) * (C.x - A.x) - (B.x - A.x) * (C.z - A.z);
        double Nz = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);

        double area = 0.5 * (((B.x - A.x)*(C.y - A.y)) - ((B.y - A.y)*(C.x - A.x)));

        Volume += (gx*Nx + gy*Ny + gz*Nz)/(3*area);

        return Volume;
    
    }
}


/*2 Reading, writing(and visualizing) a mesh */


/*1) Done */

/*2) Reading and writing Function */

int read_mesh2D(struct Mesh2D*m, const char * filename){
    FILE * f = fopen(filename,"r");

    if (f  == NULL){
        return -1;
    }

    char line [2000];
    int dimension = 0;
    int nv;
    int nt;

    while(fgets(line,2000, f)) /*While the line is well read*/{

        if(sscanf(line, "Vertices %d", &nv)==1){

            if(nv > m->vtx_capacity){
                free(m->vtx);
                m->vtx  = malloc(nv*sizeof(struct Vertex));
                m->vtx_capacity = nv;
            }

            for (int i=0,i<nv;i++){
                fgets(line, 2000, f);
                sscanf(line, "%lf %lf ", &((m->vtx[i]).x) , &((m->vtx[i].y)) );
                m->nv ++;
            }


        }else if(sscanf(line, "Triangles %d", &nt)==1){

            if(nv > m->tri_capacity){
                free(m->tri);
                m->tri  = malloc(nv*sizeof(struct Triangle));
                m->tri_capacity = nt;
            }

            for (int i=0,i<nt;i++){
                fgets(line, 2000, f);
                sscanf(line, "%lf %lf %lf ", &((m->tri[i]).idx[0]) , &((m->tri[i].idx[1])), &((m->tri[i].idx[2])) );
                m->nt++;
        }

    }          
    fclose(f);
    return 0;
    
}






/*3)gnuplot*/

int Mesh2D_to_gnuplot(struct Mesh2D*m, const char* filename){
    FILE * f = fopen(filename, "w");
    
    if (f==NULL){
        return -1;
    }

    for (int i = 0; i<m->nt;i++){
        struct Vertex A = m->vtx[m->tri[i].idx[0]];
        struct Vertex B = m->vtx[m->tri[i].idx[1]];
        struct Vertex C = m->vtx[m->tri[i].idx[2]];

        fprint(f,"%lf %lf", A.x,A.y);
        fprint(f,"%lf %lf", B.x,B.y);
        fprint(f,"%lf %lf", C.x,C.y);


    }
    fclose(f);
    return 0;
}