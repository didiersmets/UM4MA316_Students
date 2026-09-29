#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int*T, int n)
{
	int temp;

        for (int i=0; i<n-1; i++)
        {
		for (int j; j<n-1-i; j++) {
			
			if (T[j] > T[j+1]) {
				
				temp = T[j];
				T[j] = T[j+1];
				T[j+1] = temp;
			}
		}
	}
}

void insertion_sort(int*T, int n)
{
	int temp;
	int j;

	for (int i; i<n; i++) {

		temp = T[i];
		j = i-1;

		while (j>=0 && T[j]>temp) {

			T[j+1] = T[j];
			j--;
		}
		T[j+1] = temp;
	}
}

void merge(int*T, int p, int q, int r)
{
	int n1 = q-p +1;
	int n2 = r-q;
	int *G = malloc(n1*sizeof(int));
	int *D = malloc(n2*sizeof(int));

	for(int i; i<n1; i++) {

		G[i] = T[p+i];
	}

	for(int j; j<n2; j++) {

		D[j] = T[q+1+j];
	}

	int i = 0;
	int j = 0;
	int k = p;

	while (i<n1 && j<n2) {

		if (G[i]<=D[j]) {

			T[k] = G[i];
			i++;
		} else {

			T[k] = D[j];
			j++;
		}

		k++;
	}

	while (i<n1) {

		T[k] = G[i];
		i++;
		k++;
	}

	while (j<n1) {

		T[k] = D[j];
		j++;
		k++;
	}

	free(G);
	free(D);
}

void merge_sort(int*T, int p, int r)
{
	if (p<r) {

		int q = (p+r)/2;

		merge_sort(T, p, q);
		merge_sort(T, (q+1), r);

		merge(T, p, q, r);
	}
}





