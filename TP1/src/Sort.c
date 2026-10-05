/*1 Tri par insertion */

void insertion_sort (int* A, int n){
    for (int i = 0, i<n, i++){
        int j = i;
        while ((j>0) && (A[j]<A[j-1])){
            int tmp = A[j];
            A[j] = A[j-1];
            A[j-1] = tmp;
            j--;
        }
    }
}

void bubble_sort(int *A, int n){
    for (int i = 0, i<n, i++){
    /*i est le nombre d'elements rangés dans le bon ordre*/
        for (int j = 0, j<n-i, j++){
    /*j est le mec qui porte le plus grand des chiffres sur son dos pour le ranger en lieu et place n-i */
            if (A[j]>A[j+1]){
                int tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
        }

    }
}

void merge_sort(int* A, int* B, int sA, int sB){
    int idxA = 0;
    int idxB = 0;

    for (int idxC = 0; idxC < sA+sB; idxC++){
        
        if ((idxA<sA)&&((idxB==sB)||(A[idxA]<=A[idxB]))){
            C[idxC] = A[idxA ++];
        }
        else{
            C[idxC] = B[idxB++];
        }
    }
}