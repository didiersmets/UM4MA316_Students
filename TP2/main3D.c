#include <stdlib.h>
#include <stdio.h>

#include "include/meshes3D.h"

int main()
{
    // Allocate the mesh structure
    Mesh3D *m = (Mesh3D *)malloc(sizeof(Mesh3D));
    if (m == NULL)
    {
        printf("Failed to allocate Mesh3D struct!\n");
        return EXIT_FAILURE;
    }

    double surface_area;
    double volume;
    int vtx_cap = 100;
    int tri_cap = 100;

    // Initialize the mesh arrays using your API
    if (initialize_Mesh3D(m, vtx_cap, tri_cap) == EXIT_FAILURE)
    {
        printf("Failed to allocate memory for mesh arrays!\n");
        free(m);
        return EXIT_FAILURE;
    }


    m->vert[0] = (Vertex3D){.x = 0.0, .y = 0.0, .z = 0.0}; // Origin
    m->vert[1] = (Vertex3D){.x = 1.0, .y = 0.0, .z = 0.0}; // Along X axis
    m->vert[2] = (Vertex3D){.x = 0.0, .y = 1.0, .z = 0.0}; // Along Y axis
    m->vert[3] = (Vertex3D){.x = 0.0, .y = 0.0, .z = 1.0}; // Along Z axis
    m->nv = 4;

  
    m->tri[0] = (Triangle){.na = 0, .nb = 2, .nc = 1}; // Base (XY plane)
    m->tri[1] = (Triangle){.na = 0, .nb = 1, .nc = 3}; // Side (XZ plane)
    m->tri[2] = (Triangle){.na = 0, .nb = 3, .nc = 2}; // Side (YZ plane)
    m->tri[3] = (Triangle){.na = 1, .nb = 2, .nc = 3}; // Slanted face connecting the axes
    m->nt = 4;


    surface_area = Surface_Mesh3D(m);
    volume = Volume_closed_Mesh3D(m);

    printf("The surface area of the 3D mesh is %lf\n", surface_area);
    printf("The Volume of the 3D mesh is %lf\n", volume);


    // Clean up
    dispose_Mesh3D(m);


    return EXIT_SUCCESS;
}