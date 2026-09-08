#include <stdio.h>

int recursive(int i, int j){
    if ( j==0 || j>=i){
        return 1;
    } else {
        return recursive(i-1,j-1)+recursive(i-1,j);
    }
}



void pascal_triangle(int n){

    for(int i=0; i<n ; i++){
        for(int j=0; j<=i ; j++){
            printf("%d", recursive(i,j));
        }
        printf("\n");
    }
    
}



int main(){
    printf("Hello world \n");
    pascal_triangle(10);
    return 0;
}   