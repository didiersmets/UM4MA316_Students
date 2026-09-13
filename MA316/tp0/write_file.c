#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(int argc, char **argv) {
  FILE *f;
  int n, j;
  double x_min, x_max, delta_x, x_j, y_j;

  if (argc != 2) {
    printf("Usage: %s <positive integer>\n", argv[0]);
    return 1;
  }

  n = atoi(argv[1]);
  if (n < 2) {
    printf("Error: Please provide an integer greater than 1.\n");
    return 1;
  }

  f = fopen("sinc_data.txt", "w");
  if (f == NULL) {
    printf("Error: Could not open file sinc_data.txt\n");
    return 1;
  }

  x_min = M_PI * (-6.0);
  x_max = M_PI * 6.0;
  delta_x = (x_max - x_min) / (n - 1);

  for (j = 0; j < n; j++) {
    x_j = x_min + j * delta_x;
    if (fabs(x_j) > 1e-7) {
      y_j = sin(x_j) / x_j;
    } else {
      y_j = 1.0;
    }
    fprintf(f, "%f\t%f\n", x_j, y_j);
  }

  fclose(f);

  return 0;
}