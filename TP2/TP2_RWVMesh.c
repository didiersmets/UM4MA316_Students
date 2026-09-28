#include <stdlib.h>
#include <stdio.h>


/* according to documentation a mesh file is an ASCII or binary file
 * it contains the information needed to describe the surface mesh and the
 * underlying geometry. It is organized as a series of fields, identified by
 * keywords. It containes the vertex coordinates and the list of faces.voir 
 * page 35 du pdf de MEDIT * voir
 * comment calculer l'air signée par produit vectoriel!*
 */
int read_mesh2D(struct mesh2D* m, const chhar* filename){
	FILE* fptr;
	fptr = fopen(filename,"r");
		

}
