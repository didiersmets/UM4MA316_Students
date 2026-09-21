#include "../include/algos.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {

  srand(time(NULL));
  FILE *coord = fopen("plot_co.txt", "w");

  const int N[7] = {10, 20, 50, 100, 200, 500, 1000};
  
  double y_co[3][7];
  void (*sort_fct[3])(int *, int) = {bubble_sort, insertion_sort, merge_sort};

  for(int j=0; j<3; j++) {

    for(int k=0; k<7; k++) {
      
      int n = N[k];
      int array[n];

      for(int i=0; i<n; i++) {
        int p = rand() % 100 + 1;
        array[i] = p;
      }

      clock_t start = clock();

      for (int k = 0; k < 10000; k++) {
          sort_fct[j](array, n);
      }

      clock_t stop = clock();

      y_co[j][k] = ((double)(stop - start) / CLOCKS_PER_SEC) / 10000.0;

      fprintf(coord, "%d   %.10f\n", n, y_co[j][k]);
    }
  }

  fclose(coord);
  const char *command = "gnuplot plot.gnuplot";
  int cr = system(command);
  if (cr != 0) {
    fprintf(stderr, "Impossible de lancer la commande: %s\n", command);
  }
  return 0;
}
