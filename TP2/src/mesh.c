#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include "../include/mesh.h"


int initialize_mesh(struct Mesh *m, 
                      int vtx_capacity, 
                      int tri_capacity) {

  m->nv = 0;
  m->nt = 0;
  m->vert = malloc(sizeof(struct Vertex) * vtx_capacity);
  m->tri = malloc(sizeof(struct Triangle) * tri_capacity);

  if (m->vert == NULL || m->tri == NULL) {
    return 1;
  }
  
  return 0;
}

void dispose_mesh(struct Mesh *m) {
  free(m->vert);
  m->vert = NULL;
  free(m->tri);
  m->tri = NULL;
  m->nv = 0;
  m->nt = 0;
}

// on utilise la formule de Felix Klein pour la signed area 
// d'un triangle et on fait la somme de tout, en voyant la struct 
// comme un triangle mesh 

double area_mesh2D(struct Mesh *m) {
  
  double signed_area = 0;
  int n_tri = m->nt;

  for (int i=0; i<n_tri; i++) {

    struct Triangle i_tri = m->tri[i];

    struct Vertex A = m->vert[i_tri.v1]; 
    struct Vertex B = m->vert[i_tri.v2];
    struct Vertex C = m->vert[i_tri.v3];

    signed_area += 0.5 * ((A.x * B.y - B.x * A.y) - (A.x * C.y - C.x * A.y) + (B.x * C.y - C.x * B.y));
  }

  return signed_area;
}

// we assume the surface mesh is closed

double volume_mesh3D(struct Mesh *m) {

  struct Triangle *ens_tri = m->tri;
  double volume = 0.;

  for(int i=0; i<m->nt; i++) {

    struct Vertex A = m->vert[ens_tri[i].v1];
    struct Vertex B = m->vert[ens_tri[i].v2];
    struct Vertex C = m->vert[ens_tri[i].v3];

    struct Vertex barycentre;
    barycentre.x = (A.x + B.x + C.x)/3.;
    barycentre.y = (A.y + B.y + C.y)/3.;
    barycentre.z = (A.z + B.z + C.z)/3.;

    // construction des vecteurs u=AB et v=AC

    double u[3] = {B.x - A.x, B.y - A.y, B.z - A.z};
    double v[3] = {C.x - A.x, C.y - A.y, C.z - A.z};

    // aire (non signée) du triangle 

    double area = 0.5 * sqrt((u[1] * v[2] - v[1] * u[2]) + 
                             (u[0] * v[2] - u[2] * v[0]) +
                             (u[0] * v[1] - u[1] * v[0]));
    
    // construction de la normale au triangle
    
    double norm[3] = {(u[1] * v[2] - v[1] * u[2])/(2*area),
                    (u[0] * v[2] - u[2] * v[0])/(2*area),
                    (u[0] * v[1] - u[1] * v[0])/(2*area)};

    volume += area * (barycentre.x * norm[0] + 
                      barycentre.y * norm[1] + 
                      barycentre.z * norm[2]);
  }
  
  return volume/3.;
}

// pour les mesh2D (j'attribue pas les co en z) 

int read_mesh2D(struct Mesh *m, const char *filename) {

  FILE *mesh = fopen(filename, "r");

  if (mesh == NULL) {
    printf("Fichier introuvable.\n");
    fclose(mesh);
    return 1;
  }

  char line1[256];
  char line2[256];

  if (fgets(line1, sizeof(line1), mesh) == NULL || 
      fgets(line2, sizeof(line2), mesh) == NULL) {

    printf("Mauvais formatage du fichier.\n");
    fclose(mesh);
    return 1;
  }
  
  // attention il y a un espace au début dans les formatages donnés

  if (strcmp(line1, " MeshVersionFormatted 2\n") != 0 ||
      strcmp(line2, " Dimension 3\n") != 0) {

    printf("Mauvais formatage du fichier.\n");
    fclose(mesh);
    return 1;
  }
  
  char line[256];
  int n_vert;
  int n_tri;

  if (fscanf(mesh, " Vertices %d\n", &n_vert) != 1) {

    fprintf(stderr, "Erreur vertices.\n");
    fclose(mesh);
    return 1;
  }

  m->nv = n_vert;

  for (int i=0; i<n_vert; i++) {

    double x, y, z;
    int v_ref;

    if (fscanf(mesh, " %lf %lf %lf %d\n", &x, &y, &z, &v_ref) != 4) {

      fprintf(stderr, "Vertex %d invalide.\n", i+1);
      fclose(mesh);
      return 1;
    }

    m->vert[i].x = x;
    m->vert[i].y = y;
  }

  if (fscanf(mesh, " Triangles %d\n", &n_tri) != 1) {

    fprintf(stderr, "Erreur Triangles.\n");
    fclose(mesh);
    return 1;
  }

  m->nt = n_tri;

  for (int i=0; i<n_tri; i++) {
    
    int a, b, c, t_ref;
    struct Triangle i_tri;

    if (fscanf(mesh, " %d %d %d %d\n", &a, &b, &c, &t_ref) != 4) {

      fprintf(stderr, "Triangle %d invalide.\n", i+1);
      fclose(mesh);
      return 1;
    }
    
    // -1 comme les triangles sont 1_based dans le formatage
    i_tri.v1 = a-1;
    i_tri.v2 = b-1;
    i_tri.v3 = c-1;

    m->tri[i] = i_tri;
  }

  fclose(mesh);
  return 0;
}

// pour les mesh2D (on prend que les co x,y).

// Je pars du principe dans mon fichier gnuplot que mon
// fichier .txt s'appelle co_mesh.txt.

// J'ai d'abord fait une version qui crée un fichier .txt avec
// les co (x,y) qui se suivent mais avec le plot de fin ça ne 
// rend pas bien car les lignes relient les vertices consécutifs
// alors qu'on voudrait plus faire un mesh avec les lignes des triangles
// visibles (plus visuel).

int mesh2D_to_gnuplot(struct Mesh *m, const char *filename) {
  
  FILE *co_mesh = fopen(filename, "w");

  for (int i=0; i<m->nt; i++) {
    
    struct Triangle i_tri = m->tri[i];

    struct Vertex A = m->vert[i_tri.v1];
    struct Vertex B = m->vert[i_tri.v2];
    struct Vertex C = m->vert[i_tri.v3];

    fprintf(co_mesh, "%lf  %lf\n", A.x, A.y);
    fprintf(co_mesh, "%lf  %lf\n", B.x, B.y);
    fprintf(co_mesh, "%lf  %lf\n", C.x, C.y);
    fprintf(co_mesh, "%lf  %lf\n", A.x, A.y);
    
    // pour pas avoir de ligne qui relie les triangles
    fprintf(co_mesh, "\n");
  }
  
  // il faut bien fermer le .txt avant de plot sinon erreur
  fclose(co_mesh);

  const char *command = "gnuplot plot.gnuplot";

  if (system(command) != 0) {

    fprintf(stderr, "Impossible de lancer la commande : %s\n", command);
  }

  return 0;
}

int write_mesh(struct Mesh *m, const char *filename) {

  FILE *new_mesh = fopen(filename, "w");

  fprintf(new_mesh, " MeshVersionFormatted 2\n");
  fprintf(new_mesh, " Dimension 3\n");
  fprintf(new_mesh, " Vertices %d\n", m->nv);

  for (int i=0; i<m->nv; i++) {

    fprintf(new_mesh, " %lf %lf %lf %d\n", m->vert[i].x, m->vert[i].y, m->vert[i].z, 1);
  }

  fprintf(new_mesh, " Triangles %d\n", m->nt);

  for (int i=0; i<m->nt; i++) {

    fprintf(new_mesh, " %d  %d  %d  %d\n", m->tri[i].v1, m->tri[i].v2, m->tri[i].v3, 1);
  }

  fprintf(new_mesh, " End\n");
  
  fclose(new_mesh);
  return 0;
}

