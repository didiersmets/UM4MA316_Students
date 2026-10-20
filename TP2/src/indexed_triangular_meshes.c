#include "../include/indexed_triangular_meshes.h"
#include <stdlib.h>
#include <stdio.h>

int initialize_mesh2D(struct Mesh2D *m, size_t vtx_capacity, size_t tri_capacity) {

    m -> nv = 0;
    m -> nt = 0;

    m -> vtx = malloc(vtx_capacity * sizeof(struct Vertex));
    if(m -> vtx == NULL) {
        printf("Vertex array allocation failed\n");
        return 1;
    }
    m -> vtx_capacity = vtx_capacity;

    m -> tri = malloc(tri_capacity * sizeof(struct Triangle));
    if(m -> tri == NULL) {
        printf("Triangle array allocation failed\n");
        return 1;
    }
    m -> tri_capacity = tri_capacity;

    return 0;   
}

void dispose_mesh2D(struct Mesh2D *m) {
    free(m -> vtx);
    free(m -> tri);
    free(m);
}

double area_mesh2D(struct Mesh2D *m) {

    double area = 0.0;

    struct Vertex a;
    struct Vertex b;
    struct Vertex c;

    for (int i = 0; i < m->nt; i++) {
        a = m->vtx[m->tri[i].vertex[0]];
        b = m->vtx[m->tri[i].vertex[1]];
        c = m->vtx[m->tri[i].vertex[2]];

        area += 0.5 * ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
    }

    return area;
}

int read_mesh2D(struct Mesh2D *m, const char *filename) {

    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        printf("Error opening the file %s\n", filename);
        return 1;
    }

    int MeshFileVersion;
    fscanf(f, "MeshVersionFormatted %d", &MeshFileVersion);

    if(MeshFileVersion != 2) {
        printf("You shall restrict to the INRIA mesh format\n");
        fclose(f);
        return 1;
    }

    size_t nv;

    fscanf(f, " Dimension %*d");
    fscanf(f, " Vertices %zu", &nv);

    struct Vertex *vtx = malloc(nv * sizeof(struct Vertex));

    for(int i = 0; i < nv; i++) {
        fscanf(f, " %lf %lf %lf %*d", &vtx[i].x, &vtx[i].y, &vtx[i].z);
    }

    size_t nt;

    fscanf(f, " Triangles %zu", &nt);

    struct Triangle *tri = malloc(nt * sizeof(struct Triangle));

    for(int i = 0; i < nt; i++) {
        fscanf(f, " %d %d %d %*d", &tri[i].vertex[0], &tri[i].vertex[1], &tri[i].vertex[2]);
        tri[i].vertex[0] -= 1;
        tri[i].vertex[1] -= 1;
        tri[i].vertex[2] -= 1;
    }

    m -> nv = nv;
    m -> vtx_capacity = nv;
    m -> vtx = vtx;
    m -> nt = nt;
    m -> tri_capacity = nt;
    m -> tri = tri;

    fclose(f);
    return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D *m, const char *filename) {

    FILE *f = fopen(filename, "w");
    if(f == NULL) {
        printf("Error opening the file\n");
        return 1;
    }

    for(int i = 0; i < m->nt; i++) {
        for(int j = 0; j < 4; j++) {
            fprintf(f, "%g %g\n", m->vtx[m->tri[i].vertex[j%3]].x, m->vtx[m->tri[i].vertex[j%3]].y);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

int write_mesh2D(struct Mesh2D *m, const char *filename) {

    FILE *f = fopen(filename, "w");
    if(f == NULL) {
        printf("Error opening the file .mesh to write");
        return 1;
    }

    fprintf(f, "MeshVersionFormatted 2\n");
    fprintf(f, "Dimension 3\n");

    fprintf(f, "Vertices %zu\n", m -> nv);
    for(int i = 0; i < m -> nv; i++)  {
        fprintf(f, "\t%.17g\t%.17g\t%.17g\t0\n", m -> vtx[i].x, m -> vtx[i].y, m -> vtx[i].z);
    }

    fprintf(f, "Triangles %zu\n", m -> nt);
    for(int i = 0; i < m -> nt; i++)  {
        fprintf(f, "%d %d %d 0\n", m -> tri[i].vertex[0] + 1, m -> tri[i].vertex[1] + 1,
                                            m -> tri[i].vertex[2] + 1);
    }

    fprintf(f, "End\n");

    fclose(f);
    return 0;
}