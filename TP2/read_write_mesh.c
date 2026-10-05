#include <stdio.h>
#include <stdlib.h>

int read_mesh2D(struct Mesh2D* m, const char* filename)
{
	// remise à zero du maillage

	FILE* fichier = fopen(filename, "r");

	if(fichier == NULL){
		return 0; 
	}

	char line[1000];
	int dimention = 0;
	int nv = 0;
	int nt = 0;

	while(fgets(line, 1000, fichier)) {
		
		if (sscanf(line, "Vertices %d", &nv) == 1) {

			// Reserver de la mémoire pour les vertex
			if (nv > m->vtx_capacity) {
				free(m->vtx);
				m->vtx = malloc(nv*sizeof(struct Vertex));
				m->vtx_capacity = nv;
			}

			// faire une bouclle pour lire les vertex
			m->nv = 0;
			for (int i=0; i < nv; i++) {
				fgets(line, 1000, fichier);
				sscanf(line, "%lf %lf", &m->vtx[i].x, &m->vtx[i].y);
				m->nv++;
			}	

		} else if (sscanf(line, "Triangles %d", &nt) == 1) {

			if (nt > m->tri_capacity) {
				free(m->tri);
				m->tri = malloc(nt*sizeof(struct Triangle));
				m->tri_capacity = nt;
			}

			m->nt = 0;
			for (int i=0; i<nt; i++) {
				fgets(line, 1000, fichier);
				sscanf(line, "%d %d %d", 
						m->tri[i].idx[0],
						m->tri[i].idx[1],
						m->tri[i].idx[2]);
				m->nt++;
			}
		}
	}
	fclose(fichier);
	return 1;
}


int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename)
{
	FILE* fichier = fopen(filename, "w");
	
	if (fichier == NULL) {
		return 0;
	}

	for( int i=0; i<m->nt; i++) {

		struct Vertex A = m->vtx[m->tri[i].idx[0]];
		struct Vertex B = m->vtx[m->tri[i].idx[1]];
		struct Vertex C = m->vtx[m->tri[i].idx[2]];

		fprintf(fichier, "%lf %lf\n", A.x, A.y);
		fprintf(fichier, "%lf %lf\n", B.x, B.y);
		fprintf(fichier, "%lf %lf\n", C.x, C.y);
		fprintf(fichier, "%lf %lf\n", A.x, A.y);

		fprintf(fichier, "\n");
	}

	fclose(fichier);
	return 1;
}


	
