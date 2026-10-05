struct Vertex {
	double x;
	double y;
	double z;
};

struct Triangle {
	int idx[3];
};

struct Mesh3D {
	int vtx_capacity;
	int nv;
	Vertex*vtx;
	int tri_capacity;
	int nt;
	Triangle*tri;
};

#include <stdio.h>
#include <stulib.h>

int initialize_mesh3D(struct Mesh3D* m,)
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

void dispose_mesh3D(struct Mesh3D* m)
{
	free(m->vtx);
	free(m->tri);

	m->nv = 0;
	m->nt = 0;
}



double volume_mesh3D(struct mesh3D* m)
{
	double volume = 0.0;

	for (int i=0; i<m->nt; i++) {

		ia = tri[i].idx[0];
		ib = tri[i].idx[1];
		ic = tri[i].idx[2];

		Vertex A = m->vtx[ia];
		Vertex B = m->vtx[ib];
		Vertex C = m->vtx[ic];

		double gx;
		double gy;
		double gz;

		gx = (A.x + B.x + C.x)/3;
		gy = (A.y + B.y + C.y)/3;
		gz = (A.z + B.z + C.z)/3;

		double nx = 0.5*((B.y - A.y)*(C.z - A.z) - (B.z - A.z)*(C.y - A.y));
		double ny = -0.5*((B.x - A.x)*(C.z - A.z) - (B.z - A.z)*(C.x - A.x));
		double nz = 0.5*((B.x - A.x)*(C.y - A.y) - (B.y - A.y)*(C.x - A.x));

		volume += gx*nx + gy*ny + gz*nz;
	}
	 return volume/6
}

