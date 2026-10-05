#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int read_mesh2D(struct Mesh2D* m, const char* filename){
	FILE *f = fopen(filename, "r");
	if f==NULL
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

	
