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
  Aluno *fim;
  int tamanho;
};

Registros* registro_criar(void){
  Registros *r = (Registros*)malloc(sizeof(Registros));
  if(r==NULL)
    return NULL;
  r->inicio = NULL;
  r->fim = NULL;
  r->tamanho = 0;
  return r;
}

void registro_deletar(Registros *r){//funcao 6
    Aluno* curr = (Aluno *)malloc(sizeof(Aluno);
    curr = r->inicio;
    Aluno* prox = (Aluno *)malloc(sizeof(Aluno);
    while(curr!=NULL){
        prox = curr->prox;
        free(curr);
        Aluno* curr = (Aluno *)malloc(sizeof(Aluno);
        curr = prox;
    }
    free(r);
    free(curr);
    free(prox);
    exit(1);                                 
}

Aluno* aluno_criar(int id, float horasDeEstudo, float nota1, float nota2){
  Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));
  if(aluno==NULL)
    return NULL;
  aluno->id = id;
  aluno->horasDeEstudo = horasDeEstudo;
  aluno->nota1 = nota1;
  aluno->nota2 = nota2;

  return aluno;
}

void registro_inserir(Registros *r, Aluno* aluno){//funcao 1
  if(r->tamanho>0){
    r->fim->prox = aluno;
  }else{
    r->inicio = aluno;
  }

  r->fim = aluno;
  r->tamanho++;
}

int registro_remover(Registros *r, int IDdoAluno){//funcao 2
    // TODO função não está funcionando
    Aluno* prev = (Aluno *)malloc(sizeof(Aluno); 
    prev = NULL;
    Aluno* curr = (Aluno *)malloc(sizeof(Aluno); 
    curr = r->inicio;
    int i = 0;
    char encontrou = 0;
    for (i = 0; i < r->tamanho; i++) {
        if(curr->id == IDdoAluno){
            if(curr==r->inicio){
                r->inicio = curr->prox;
            }else if(curr==r->fim){
                r->fim = prev;
                r->fim->prox = NULL;
            }else{
                prev->prox = curr->prox;
                curr->prox = NULL;
            }
            curr->prox = NULL;
            free(curr);
        }
        prev = curr;
        curr = curr->prox;
    }
    r->tamanho--;
    return encontrou;
}

Aluno *registro_busca(Registros *r, int IDdoAluno){
    Aluno* curr = r->inicio;
    int i;
    if(r!=NULL){
        while(curr!=NULL){
            if(curr->id==IDdoAluno){
                return curr;
            }
            curr=curr->prox;
        }
    }
    return NULL;
}

void registro_imprimir(Registros *r){//funcao 3
  Aluno* curr = r->inicio;
  if(r!=NULL){
    while(curr!=NULL){
      printf("id: %d\n",curr->id);
      printf("Horas de estudo: %f\n", curr->horasDeEstudo);
      printf("Nota da primeira avaliação: %f\n", curr->nota1);
      printf("Nota da segunda avaliação: %f\n", curr->nota2);
      printf("\n");
      curr=curr->prox;
    }
  }
  else 
    printf("Não há registros.\n");
}

void relatorio_de_aprovacoes(Registros *r);//funcao 4
void horas_de_estudo(Registros *r){//funcao 5
  Aluno *curr;
  curr = (Aluno *)malloc(sizeof(Aluno));
  curr = r->inicio;
  int qntdAlunos = 0;
  float somaDasNotas = 0;
  if(r!=NULL){
    while(curr!=NULL){
      somaDasNotas += curr->horasDeEstudo;
      qntdAlunos++;
      curr = curr->prox;
    }
    printf("Tempo médio de estudo da turma: %f.\n", somaDasNotas/qntdAlunos);
  }
  else
    printf("Não há registros."\n);
}
