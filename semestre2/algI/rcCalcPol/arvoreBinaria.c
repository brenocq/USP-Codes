#include "arvoreBinaria.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _no{
  char* str;
  bool isOperador;
  struct _no* filhoDir;
  struct _no* filhoEsq;
}No;

struct _arvBin{
  No *raiz;
};

void no_deletar(No *no);
No* no_criar(char* str, bool isOperador);

ArvBin* arv_criar(){
  ArvBin *a = (ArvBin*)malloc(sizeof(ArvBin));
  if(a==NULL){
      printf("Memória cheia, o programa será encerrado.\n");
      exit(1);
  }

  a->raiz = NULL;
  return a;
}

No* no_criar(char* str, bool isOperador){
  No *no = (No*)malloc(sizeof(No));
  if(no==NULL){
      printf("Memória cheia, o programa será encerrado.\n");
      exit(1);
  }
  no->str = str;
  no->isOperador = isOperador;
  return no;
}

void no_deletar(No *no){
  if(no==NULL)
    return;
  if(no->filhoDir!=NULL){
    no_deletar(no->filhoDir);
    free(no->filhoDir);
  }
  if(no->filhoEsq!=NULL){
    no_deletar(no->filhoEsq);
    free(no->filhoEsq);
  }
  free(no->str);
}

void arv_deletar(ArvBin **a){
  no_deletar((*a)->raiz);
  free((*a)->raiz);
  free(*a);
  a = NULL;
}

bool arv_inserir_ordem(No* raiz, No *no){
  // Recursão para achar em que posição deve adicionar o nó que está entrando
  if(raiz->filhoDir!=NULL && raiz->filhoEsq!=NULL && raiz->filhoDir->isOperador==false && raiz->filhoEsq->isOperador==false)
    return false;

  if(raiz->filhoDir==NULL){
    raiz->filhoDir = no;
    return true;
  }else if(raiz->filhoDir->isOperador==false){
    if(raiz->filhoEsq==NULL){
      raiz->filhoEsq = no;
      return true;
    }else{
      return arv_inserir_ordem(raiz->filhoEsq, no);
    }
  }else if(raiz->filhoDir->isOperador==true){
    bool res = arv_inserir_ordem(raiz->filhoDir, no);
    if(res==false){
      if(raiz->filhoEsq==NULL){
        raiz->filhoEsq = no;
        return true;
      }
      else
        if(raiz->filhoEsq->isOperador==false){
          return false;
        }else{
          if(arv_inserir_ordem(raiz->filhoEsq, no))
            return true;
          else
            return false;
        }
    }else{
      return true;
    }
  }
  return false;
}

void arv_inserir(ArvBin *a, char* str){
  char operadores[5] = "+-*/";
  bool isOperador = false;
  int i;

  for (i = 0; i < 5; i++) {
    if(str[0]==operadores[i])
      isOperador=true;
  }

  No *no = no_criar(str, isOperador);

  if(a->raiz == NULL){
    a->raiz = no;
  }else{
    if(!arv_inserir_ordem(a->raiz, no)){
      printf("Não inseriu!!\n");
    }
  }
}

float result_no(No* raiz){
  if(raiz->isOperador==false)
    return atof(raiz->str);
  else{
    float resDir, resEsq;
    resDir = result_no(raiz->filhoDir);
    resEsq = result_no(raiz->filhoEsq);

    switch(raiz->str[0]){
      case '+':
        return resEsq+resDir;
      break;
      case '-':
        return resEsq-resDir;
      break;
      case '*':
        return resEsq*resDir;
      break;
      case '/':
        if(resDir==0)
          return -32000;
        else
          return resEsq/resDir;
      break;
    }
  }
  return -32000;
}

float arv_pos_ordem(ArvBin *a){
  return result_no(a->raiz);
}
