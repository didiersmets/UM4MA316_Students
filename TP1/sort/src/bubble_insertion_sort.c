#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void bubble_sort(int* input_vector, int vector_size);
void insertion_sort(int* input_vector, int vector_size);

void print_vector(int* input_vector, int vector_size);
void verifier(int* input_vector, int vector_size);

int main(int argc, char *argv[]){
    srand(time(NULL));
    
    int n_elements[] = {10, 20, 50, 100, 200, 500, 1000};
    int n_elements_size = 7;
    double exec_times[n_elements_size];
    memset(exec_times, 0, sizeof(exec_times));


    int curr_vector_size = 0;
    for(int i = 0; i < n_elements_size; i++){
        curr_vector_size = n_elements[i];
        //generates an array of N random integers
        int *vector = malloc(curr_vector_size * sizeof(int));

        //fill the vector randomly and display it
        for (int j = 0; j < curr_vector_size; j++){
            int el = rand() % 101;
            vector[j] = el;
        }
        printf("Unsorted vector \n");
        print_vector(vector, curr_vector_size);


        // --- SORTING ---

        clock_t start = clock();
        //bubble_sort(vector,curr_vector_size);
        insertion_sort(vector, curr_vector_size);
        clock_t end = clock();
        verifier(vector,curr_vector_size);
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        exec_times[i] = seconds;
        printf("Execution of sort with %d elements took %lf \n", curr_vector_size, seconds);

        printf("Bubble Sorted vector \n");
        print_vector(vector, curr_vector_size);


        printf("\n");
        free(vector);
    }

    FILE *fp = fopen("insertion_exec_times.txt", "w");

    for(int i = 0; i < n_elements_size; i++){
        fprintf(fp,"%d\t%lf \n", n_elements[i], exec_times[i]);
    }


    fclose(fp);


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
                }
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