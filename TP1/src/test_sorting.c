#include "../include/sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_ALGORITHMS 4
#define OUTPUT_FILE "sorting_times.dat"

static double now(void){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

static void run_algorithm(int algo, int *array, int n){
    switch(algo){
        case 0: bubbleSort(array, n); break;
        case 1: insertionSort(array, n); break;
        case 2: mergeSort(array, n); break;
        case 3: userPingPong(array, n); break;
    }
}

int main(void) {

    srand(time(NULL));

    int N[] = {10, 20, 50, 100, 200, 500, 1000};
    int n_sizes = sizeof(N) / sizeof(N[0]);

    const char *names[N_ALGORITHMS] = {
        "Bubble", "Insertion", "Merge", "PingPong"
    };

    FILE *out = fopen(OUTPUT_FILE, "w");
    if(out == NULL) {
        printf("Error opening %s\n", OUTPUT_FILE);
        return 1;
    }

    // Header line (gnuplot ignores lines starting with #)
    fprintf(out, "# N");
    for(int a = 0; a < N_ALGORITHMS; a++) {
        fprintf(out, "\t%s", names[a]);
    }
    fprintf(out, "\n");

    for(int i = 0; i < n_sizes; i++) {

        int *base = malloc(N[i] * sizeof(int));
        int *reference = malloc(N[i] * sizeof(int));
        int *arr = malloc(N[i] * sizeof(int));

        if(base == NULL || reference == NULL || arr == NULL) {
            printf("Memory allocation failed\n");
            free(base);
            free(reference);
            free(arr);
            fclose(out);
            return 1;
        }

        /* Generate random array */
        for(int j = 0; j < N[i]; j++) {
            base[j] = rand() % 100;
        }

        fprintf(out, "%d", N[i]);
        printf("N = %d\n", N[i]);

        for(int a = 0; a < N_ALGORITHMS; a++) {

            /* Every algorithm sorts the same input */
            memcpy(arr, base, N[i] * sizeof(int));

            double start = now();
            run_algorithm(a, arr, N[i]);
            double elapsed = now() - start;

            fprintf(out, "\t%e", elapsed);
            printf("  %-10s %e s\n", names[a], elapsed);

            /* Compare with the result of the first algorithm */
            if(a == 0) {
                memcpy(reference, arr, N[i] * sizeof(int));
            } else if(memcmp(reference, arr, N[i] * sizeof(int)) != 0) {
                printf("ERROR: %s produced a different result\n", names[a]);
                free(base);
                free(reference);
                free(arr);
                fclose(out);
                return 1;
            }
        }

        fprintf(out, "\n");

        free(base);
        free(reference);
        free(arr);
    }

    fclose(out);

    printf("\nAll tests passed, times written to %s\n", OUTPUT_FILE);

    return 0;
}
