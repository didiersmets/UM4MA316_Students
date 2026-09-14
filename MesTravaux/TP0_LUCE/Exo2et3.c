#include <stdio.h>

int recursive(int i, int j){
    //retroune la combinaison de j parmi i
    if ( j==0 || j>=i){ // 0 parmi n = 1
        return 1;
    } else {
        return recursive(i-1,j-1)+recursive(i-1,j); //car j-1 parmi i-1 + j parmi i-1 fait j parmi i
    }
}



void pascal_triangle(int n){

    for(int i=0; i<n ; i++){
        for(int j=0; j<=i ; j++){
            printf("%d ", recursive(i,j));
        }
        printf("\n");
    }
    
}



int main(){
    printf("Hello world \n");
    pascal_triangle(10);
    return 0;
}   