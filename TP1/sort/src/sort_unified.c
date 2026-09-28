#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

double get_wall_time() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (double)time.tv_sec + (double)time.tv_nsec * 1e-9;
}

void bubble_sort(int* input_vector, int vector_size);
void insertion_sort(int* input_vector, int vector_size);
void merge_sort(int* T, int p, int r);
void merge(int *T, int p, int q, int r);

void merge_pingpong(int* vector, int n);
void merge_sort_noalloc(int* unsorted, int p, int r, int* sorted);
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


void print_vector(int* input_vector, int vector_size);
void verifier(int* input_vector, int vector_size);
int* generate_random_vector(int size);

int main(int argc, char *argv[]){
    srand(time(NULL));
    
    int n_elements[] = {10, 20, 50, 100, 200, 500, 1000, 10000, 100000, 1000000};
    int n_elements_size = 10;

    double exec_times_bubble[n_elements_size];
    memset(exec_times_bubble, 0, sizeof(exec_times_bubble));
    double exec_times_insertion[n_elements_size];
    memset(exec_times_insertion, 0, sizeof(exec_times_insertion));
    double exec_times_merge[n_elements_size];
    memset(exec_times_merge, 0, sizeof(exec_times_merge));
    double exec_times_merge_noalloc[n_elements_size];
    memset(exec_times_merge_noalloc, 0, sizeof(exec_times_merge_noalloc));
    double exec_times_pingpong[n_elements_size];
    memset(exec_times_pingpong, 0, sizeof(exec_times_pingpong));
    double exec_times_merge_noalloc_opt[n_elements_size];
    memset(exec_times_merge_noalloc_opt, 0, sizeof(exec_times_merge_noalloc_opt));
    double exec_times_merge_noalloc_opt_par[n_elements_size];
    memset(exec_times_merge_noalloc_opt_par, 0, sizeof(exec_times_merge_noalloc_opt_par));

    // --- Random Array Generation ---
    int curr_vector_size = 0;
    for(int i = 0; i < n_elements_size; i++){
        curr_vector_size = n_elements[i];
        //generates an array of N random integers and displays it
        int *vector = generate_random_vector(curr_vector_size);
        //generate the input vector to be fed to the algo
        int *unsorted = malloc(curr_vector_size * sizeof(int));
        int *sorted_temp = malloc(curr_vector_size * sizeof(int));
        
        // --- BUBBLE SORT ---
        if (curr_vector_size <= 10000) {
            memcpy(unsorted, vector, curr_vector_size * sizeof(int));
            double start_bubble = get_wall_time();
            bubble_sort(unsorted, curr_vector_size);
            double end_bubble = get_wall_time();
            verifier(unsorted, curr_vector_size);
            exec_times_bubble[i] = end_bubble - start_bubble;
            printf("Execution of bubble sort with %d elements took %lf \n", curr_vector_size, exec_times_bubble[i]);
            printf("Bubble Sorted vector \n");
            print_vector(unsorted, curr_vector_size);
            printf("\n");
        }

        // --- INSERTION SORT ---
        if (curr_vector_size <= 10000) {
            memcpy(unsorted, vector, curr_vector_size * sizeof(int));
            double start_insertion = get_wall_time();
            insertion_sort(unsorted, curr_vector_size);
            double end_insertion = get_wall_time();
            verifier(unsorted, curr_vector_size);
            exec_times_insertion[i] = end_insertion - start_insertion;
            printf("Execution of insertion sort with %d elements took %lf \n", curr_vector_size, exec_times_insertion[i]);
            printf("Insertion Sorted vector \n");
            print_vector(unsorted, curr_vector_size);
            printf("\n");
        }

        // --- STANDARD MERGE SORT ---
        memcpy(unsorted, vector, curr_vector_size * sizeof(int));
        double start_merge = get_wall_time();
        merge_sort(unsorted, 0, curr_vector_size-1);
        double end_merge = get_wall_time();
        verifier(unsorted, curr_vector_size);
        exec_times_merge[i] = end_merge - start_merge;
        printf("Execution of merge sort with %d elements took %lf \n", curr_vector_size, exec_times_merge[i]);
        printf("Merge Sorted vector \n");
        print_vector(unsorted, curr_vector_size);
        printf("\n");

        // --- MERGE NOALLOC ---
        memcpy(unsorted, vector, curr_vector_size * sizeof(int));
        memcpy(sorted_temp, vector, curr_vector_size * sizeof(int));
        double start_noalloc = get_wall_time();
        merge_sort_noalloc(unsorted, 0, curr_vector_size-1, sorted_temp);
        double end_noalloc = get_wall_time();
        verifier(sorted_temp, curr_vector_size);
        exec_times_merge_noalloc[i] = end_noalloc - start_noalloc;
        printf("Execution of merge_noalloc sort with %d elements took %lf \n", curr_vector_size, exec_times_merge_noalloc[i]);
        printf("Merge Noalloc Sorted vector \n");
        print_vector(sorted_temp, curr_vector_size);
        printf("\n");

        // --- MERGE NOALLOC OPT ---
        memcpy(unsorted, vector, curr_vector_size * sizeof(int));
        memcpy(sorted_temp, vector, curr_vector_size * sizeof(int));
        double start_noalloc_opt = get_wall_time();
        merge_sort_noalloc_opt(unsorted, 0, curr_vector_size-1, sorted_temp);
        double end_noalloc_opt = get_wall_time();
        verifier(sorted_temp, curr_vector_size);
        exec_times_merge_noalloc_opt[i] = end_noalloc_opt - start_noalloc_opt;
        printf("Execution of merge_noalloc_opt sort with %d elements took %lf \n", curr_vector_size, exec_times_merge_noalloc_opt[i]);
        printf("Merge Noalloc Opt Sorted vector \n");
        print_vector(sorted_temp, curr_vector_size);
        printf("\n");

        // --- MERGE NOALLOC OPT PARALLEL ---
        memcpy(unsorted, vector, curr_vector_size * sizeof(int));
        memcpy(sorted_temp, vector, curr_vector_size * sizeof(int));
        double start_noalloc_opt_par = get_wall_time();
        merge_sort_noalloc_opt_par(unsorted, 0, curr_vector_size-1, sorted_temp);
        double end_noalloc_opt_par = get_wall_time();
        verifier(sorted_temp, curr_vector_size);
        exec_times_merge_noalloc_opt_par[i] = end_noalloc_opt_par - start_noalloc_opt_par;
        printf("Execution of merge_noalloc_opt_par sort with %d elements took %lf \n", curr_vector_size, exec_times_merge_noalloc_opt_par[i]);
        printf("Merge Noalloc Opt Par Sorted vector \n");
        print_vector(sorted_temp, curr_vector_size);
        printf("\n");

        // --- PINGPONG ---
        double start_pingpong = get_wall_time();
        merge_pingpong(vector, curr_vector_size);
        double end_pingpong = get_wall_time();
        verifier(vector, curr_vector_size);
        exec_times_pingpong[i] = end_pingpong - start_pingpong;
        printf("Execution of pingpong sort with %d elements took %lf \n", curr_vector_size, exec_times_pingpong[i]);
        printf("Pingpong Sorted vector \n");
        print_vector(vector, curr_vector_size);
        printf("\n");

        free(vector);
        free(unsorted);
        free(sorted_temp);
    }

    FILE *fp1 = fopen("bubble_exec_times.txt", "w");
    FILE *fp2 = fopen("insertion_exec_times.txt", "w");
    FILE *fp3 = fopen("merge_exec_times.txt", "w");
    FILE *fp4 = fopen("merge_noalloc_exec_times.txt", "w");
    FILE *fp5 = fopen("merge_pingpong_exec_times.txt", "w");
    FILE *fp6 = fopen("merge_noalloc_opt_exec_times.txt", "w");
    FILE *fp7 = fopen("merge_noalloc_opt_par_exec_times.txt", "w");

    for(int i = 0; i < n_elements_size; i++){
        if (n_elements[i] <= 10000) {
            fprintf(fp1,"%d\t%lf \n", n_elements[i], exec_times_bubble[i]);
            fprintf(fp2,"%d\t%lf \n", n_elements[i], exec_times_insertion[i]);
        }
        fprintf(fp3,"%d\t%lf \n", n_elements[i], exec_times_merge[i]);
        fprintf(fp4,"%d\t%lf \n", n_elements[i], exec_times_merge_noalloc[i]);
        fprintf(fp5,"%d\t%lf \n", n_elements[i], exec_times_pingpong[i]);
        fprintf(fp6,"%d\t%lf \n", n_elements[i], exec_times_merge_noalloc_opt[i]);
        fprintf(fp7,"%d\t%lf \n", n_elements[i], exec_times_merge_noalloc_opt_par[i]);
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    fclose(fp6);
    fclose(fp7);

    system("gnuplot merge_plot.gp");

    return 0;
}

void bubble_sort(int* input_vector, int vector_size){
    if (input_vector == NULL || vector_size == 0){
        printf("provide a valid vector or a size > 0 \n");
    }else{
        //iteration until fully sorted (n-1)
        for(int i = 0; i < vector_size-1; i++){
            //iteration on progressively smaller parts of array
            for(int j = 0; j < vector_size-i-1; j++){
                if(input_vector[j+1] < input_vector[j]){
                    //swap
                    int tmp = input_vector[j];
                    input_vector[j] = input_vector[j+1];
                    input_vector[j+1] = tmp;
                }
            }
        }
    }
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


void print_vector(int* input_vector, int vector_size){
    // for(int i = 0; i < vector_size; i++){
    //     printf("%d ", input_vector[i]);
    // }
    // printf("\n");
}


void verifier(int* input_vector, int vector_size){
    for (int i = 0; i < vector_size - 1; i++) {
        if (input_vector[i + 1] < input_vector[i]) {

            fprintf(stderr, "Error at index %d \n", i); 
            return;
        }
    }
}

int* generate_random_vector(int size) {
    int *vector = malloc(size * sizeof(int));
    for (int j = 0; j < size; j++){
        vector[j] = rand() % 10001;
    }
    printf("Unsorted vector \n");
    print_vector(vector, size);
    return vector;
}

void merge_sort_noalloc_opt_par(int* unsorted, int p, int r, int* sorted){
    if (unsorted == NULL || sorted == NULL){
        printf("provide a valid vector or a size > 0 \n");
    }else{
        int curr_size = r + 1 - p;

        if(curr_size < 16){ //if the vector is smaller than 16 elements call insertion sort instead of the recursive function
            for(int i = p; i <= r; i++) {
                sorted[i] = unsorted[i];
            }
            insertion_sort(sorted + p, r + 1 - p);
        }else{
            if(p<r){
                int q = (p+r)/2;

                if(curr_size > 10000){

                    //prepare data for thread spawning
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

void* merge_sort_thread_worker(void* arg){

    sorting_data* data = (sorting_data*) arg;

    merge_sort_noalloc_opt_par(data->sorted, data->p, data->r, data->unsorted);

    free(data);

    return NULL;
}