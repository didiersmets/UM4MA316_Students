#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    const double xmin = -6.0 * M_PI;
    const double xmax = 6.0 * M_PI;
    const char *filename = "sinc.dat";
    int n;
    double dx, x, y;
    FILE *f;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <n> [output_file]\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    if (n < 2) {
        fprintf(stderr, "n must be an integer >= 2\n");
        return 1;
    }

    if (argc == 3)
        filename = argv[2];

    f = fopen(filename, "w");
    if (f == NULL) {
        perror(filename);
        return 1;
    }

    dx = (xmax - xmin) / (n - 1);

    for (int j = 0; j < n; j++)
    {
        x = xmin + j * dx;
        /* sin(x)/x -> 1 as x -> 0 */
        if (fabs(x) < 1e-12)
            y = 1.0;
        else
            y = sin(x) / x;

        fprintf(f, "%.10f\t%.10f\n", x, y);
    }

    fclose(f);
    return 0;
}
