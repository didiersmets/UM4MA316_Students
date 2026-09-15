#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000 // The hardcoded, fixed maximum size

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

        int triangle[MAX_SIZE][MAX_SIZE];
        

        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                if( 0 < j && j < i){
                    triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
                    printf(" %d ",triangle[i][j]);
                }else{
                    triangle[i][j] = 1;
                    printf(" 1 ");
                }
            }
            printf("\n");

        }
    }

    return 0;
}