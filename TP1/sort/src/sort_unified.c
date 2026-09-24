#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void bubble_sort(int* input_vector, int vector_size);
void insertion_sort(int* input_vector, int vector_size);
void merge_sort(int* T, int p, int r);
void merge(int *T, int p, int q, int r);

void merge_pingpong(int* vector, int n);
void merge_sort_noalloc(int* unsorted, int p, int r, int* sorted);
void merge_noalloc(int *unsorted, int p, int q, int r, int* sorted);
void merge_sort_noalloc_opt(int* unsorted, int p, int r, int* sorted);


void print_vector(int* input_vector, int vector_size);
void verifier(int* input_vector, int vector_size);
int* generate_random_vector(int size);

int main(int argc, char *argv[]){
    srand(time(NULL));
    
    int n_elements[] = {10, 20, 50, 100, 200, 500, 1000, 10000};
    int n_elements_size = 8;

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
        memcpy(unsorted, vector, curr_vector_size * sizeof(int));
        clock_t start_bubble = clock();
        bubble_sort(unsorted, curr_vector_size);
        clock_t end_bubble = clock();
        verifier(unsorted, curr_vector_size);
        exec_times_bubble[i] = (double)(end_bubble - start_bubble) / CLOCKS_PER_SEC;
        printf("Execution of bubble sort with %d elements took %lf \n", curr_vector_size, exec_times_bubble[i]);
        printf("Bubble Sorted vector \n");
        print_vector(unsorted, curr_vector_size);
        printf("\n");

        // --- INSERTION SORT ---
        memcpy(unsorted, vector, curr_vector_size * sizeof(int));
        clock_t start_insertion = clock();
        insertion_sort(unsorted, curr_vector_size);
        clock_t end_insertion = clock();
        verifier(unsorted, curr_vector_size);
        exec_times_insertion[i] = (double)(end_insertion - start_insertion) / CLOCKS_PER_SEC;
        printf("Execution of insertion sort with %d elements took %lf \n", curr_vector_size, exec_times_insertion[i]);
        printf("Insertion Sorted vector \n");
        print_vector(unsorted, curr_vector_size);
        printf("\n");

        // --- STANDARD MERGE SORT ---
        memcpy(unsorted, vector, curr_vector_size * sizeof(int));
        clock_t start_merge = clock();
        merge_sort(unsorted, 0, curr_vector_size-1);
        clock_t end_merge = clock();
        verifier(unsorted, curr_vector_size);
        exec_times_merge[i] = (double)(end_merge - start_merge) / CLOCKS_PER_SEC;
        printf("Execution of merge sort with %d elements took %lf \n", curr_vector_size, exec_times_merge[i]);
        printf("Merge Sorted vector \n");
        print_vector(unsorted, curr_vector_size);
        printf("\n");

        // --- MERGE NOALLOC ---
        memcpy(unsorted, vector, curr_vector_size * sizeof(int));
        memcpy(sorted_temp, vector, curr_vector_size * sizeof(int));
        clock_t start_noalloc = clock();
        merge_sort_noalloc(unsorted, 0, curr_vector_size-1, sorted_temp);
        clock_t end_noalloc = clock();
        verifier(sorted_temp, curr_vector_size);
        exec_times_merge_noalloc[i] = (double)(end_noalloc - start_noalloc) / CLOCKS_PER_SEC;
        printf("Execution of merge_noalloc sort with %d elements took %lf \n", curr_vector_size, exec_times_merge_noalloc[i]);
        printf("Merge Noalloc Sorted vector \n");
        print_vector(sorted_temp, curr_vector_size);
        printf("\n");

        // --- MERGE NOALLOC OPT ---
        memcpy(unsorted, vector, curr_vector_size * sizeof(int));
        memcpy(sorted_temp, vector, curr_vector_size * sizeof(int));
        clock_t start_noalloc_opt = clock();
        merge_sort_noalloc_opt(unsorted, 0, curr_vector_size-1, sorted_temp);
        clock_t end_noalloc_opt = clock();
        verifier(sorted_temp, curr_vector_size);
        exec_times_merge_noalloc_opt[i] = (double)(end_noalloc_opt - start_noalloc_opt) / CLOCKS_PER_SEC;
        printf("Execution of merge_noalloc_opt sort with %d elements took %lf \n", curr_vector_size, exec_times_merge_noalloc_opt[i]);
        printf("Merge Noalloc Opt Sorted vector \n");
        print_vector(sorted_temp, curr_vector_size);
        printf("\n");

        // --- PINGPONG ---
        clock_t start_pingpong = clock();
        merge_pingpong(vector, curr_vector_size);
        clock_t end_pingpong = clock();
        verifier(vector, curr_vector_size);
        exec_times_pingpong[i] = (double)(end_pingpong - start_pingpong) / CLOCKS_PER_SEC;
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

    for(int i = 0; i < n_elements_size; i++){
        fprintf(fp1,"%d\t%lf \n", n_elements[i], exec_times_bubble[i]);
        fprintf(fp2,"%d\t%lf \n", n_elements[i], exec_times_insertion[i]);
        fprintf(fp3,"%d\t%lf \n", n_elements[i], exec_times_merge[i]);
        fprintf(fp4,"%d\t%lf \n", n_elements[i], exec_times_merge_noalloc[i]);
        fprintf(fp5,"%d\t%lf \n", n_elements[i], exec_times_pingpong[i]);
        fprintf(fp6,"%d\t%lf \n", n_elements[i], exec_times_merge_noalloc_opt[i]);
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    fclose(fp6);

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

int* generate_random_vector(int size) {
    int *vector = malloc(size * sizeof(int));
    for (int j = 0; j < size; j++){
        vector[j] = rand() % 10001;
    }
    printf("Unsorted vector \n");
    print_vector(vector, size);
    return vector;
}
