#include <stdlib.h>

#include "mesh.h"

void initialize_mesh(struct Mesh *m)
{
	m->nvert = 0;
	m->ntri = 0;
	m->vertices = NULL;
	m->triangles = NULL;
}

void dispose_mesh(struct Mesh *m)
{
	m->nvert = 0;
	m->ntri = 0;
	free(m->vertices);
	m->vertices = NULL;
	free(m->triangles);
	m->triangles = NULL;
}
