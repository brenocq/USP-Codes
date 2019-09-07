#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct _lista{
  int *item;
  int tamanho;// Tamanho atual da lista
  int tamMaximo;// Tamanho máximo da lista
  int qtdComp;// Quantidade de comparações
};

LISTA* lista_criar(int tamanho){
  // Aloca dinamicamente a lista e define o valor de cada variável utilizando o tamanho definido
  LISTA *lista = (LISTA*)malloc(sizeof(LISTA));
  lista->item = (int*)malloc(sizeof(int)*tamanho);
  lista->tamMaximo = tamanho;
  lista->qtdComp = 0;
  return lista;
}

int lista_inserir(LISTA* lista, int num){
  // Tenta inserir mais um número na lista
  // Saída: -1 para erro ao inserir e 1 para operação com sucesso
  int i;
  for(i=0;i<lista->tamanho;i++){// Confere cada elemento ate um repetido (ou o final)
    lista->qtdComp++;// Adiciona mais uma comparacao ao contador
    if(lista->item[i]==num){
      // O número já existe. Termina a função sem inserir
      return 1;
    }
  }

  // Número de elementos ultrapassou o máximo permitido
  if(lista->tamanho==lista->tamMaximo){
    return -1;
  }

  // Adiciona o número com sucesso na lista
  lista->item[lista->tamanho]=num;
  lista->tamanho++;
  return 1;
}

void lista_imprimir(LISTA* lista){
  // Imprimi a lista e informações sobre o tamanho e comparações
  int i;

  for(i=0;i<lista->tamanho;i++){
    printf("%d", lista->item[i]);
    if(i<lista->tamanho-1)
      printf("\t");
    else
      printf("\n");
  }

  printf("Tamanho da lista: %d\n", lista->tamanho);
  printf("Total de comparações: %d\n", lista->qtdComp);
}
