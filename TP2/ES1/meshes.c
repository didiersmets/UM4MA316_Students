#include <stdio.h>
#include <stdlib.h>

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
    m->vtx = NULL;
    m->tri = NULL;
    m->nv = 0;
    m->nt = 0;
    m->tri_capacity = 0;
    m->vtx_capacity = 0;
}

double area_mesh2D(Mesh2D* m){

    Vertex* vtx = m->vtx;
    double tot_area = 0;

    for(int i=0;i<m->nt;i++){

        int* idx = m->tri[i].idx;

        double xa = vtx[idx[0]].x;
        double ya = vtx[idx[0]].y;

        double xb = vtx[idx[1]].x;
        double yb = vtx[idx[1]].y;

        double xc = vtx[idx[2]].x;
        double yc = vtx[idx[2]].y;

        double area = 0.5*((xb-xa)*(yc-ya)-(xc-xa)*(yb-ya));
        tot_area += area;
    }

    return tot_area;
}

int read_mesh2D(struct Mesh2D* m, const char* filename){

    FILE *fp = fopen(filename, "r");
    if(fp==NULL){
        printf("Error reading the file!\n");
        return -1;
    }

    char line[256];
    double x,y;
    int v[3];

    while(fgets(line, 256, fp)){

        if(sscanf(line, "Vertices %d", &m->nv)==1){
            for(int i=0;i<m->nv;i++){
            
                if(fgets(line, 256, fp)==NULL){
                    return -1;
                }
                
                sscanf(line, "%lf %lf %*lf %*d", &x, &y);

                m->vtx[i].x = x;
                m->vtx[i].y = y;
            }
        }else if(sscanf(line, "Triangles %d", &m->nt)==1){
            for(int j=0;j<m->nt;j++){
                if(fgets(line, 256, fp)==NULL){
                    return -1;
                }

                sscanf(line, "%d %d %d %*d", &v[0], &v[1], &v[2]);

                m->tri[j].idx[0] = v[0]-1;
                m->tri[j].idx[1] = v[1]-1;
                m->tri[j].idx[2] = v[2]-1;
            }
        } 
    }

    fclose(fp);
    return 0;
}

int main(int argc, char* argv[]){

    return 0;
}