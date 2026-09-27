#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void insertion_sort(int* input_vector, int vector_size);
void merge_sort(int* T, int p, int r);
void merge(int *T, int p, int q, int r);

void merge_pingpong(int* vector, int n);
void merge_sort_noalloc(int* unsorted, int p, int r, int* sorted);
void merge_noalloc(int *unsorted, int p, int q, int r, int* sorted);
void merge_sort_noalloc_opt(int* unsorted, int p, int r, int* sorted);
void merge_sort_noalloc_opt_par(int* unsorted, int p, int r, int* sorted);
void* merge_sort_thread_worker(void* arg);


void print_vector(int* input_vector, int vector_size);
void verifier(int* input_vector, int vector_size);


typedef struct{
    int *unsorted;
    int *sorted;
    int p;
    int r;
}sorting_data;

int main(int argc, char *argv[]){
    srand(time(NULL));
    
    int n_elements[] = {10, 20, 50, 100, 200, 500, 1000, 10000, 100000, 1000000};
    int n_elements_size = 10;
    double exec_times[n_elements_size];
    memset(exec_times, 0, sizeof(exec_times));

    // --- Random Array Generation ---
    int curr_vector_size = 0;
    for(int i = 0; i < n_elements_size; i++){
        curr_vector_size = n_elements[i];
        //generates an array of N random integers
        int *vector = malloc(curr_vector_size * sizeof(int));

        //fill the vector randomly and display it
        for (int j = 0; j < curr_vector_size; j++){
            int el = rand() % 1000000;
            vector[j] = el;
        }
        printf("Unsorted vector \n");
        print_vector(vector, curr_vector_size);


        // --- SORTING ---

        clock_t start = clock();

        //merge_sort(vector, 0, curr_vector_size-1);
        merge_pingpong(vector, curr_vector_size);

        verifier(vector,curr_vector_size);
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        exec_times[i] = seconds;
        printf("Execution of sort with %d elements took %lf \n", curr_vector_size, seconds);

        printf("Merge Sorted vector \n");
        print_vector(vector, curr_vector_size);


        printf("\n");
        free(vector);
    }

    FILE *fp = fopen("merge_sort_parallel.txt", "w");

    for(int i = 0; i < n_elements_size; i++){
        fprintf(fp,"%d\t%lf \n", n_elements[i], exec_times[i]);
    }


    fclose(fp);


    return 0;
}

void insertion_sort(int* input_vector, int vector_size){
    if (input_vector == NULL || vector_size == 0){
        printf("provide a valid vector or a size > 0 \n");
    }else{
        //iteration until fully sorted (n-1)
        for(int i = 0; i < vector_size-1; i++){
            //iteration on progressively smaller parts of array
            for(int k = i; k >= 0; k--){
                if(input_vector[k+1] < input_vector[k]){
                    //swap
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



void merge_sort(int* T, int p, int r){
    if (T == NULL){
        printf("provide a valid vector or a size > 0 \n");
    }else{
        if(p<r){
            int q = (p+r)/2;
            merge_sort(T, p, q);
            merge_sort(T, q+1, r);
            merge(T, p, q, r);
        }
    }
}


void merge(int *T, int p, int q, int r){
    int *C = malloc((r+1-p)*sizeof(int));
    int idx_A = 0;
    int idx_B = 0;
    for(int idx_C = p; idx_C < r+1; idx_C ++){
        if(idx_B == r+1-(q+1) || (idx_A < (q+1)-p && T[p+idx_A] <= T[q+1+idx_B])){
            C[idx_C-p] = T[p+idx_A];
            idx_A++;
        }else{
            C[idx_C-p] = T[q+1+idx_B];
            idx_B++;
        }
    }
    for(int i = p; i < r+1; i++){
        T[i] = C[i-p];
    }
    free(C);
}


void merge_pingpong(int* vector, int n){
        int* sorted = malloc(n * sizeof(int));
        memcpy(sorted, vector, n * sizeof(int));
        merge_sort_noalloc(sorted, 0, n-1, vector);
        free(sorted);
}

void merge_sort_noalloc(int* unsorted, int p, int r, int* sorted){
        if (unsorted == NULL || sorted == NULL){
        printf("provide a valid vector or a size > 0 \n");
    }else{
        if(p<r){
            int q = (p+r)/2;
            merge_sort_noalloc(sorted, p, q, unsorted);
            merge_sort_noalloc(sorted, q+1, r, unsorted);
            merge_noalloc(unsorted, p, q, r, sorted);
        }
    }
}
void merge_sort_noalloc_opt(int* unsorted, int p, int r, int* sorted){
    if (unsorted == NULL || sorted == NULL){
        printf("provide a valid vector or a size > 0 \n");
    }else{
        if ((r+1-p) < 16){ //if the vector is smaller than 20 elements call insertion sort instead of the recursive function
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

        if(curr_size < 16){ //if the vector is smaller than 20 elements call insertion sort instead of the recursive function
            for(int i = p; i <= r; i++) {
                sorted[i] = unsorted[i];
            }
            insertion_sort(sorted + p, r + 1 - p);
        }else{
            if(p<r){
                int q = (p+r)/2;

                if(curr_size > 10000){

                    //prepara data for thread spawning
                    sorting_data* left_data = (sorting_data*)malloc(sizeof(sorting_data));
                    left_data->unsorted = unsorted;
                    left_data->sorted = sorted;
                    left_data->p = p;
                    left_data->r = q;

                    pthread_t left_thread;

                    pthread_create(&left_thread, NULL, merge_sort_thread_worker, left_data);


                    merge_sort_noalloc_opt_par(sorted, q+1, r, unsorted); //let subthread compute right part

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



void print_vector(int* input_vector, int vector_size){
    for(int i = 0; i < vector_size; i++){
        printf("%d ", input_vector[i]);
    }
    printf("\n");
}


void verifier(int* input_vector, int vector_size){
    for (int i = 0; i < vector_size - 1; i++) {
        if (input_vector[i + 1] < input_vector[i]) {

            fprintf(stderr, "Error at index %d \n", i); 
            return;
        }
    }
}


void* merge_sort_thread_worker(void* arg){

    sorting_data* data = (sorting_data*) arg;

    merge_sort_noalloc_opt(data->sorted, data->p, data->r, data->unsorted);

    free(data);

    return NULL;
}