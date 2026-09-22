#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void random_fill(int *data, int size);
void merge_sort(int *data, int p, int r);
void insertion_sort(int *data, int size);
void merge(const int *A, int sA, const int *B, int sB, int *C);
void merge_sort_noalloc(int *data, int p, int r, int *memory);
void merge_pingpong_recursive(int *unsorted, int p, int r, int *sorted);
void merge_sort_pingpong(int *data, int size);

int main()
{
    srand(time(NULL));
    int N[] = {10, 20, 50, 100, 200, 500, 1000};
    int random;
    double exe_time[7] = {0.0};
    const char *filename = "exetime_merge_pingpong.dat";
    FILE *f;

    f = fopen(filename, "w");
    if (f == NULL)
    {
        perror(filename);
        return 1;
    }

    for (int i = 0; i < 7; i++)
    {
        int *data = (int *)malloc(N[i] * sizeof(int));
        random_fill(data, N[i]);

        clock_t begin = clock();
        merge_sort_pingpong(data, N[i]);
        // insertion_sort
        if (i == 1)
        {
            for (int j = 0; j < N[i]; j++)
            {
                printf("%d ", data[j]);
            }
        }
        clock_t end = clock();

        exe_time[i] = (double)(end - begin) / CLOCKS_PER_SEC;

        fprintf(f, "%d %lf\n", N[i], exe_time[i]);

        free(data);
    }

    fclose(f);

    return EXIT_SUCCESS;
}

void random_fill(int *data, int size)
{
    int random;
    for (int i = 0; i < size; i++)
    {
        random = rand() % 101;
        data[i] = random;
    }
}

void insertion_sort(int *data, int size)
{
    assert(data != NULL);
    int j = 0;
    int temp;
    if (size == 1)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        // perform a backward positioning
        j = i;
        while (j > 0 && data[j] < data[j - 1])
        {
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            j--;
        }
    }
}

void merge_sort(int *data, int p, int r)
{
    int q;
    if (p < r)
    {
        q = (p + r) / 2;
        merge_sort(data, p, q);
        merge_sort(data, q + 1, r);
        int *C = (int *)malloc((r + 1 - p) * sizeof(int));
        merge(data + p, q - p + 1, data + q + 1, r - q, C);
        for (int i = p; i < r + 1; i++)
        {
            data[i] = C[i - p];
        }
        free(C);
    }
}

void merge(const int *A, int sA, const int *B, int sB, int *C)
{
    int idxA = 0;
    int idxB = 0;
    for (int idxC = 0; idxC < sA + sB; idxC++)
    {

        if ((idxA < sA) && ((idxB == sB) || A[idxA] <= B[idxB]))
        {
            C[idxC] = A[idxA++];
        }
        /* otherwise we necessarily pick from B */
        else
        {
            C[idxC] = B[idxB++];
        }
    }
}
void merge_sort_noalloc(int *data, int p, int r, int *memory)
{
    int q;
    if (p >= r)
    {
        return;
    }

    q = (p + r) / 2;
    merge_sort_noalloc(data, p, q, memory);
    merge_sort_noalloc(data, q + 1, r, memory);
    merge(data + p, q - p + 1, data + q + 1, r - q, memory + p);
    for (int i = p; i < r + 1; i++)
    {
        data[i] = memory[i];
    }
}

void merge_pingpong_recursive(int *unsorted, int p, int r, int *sorted)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_pingpong_recursive(sorted, p, q, unsorted);
        merge_pingpong_recursive(sorted, q + 1, r, unsorted);
        merge(unsorted + p, q - p + 1, unsorted + q + 1, r - q, sorted + p);
    }
}

void merge_sort_pingpong(int *data, int size)
{
    int *S = (int *)malloc(size * sizeof(int));
    if (!S)
        return;
    for (int i = 0; i < size; i++)
    {
        S[i] = data[i];
    }
    merge_pingpong_recursive(S, 0, size - 1, data);
    free(S);
}
