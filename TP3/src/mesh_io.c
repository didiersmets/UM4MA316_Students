#include "../include/mesh_io.h"

#include <stdio.h>   // Used for fopen, fclose, fgets, sscanf and printf
#include <stdlib.h>  // Used for malloc and free
#include <string.h>  // Used for strcmp

#include "../include/mesh.h"

#define LINE 128

int read_mesh_from_medit_file(struct Mesh *m, const char *filename) {
	FILE *f = fopen(filename, "r");
	char line[LINE];
	do {
		fgets(line, LINE, f);
	} while (strncmp(line, "Vertices", 8) != 0);
	fgets(line, LINE, f);
	sscanf(line, "%d", &m->nvert);
	m->vertices = malloc(m->nvert * sizeof(struct Vertex));
	for (int i = 0; i < m->nvert; ++i) {
		fgets(line, LINE, f);
		sscanf(line, "%lf %lf %lf", &m->vertices[i].x,
		       &m->vertices[i].y, &m->vertices[i].z);
	}
	do {
		fgets(line, LINE, f);
	} while (strncmp(line, "Triangles", 9) != 0);
	fgets(line, LINE, f);
	sscanf(line, "%d", &m->ntri);
	m->triangles = malloc(m->ntri * sizeof(struct Triangle));
	for (int i = 0; i < m->ntri; ++i) {
		fgets(line, LINE, f);
		sscanf(line, "%d %d %d", &m->triangles[i].v1,
		       &m->triangles[i].v2, &m->triangles[i].v3);
		// We index vertices starting from 0 while .mesh file spec
		// starts with 1, so we shift our indices by -1.
		m->triangles[i].v1 -= 1;
		m->triangles[i].v2 -= 1;
		m->triangles[i].v3 -= 1;
	}
	fclose(f);
	return 0;
}

int write_mesh_to_medit_file(const struct Mesh *m, const char *filename) {
	FILE *f;
	f = fopen(filename, "w");
	if (f == NULL) return -1;
	fprintf(f, "MeshVersionFormatted 1\n");
	fprintf(f, "Dimension 3\n\n");
	fprintf(f, "Vertices\n");
	fprintf(f, "%d\n", m->nvert);
	for (int i = 0; i < m->nvert; ++i) {
		fprintf(f, "%lf %lf %lf 0\n", m->vertices[i].x,
			m->vertices[i].y, m->vertices[i].z);
	}
	fprintf(f, "\n");
	fprintf(f, "Triangles\n");
	fprintf(f, "%d\n", m->ntri);
	for (int i = 0; i < m->ntri; ++i) {
		fprintf(f, "%d %d %d %d\n", m->triangles[i].v1 + 1,
			m->triangles[i].v2 + 1, m->triangles[i].v3 + 1, 0);
	}
	fclose(f);
	return 0;
}

static void parse_face_line(const char *line, struct Triangle *t);

int read_mesh_from_wavefront_file(struct Mesh *m, const char *filename) {
	FILE *f;
	f = fopen(filename, "r");
	if (f == NULL) return -1;
	char line[LINE];
	int nvert = 0;
	int ntri = 0;
	while (fgets(line, LINE, f) != NULL) {
		if (line[0] == 'v' && line[1] == ' ') {
			nvert += 1;
		} else if (line[0] == 'f' && line[1] == ' ') {
			ntri += 1;
		}
	}
	m->nvert = nvert;
	m->ntri = ntri;
	m->vertices = malloc(m->nvert * sizeof(struct Vertex));
	m->triangles = malloc(m->ntri * sizeof(struct Triangle));
	rewind(f);
	int idxv = 0;
	int idxt = 0;
	while (fgets(line, LINE, f) != NULL) {
		if (line[0] == 'v' && line[1] == ' ') {
			struct Vertex *v = &m->vertices[idxv];
			sscanf(line, "v %lf %lf %lf", &v->x, &v->y, &v->z);
			idxv++;
		} else if (line[0] == 'f' && line[1] == ' ') {
			struct Triangle *t = &m->triangles[idxt];
			parse_face_line(line, t);
			idxt++;
		}
	}
	fclose(f);
	return 0;
}

static void parse_face_line(const char *line, struct Triangle *t) {
	const char *pos = line + 2;
	int idx = 0;
	while (*pos == 9 || *pos == 32) ++pos;	// advance to fist field
	while (*pos >= '0') {			// read int
		idx *= 10;
		idx += (*pos - '0');
		pos++;
	}
	t->v1 = idx - 1;
	idx = 0;
	while (*pos != 9 && *pos != 32) ++pos;	// skip vt vn if present
	while (*pos == 9 || *pos == 32) ++pos;	// advance to next field
	while (*pos >= '0') {			// read int
		idx *= 10;
		idx += (*pos - '0');
		pos++;
	}
	t->v2 = idx - 1;
	idx = 0;
	while (*pos != 9 && *pos != 32) ++pos;	// skip vt vn if present
	while (*pos == 9 || *pos == 32) ++pos;	// advance to last field
	while (*pos >= '0') {			// read int
		idx *= 10;
		idx += (*pos - '0');
		pos++;
	}
	t->v3 = idx - 1;
}

int write_mesh_to_wavefront_file(const struct Mesh *m, const char *filename) {
	FILE *f;
	f = fopen(filename, "w");
	if (f == NULL) return -1;
	for (int i = 0; i < m->nvert; ++i) {
		fprintf(f, "v %.4f %.4f %.4f\n", m->vertices[i].x,
			m->vertices[i].y, m->vertices[i].z);
	}
	for (int i = 0; i < m->ntri; ++i) {
		struct Triangle *t = &m->triangles[i];
		fprintf(f, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", t->v1 + 1,
			t->v1 + 1, t->v1 + 1, t->v2 + 1, t->v2 + 1,
			t->v2 + 1,  // different clockwiseness
			t->v3 + 1, t->v3 + 1, t->v3 + 1);
	}
	fclose(f);
	return 0;
}

#undef LINE

