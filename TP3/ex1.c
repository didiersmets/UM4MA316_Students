#include "hash_tables.h"
int edge_pos_in_tri (int v1, int v2, struct Triangle t) {
	if (v1==t.x && v2==t.y){
		return 0;
	}else if (v1==t.y && v2==t.z){
		return 1;
	}else if (v1==t.z && vé==t.x){
		return 2;
	}
	return -1;
}

int tris_are_neighbors (int tri1, int tri2, const struct Mesh *m){
	int v0 = edge_pos_in_tri(tri2.y, tri2.x, tri1);
	int v1 = edge_pos_in_tri(tri2.z, tri2.y, tri1);
	int v2 = edge_pos_in_tri(tri2.x, tri2.z, tri1);
	if (v0!=-1){
		return v0;
	}else if (v1!=-1){
		return v1;
	}
	return v2;
}

int *build_adjacency_table1(const struct Mesh *m){
	int* adj = malloc(3*m->ntri * sizeof(int));
	for(int i = 0; i < 3*m->ntri; i++){
		adj[i] = -1;
	}

	for(int i = 0; i < m->ntri; i++){
		for(int j = 0; j < m->ntri; j++){
			int edge = tris_are_neighbors(m->tri[i], m->tri[j], m);
			adj[3*i+edge] = j;
		}
	}
	return adj;
}

struct Edge {
	int v1;
	int v2;
};

struct HashTable *build_edge_table1(const struct Mesh *m){
	struct HashTable *h = hash_table_init(m->ntri, sizeof(struct Edge), sizeof(int));
	h->data = malloc(m->ntri*sizeof(int));
	for (int i=0; i<m->ntri; i++){
		h->data = i;
		h->data +=1;
	}
	
	struct Edge e;
	for (int i=0; i<m->ntri; i++){
		for (int j=0; j<3; j++){
			e.v1 = m->tri[i][j];
			e.v2 = m->tri[i][(j+1)mod3];
			hash_table_insert(h, e, i);
		}
	}

	return h;
}


int *build_adjacency_table2(const struct Mesh *m){
	int *adj = malloc(3*m->ntri*sizeof(int));
	for (int i=0; i<3*m->ntri; i++){
		adj[i] = -1;
	}

	struct HashTable *h = build_edge_table1(m); 

	struct Edge e;
	for (int i=0; i<m->ntri; i++){
		for (int j=0; j<3; j++){
			e.v1 = m->tri[i][(j+1)mod3];
			e.v2 = m->tri[i][j];
			void res = hash_table_find(h, e);
			if (res!=NULL){
				adj[3*i+j] = res;
			}
		}
	}

	hash_table_fini(h);
	return adj;
}


struct EdgeTable {
	int *head;
	int *next;
}





























		












































