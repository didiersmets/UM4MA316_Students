#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double rand_max = 100;

void merge_subroutine(int *T,  int p, int q, int r){
    //both start at the middle, i will go left and j will go right
    int i = q;
    int j = q + 1;

    //error cases
    if (p > q || q >= r) {
        return;
    }

    //already ordered
    if (T[q] <= T[q + 1]) {
        return;
    }
    
    //as long as i-n is bigger than j+n (n being the loop iteration) we continue 
    while (i >= p && j <= r && T[i] > T[j]) {
        i--;
        j++;
    }

    //we establish the start of our 2 blocks that have to be switched
    int blockA = i+1;
    int blockB = q+1;

    //we switch both blocks
    while (blockA <= q && blockB < j) {
        int tmp = T[blockA];
        T[blockA] = T[blockB];
        T[blockB] = tmp;
        blockA++;
        blockB++;
    }

    //we call the subroutine again to rework on these 2 blocks
    merge_subroutine(T, p, i, q);
    merge_subroutine(T, q + 1, j - 1, r);

}

void merge_sort(int* T, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        merge_sort(T, p, q);
        merge_sort(T, q + 1, r);
        merge_subroutine(T, p, q, r);
    }
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int *T = malloc(sizeof(int) * n);
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        T[i] = (rand() % 100) + 1;
        printf("%d ", T[i]);
    }
    printf("\n");

    merge_sort(T, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", T[i]);
    }

    printf("\n");
    free(T);
    return 0;
}