#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 1000

struct _itemPilha{
  char *str;
  struct _itemPilha *prev;
};

typedef struct _itemPilha ItemPilha;

struct _pilha{
  ItemPilha *topo;
  int tamanho;
};

ItemPilha* item_pilha_criar(char *str);

Pilha* pilha_criar(){
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));

  if(p==NULL){
      printf("Memória cheia, o programa será encerrado.\n");
      exit(1);
  }

  p->topo = NULL;
  p->tamanho = 0;

  return p;
}

void pilha_deletar(Pilha **p){
  ItemPilha *curr = (*p)->topo;
  while(curr != NULL){
    ItemPilha *prox = curr->prev;
    free(curr);
    curr = prox;
  }
  free(*p);
  p = NULL;
}

int pilha_tamanho(Pilha *p){
    return p->tamanho;
}

ItemPilha* item_pilha_criar(char *str){
    ItemPilha* item = (ItemPilha*)malloc(sizeof(ItemPilha));
    if(item==NULL){
        printf("Memória cheia, o programa será encerrado.\n");
        exit(1);
    }

    item->str = str;
    item->prev = NULL;
    return item;
}

bool pilha_inserir(Pilha *p, char *str){
  char* newStr = (char*)malloc(sizeof(char)*(strlen(str)+1));
  if(newStr==NULL){
      printf("Memória cheia, o programa será encerrado.\n");
      exit(1);
  }

  strcpy(newStr, str);

  if(pilha_cheia(p)) return false;
  ItemPilha *i = item_pilha_criar(newStr);
  if(i != NULL){
    i->prev = p->topo;
    p->tamanho++;
    p->topo = i;
    return true;
  }
  return false;
}

char* pilha_remover(Pilha *p){
  if(pilha_vazia(p)) return NULL;
  ItemPilha *i = p->topo;
  p->topo = p->topo->prev;
  i->prev = NULL;
  p->tamanho--;

  char* res = i->str;
  free(i);
  return res;
}

bool pilha_vazia(Pilha *p){
  return (p->tamanho == 0);
}

bool pilha_cheia(Pilha *p){
  return (p->tamanho == MAX);
}
