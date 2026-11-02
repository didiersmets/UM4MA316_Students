#include <stdlib.h>
#include "mesh.h"
#include "hash_tables.h"


int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{
	if (t.idx[0]==v1 && t.idx[1]==v2)
		return 0;

	if (t.idx[1]==v1 && t.idx[2]==v2)
                return 1;

	if (t.idx[2]==v1 && t.idx[0]==v2)
                return 2;

	return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m)
{
	struct Triangle t1 = m->triangles[tri1];
	struct Triangle t2 = m->triangles[tri2];

	for(int j= 0; j<3; j++) {
		int v1 = t1.idx[j];
		int v2 = t2.idx[(j+1)%3];

		if (edge_pos_tri(v2,v1vt2) != 1) {
			return j;
		}
	}
	return -1;
}

int *build_adjacency_table1(const struct Mesh *m)
{
	int *adj = malloc (3*m->ntri*sizeof(int));

	if (adj==NULL)
		return NULL;

	for (int i=0; i<3*m->ntri; i++) {
		adj[i] = -1;
	}

	for (int i=0; i<m->ntri; i++) {
		
		for(int k=0; k<m->ntri; k++) {

			if (i!=k) {
				int pos = tris_are_neighbors(i,k,m);

				if (pos!=-1) {
					adj[3*i + pos] = k;
				}
			}
		}
	}
	return adj;
}

struct Edge {
	int v1;
	int v2;
};

struct HashTable *build_edge_table1(const struct Mesh *m)
{
	struct HashTable*ht = hash_table_int(6*m->ntri, sizeof(struct Edge), sizeof(int));
	
	if (ht == NULL)
		return NULL;

	for (int i=0; i<m->ntri; i++) {

		struct Triangle t = m->tri[i];

		for  (int j=0; j<3; j++) {
			struct Edge e;

			e.v1 = t.v[j];
			e.v2 = t.v[(j+1)%3];

			int value =i;
			hash_table_insert(ht, &e, &value);
		}
	}
	return ht;
}

int *build_adjacency_table2(const struct Mesh *m)
{
	struct HashTable *ht = build_edge_table1(m);

	if (ht==NULL)
		return NULL;

	int *adj = malloc(3*m -> ntri*sizeof(int));

	if (adj==NULL) {
		hash_table_fini(ht);
		return NULL;
	}

	for(int i=0; i<3*m->ntri; i++)
		adj[i] = -1;

	for(int i=0; i<m->ntri; i++) {

		struct Triangle t = m-> triangles[i];

		for (int j=0; j<3; j++) {

			struct Edge e;

			e.v1 = t.idx[(j+1)%3];
			e.v2 = t.idx[j];

			int *neighbor = hash_table_find(ht, &e);

			if (neighbor!=NULL) {
				adj[3*i+j] = *neighbor;
			}
		}
	}
	hash_table_fini(ht);
	return adj;
}

struct EdgeTable {
	int *head;
	int *next;
};

void edge_table_initializa(struct EdgeTable *et, int nvert, int ntri)
{
	et->head = malloc(nvert*sizeof(int));
	et->next = malloc(3*ntri*sizeof(int));

	if (et->==NULL || et->next==NULL) {
		free(et->head);
		free(et->next);

		et->head = NULL;
		et->next = NULL;
		return;
	}
	for(inti=0; i<nvert; i++)
		et->head[i] = -1;

	for (int i=0; i<3*ntri; i++)
		et->next[i] = -1;
}

void edge_table_dispose(struct EdgeTable *et)
{
	free(et->head);
	free(et->next);
	free(et);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et)
{
	int tmp = et->head[v1];
	et->head[v1] = edge_code;
	et->next[edge_code] = tmp;
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m)
{
	int code = et->head[v1];

	while(code!=-1) {
		int i = code/3;
		int j = code%3;

		int a = m->triangles[i].idx[j];
		int b = m->triangles[i].idx[(j+1)%3];

		if(a==v1 && b==v2)
			return code;
		
		code = et->next[code];
	}
	return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m)

int *build_adjacency_table3(const struct Mesh *m)










