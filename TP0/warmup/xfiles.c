#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int N = atoi(argv[1]);
  double x_min = -6 * M_PI;
  double x_max = 6 * M_PI;

  FILE *xfile = fopen("computed_list.txt", "w");

  for (int i=0; i<N; i++) {
    double delta_x = (x_max - x_min) / (N-1);
    double x_tmp = x_min + i * delta_x;
    double y_tmp = sin(x_tmp) / x_tmp;
    fprintf(xfile, "%f    %f\n", x_tmp, y_tmp);

    x_min = (x_tmp < x_min) ? x_tmp : x_min;
    x_max = (x_tmp > x_max) ? x_tmp : x_max;
  }
  return 0;
}
