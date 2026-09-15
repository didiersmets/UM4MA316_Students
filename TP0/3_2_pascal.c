#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000 // The hardcoded, fixed maximum size

#define get_index(i,j) (((i) * (n)) + (j))
//NB
// #define get_index(i,j) ((i * n) + j) this fails to protect the parenthesis as if i is changed to 4-1 it will do 4-1*n and change the order of ops

int main(int argc, char *argv[]){
    //declare the number
    

    if (argc < 2){
        printf("Please only provide one interger as input \n");
        return 0;
    }else{
        int n = atoi(argv[1]);
        printf("Your input no is: %d \n", n);
        printf("Now generating pascal triangle of size: %d \n", n);
        
        //if input is larger than 1000 exit
        if( n > MAX_SIZE){
            printf("please enter n<=1000\n");
            return 0;
        }

        //int triangle[MAX_SIZE][MAX_SIZE];
        int *triangle = malloc(n*n*sizeof(int));

        if(triangle != NULL){
            
            for(int i = 0; i < n; i++){
                for(int j = 0; j < i; j++){
                    if( 0 < j && j < i){
                    
                        triangle[get_index(i,j)] = triangle[get_index(i-1,j-1)] + triangle[get_index(i-1,j)];
                        printf(" %d ",triangle[get_index(i,j)]);
                    }else{
                        triangle[get_index(i,j)] = 1;
                        printf(" 1 ");
                    }
                }

            printf("\n");
            
            }
            free(triangle);
        }
    }

    return 0;
}