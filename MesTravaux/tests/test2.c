#include <stdio.h>


int facto(int n){
    if (n==1){
        return 1;
    }
    return n*facto(n-1);
}

