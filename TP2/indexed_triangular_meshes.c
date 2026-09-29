struct Vertex {
	double x;
	double y;
};

struct Triangle {
	int idx[3];
};

struct Mesh2D {
	int vtx_capacity;
	int nv;
	Vertex*vtx;
	int tri_capacity;
	int nt;
	Triangle*tri;
};

#include <stdio.h>
#include <stulib.h>

int initialize_mesh2D(struct Mesh2D* m,)
{
	m->nv = 0;
	m->nt = 0;
	
	m->vtx = malloc(m->vtx_capacity*sizeof(struct Vertex));
	m->tri = malloc(m->tri_capacity*sizeof(struct Triangle));

	if (m->vtx == NULL || m->tri == NULL) {

		free(m->vtx);
		free(m->tri);
		return 0;
	}
	return 1;
}	

void dispose_mesh2D(struct Mesh2D* m)
{
	free(m->vtx);
	free(m->tri);

	m->nv = 0;
	m->nt = 0;
}



double area_mesh2D(struct mesh2D* m)
{
	double area = 0.0;

	for (int i=0; i<m->nt; i++) {

		ia = tri[i].idx[0];
		ib = tri[i].idx[1];
		ic = tri[i].idx[2];

		Vertex A = m->vtx[ia];
		Vertex B = m->vtx[ib];
		Vertex C = m->vtx[ic];

		area += 0.5*((B.x - A.x)*(C.y - A.y) - (B.y - A.y)*(C.x - A.x));
	}
	 return area;
}

