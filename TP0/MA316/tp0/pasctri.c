#include <stdio.h>
#include <stdlib.h>

int main(){
    int n = 0;
    int i,j;
    int mem[100000] = {1};
    int temp;
    
    do{
        printf("Insert an integer n:\n");
        scanf("%d", &n);
    }while(n<0);

    printf("here is your pascal triangle of size:%d\n", n);


    for (i = 0; i < n; i++) {        
        for (j = i; j > 0; j--) {           
            mem[j] = mem[j] + mem[j-1];
        }        
        for (j = 0; j <= i; j++) {
            printf("%d ", mem[j]);
        }
        printf("\n");
    }
    return 0;
}

