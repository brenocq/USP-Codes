#include <stdlib.h>
#include <stdio.h>
#include "relatorio.h"


int main(int argc, char const *argv[]) {
    Registros *registro = registro_criar();// Cria um registro vazio
    int id;// Auxiliar para receber o id do aluno
    float horasDeEstudo;// Auxiliar para receber as horas de estudo
    float nota1, nota2;// Auxiliares para receber as notas digitadas
    int funcao;// Auxiliar para receber a função desejada
  while(1){
    printf("\n\n\n----- MENU -----\n");
    printf("Escolha uma das funções abaixo colocando o número correspondente:\n");
    printf("Função 1: Inserir Registro\n");
    printf("Função 2: Remover Registro\n");
    printf("Função 3: Imprimir Registros\n");
    printf("Função 4: Relatório de Aprovação\n");
    printf("Função 5: Horas de Estudo\n");
    printf("Função 6: Sair\n");
    printf("\nSua escolha: ");
    scanf("%d", &funcao);
    switch(funcao){
      case 1:
            printf("\n\n\n----- Inserir Registro -----\n");
            printf("Insira os dados do aluno abaixo\n");
            printf("Id: ");
            scanf("%d", &id);
            printf("Horas de estudo: ");
            scanf("%f", &horasDeEstudo);
            printf("Primeira nota: ");
            scanf("%f", &nota1);
            printf("Segunda nota: ");
            scanf("%f", &nota2);
            Aluno* aluno = aluno_criar(id,horasDeEstudo,nota1,nota2);
            if(registro_inserir(registro, aluno)==true){
                printf("Aluno adicionado com sucesso.\n");
            }else{
                printf("Erro ao inserir. Por favor tente novamente.\n");
            }
            break;
      case 2:
            printf("\n\n\n----- Remover Registro -----\n");
            printf("Insira id do aluno para remover: ");
            scanf("%d", &id);
            if(registro_remover(registro, id)==true){
                printf("Aluno removido com sucesso.\n");
            }else{
                printf("Erro ao remover. Por favor tente novamente.\n");
            }
          break;

      case 3:
            printf("\n\n\n----- Imprimir Registros -----\n");
            if(registro_vazio(registro)){
              printf("Não há alunos cadastrados.\n");
            }else{
              registro_imprimir(registro);
            }
          break;

      case 4:
            printf("\n\n\n----- Relatório de Aprovações -----\n");
            if(registro_vazio(registro)){
              printf("Não há alunos cadastrados.\n");
            }else{
              registro_imprimir(registro);
              relatorio_de_aprovacoes(registro);
            }
          break;

      case 5:
            printf("\n\n\n----- Horas de Estudo -----\n");
            if(registro_vazio(registro)){
              printf("Não há alunos cadastrados.\n");
            }else{
              horas_de_estudo(registro);
            }
          break;

      case 6:
            printf("\n\n\n----- Sair -----\n");
            registro_deletar(&registro);
            printf("Registros deletados. Encerrando o programa...\n");
            exit(1);
    }
  }
  return 0;
}
