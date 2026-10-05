#include <stdlib.h>
#include <stdio.h>
#include <math.h>
struct Vertex{
    double x;
    double y;
};

struct Triangle {
    int node[3];
};

struct Mesh2D{
    int nv;
    struct Vertex *vert;
    int nt;
    struct Triangle *tri;
};

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
    m->nv=vtx_capacity;
    m->vert=(struct Vertex *)malloc(sizeof(struct Vertex)*vtx_capacity);
    m->nt=tri_capacity;
    m->tri=(struct Triangle *)malloc(sizeof(struct Triangle)*tri_capacity);
    return 0;
}
void dispose_mesh2D(struct Mesh2D* m){
    free(m->vert);
    free(m->tri);
}

double area_mesh2D(struct Mesh2D* m){
    double area = 0.0;

    for (int i = 0; i < m->nt; i++)
    {
        struct Vertex A = m->vert[m->tri[i].node[0]];
        struct Vertex B = m->vert[m->tri[i].node[1]];
        struct Vertex C = m->vert[m->tri[i].node[2]];

        area += 0.5 * fabs(
            (B.x - A.x) * (C.y - A.y)
            - (C.x - A.x) * (B.y - A.y)
        );
    }

    return area;
}
// int main(void)
// {
//     struct Mesh2D m;

//     int result = initialize_mesh2D(&m, 4, 1);

//     m.vert[0].x = 0.0;
//     m.vert[0].y = 0.0;

//     m.vert[1].x = 1.0;
//     m.vert[1].y = 0.0;

//     m.vert[2].x = 0.0;
//     m.vert[2].y = 1.0;

//     m.tri[0].node[0] = 0;
//     m.tri[0].node[1] = 1;
//     m.tri[0].node[2] = 2;

//     printf("result for area = %f\n", area_mesh2D(&m));
//     printf("nv = %d\n", m.nv);
//     printf("nt = %d\n", m.nt);

//     dispose_mesh2D(&m);

//     return 0;
// }



// cas en 3D
struct Vertex3D{
    double x;
    double y;
    double z;
};

struct Triangle3D{
    int node[3];
};

struct Mesh3D{
    int nv;
    struct Vertex3D *vert;
    int nt;
    struct Triangle3D *tri;
};

int initialize_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity){
    m->nv=vtx_capacity;
    m->vert=(struct Vertex3D *)malloc(sizeof(struct Vertex3D)*vtx_capacity);
    m->nt=tri_capacity;
    m->tri=(struct Triangle3D *)malloc(sizeof(struct Triangle3D)*tri_capacity);
    return 0;
}
void dispose_mesh3D(struct Mesh3D* m){
    free(m->vert);
    free(m->tri);
}


double volume_mesh3D(struct Mesh3D* m){
    double volume = 0.0;

    for (int i = 0; i < m->nt; i++)
    {
        struct Vertex3D A = m->vert[m->tri[i].node[0]];
        struct Vertex3D B = m->vert[m->tri[i].node[1]];
        struct Vertex3D C = m->vert[m->tri[i].node[2]];
        double area = 0.5 * fabs(A.y*B.z*C.x-A.z*B.y*C.x+A.z*B.x*C.y-A.x*B.z*C.y+A.x*B.y*C.z-A.y*B.x*C.z);
        double somme=(A.x+A.y+A.z+C.x+C.y+C.z+B.x+B.y+B.z);
        volume += fabs(area*somme/3);
    }
    return volume/3;
}


// int main(void)
// {
//     struct Mesh3D m;

//     int result = initialize_mesh3D(&m, 4, 1);

//     m.vert[0].x = 0.0;
//     m.vert[0].y = 0.0;
//     m.vert[0].z = 0.0;

//     m.vert[1].x = 1.0;
//     m.vert[1].y = 0.0;
//     m.vert[1].z = 0.0;

//     m.vert[2].x = 0.0;
//     m.vert[2].y = 1.0;
//     m.vert[2].z = 0.0;

//     m.tri[0].node[0] = 0;
//     m.tri[0].node[1] = 1;
//     m.tri[0].node[2] = 2;

//     printf("result for area = %f\n", volume_mesh3D(&m));
//     printf("nv = %d\n", m.nv);
//     printf("nt = %d\n", m.nt);

//     dispose_mesh3D(&m);

//     return 0;
// }

int read_mesh2D(struct Mesh2D* m, const char* filename){
    FILE *fp = fopen(filename, "r");
    if (!fp) return 1;
    char ligne [256];
    int j=0;
    while (fgets(ligne, sizeof(ligne), fp)) {
        int vtx_num;
        int tri_num;
        if (sscanf(ligne,"Vertices %d",&vtx_num) == 1) {
            struct Vertex *vtx=malloc(sizeof(struct Vertex)*(vtx_num));
            for(int i=0;i<vtx_num;i++){
                fgets(ligne, sizeof(ligne), fp);
                double vtx_x;
                double vtx_y;
                sscanf(ligne,"%lf %lf",&vtx_x,&vtx_y);
                vtx[i].x=vtx_x;
                vtx[i].y=vtx_y;
            }
            m->nv=vtx_num;
            m->vert=vtx;
            
        }
        if (sscanf(ligne,"Triangles %d",&tri_num) == 1) {
            struct Triangle *triv=malloc(sizeof(struct Triangle)*(tri_num));
            for(int i=0;i<tri_num;i++){
                fgets(ligne, sizeof(ligne), fp);
                int tri_0;
                int tri_1;
                int tri_2;
                sscanf(ligne,"%d %d %d",&tri_0,&tri_1,&tri_2);
                (triv[i]).node[0]=tri_0;
                (triv[i]).node[1]=tri_1;
                (triv[i]).node[2]=tri_2;
            }
            m->tri=triv;
            m->nt=tri_num;
        }
    }
    fclose(fp);
    
}

int main(void)
{
    struct Mesh2D m;
    const char *filename="../../mesh1-tp2.mesh";
    read_mesh2D(&m,filename);

    printf("result for area = %f\n", area_mesh2D(&m));
    printf("nv = %d\n", m.nv);
    printf("nt = %d\n", m.nt);

    dispose_mesh2D(&m);

    return 0;
}