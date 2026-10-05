#include <stdlib.h>


typedef struct Vertex{
    double x;
    double y;
}Vertex;

typedef struct Triangle{
    int v1;
    int v2;
    int v3;
}Triangle;

typedef struct Mesh2D{
    int nv; //no of vertices in the mesh
    struct Vertex *vert; //array of vertices
    int nt; //no of triangles in the mesh
    struct Triangle *tri; //array of triangles

}Mesh2D;


int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity); //should allocate memory
void dispose_mesh2D(struct Mesh2D* m); //shall release allocated memory
double area_mesh2D(struct Mesh2D* m); //computes the signed area of a mesh

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Error: Missing file argument.\n");
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    int nv = atoi(argv[1]);

    Mesh2D mesh;
    initialize_mesh2D(&mesh, nv, 3 * nv);
    
    return 0;
}


int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){

    m->nv = 0;
    m->nt = 0;

    Vertex *vertices = malloc(vtx_capacity * sizeof(Vertex));
    if(vertices == NULL){
        printf("Vertex memory allocation failed.\n");
        return 1;
    }
    struct Triangle *triangles = malloc(tri_capacity *sizeof(Vertex));
        if(vertices == NULL){
        printf("Triangle memory allocation failed.\n");
        return 1;
    }

    m->vert = vertices;
    m->tri = triangles;

    
    
}
void dispose_mesh2D(struct Mesh2D* m){

    free(m->tri);
    free(m->vert);
    free(m);

}   


double area_mesh2D(struct Mesh2D* m){

}