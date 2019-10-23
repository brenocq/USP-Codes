#include <stdlib.h>
#include <stdio.h>
#include "carro.h"
#include "estacionamento.h"


int main(int argc, char const *argv[]) {
  int selecao;
  Estacionamento *e = estacionamento_criar();
  do{
    printf("\n\nO que você deseja fazer?\n");
    printf("1 - Registrar carro\n");
    printf("2 - Imprimir carros\n");
    printf("3 - Sair\n");
    printf("Insira sua resposta: ");
    scanf("%d", &selecao);

    switch (selecao) {
      case 1:{
          // Registrar Carro
        Carro* carro = estacionamento_checkin(e);
        bool disponibilidade;
        if(carro!=NULL){
          estacionamento_checkout(e, carro);
          estacionamento_sorteio(e, carro);
          disponibilidade = estacionamento_disponibilidade(e, carro);
          estacionamento_rejeicao(e, carro, disponibilidade);
        }

      }break;
      case 2:{
          // Imprimir Carros:
          estacionamento_imprimir(e);
      }break;
      case 3:{
          // Sair
          estacionamento_deletar(&e);
          exit(0);
      }default:{
        printf("Esta não é uma opção. Por favor escolha novamente.\n");
      }break;
    }

  }while(selecao!=3);



  return 0;
}
