#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n < 2) {
        printf("n must be at least 2\n");
        return 1;
    }


    double xmin = -6 * M_PI;
    double xmax =  6.0 * M_PI;

    double delta = (xmax - xmin) / (n - 1);
    double *x = malloc(n * sizeof(double));
    double *y = malloc(n * sizeof(double));

    FILE *file;
    file = fopen("output.txt", "w");

    if (file == NULL) {
        printf("Error opening file\n");
        free(x);
        free(y);
        return 1;
    }

    for (int j = 0; j < n; j++) {

        x[j] = xmin + j * delta;
        if(x[j]==0)
            y[j]=1;
        else
            y[j]= sin(x[j])/x[j];

        fprintf(file, "%f\t%f\n", x[j], y[j]);
    }

    fclose(file);
    free(x);
    free(y);

    return 0;
}