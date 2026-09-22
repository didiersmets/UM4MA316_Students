#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void bubble_sort(int *data, int size);
void insertion_sort(int *data, int size);
void random_fill(int *data, int size);

int main()
{
    int N[] = {10, 20, 50, 100, 200, 500, 1000};
    int random;
    double exe_time[7] = {0.0};
    const char *filename = "exetime_insertion.dat";
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
        insertion_sort(data, N[i]);
        //bubble_sort(data, N[i]);
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

void bubble_sort(int *data, int size)
{
    assert(data != NULL);
    if (size == 1)
    {
        return;
    }
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size - j - 1; i++)
        {
            if (data[i] > data[i + 1])
            {
                // perform a switch
                int temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
            }
        }
    }
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
