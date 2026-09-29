#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sorting.h"

void fill_random(int *T, int N) {
    for (int i=0; i<N; ++i) {
        T[i] = rand() % 1000;
        
    }
}

int main(void) {
    int sizes[] = { 10, 20, 50, 100, 200, 500, 1000};
    int nb_sizes = sizeof(sizes)/ sizeof(sizes[0]);

    FILE * f = fopen ("test_sorting.txt" , "w");
    
    if (!f) {
        perror ("Error opening file");
        return -1;
    }

    for (int k = 0; k < nb_sizes; k++) {
        int N = sizes[k];
        int * T = malloc(N *sizeof(int));

        fill_random(T, N);
        clock_t start = clock();
        bubble_sort(T, N);
        clock_t end = clock();
        double t_bubble = (double)(end - start)/ CLOCKS_PER_SEC;

        fill_random(T, N);
        start = clock();
        insertion_sort(T, N);
        end = clock();
        double t_insertion = (double)(end - start)/ CLOCKS_PER_SEC;

        fill_random(T, N);
        start = clock();
        merge_sort(T, N);
        end = clock();
        double t_merge = (double)(end - start)/ CLOCKS_PER_SEC;

        fprintf(f, "%d %g %g %g\n" , N , t_bubble , t_insertion , t_merge );
        free(T);

        }

    fclose (f);

    system("gnuplot -p -e \"set logscale xy; set xlabel 'N'; set ylabel 'temps(sec)'; "
        "plot 'test_sorting.txt' using 1:2 with linespoints title 'bubble', "
        " '' using 1:3 with linespoints title 'insertion' , "
        " '' using 1:4 with linespoints title 'merge'\"");
 
    return 0;
}
