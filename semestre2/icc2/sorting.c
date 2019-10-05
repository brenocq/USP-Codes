#include <stdlib.h>
#include <stdio.h>

using namespace std;

void shellSort(int *vec);
void quicksort(int *vec, int began, int end);
void mergeSort(int *vec, int subVecSize);
void bubbleSort(int *vec);

#define SIZE 10
int main(int argc, char const *argv[]) {
  int vec[SIZE]={9,8,7,6,5,4,3,2,1,0};

  for (int i = 0; i < SIZE; i++)
    printf("%s%d%s",i==0?"(":"",vec[i],i==SIZE-1?")\n":", ");
  
  //bubbleSort(vec);
  //quicksort(vec, 0, SIZE);
  shellSort(vec);

  for (int i = 0; i < SIZE; i++)
    printf("%s%d%s",i==0?"(":"",vec[i],i==SIZE-1?")\n":", ");

  return 0;
}

void bubbleSort(int *vec){
  // Melhor caso: ordenado O(n)
  // Pior caso: inversamente ordenado O(n^2)
  // Aprimorado
  int aux;
  int troca = 1;
  for (int i = SIZE-1; i>=1 && troca ; i--){
    troca = 0;
    for (int j = 0; j < i; j++){
      troca = 1;
      if(vec[j]>vec[j+1]){
        aux = vec[j];
        vec[j] = vec[j+1];
        vec[j+1] = aux;
      }
    }
  }
}


void quicksort(int *vec, int began, int end) {
  // Melhor caso: divide no meio (nlogn)
  // Pior caso: divide uma sublista com 0 e outra com n-1 (n^2)
	int i, j, pivo, aux;
	i = began;
	j = end-1;
	pivo = vec[(began + end) / 2];
	while(i <= j)
	{
		while(vec[i] < pivo && i < end)
		{
			i++;
		}
		while(vec[j] > pivo && j > began)
		{
			j--;
		}
		if(i <= j)
		{
			aux = vec[i];
			vec[i] = vec[j];
			vec[j] = aux;
			i++;
			j--;
		}
	}
	if(j > began)
		quicksort(vec, began, j+1);
	if(i < end)
		quicksort(vec, i, end);
}

void shellSort(int *vec){
  // Melhor caso: vetor ordenado O(n)
  // Pior caso: vetor inversamente ordenado O(n^2)
  int i,j,x;
  for(i=1;i<SIZE;i++){
    x=vec[i];
    j = i-1;
    while(j>=0 && x<vec[j]){
      vec[j+1]=vec[j];
      j--;
    }
    vec[j+1]=x;
  }
}

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 

        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 

        merge(arr, l, m, r); 
    } 
} 