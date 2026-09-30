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
    int vtx_cap = 100;
    int tri_cap = 100;

    if (initialize_mesh2D(m, vtx_cap, tri_cap) == EXIT_FAILURE)
    {
        printf("Failed to allocate memory!\n");
        return EXIT_FAILURE;
    }

    m->vert[0] = (Vertex){.x = 0, .y = 0};
    m->vert[1] = (Vertex){.x = 3, .y = 0};
    m->vert[2] = (Vertex){.x = 0, .y = 3};
    m->vert[3] = (Vertex){.x = 3, .y = 3};
    m->vert[4] = (Vertex){.x = 3, .y = 6};
    m->nv = 5;

    m->tri[0] = (Triangle){.na = 0, .nb = 1, .nc = 2};
    m->tri[1] = (Triangle){.na = 1, .nb = 3, .nc = 2};
    m->tri[2] = (Triangle){.na = 3, .nb = 4, .nc = 2};
    m->nt = 3;

    area = area_mesh2D(m);

    printf("The area of the mesh is %lf\n", area);

    dispose_mesh2D(m);


    return EXIT_SUCCESS;
}