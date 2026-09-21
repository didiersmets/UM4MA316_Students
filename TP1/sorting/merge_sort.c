#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


void random_fill(int *data, int size);
void merge_sort(int *data, int size);

int main()
{
    int N[] = {10, 20, 50, 100, 200, 500, 1000};
    int random;
    double exe_time[7] = {0.0};
    const char *filename = "exetime_bubble.dat";
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
        //merge_sort(data, N[i]);
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



void merge_sort(int *data, int size)
{

}