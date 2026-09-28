#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void insertion_sort(int *array, int n)
{
    for (int i = 1; i < n; i++)
    {
        int j = i;

        while (j > 0 && array[j] < array[j - 1])
        {
            int temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;

            j--;
        }
    }
}


int main()
{
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000};

    FILE *file = fopen("insertion_times.dat", "w");

    for (int k = 0; k < 7; k++)
    {
        int N = sizes[k];

        int *T = malloc(N * sizeof(int));

        for (int i = 0; i < N; i++)
        {
            T[i] = rand();
        }

        clock_t start = clock();

        insertion_sort(T, N);

        clock_t end = clock();

        double time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("N = %d, time = %f seconds\n", N, time);

        fprintf(file, "%d %f\n", N, time);

        free(T);
    }

    fclose(file);

    return 0;
}
