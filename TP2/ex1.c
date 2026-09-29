#include<stdio.h>
#include<stdlib.h>
struct Vertex{
	double x;
	double y;
};

struct Triangle{
	struct Vertex *V;
};

struct Mesh2D{
	int nv;
	struct Vertex *vtx;
	int vtx_capacity;
	int nt;
	struct Triangle *tri;
	int tri_capacity;
};

int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity){
	m->vtx = malloc(m->vtx_capacity*sizeof(struct Vertex));
	m->tri = malloc(m->tri_capacity*sizeof(struct Triangle));
}

void dispose_mesh2D(struct Mesh2D *m){
	free(m->vtx);
	free(m->tri);
}

double area_mesh2D(struct Mesh2D *m){
	int n = m->nt;
	double s=0;
	for(int i=0; i<n; ++i){
		struct Vertex A = m->tri[i].V[0];
		struct Vertex B = m->tri[i].V[1];
		struct Vertex C = m->tri[i].V[2];
		s += ((B.x-A.x)*(C.x-A.x)+(B.y-A.y)*(C.y-A.y));
	}
	return s / 2;
}

struct Vertex_3D{
        double x;
        double y;
	double z;
};

struct Triangle_3D{
        struct Vertex_3D *V;
};

struct Mesh3D{
        int nv;
        struct Vertex_3D *vtx;
        int vtx_capacity;
        int nt;
        struct Triangle_3D *tri;
        int tri_capacity;
};

double area_mesh3D(struct Mesh3D *m){
        int n = m->nt;
	double v=0;
        for(int i=0; i<n; ++i){
                struct Vertex A = m->tri[i].V[0];
                struct Vertex B = m->tri[i].V[1];
                struct Vertex C = m->tri[i].V[2];
                double Nx = ((B.y-A.y)*(C.z-A.z)+(B.z-A.z)*(C.y-A.y));
                double Ny = ((B.z-A.z)*(C.x-A.x)+(B.x-A.x)*(C.z-A.z));
                double Nz = ((B.x-A.x)*(C.y-A.y)+(B.y-A.y)*(C.x-A.x));
		double baryx = (A.x + B.x + C.x) / 3.;
		double baryy = (A.y + B.y + C.y) / 3.;
		double baryz = (A.z + B.z + C.z) / 3.;
		v += (baryx * Nx + baryy * Ny + baryz * Nz) / 6.; 

        }
        return v;
}



