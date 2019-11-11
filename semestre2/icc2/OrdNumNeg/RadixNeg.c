#include <stdio.h>
#include <stdlib.h>

void radixSort(int vec[], int tamanho);
void radixSortNeg(int vec[], int tamanho);

int main(int argc, char const *argv[]) {
  int i;
  int tamanho;
  int aux;
  scanf("%d", &tamanho);
  int *vec = (int*)malloc(sizeof(int)*tamanho);

  for (i = 0; i < tamanho; i++) {
    scanf("%d", &aux);
    vec[i] = aux;
  }

  radixSortNeg(vec, tamanho);

  for (i = 0; i < tamanho; i++) {
    printf("%d ", vec[i]);
  }
  printf("\n");

  free(vec);
  return 0;
}

void radixSortNeg(int vec[], int tamanho){
  int i;
  int tamPos=0, tamNeg=0;
  int *vecPos = (int*)malloc(sizeof(int)*tamanho);
  int *vecNeg = (int*)malloc(sizeof(int)*tamanho);

  for(i=0;i<tamanho;i++){
    if(vec[i]>=0){
      vecPos[tamPos++]= vec[i];
    }else{
      vecNeg[tamNeg++]=-vec[i];
    }
  }
  radixSort(vecPos, tamPos);
  radixSort(vecNeg, tamNeg);
  for (i = tamNeg-1; i >=0; i--) {
    vec[(tamNeg-1)-i]=-vecNeg[i];
  }
  for (i = 0; i < tamPos; i++) {
    vec[tamNeg++]=vecPos[i];
  }
  free(vecPos);
  free(vecNeg);
}

void radixSort(int vec[], int tamanho) {
    int i;
    int *b;
    int maior = vec[0];
    int exp = 1;

    b = (int *)calloc(tamanho, sizeof(int));

    for (i = 0; i < tamanho; i++) {
        if (vec[i] > maior)
    	    maior = vec[i];
    }

    while (maior/exp > 0) {
        int buffer[10] = { 0 };
    	for (i = 0; i < tamanho; i++)
    	    buffer[(vec[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    buffer[i] += buffer[i - 1];
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--buffer[(vec[i] / exp) % 10]] = vec[i];
    	for (i = 0; i < tamanho; i++)
    	    vec[i] = b[i];
    	exp *= 10;
    }

    free(b);
}
