#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../include/hash_tables.h"
#include "../include/mesh.h"
#include "../include/mesh_adjacency.h"
#include "../include/mesh_io.h"

//on prend en argument le data file voulu en line command

int main(int argc, char *argv[]) {

  srand(time(NULL));

  char *tables[3] = {"table1", "table2", "table3"};
  
  int *(*adjacency_table[3])(const struct Mesh *) = {build_adjacency_table1,
                                                     build_adjacency_table2,
                                                     build_adjacency_table3};
  const char *file = argv[1];
  struct Mesh m;
  //attention pour bugatti.obj la table1 est trop lente en pratique
  if (read_mesh_from_wavefront_file(&m, file) != -1) {
    for (int i=0; i<3; i++) {

      if (strcmp(file, "data/bugatti.obj") == 0 && i == 0) {
        continue;
      }

      clock_t start = clock();

      int *adj_array = adjacency_table[i](&m);

      clock_t stop = clock();
      double res = ((double)(stop-start)/CLOCKS_PER_SEC);

      printf("Exec time for %s: %f sec.\n", tables[i], res);
      free(adj_array);
    }
  }
  
  dispose_mesh(&m);
  return 0;
}
