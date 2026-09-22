#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Merge(int* T, int p, int q, int r,int* D){
	int idxA = 0;
	int idxB = 1;
	int sA = q - p + 1;
	int sB = r - q;
	int* C = malloc(sizeof(int)*(r-p+1));

	for(int idxC = 0; idxC < sA + sB ;idxC++){

		if ((idxB == sB+1)|| ((idxA < sA) && (T[p+idxA] <= T[q+idxB] ))){
			C[idxC] = T[p+idxA++];
		}

		else{
			C[idxC] = T[q+idxB++];
		}
	}
	
        memcpy(D+p,C,sizeof(int)*(r-q+1));	
}


/*void MergeSort(int *T, int p, int r){
	if (p<r){
		int* tmp = malloc(sizeof(int)*(r-p+1)); 
		int q = (p+r)/2;
		MergeSort(T,p,q);
		MergeSort(T,q+1,r);
		tmp = Merge(T,p,q,r);
	} on a une routine merge que l'utilisateur verra et triera le tableau par dessus lui meme (faire un malloc que la meme taille que le tableau et le copier dans ce nouveau tableau, puis routine récusive qui prendra un tableau d'entrée et un tableau en sortie. On a deux tableaux le final, la copie, au premier niveau de la récursion le merge final ira de la copie vers l'original
}*/

void merge_sort_recursive(int* C, int p, int r, int* D){
	if (p<r){
                int q = (p+r)/2;
                merge_sort_recursive(D,p,q,C);
                merge_sort_recursive(D,q+1,r,C);
                Merge(C,p,q,r,D);
        }		

}
void merge_sort(int *A, int N){
	int* B = malloc(sizeof(int)*N);
	memcpy(B,A,sizeof(int)*N);
	merge_sort_recursive(B,0,N-1,A);
}

int main(){

        int tab[10]= {6,11,23,54,89,2,4,7,8,45};
        merge_sort(tab,10);
        for(int i = 0;i < 10;i++){
                printf("%d ",tab[i]);
        }
        printf("\n");
        return 0;
}

