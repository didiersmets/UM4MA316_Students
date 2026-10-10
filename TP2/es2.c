#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "es2.h"

// reads the next keyword of the file, skipping blank lines.
// returns 1 if a word was read, 0 at end of file
static int read_keyword(FILE *f, char *word) {
    return fscanf(f, " %63s", word) == 1;
}

int read_mesh2D(Mesh2D *m, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error opening the file %s\n", filename);
        return 1;
    }

    char keyword[64];
    int dim = 0;
    int nv = -1;
    int nt = -1;
    m->vtx = NULL;
    m->tri = NULL;

    while (read_keyword(f, keyword)) {
        if (strcmp(keyword, "MeshVersionFormatted") == 0) {
            int version;
            if (fscanf(f, "%d", &version) != 1)
                goto error;
        } else if (strcmp(keyword, "Dimension") == 0) {
            if (fscanf(f, "%d", &dim) != 1 || (dim != 2 && dim != 3)) {
                printf("Unsupported dimension in %s\n", filename);
                goto error;
            }
        } else if (strcmp(keyword, "Vertices") == 0) {
            if (dim == 0 || fscanf(f, "%d", &nv) != 1 || nv < 0)
                goto error;
            m->vtx = malloc(nv * sizeof(Vertex));
            if (m->vtx == NULL)
                goto error;
            for (int i = 0; i < nv; i++) {
                double z;
                int ref;
                int ok = dim == 3 ? fscanf(f, "%lf %lf %lf %d", &m->vtx[i].x,
                                           &m->vtx[i].y, &z, &ref) == 4
                                  : fscanf(f, "%lf %lf %d", &m->vtx[i].x,
                                           &m->vtx[i].y, &ref) == 3;
                if (!ok)
                    goto error;
            }
        } else if (strcmp(keyword, "Triangles") == 0) {
            if (fscanf(f, "%d", &nt) != 1 || nt < 0)
                goto error;
            m->tri = malloc(nt * sizeof(Triangle));
            if (m->tri == NULL)
                goto error;
            for (int i = 0; i < nt; i++) {
                int a, b, c, ref;
                if (fscanf(f, "%d %d %d %d", &a, &b, &c, &ref) != 4)
                    goto error;
                // .mesh indices start at 1, ours at 0
                m->tri[i].a = a - 1;
                m->tri[i].b = b - 1;
                m->tri[i].c = c - 1;
            }
        } else if (strcmp(keyword, "End") == 0) {
            break;
        } else {
            printf("Unsupported section '%s' in %s\n", keyword, filename);
            goto error;
        }
    }

    if (nv < 0 || nt < 0) {
        printf("Missing Vertices or Triangles in %s\n", filename);
        goto error;
    }
    for (int i = 0; i < nt; i++) {
        Triangle t = m->tri[i];
        if (t.a < 0 || t.a >= nv || t.b < 0 || t.b >= nv || t.c < 0 || t.c >= nv) {
            printf("Triangle %d has an invalid vertex index\n", i + 1);
            goto error;
        }
    }

    m->nv = nv;
    m->vtx_capacity = nv;
    m->nt = nt;
    m->tri_capacity = nt;
    fclose(f);
    return 0;

error:
    printf("Error reading %s\n", filename);
    free(m->vtx);
    free(m->tri);
    m->vtx = NULL;
    m->tri = NULL;
    m->nv = m->nt = m->vtx_capacity = m->tri_capacity = 0;
    fclose(f);
    return 1;
}

int mesh2D_to_gnuplot(Mesh2D *m, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening the file %s\n", filename);
        return 1;
    }

    for (int i = 0; i < m->nt; i++) {
        int idx[4] = {m->tri[i].a, m->tri[i].b, m->tri[i].c, m->tri[i].a};
        for (int j = 0; j < 4; j++) {
            fprintf(f, "%.17g %.17g\n", m->vtx[idx[j]].x, m->vtx[idx[j]].y);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

int write_mesh2D(Mesh2D *m, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening the file %s\n", filename);
        return 1;
    }

    fprintf(f, "MeshVersionFormatted 2\n");
    fprintf(f, "Dimension 2\n");

    fprintf(f, "Vertices %d\n", m->nv);
    for (int i = 0; i < m->nv; i++) {
        fprintf(f, "%.17g %.17g 0\n", m->vtx[i].x, m->vtx[i].y);
    }

    fprintf(f, "Triangles %d\n", m->nt);
    for (int i = 0; i < m->nt; i++) {
        fprintf(f, "%d %d %d 0\n", m->tri[i].a + 1, m->tri[i].b + 1,
                m->tri[i].c + 1);
    }

    fprintf(f, "End\n");

    fclose(f);
    return 0;
}
