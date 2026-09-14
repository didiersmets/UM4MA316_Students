#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("No integer provided in the command line\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if(n < 0) {
        printf("n must be a positive integer\n");
        return 1;
    }

    double x_min = -6 * M_PI;
    double x_max = 6 * M_PI;
    double delta_x = (x_max - x_min) / (n - 1);

    double *x = malloc(n * sizeof(double));
    double *y = malloc(n * sizeof(double));

    FILE *output;
    output = fopen("output.txt", "w");

    for(int j = 0; j < n; j++) {
        
        x[j] = x_min + j * delta_x;
        y[j] = x[j] == 0 ? 1 : sin(x[j]) / x[j];
        
        fprintf(output, "%f\t%f\n", x[j], y[j]);
    }

    fclose(output);
    free(x);
    free(y);

    return 0;
}