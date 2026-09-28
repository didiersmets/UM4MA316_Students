#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void) {
    int sizes[] = { 10, 20, 50, 100, 200, 500, 1000};
        int * T = malloc(int *N * sizeof(int));

    FILE * f = fopen ("test_sorting.txt" , "r");
    
    if (!f) {
        perror ("Error opening file");
        return -1;
    }

    fwrite (T, sizeof(char), sizeof(T), f);
    fclose (f);
    return 0;
}

void fill_random(int *T, int N) {
    for (int i=0; i<N; ++i) {
        T[i] = rand() % 1000;
        
    }
}

clock_t start = clock()
bubble_sort(T, N);
clock_t end = clock()

