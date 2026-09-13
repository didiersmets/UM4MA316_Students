#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 1) {
        printf("n must be greater than 1.\n");
        return 1;
    }

    double xmin = -6.0 * M_PI;
    double xmax =  6.0 * M_PI;
    double dx = (xmax - xmin) / (n - 1);

    FILE *f = fopen("sinc.txt", "w");

    if (f == NULL) {
        printf("Cannot open output file.\n");
        return 1;
    }

    for (int j = 0; j < n; j++) {
        double x = xmin + j * dx;
        double y;

        if (x == 0.0) {
            y = 1.0;
        } else {
            y = sin(x) / x;
        }

        fprintf(f, "%f\t%f\n", x, y);
    }

    fclose(f);

    return 0;
}