#include "../include/sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {

    srand(time(NULL));

    int N[] = {10, 20, 50, 100, 200, 500, 1000};
    int n_sizes = sizeof(N) / sizeof(N[0]);

    for(int i = 0; i < n_sizes; i++) {

        printf("\n----------------------------------\n");
        printf("Testing array of size %d\n", N[i]);
        printf("----------------------------------\n");

        int *arrBubble = malloc(N[i] * sizeof(int));
        int *arrInsertion = malloc(N[i] * sizeof(int));
        int *arrMerge = malloc(N[i] * sizeof(int));

        if(arrBubble == NULL ||
           arrInsertion == NULL ||
           arrMerge == NULL) {

            printf("Memory allocation failed\n");
            return 1;
        }

        /* Generate random array */
        for(int j = 0; j < N[i]; j++) {
            arrBubble[j] = rand() % 100;
        }

        /* Copy the same array */
        memcpy(arrInsertion, arrBubble, N[i] * sizeof(int));
        memcpy(arrMerge, arrBubble, N[i] * sizeof(int));

        /* Run sorting algorithms */
        bubbleSort(arrBubble, N[i]);

        insertionSort(arrInsertion, N[i]);

        mergSort(arrMerge, 0, N[i] - 1);

        /* Compare results */
        for(int j = 0; j < N[i]; j++) {

            if(arrBubble[j] != arrInsertion[j] ||
               arrInsertion[j] != arrMerge[j]) {

                printf("ERROR: algorithms produced different results\n");

                free(arrBubble);
                free(arrInsertion);
                free(arrMerge);

                return 1;
            }
        }

        printf("Test passed\n");

        free(arrBubble);
        free(arrInsertion);
        free(arrMerge);
    }

    printf("\nAll tests passed!\n");

    return 0;
}