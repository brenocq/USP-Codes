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

Registros* registro_criar(){
  Registros *r = (Registros*)malloc(sizeof(Registros));
  if(r==NULL)
    return NULL;
  r->inicio = NULL;
  r->fim = NULL;
  r->tamanho = 0;

  return r;
}

void registro_deletar(Registros *r){
    Aluno* curr = r->inicio;
    Aluno* prox;
    while(curr!=NULL){
        prox = curr->prox;
        free(curr);
        curr = prox;
    }
    free(r);
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

void registro_inserir(Registros *r, Aluno* aluno){
  if(r->tamanho>0){
    r->fim->prox = aluno;
  }else{
    r->inicio = aluno;
  }

  r->fim = aluno;
  r->tamanho++;
}

int registro_remover(Registros *r, int IDdoAluno){
    // TODO função não está funcionando
    Aluno* prev = NULL;
    Aluno* curr = r->inicio;
    int i=0;
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

Aluno* registro_busca(Registros *r, int IDdoAluno){
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

void registro_imprimir(Registros *r){
  Aluno* curr = r->inicio;
  while(curr!=NULL){
    printf("id: %d\n",curr->id);
    curr=curr->prox;
  }
}

void relatorio_de_aprovacoes(Registros *r);
void horas_de_estudo(Registros *r);
