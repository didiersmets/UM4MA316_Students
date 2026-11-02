#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Vertex{
	double x;
	double y;
};

struct Triangle{
	int *v;
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
		struct Vertex A = m->vtx[m->tri[i].v[0]];
		struct Vertex B = m->vtx[m->tri[i].v[1]];
		struct Vertex C = m->vtx[m->tri[i].v[2]];
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
        int *v;
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
                struct Vertex_3D A = m->vtx[m->tri[i].v[0]];
                struct Vertex_3D B = m->vtx[m->tri[i].v[1]];
                struct Vertex_3D C = m->vtx[m->tri[i].v[2]];
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


int read_mesh2D(struct Mesh2D* m, const char* filename){
	FILE *f = fopen(filename, "r");
        if (f==NULL)
                return 0;

        char line[256];
        int n_ver;
        int n_tri;

        while(fgets(line, 256, f)){
                if (sscanf(line, "Vertices %d", &n_ver)== 1) {
                        // allocate memory for vertices
                        m->vtx = malloc(n_ver*sizeof(struct Vertex));
                        // read the vertices
                        for (int i = 0; i < n_vert; i++) {
                                double x;
                                double y;
                                fgets(line, 256, f);
                                sscanf("%lf %lf", &x, &y);
                                m->vtx[i].x = x;
                                m->vtx[i].y = y;

                        }
                }
                if(sscanf(line, "Triangles %d", &n_tri)==1){
                        m->tri = malloc(n_tri*sizeof(struct Triangle));
                        for (int i = 0; i<n_tri; i++) {
                                int x;
                                int y;
                                int z;
                                fgets(line, 256, f);
                                sscanf("%d %d %d", &x, &y, &z);
                                m->tri[i][0] = m->vtx[x-1];
                                m->tri[i][1] = m->vtx[y-1];
                                m->tri[i][2] = m->vtx[z-1];
                        }
                }
        }
        fclose(f);
        return 1;
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename){
        FILE *f = fopen(filename, "w");

        if (f == NULL)
                return 0;

        for (int i = 0; i < m->nt; i++){
                struct Triangle t = m->tri[i];
                for (int j = 0; j < 4; j++) {
                        struct Vertex p = m->vtx[t.v[j%3]];

                        fprintf(f, "%lf %lf\n", p.x, p.y);
                }
                fprintf(f, "\n");
        }

        return fclose(f) = 0;
}

int write_mesh2D (struct Mesh2D *m, const char* filename) {
        FILE *f = fopen(filename, "w");

        if (f == NULL)
                return 0;

        fprintf(f, "MeshVersionFormatted 2\n");
        fprintf(f, "Dimension 2\n");
        fprintf(f, "Vertices %d\n", m->nv);

        for (int i = 0; i < m->nv; i++){
                fprintf(f, "%lf %lf 0\n", m->vtx[i].x, m->vtx[i].y);
        }

        fprintf(f, "Triangles %d\n", m->nt);

        for (int i = 0, i < m-nt; i++) {
                fprintf(f, "%d %d %d 0\n", m->tri[i].v[0]+1, m->tri[i].v[1]+1, m->tri[i].v[2]+1);
        }

        fprintf(f, "End");
        fclose(f);
        return 1;
}


