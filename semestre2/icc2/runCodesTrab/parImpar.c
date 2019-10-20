#include <stdlib.h>
#include <stdio.h>

void quicksort(int vec[], int ini, int fim)
{
  int pivo, aux;
	int i, j;
	i = ini;
	j = fim-1;
	pivo = vec[(ini+fim)/2];
	while(i <= j){
		while(vec[i]<pivo && i<fim){
			i++;
		}
		while(vec[j]>pivo && j>ini){
			j--;
		}
		if(i <= j){
			aux = vec[i];
			vec[i] = vec[j];
			vec[j] = aux;
			i++;
			j--;
		}
	}
	if(j>ini)
		quicksort(vec, ini, j+1);
	if(i<fim)
		quicksort(vec, i, fim);
}


int main(int argc, char const *argv[]) {
  int *vecPar;
  int *vecImpar;
  int sizePar=0;
  int sizeImpar=0;
  int qtd, aux, i;
  scanf("%d", &qtd);
  vecPar = (int*)malloc(sizeof(int)*qtd);
  vecImpar = (int*)malloc(sizeof(int)*qtd);
  while(qtd--){
    scanf("%d", &aux);
    if(aux%2){
      vecImpar[sizeImpar] = aux;
      sizeImpar++;
    }else{
      vecPar[sizePar] = aux;
      sizePar++;
    }
  }

  quicksort(vecPar, 0, sizePar);
  quicksort(vecImpar, 0, sizeImpar);

  for(i =0;i<sizePar;i++){
    printf("%d\n", vecPar[i]);
  }
  for(i =sizeImpar-1;i>=0;i--){
    printf("%d", vecImpar[i]);
    if(i!=0)
    printf("\n");
  }
  free(vecPar);
  free(vecImpar);
  return 0;
}
