#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int *T, int p, int q, int r)
{
    int n = r - p + 1;
    int *temp = malloc(n * sizeof(int));

    int i = p;
    int j = q + 1;
    int k = 0;

    while (i <= q && j <= r)
    {
        if (T[i] <= T[j])
        {
            temp[k] = T[i];
            i++;
        }
        else
        {
            temp[k] = T[j];
            j++;
        }

        k++;
    }

    while (i <= q)
    {
        temp[k] = T[i];
        i++;
        k++;
    }

    while (j <= r)
    {
        temp[k] = T[j];
        j++;
        k++;
    }

    for (int x = 0; x < n; x++)
    {
        T[p + x] = temp[x];
    }

    free(temp);
}

void merge_sort(int *T, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;

        merge_sort(T, p, q);
        merge_sort(T, q + 1, r);

        merge(T, p, q, r);
    }
}


int main()
{
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000};

    FILE *file = fopen("merge_times.dat", "w");

    for (int k = 0; k < 7; k++)
    {
        int N = sizes[k];

        int *T = malloc(N * sizeof(int));

        for (int i = 0; i < N; i++)
        {
            T[i] = rand();
        }

        clock_t start = clock();

        merge_sort(T, 0, N - 1);

        clock_t end = clock();

        double time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("N = %d, time = %f seconds\n", N, time);

        fprintf(file, "%d %f\n", N, time);

        free(T);
    }

    fclose(file);

    return 0;
}
