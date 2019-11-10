#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.h"
#include "arvoreBinaria.h"

int main(int argc, char const *argv[]) {
  Pilha *p = pilha_criar();
  ArvBin *a = arv_criar();
  char *posfixa;// Recebe a string posfixa
  char *aux;// Auxiliar para dividir a string posfixa
  int i;
  float result;

  posfixa = (char*)malloc(sizeof(char)*100);
  aux = (char*)malloc(sizeof(char)*10);
  scanf("%[^\n]s", posfixa);

  // Recebe a equação posfixa e organiza em uma pilha
  for (i = 0; i < int(strlen(posfixa)); i++) {
    if(posfixa[i]==' '){
      pilha_inserir(p, aux);
      aux[0] = '\0';
    }else if(i!=int(strlen(posfixa))-1){
      int currlen = strlen(aux);
      aux[currlen] = posfixa[i];
      aux[currlen+1] = '\0';
    }else{
      int currlen = strlen(aux);
      aux[currlen] = posfixa[i];
      aux[currlen+1] = '\0';
      pilha_inserir(p, aux);
    }
  }

  // Cria a arvore binaria a partir da pilha
  while(!pilha_vazia(p)){
    arv_inserir(a, pilha_remover(p));
  }

  // Calcula o resultado a partir da arvore binaria
  result = arv_pos_ordem(a);
  if(result==-32000)
    printf("Não foi possível realizar a operação.\n");
  else
    printf("O resultado da operação é %.2f.\n", result);

  pilha_deletar(&p);
  arv_deletar(&a);
  free(posfixa);
  free(aux);
  return 0;
}
