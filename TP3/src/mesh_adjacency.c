#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mesh_adjacency.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{
	// from the triangle t deduce whichever is the position of edge v1->v2
	// inside a triangle idx[0]->idx[1] has position 0 idx[1]->idx[2] has position 1 idx[2]->idx[0] has position 2
	// if v1->v2 is not an edge of t the funciton should return -1
	if (v1 == t.idx[0] && v2 == t.idx[1])
	{
		return 0;
	}

	if (v1 == t.idx[1] && v2 == t.idx[2])
	{
		return 1;
	}

	if (v1 == t.idx[2] && v2 == t.idx[0])
	{
		return 2;
	}

	// or for (int i = 0; i < 3; i++) {
	//	    if (t.idx[i] == v1 && t.idx[(i + 1) % 3] == v2)
	//		return i;
	// }

	return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m)
{
	struct Triangle t1 = m->triangles[tri1];
	struct Triangle t2 = m->triangles[tri2];

	for (int i = 0; i < 3; i++)
	{
		int a = t1.idx[i];
		int b = t1.idx[(i + 1) % 3];
		if (edge_pos_in_tri(b, a, t2) != -1) // we have already developed an "is in"
			return i;
	}
	return -1;
}

int *build_adjacency_table1(const struct Mesh *m)
{
	
	int *adj = malloc(3 * (size_t)m->ntri * sizeof *adj);
	if (adj == NULL)
		return NULL;

	for (int i = 0; i < 3 * m->ntri; i++)
		adj[i] = -1;

	for (int i = 0; i < m->ntri; i++) {
		for (int k = 0; k < m->ntri; k++) {
			int pos = tris_are_neighbors(i, k, m);
			if (pos != -1)
				adj[3 * i + pos] = k;
		}
	}
	return adj;
}

struct HashTable *build_edge_table1(const struct Mesh *m)
{
	struct HashTable *edge_table = hash_table_init(6*m->ntri, sizeof(struct Edge), sizeof(int));
	if(!edge_table){
		printf("failed to allocate memory\n");
		return NULL;
	}
	//we just need a cycle of inserts for every edge, we can cycle on triangles
	for(int i = 0; i < m->ntri; i++){
		struct Triangle tri = m->triangles[i];
		for(size_t vertex = 0; vertex < 3; vertex++){
			struct Edge key_edge = {.v1 = tri.idx[vertex], .v2 = tri.idx[(vertex+1)%3]};
			hash_table_insert(edge_table, &key_edge, &i);
		}
	}
	return edge_table;
}

int *build_adjacency_table2(const struct Mesh *m)
{
	int *adj = malloc(3 * (size_t)m->ntri * sizeof *adj);
	if (adj == NULL){
	    printf("failed to allocate memory\n");
		return NULL;
	}
	struct HashTable *edge_table = build_edge_table1(m);
	if (edge_table==NULL){
		printf("failed to allocate memory\n");
		free(adj);
		return NULL;
	}
	for (int i = 0; i < 3 * m->ntri; i++)
		adj[i] = -1;
    //loop on the triangles look up for the opposing edge in the HashTable
	for (int i = 0; i < m->ntri; i++){
		struct Triangle tri = m->triangles[i];
		for(size_t vertex = 0; vertex < 3; vertex++){
			struct Edge opposing_key_edge = {.v2 = tri.idx[vertex], .v1 = tri.idx[(vertex+1)%3]};
			void *found = hash_table_find(edge_table, &opposing_key_edge);
			if(found != NULL){
			    int check;
			    memcpy(&check,found,sizeof(int));  
			    adj[3 * i + vertex] = check;
			}
		}
	}
	hash_table_fini(edge_table);
	free(edge_table);
	return adj;
}
void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri)
{
	et->head = malloc(nvert * sizeof(int));
	et->next = malloc(3 * ntri * sizeof(int));
	if(et->head == NULL || et->next == NULL){
		free(et->head);
	    free(et->next);
	    et->head = NULL;
	    et->next = NULL;
	    return;
	}
	for(int i = 0; i<nvert; i++){
		et->head[i] = -1;
	}
	for(int i = 0; i<3*ntri;i++){
		et->next[i] = -1;
	}
}

void edge_table_dispose(struct EdgeTable *et){
	free(et->head);
	free(et->next);
	et->head = NULL;
	et->next = NULL;
}
void edge_table_insert(int v1, int edge_code, struct EdgeTable *et)
{
	if(et->head == NULL || et->next == NULL){
		printf("error: edge table not initialised\n");
		return;
	}
	int tmp = et->head[v1];
	et->head[v1] = edge_code;
	et->next[edge_code] = tmp;
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m)
{
	int code = et->head[v1];
	while(code != -1){
		struct Triangle t = m->triangles[code/3];
		if (t.idx[(code % 3 + 1) % 3] == v2){
			return code;
		}
		code = et->next[code];
	}
	return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m)
{
	struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
	if(et == NULL){
		return NULL;
	}
	edge_table_initialize(et, m->nvert, m->ntri);
	if (et->head == NULL) {
	    free(et);
	    return NULL;
    }
	for (int i = 0; i < m->ntri; i++){
		struct Triangle tri = m->triangles[i];
		for(int vertex = 0; vertex < 3; vertex++){
			edge_table_insert(tri.idx[vertex], 3*i + vertex, et);
		}
	}
	return et;
}

int *build_adjacency_table3(const struct Mesh *m)
{
	int *adj = malloc(3 * (size_t)m->ntri * sizeof *adj);
	if (adj == NULL){
	    printf("failed to allocate memory\n");
		return NULL;
	}
	struct EdgeTable *edge_table = build_edge_table3(m);
	if (edge_table==NULL){
		printf("failed to allocate memory\n");
		free(adj);
		return NULL;
	}
	for (int i = 0; i < 3 * m->ntri; i++)
		adj[i] = -1;
    //loop on the triangles look up for the opposing edge in the Edgetable
	for (int i = 0; i < m->ntri; i++){
		struct Triangle tri = m->triangles[i];
		for(int vertex = 0; vertex < 3; vertex++){
			int code = edge_table_find(tri.idx[(vertex+1)%3],tri.idx[vertex],edge_table,m);
			if(code != -1){ 
			    adj[3 * i + vertex] = code/3;
			}
		}
	}
	edge_table_dispose(edge_table);
	free(edge_table);
	return adj;
}