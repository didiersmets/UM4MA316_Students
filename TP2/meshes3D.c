#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex{
    double x;
    double y;
    double z;
}Vertex;

typedef struct Triangle{
    int idx[3];
}Triangle;

typedef struct Mesh3D{
    int nv;
    Vertex* vtx;
    int vtx_capacity;
    int nt;
    Triangle* tri;
    int tri_capacity;
}Mesh3D;

int initialize_Mesh3D(Mesh3D* m, int vtx_capacity, int tri_capacity){
    Vertex* vtx = malloc(vtx_capacity*sizeof(Vertex));
    Triangle* tri = malloc(tri_capacity*sizeof(Triangle));

    if(vtx==NULL || tri==NULL){
        fprintf(stderr, "Error allocating memory!\n");
        free(vtx);
        free(tri);
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

void dispose_Mesh3D(Mesh3D* m){
    free(m->vtx);
    free(m->tri);
    m->vtx = NULL;
    m->tri = NULL;
    m->nv = 0;
    m->nt = 0;
    m->tri_capacity = 0;
    m->vtx_capacity = 0;
}

double volume_mesh3D(Mesh3D* m){

    Vertex* vtx = m->vtx;
    double vol = 0;

    for(int i=0;i<m->nt;i++){

        Vertex a = vtx[m->tri[i].idx[0]];
        Vertex b = vtx[m->tri[i].idx[1]];
        Vertex c = vtx[m->tri[i].idx[2]];

        /* B x C */
        double cx = b.y*c.z - b.z*c.y;
        double cy = b.z*c.x - b.x*c.z;
        double cz = b.x*c.y - b.y*c.x;

        /* A . (B x C) */
        vol += a.x*cx + a.y*cy + a.z*cz;
    }

    return vol/6.0;
}

int read_Mesh3D(struct Mesh3D* m, const char* filename){

    FILE *fp = fopen(filename, "r");
    if(fp==NULL){
        fprintf(stderr, "Error reading the file!\n");
        return -1;
    }

    char line[256];
    double x,y,z;
    int v[3];
    int n;

    while(fgets(line, 256, fp)){

        if(sscanf(line, " Vertices %d", &n)==1){

            if(n < 0 || n > m->vtx_capacity){
                fprintf(stderr, "Error: too many vertices (%d > %d)\n", n, m->vtx_capacity);
                goto fail;
            }

            for(int i=0;i<n;i++){
            
                if(fgets(line, 256, fp)==NULL) goto fail;
                
                if(sscanf(line, "%lf %lf %lf", &x, &y, &z)!=3) goto fail;

                m->vtx[i].x = x;
                m->vtx[i].y = y;
                m->vtx[i].z = z;
            }

            m->nv = n;

        }else if(sscanf(line, " Triangles %d", &n)==1){

            if(n < 0 || n > m->tri_capacity){
                fprintf(stderr, "Error: too many triangles (%d > %d)\n", n, m->tri_capacity);
                goto fail;
            }

            for(int j=0;j<n;j++){
                if(fgets(line, 256, fp)==NULL) goto fail;

                if(sscanf(line, "%d %d %d", &v[0], &v[1], &v[2])!=3) goto fail;

                for(int k=0; k<3;k++){
                    if(v[k]<1) goto fail;
                    m->tri[j].idx[k] = v[k]-1;
                }
            }

            m->nt = n;

        } 
    }

    for(int j=0;j<m->nt;j++){
        for(int k=0;k<3;k++){
            if(m->tri[j].idx[k] >= m->nv) goto fail;
        }
    }

    fclose(fp);
    return 0;

    fail:
    fprintf(stderr, "Malformed mesh file %s\n", filename);
    fclose(fp);
    return -1;
}

int Mesh3D_to_gnuplot(struct Mesh3D* m, const char* filename){

    FILE* fp = fopen(filename, "w");
    if(fp == NULL){
        fprintf(stderr, "Cannot open %s\n", filename);
        return -1;
    }

    for(int j = 0; j < m->nt; j++){
        for(int k = 0; k < 4; k++){
            Vertex v = m->vtx[m->tri[j].idx[k % 3]];
            fprintf(fp, "%.17g %.17g %.17g\n", v.x, v.y, v.z);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}

int write_Mesh3D(struct Mesh3D* m, const char* filename){

    FILE* fp = fopen(filename, "w");
    if(fp==NULL){
        fprintf(stderr, "Cannot open %s\n", filename);
        return -1;
    }

    fprintf(fp, "MeshVersionFormatted 2\nDimension 2\nVertices %d\n", m->nv);

    for(int i=0;i<m->nv;i++){
        Vertex v = m->vtx[i];
        fprintf(fp, "%.17g %.17g %.17g0\n", v.x, v.y, v.z);
    }

    fprintf(fp, "Triangles %d\n", m->nt);

    for(int j=0;j<m->nt;j++){
        Triangle t = m->tri[j];

        fprintf(fp, "%d %d %d 0\n", t.idx[0]+1,t.idx[1]+1,t.idx[2]+1);
    }

    fprintf(fp, "End\n");

    fclose(fp);
    return 0;
}

int main(int argc, char* argv[]){

    Mesh3D m;

    if(initialize_Mesh3D(&m,10000,20000) != 0){
        return 1;
    }
    
   if(read_Mesh3D(&m, "mesh2-tp2.mesh") != 0){
        dispose_Mesh3D(&m);
        return 1;
    }

    printf("Volume of the Mesh: %.17g\n", volume_mesh3D(&m));

    Mesh3D_to_gnuplot(&m, "mesh.dat");

    if(write_Mesh3D(&m, "output.mesh") != 0){
        dispose_Mesh3D(&m);
        return 1;
    }

    dispose_Mesh3D(&m);
    return 0;
}