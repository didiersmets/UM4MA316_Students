#include <stdlib.h>
#include <stdio.h>

#include "include/meshes.h"

int main()
{
    Mesh2D *m = (Mesh2D *)malloc(sizeof(Mesh2D));
    if (m == NULL)
    {
        return EXIT_FAILURE;
    }

    double area;

    read_mesh2D(m, "mesh2-tp2.mesh");

    mesh2D_to_gnuplot(m, "mesh_gnu.dat");

    write_mesh2D(m,"MyMesh.mesh");
    
    area = area_mesh2D(m);

    printf("The area of the mesh is %lf\n", area);

    dispose_mesh2D(m);

    return EXIT_SUCCESS;
}