#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX 50

struct _item{
  Carro *carro;
  struct _item *prev;
};

struct _pilha{
  Item *topo;
  int tamanho;
};

Pilha* pilha_criar(){
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  if(p != NULL){
    p->topo = NULL;
    p->tamanho = 0;
  }
  return p;
}

Item* item_criar(Carro *c){
  Item *i = (Item *)malloc(sizeof(Item));
  if(i != NULL){
    i->carro = c;
    i->prev = NULL;
  }
  return i;
}

void pilha_deletar(Pilha **p){
  Item *i = (*p)->topo;
  while(n != NULL){
    Item *prox = i->prev;
    free(i);
    n = next;
  }
  free(*p);
  *p = NULL;
}

bool pilha_inserir(Pilha *p, Carro *c){
  if(pilha_cheia) return FALSE;
  Item *i = item_criar(c);
  if(i != NULL){
    i->prev = p->topo;
    p->tamanho++;
    p->topo = i;
    return TRUE;
  }
  return FALSE;
}

Carro* pilha_remover(Pilha *p){
  if(fila_vazia) return NULL;
  Item *i = p->topo;
  p->topo = p->topo->prev;
  i->prev = NULL;
  p->tamanho--;
  return i->carro;
}

bool pilha_vazia(Pilha *p){
  return (p->tamanho == 0);
}

bool pilha_cheia(Pilha *p){
  return (p->tamanho == MAX);
}

Carro* pilha_topo(Pilha *p){
  if(pilha_vazia) return NULL;
  return p->topo->carro;
}

void pilha_checkout(Pilha *p, int horaSaida){

}
