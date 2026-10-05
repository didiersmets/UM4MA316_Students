#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../include/meshes.h"

int initialize_mesh2D(Mesh2D *m, int vtx_capacity, int tri_capacity)
{
    m->nv = 0;
    m->nt = 0;
    m->vert = (Vertex *)malloc(vtx_capacity * sizeof(Vertex));
    m->tri = (Triangle *)malloc(tri_capacity * sizeof(Triangle));
    if (m->vert == NULL || m->tri == NULL)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void dispose_mesh2D(Mesh2D *m)
{
    if (m == NULL)
    {
        return;
    }

    free(m->vert);
    free(m->tri);
    free(m);
}

double area_mesh2D(Mesh2D *m)
{
    double areaTot = 0.0;

    if (m->vert == NULL || m->tri == NULL)
    {
        return 0.0;
    }
    for (int i = 0; i < m->nt; i++)
    {
        areaTot += tri_area(m->vert[m->tri[i].na], m->vert[m->tri[i].nb], m->vert[m->tri[i].nc]);
    }

    return areaTot;
}

double tri_area(Vertex v1, Vertex v2, Vertex v3)
{
    return 0.5 * (v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y));
}

int read_mesh2D(Mesh2D *m, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: file %s failed to open\n", filename);
        return EXIT_FAILURE;
    }
    char keyword[256];
    int nv = 0;
    int nt = 0;

    while (fscanf(file, "%255s", keyword) != EOF) // end of file
    {
        if (strcmp(keyword, "Vertices") == 0) // find the word Vertices
        {
            fscanf(file, "%d", &nv); // the immediate number after that word is the number of vertices
        }
        else if (strcmp(keyword, "Triangles") == 0) // find the word Triangles
        {
            fscanf(file, "%d", &nt); // the immediate number after that word is the number of triangles
        }
    }

    if (initialize_mesh2D(m, nv, nt) == EXIT_FAILURE) // note this initializes the mesh
    {
        printf("Failed to allocate memory for mesh\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    m->nv = nv; // set the capacyties
    m->nt = nt;

    rewind(file); // the fscanf has pointed to the end of the file so we need to go back to the beginning

    while (fscanf(file, "%255s", keyword) != EOF) // scan the file again
    {
        if (strcmp(keyword, "Vertices") == 0)
        {
            int dummy;
            fscanf(file, "%d", &dummy); // remove nv number

            for (int i = 0; i < m->nv; i++)
            {
                int bin;
                double z;
                fscanf(file, "%lf %lf %lf %d", &m->vert[i].x, &m->vert[i].y, &z, &bin); // dispose of z
            }
        }
        else if (strcmp(keyword, "Triangles") == 0)
        {
            int dummy;
            fscanf(file, "%d", &dummy); // don't need nt

            for (int i = 0; i < m->nt; i++)
            {
                int v1, v2, v3, bin;

                fscanf(file, "%d %d %d %d", &v1, &v2, &v3, &bin);

                m->tri[i].na = v1 - 1;
                m->tri[i].nb = v2 - 1;
                m->tri[i].nc = v3 - 1;
            }
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int mesh2D_to_gnuplot(Mesh2D *m, const char *filename)
{
    assert(m != NULL);

    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("failed to create or open data file");
        return EXIT_FAILURE;
    }
    for (int tri_i = 0; tri_i < m->nt; tri_i++)
    {
        Vertex va = m->vert[m->tri[tri_i].na];
        Vertex vb = m->vert[m->tri[tri_i].nb];
        Vertex vc = m->vert[m->tri[tri_i].nc];

        fprintf(f, "%lf %lf\n", va.x, va.y);
        fprintf(f, "%lf %lf\n", vb.x, vb.y);
        fprintf(f, "%lf %lf\n", vc.x, vc.y);

        fprintf(f, "%lf %lf\n\n", va.x, va.y); // necessary to close the loop
    }

    fclose(f);

    return EXIT_SUCCESS;
}

int write_mesh2D(Mesh2D *m, const char *filename)
{
    assert(m != NULL);
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("failed to create or open data file");
        return EXIT_FAILURE;
    }

    fprintf(f, "MeshVersionFormatted 2\n");
    fprintf(f, "dimension 2\n");

    fprintf(f, "Vertices %d\n", m->nv);
    for (int vtx_i=0; vtx_i < m->nv; vtx_i++)
    {

        fprintf(f, "%20.14g %25.14g\n", m->vert[vtx_i].x,m->vert[vtx_i].y);
    }

    fprintf(f, "Triangles %d\n", m->nt);
    for (int tri_i=0; tri_i < m->nt; tri_i++)
    {
        fprintf(f, "%d %d %d\n", m->tri[tri_i].na+1, m->tri[tri_i].nb+1, m->tri[tri_i].nc+1);//attention to the +1
    }

    fclose(f);

    return EXIT_SUCCESS;
}