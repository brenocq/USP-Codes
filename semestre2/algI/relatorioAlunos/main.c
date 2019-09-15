#include <stdlib.h>
#include <stdio.h>
#include "relatorio.h"


int main(int argc, char const *argv[]) {
  while(1){
    int funcao;
    printf("MENU\n");
    printf("Escolha uma das funções abaixo colocando o número correspondente:\n);
    printf("Função 1: Inserir Registro\n");
    printf("Função 2: Remover Registro\n");
    printf("Função 3: Imprimir Registros\n");
    printf("Função 4: Relatório de Aprovação\n");
    printf("Função 5: Horas de Estudo\n");
    printf("Função 6: Sair\n");
    switch(scanf("%d", &funcao)){
      case 1: 
      
          break;
      case 2:
      
          break;
      
      case 3:
      
          break;
      
      case 4:
      
          break;
      
      case 5:
      
          break;
      
      case 6:
      
          exit(1);
    }
  }
  Registros *registro = registro_criar();
  Aluno* aluno1 = aluno_criar(0,5,10,9);
  Aluno* aluno2 = aluno_criar(4,5,10,9);
  Aluno* aluno3 = aluno_criar(1,5,10,9);

  registro_inserir(registro, aluno1);
  registro_inserir(registro, aluno3);
  registro_remover(registro, 1);
  registro_remover(registro, 0); 
  registro_inserir(registro, aluno2);

  registro_imprimir(registro);

  registro_deletar(registro);
  return 0;
}
