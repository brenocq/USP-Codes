#include "lista.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
  int qtd, val, i;
  LISTA *l = lista_criar(100);// Cria lista para 100 elementos
  scanf("%d", &qtd);// Recebe quantos números serão inseridos

  for (i = 0; i < qtd; i++) {
    scanf("%d", &val);
    // Tenta inserir o número na lista
    if(lista_inserir(l, val)==-1){
      // Mensagem de erro de inserção
      printf("Lista cheia. Impossível realizar o processamento.\n");
      return 0;// Finaliza o programa sem imprimir informações sobre a lista
    }
  }
  lista_imprimir(l);
  return 0;
}
