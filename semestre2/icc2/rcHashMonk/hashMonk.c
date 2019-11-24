#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

#define SIZE 100
#define EMPTY -32000

Lista* hash[SIZE];

void insert(int val, char nome[26]);
char* search(int val);
void print();

int main(int argc, char const *argv[]) {
  int i, qtd, aux;
  char nome[26];
  for (i = 0; i < SIZE; i++) {
    hash[i]=lista_criar();
  }

  scanf("%d", &qtd);

  for (i = 0; i < qtd; i++) {
    scanf("%d", &aux);
    scanf("%s", nome);
    insert(aux, nome);
  }

  scanf("%d", &qtd);

  for (i = 0; i < qtd; i++) {
    scanf("%d", &aux);
    char* res = search(aux);
    //printf("%s\n",res);
  }

  return 0;
}

void insert(int val, char nome[26]){
  int hashKey = val%SIZE;
  Item* item = item_criar(nome);
  lista_inserir(hash[hashKey], item);
}

char* search(int val){
  int hashKey = val%SIZE;
  printf("1!\n");
  char* res = lista_busca(hash[hashKey],val);
  printf("2!\n");
  return res;
}
