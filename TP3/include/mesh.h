#pragma once

/* The Vertex structure, just a triple of double precision floating point 
 * numbers which correspond to the coordinates of the vertex in a given
 * reference frame.
 */
struct Vertex {
	union {
		struct {
			double x,y,z;
		};
		double coord[3];
	};
};

/* The Triangle structure, a triple of integers refering to vertex
 * indices inside a vertex table.
 */
struct Triangle {
	union {
		struct {
			int v1, v2, v3;
		};
		int idx[3];
	};
};

/* The Mesh structure : it contains the number of vertices, the number
 * of triangles, a pointer to the vertices and a pointer to the triangles. 
 */
struct Mesh {
	int nvert;
	int ntri;
	struct Vertex *vertices;
	struct Triangle *triangles;
};

void initialize_mesh(struct Mesh *m);
void dispose_mesh(struct Mesh *m);
