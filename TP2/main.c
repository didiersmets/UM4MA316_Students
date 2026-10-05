#include <stdlib.h>
#include <stdio.h>


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
    int vtx_capacity;
    int nt; //no of triangles in the mesh
    struct Triangle *tri; //array of triangles
    int tri_capacity;

}Mesh2D;


int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity); //should allocate memory
void dispose_mesh2D(struct Mesh2D* m); //shall release allocated memory
double area_triangle(Vertex* vertices,int v1, int v2, int v3);// computes the area of a triangle given 3 verices
double area_mesh2D(struct Mesh2D* m); //computes the signed area of a mesh

int read_mesh2D(struct Mesh2D* m, const char* filename);

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

    m->vtx_capacity = vtx_capacity;
    m->vert = vertices;

    m->tri = triangles;
    m->tri_capacity = tri_capacity;

    
    return 0;
}
void dispose_mesh2D(struct Mesh2D* m){

    free(m->tri);
    free(m->vert);
    //free(m);

}   

double area_triangle(Vertex * vertices, int v1, int v2, int v3){
    double area = 1/2 * (vertices[v1].x * (vertices[v2].y - vertices[v3].y)
                        + vertices[v2].x * (vertices[v3].y - vertices[v1].y)
                        + vertices[v3].x * (vertices[v1].y - vertices[v2].y));
    return area;
}


double area_mesh2D(struct Mesh2D* m){

    double total_area = 0;

    for(int i = 0; i < m->nt; i++){
        total_area += area_triangle(m->vert, m->tri[i].v1, m->tri[i].v2, m->tri[i].v3);
    }

    return total_area;
}

int read_mesh2D(struct Mesh2D* m, const char* filename){
    FILE *fp;
    fp = fopen(filename,"r");

    char line[256];
    int mesh_version;
    int dimention;
    int vertices;
    int triangles;

    while(fgets(line, 256, fp)){

        if (sscanf(line, "MeshVersionFormatted %d", &mesh_version) == 1){
            printf("Found Mesh Version: %d\n", mesh_version);
            continue;
        }
        if (sscanf(line, "Dimension %d", &dimention) == 1){
            printf("Found Dimension: %d\n", dimention);
            continue;
        }
        if (sscanf(line, "Vertices %d", &vertices) == 1){
            printf("Found Vertices Count: %d\n", vertices);
            int x;
            int y;
            int x; //ignored for mesh2D
            for(int i = 0; i < vertices; i++){
                fgets(line, 256, fp);
                if(sscanf(line, "%d %d %d", &x, &y, &x) == 1){
                    //insert vertices where they belong
                    continue;
                }
            }
            continue;
        }
        if (sscanf(line, "Triangles %d", &triangles) == 1){
            //parse data for n triangles
            int v1;
            int v2;
            int v3;
            int v4; //ignored for mesh2D
            for(int i = 0; i < triangles; i++){
                fgets(line, 256, fp);
                if(sscanf(line, "%d %d %d", &v1, &v2, &v3, &v4) == 1){
                    //insert triangles where they belong
                    continue;
                }
            }
        }

    }

    fclose(fp);
}