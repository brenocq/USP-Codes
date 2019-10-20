#include "stdlib.h"
#include "stdio.h"
#include "lista.h"

int main(int argc, char const *argv[]) {
  int escolha = -1;
  char titulo[41];
  char url[512];
  int pos;

  Lista* lista = lista_criar();

  // Executa até que a escolha seja 4 (sair)
  do{
    scanf("%d", &escolha);
    switch (escolha) {
      case 1:// Inclui nova aba
        scanf("%s", titulo);
        scanf("%s", url);
        Item *item =  item_criar(titulo, url);
        lista_inserir(lista, item, -1);
      break;
      case 2:// Altera posição da aba
        scanf("%s", titulo);
        scanf("%d", &pos);
        lista_troca(lista, titulo, pos);
      break;
      case 3:// Imprimir
        lista_print(lista);
      break;
    }
  }while(escolha!=4);

  // Libera o espaço da memória
  lista_deletar(&lista);

  return 0;
}
