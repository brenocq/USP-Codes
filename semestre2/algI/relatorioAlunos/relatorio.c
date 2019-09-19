#include "relatorio.h"
#include <stdlib.h>
#include <stdio.h>

struct _aluno{
    int id;
    float horasDeEstudo;
    float nota1, nota2;
    struct _aluno* prox;
    struct _aluno* prev;
};

struct _registros{
    Aluno *cabeca;
    Aluno *fim;
    int tamanho;
};

bool registro_vazio(Registros* r){
    return(r->cabeca->prox == NULL);
}

bool registro_cheio(Registros* r){
    return(r->tamanho == TAM_MAX);
}

Registros* registro_criar(void){
    // Criar um registro vazio
    Registros *r = (Registros*)malloc(sizeof(Registros));
    if(r==NULL){
      printf("Não foi possível criar o registro, memória cheia.\n");
      return NULL;
    }
    Aluno *cabeca = aluno_criar(-1,0,0,0);
    r->cabeca = cabeca;
    r->fim = NULL;
    r->tamanho = 0;
    return r;
}

Aluno* aluno_criar(int id, float horasDeEstudo, float nota1, float nota2){
    // Cria elemento de aluno
    Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));
    if(aluno==NULL){
      printf("Não foi possível criar Aluno de id %d, memória cheia.\n", id);
      return NULL;
    }

    aluno->id = id;
    aluno->horasDeEstudo = horasDeEstudo;
    aluno->nota1 = nota1;
    aluno->nota2 = nota2;
    aluno->prox = NULL;
    aluno->prev = NULL;

    return aluno;
}

Aluno *registro_busca(Registros *r, int IDdoAluno){
    // Retorna o primeiro aluno com este ID
    Aluno* curr = r->cabeca->prox;

    if(r==NULL){
      return NULL;
    }
    while(curr!=NULL){
        if(curr->id==IDdoAluno){
            return curr;
        }
        curr=curr->prox;
    }
    return NULL;
}

bool registro_inserir(Registros *r, Aluno* aluno){//funcao 1
  // Insere novo aluno nos registros
  if(r==NULL || aluno==NULL){
    return false;
  }
  if(!registro_cheio(r)){
      if(!registro_vazio(r)){
        r->fim->prox = aluno;
        aluno->prox = NULL;
        aluno->prev = r->fim;
      }else{
        r->cabeca->prox = aluno;
        aluno->prox = NULL;
        aluno->prev = r->cabeca;
      }
  }
  r->fim = aluno;
  r->tamanho++;
  return true;
}

bool registro_remover(Registros *r, int IDdoAluno){//funcao 2
    // Remove aluno dos registros
    if(r==NULL){
      return false;
    }

    Aluno *aluno = registro_busca(r, IDdoAluno);
    if(aluno==NULL)
      return false;

    if(aluno==r->fim){
        r->fim = aluno->prev;
        r->fim->prox = NULL;
    }else{
        aluno->prev->prox = aluno->prox;
        aluno->prox->prev = aluno->prev;
    }
    aluno->prev = NULL;
    aluno->prox = NULL;
    free(aluno);

    r->tamanho--;
    return true;
}

void registro_imprimir(Registros *r){//funcao 3
  // Imprime todas as informações registradas
  Aluno* curr = r->cabeca->prox;
  if(r!=NULL){
    while(curr!=NULL){
      printf("ID: %d\n",curr->id);
      printf("Horas de estudo: %.1f\n", curr->horasDeEstudo);
      printf("Nota da primeira avaliação: %.1f\n", curr->nota1);
      printf("Nota da segunda avaliação: %.1f\n", curr->nota2);
      printf("\n");
      curr=curr->prox;
    }
  }
  else
    printf("Não há registros.\n");
}

void relatorio_de_aprovacoes(Registros *r){//funcao 4
  Aluno* curr = r->cabeca->prox;
  if(r!=NULL){
    while(curr!=NULL){
      printf("id: %d -> ",curr->id);
      if((curr->nota1 + curr->nota2)/2 >= 5)
          printf("APROVADO.");
      else
          printf("REPROVADO.");
      printf("\n");
      curr=curr->prox;
    }
  }
  else
    printf("Não há registros.\n");
}

void horas_de_estudo(Registros *r){//funcao 5
  // Imprimi a quantidade de horas de estudo
  Aluno *curr = r->cabeca->prox;
  int qntdAlunos = 0;
  float somaDasNotas = 0;
  if(r!=NULL){
    while(curr!=NULL){
      somaDasNotas += curr->horasDeEstudo;
      qntdAlunos++;
      curr = curr->prox;
    }
    printf("Tempo médio de estudo da turma: %.2f horas.\n", somaDasNotas/qntdAlunos);
  }
  else
    printf("Não há registros.\n");
}

bool registro_deletar(Registros **r){//funcao 6
  // Deleta o registro
  if((*r)==NULL){
    return false;
    printf("Não foi possível deletar os registros.\n");
  }
    Aluno* curr = (*r)->cabeca;
    Aluno* prox;
    while(curr!=NULL){
        prox = curr->prox;
        free(curr);
        curr = prox;
    }
    free(*r);
    (*r) = NULL;
    return true;
}
