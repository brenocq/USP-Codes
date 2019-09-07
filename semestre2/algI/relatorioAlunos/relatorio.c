#include "relatorio.h"
#include <stdlib.h>
#include <stdio.h>

struct _aluno{
  int id;
  float horasDeEstudo;
  float nota1, nota2;
  struct _aluno* prox;
};

struct _registros{
  Aluno *inicio;
  int tamanho;
};

Registros* registro_criar(){
  Registros *r = (Registros*)malloc(sizeof(Registros));
  r->tamanho = 0;

  return r;
}

void registro_deletar(Registros *r){

}

Aluno* aluno_criar(int id, float horasDeEstudo, float nota1, float nota2){
  Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));
  aluno->id = id;
  aluno->horasDeEstudo = horasDeEstudo;
  aluno->nota1 = nota1;
  aluno->nota2 = nota2;

  return aluno;
}

void registro_inserir(Registros *r, Aluno* aluno){
  Aluno* curr = r->inicio;

  // Vai para a ultima posicao
  if(r->tamanho>0){
    while(curr->prox!=NULL){
      curr = curr->prox;
    }
    curr->prox = aluno;
  }else{
    r->inicio = aluno;
  }
  r->tamanho++;
}

int registro_remover(Registros *r, int IDdoAluno){

}

void registro_imprimir(Registros *r){
  Aluno* curr = r->inicio;
  while(curr!=NULL){
    printf("id: %d\n",curr->id);
    curr=curr->prox;
  }
}

void relatorio_de_aprovacoes(Registros *r);
void horas_de_estudo(Registros *r);
