#pragma once
#include "mesh.h"

/* Charge un maillage à partir d'un fichier au format Medit .mesh.
 * @param m : adresse du maillage.
 * @param filename : le nom du fichier Medit source. 
 * NB : toutes les infos autres que coordonnées des sommets (Vertices)
 * et faces (Triangles) [supposés triangulaires] sont omises.
 */
int read_mesh_from_medit_file(struct Mesh *m, const char* filename);

/* Ecrit un maillage dans un fichier au format Medit .mesh.
 * @param m : adresse du maillage.
 * @param filename : le nom du fichier pour écriture.
 */
int write_mesh_to_medit_file(const struct Mesh *m, const char* filename);

/* Charge un maillage à partir d'un fichier au format Wavefront .obj.
 * @param m : adresse du maillage.
 * @param filename : le nom du fichier Wavefront source. 
 * NB : toutes les infos autres que coordonnées des sommets (v) et faces 
 * (f) [supposés triangulaires] sont omises.
 */
int read_mesh_from_wavefront_file(struct Mesh *m, const char *filename);

/* Ecrit un maillage dans un fichier au format Wavefront .obj.
 * @param m : adresse du maillage.
 * @param filename : le nom du fichier pour écriture.
 */
int write_mesh_to_wavefront_file(const struct Mesh *m, const char *filename);

