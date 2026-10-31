#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"


int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity) {

    m->vert = malloc(vtx_capacity * sizeof(struct Vertex));
    m->tri = malloc(tri_capacity * sizeof(struct Triangle));

    m->nv = vtx_capacity;
    m->nt = tri_capacity;

    return 0;
}

void dispose_mesh2D(struct Mesh2D *m) {
    free(m->vert);
    free(m->tri);
}

double triangle_area(struct Triangle *tri, struct Vertex *vert) {
    struct Vertex vect1, vect2;
    vect1.x = vert[tri->v2].x - vert[tri->v1].x;
    vect1.y = vert[tri->v2].y - vert[tri->v1].y;
    vect2.x = vert[tri->v3].x - vert[tri->v1].x;
    vect2.y = vert[tri->v3].y - vert[tri->v1].y;

    double area = vect1.x * vect2.y - vect2.x * vect1.y;
    return area;
}

double mesh_area2D(struct Mesh2D *m) {
    double area = 0;
    for (size_t i = 0 ; i < m->nt ; i++) {
	area += triangle_area(&m->tri[i], m->vert);
    }
    
    return area/2;

}

int read_mesh2D(struct Mesh2D *m, const char *filename) {
    FILE *f = fopen(filename, "r");
    char buffer[64]; 

    while(fscanf(f, "%s", buffer)==1) {
	if (strcmp(buffer, "Dimension") == 0) {
	    int dim;
	    fscanf(f, "%d", &dim);
	    if (dim != 2) {
		printf("Error: Mesh dimension in file is %d.\n", dim);
		return 1;
	    }
	}
	else if (strcmp(buffer, "Vertices") == 0) {
	    int nv;
	    fscanf(f, "%d", &nv);
	    if (nv != m->nv) {
		printf("Error: the number of vertices in the mesh file (%d) does not match the number of vertices from the mesh struct (%d).\n", nv, m->nv);
	    }
	    for (size_t i = 0 ; i < nv ; i++) {
		int garbage_val;
		fscanf(f, "%lf %lf %d", &m->vert[i].x, &m->vert[i].y, &garbage_val);
	    }
	}
	else if (strcmp(buffer, "Triangles") == 0) {
	    int nt;
	    fscanf(f, "%d", &nt);
	    if (nt != m->nt) {
		printf("Error: the number of triangles in the mesh file does not match the number of triangles from the mesh struct.\n");
	    }
	    for (size_t i = 0 ; i < nt ; i++) {
		int garbage_val;
		fscanf(f, "%ld %ld %ld %d", &m->tri[i].v1, &m->tri[i].v2, &m->tri[i].v3, &garbage_val);
	    }
	}
    }
    fclose(f);

    return 0;
}
