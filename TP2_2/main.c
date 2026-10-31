#include <stdio.h>
#include "mesh.h"


int main(void) {

    struct Mesh2D mesh;
    int vtx_capacity = 3;
    int tri_capacity = 1;

    if (initialize_mesh2D(&mesh, vtx_capacity, tri_capacity) != 0) {
	printf("Error: could not initialize mesh.\n");
    }
    printf("Success in initializing 2D mesh memory.\n");

    char *filename = "./my_2DMesh.mesh";

    if (read_mesh2D(&mesh, filename) != 0) {
	printf("Error: could not read the 2D mesh.\n");
    }

    printf("Area of the mesh in %s is %f.\n", filename, mesh_area2D(&mesh));

    dispose_mesh2D(&mesh);

    return 0;
}
