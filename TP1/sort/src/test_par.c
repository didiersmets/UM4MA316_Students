#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void insertion_sort(int* input_vector, int vector_size);
void merge(int *T, int p, int q, int r);
void merge_noalloc(int *unsorted, int p, int q, int r, int* sorted);
void merge_sort_noalloc_opt(int* unsorted, int p, int r, int* sorted);
void merge_sort_noalloc_opt_par(int* unsorted, int p, int r, int* sorted);
void* merge_sort_thread_worker(void* arg);

typedef struct{
    int *unsorted;
    int *sorted;
    int p;
    int r;
}sorting_data;

void insertion_sort(int* input_vector, int vector_size){
    if (input_vector == NULL || vector_size == 0){
        printf("provide a valid vector or a size > 0 \n");
    }else{
        for(int i = 0; i < vector_size-1; i++){
            for(int k = i; k >= 0; k--){
                if(input_vector[k+1] < input_vector[k]){
                    int tmp = input_vector[k];
                    input_vector[k] = input_vector[k+1];
                    input_vector[k+1] = tmp;
                } else {
                    break;
                }
            }
        }
    }
}

void merge_noalloc(int *unsorted, int p, int q, int r, int* sorted){
    int idx_A = 0;
    int idx_B = 0;
    for(int idx_sorted = p; idx_sorted < r+1; idx_sorted ++){
        if(idx_B == r+1-(q+1) || (idx_A < (q+1)-p && unsorted[p+idx_A] <= unsorted[q+1+idx_B])){
            sorted[idx_sorted] = unsorted[p+idx_A];
            idx_A++;
        }else{
            sorted[idx_sorted] = unsorted[q+1+idx_B];
            idx_B++;
        }
    }
}

void merge_sort_noalloc_opt(int* unsorted, int p, int r, int* sorted){
    if (unsorted == NULL || sorted == NULL){
        printf("provide a valid vector or a size > 0 \n");
    }else{
        if ((r+1-p) < 16){
            for(int i = p; i <= r; i++) {
                sorted[i] = unsorted[i];
            }
            insertion_sort(sorted + p, r + 1 - p);
        }else{
            if(p<r){
                int q = (p+r)/2;
                merge_sort_noalloc_opt(sorted, p, q, unsorted);
                merge_sort_noalloc_opt(sorted, q+1, r, unsorted);
                merge_noalloc(unsorted, p, q, r, sorted);
            }
        }
    }
}

void merge_sort_noalloc_opt_par(int* unsorted, int p, int r, int* sorted){
    if (unsorted == NULL || sorted == NULL){
        printf("provide a valid vector or a size > 0 \n");
    }else{
        int curr_size = r + 1 - p;

        if(curr_size < 16){
            for(int i = p; i <= r; i++) {
                sorted[i] = unsorted[i];
            }
            insertion_sort(sorted + p, r + 1 - p);
        }else{
            if(p<r){
                int q = (p+r)/2;

                if(curr_size > 10000){
                    sorting_data* left_data = (sorting_data*)malloc(sizeof(sorting_data));
                    left_data->unsorted = unsorted;
                    left_data->sorted = sorted;
                    left_data->p = p;
                    left_data->r = q;

                    pthread_t left_thread;
                    pthread_create(&left_thread, NULL, merge_sort_thread_worker, left_data);

                    merge_sort_noalloc_opt_par(sorted, q+1, r, unsorted);
                    pthread_join(left_thread, NULL);
                }else{
                    merge_sort_noalloc_opt(sorted, p, q, unsorted);
                    merge_sort_noalloc_opt(sorted, q+1, r, unsorted);
                }
                merge_noalloc(unsorted, p, q, r, sorted);
            }
        }
    }
}

void* merge_sort_thread_worker(void* arg){
    sorting_data* data = (sorting_data*) arg;
    // Modified to call _par version instead of serial version for better parallelism
    merge_sort_noalloc_opt_par(data->sorted, data->p, data->r, data->unsorted);
    free(data);
    return NULL;
}

int main() {
    int n = 100000;
    int *vector = malloc(n * sizeof(int));
    int *sorted = malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
        vector[j] = rand() % 1000000;
    }
    memcpy(sorted, vector, n * sizeof(int));
    
    clock_t start = clock();
    merge_sort_noalloc_opt_par(vector, 0, n-1, sorted);
    clock_t end = clock();
    
    for (int i = 0; i < n - 1; i++) {
        if (sorted[i + 1] < sorted[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }
    printf("Successfully sorted %d elements in %lf seconds\n", n, (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
