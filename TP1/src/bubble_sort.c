#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int *T, int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (T[j] > T[j + 1])
            {
                int temp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000};

    FILE *file = fopen("bubble_times.dat", "w");

    for (int k = 0; k < 7; k++)
    {
        int N = sizes[k];

        int *T = malloc(N * sizeof(int));

        for (int i = 0; i < N; i++)
        {
            T[i] = rand();
        }

        clock_t start = clock();

        bubble_sort(T, N);

        clock_t end = clock();

        double time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("N = %d, time = %f seconds\n", N, time);

        fprintf(file, "%d %f\n", N, time);

        free(T);
    }

    fclose(file);

    return 0;
}
