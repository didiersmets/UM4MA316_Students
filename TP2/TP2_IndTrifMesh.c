#include <stdlib.h>
#include <stdio.h>

struct Vertex{
	double x;
	double y;
};

// important concept : indexed mesh.
struct Triangle{
	struct Vertex* trig = malloc(3*sizeof(int));	

};

struct Mesh2D{
	int nv;
	struct Vertex* vert;
	int nt;
	struct Triange* tri;
}


int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
	
	m->nv = vtx_capacity ; 
	m-> vert = malloc(vtx_capacity*sizeof(struct Vertex));
	m->nt = tri_capacity;
	m->tri = malloc(tri_capacity*sizeof(struct Triangle));
	return 0;
}


void dispose_mesh2D(struct Mesh2D* m){
	free(m->vert);
	free(m-> tri);
	free(m);

}

//On suppose que l'air totale est la somme des aires ORIENTEES des triangles.
double area_mesh2D(struct Mesh2D* m){
	double area = 0;
	for(int i = 0;i< m->tri_capacity; i++){
		double loc = 0;
		struct Vertex v1 = m->vert[m->tri[i][0]];
		struct Vertex v2 = m->vert[m->tri[i][1]];
		struct Vertex v3 = m->vert[m->tri[i][2]];
		loc = 0.5*(v1->x*(v2->y - v3->y) + v2->x*(v3->y - v1->x) + v3->x*(v1->y - v2->y)); //November the third for the exam !
		area = area + loc;

	}
	return area;
}
