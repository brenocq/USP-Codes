#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX 5

struct _itemPilha{
  Carro *carro;
  struct _itemPilha *prev;
};

typedef struct _itemPilha ItemPilha;

struct _pilha{
  ItemPilha *topo;
  int tamanho;
};

ItemPilha* item_pilha_criar(Carro *c);

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
  *p = NULL;
}

int pilha_tamanho(Pilha *p){
    return p->tamanho;
}

ItemPilha* item_pilha_criar(Carro *c){
    ItemPilha* item = (ItemPilha*)malloc(sizeof(ItemPilha));
    if(item==NULL){
        printf("Memória cheia, o programa será encerrado.\n");
        exit(1);
    }

    item->carro = c;
    item->prev = NULL;
    return item;
}

bool pilha_inserir(Pilha *p, Carro *c){
  if(pilha_cheia(p)) return false;
  ItemPilha *i = item_pilha_criar(c);
  if(i != NULL){
    i->prev = p->topo;
    p->tamanho++;
    p->topo = i;
    return true;
  }
  return false;
}

Carro* pilha_remover(Pilha *p){
  if(pilha_vazia(p)) return NULL;
  ItemPilha *i = p->topo;
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
void pilha_imprimir(Pilha *p);
Carro* pilha_topo(Pilha *p){
  if(pilha_vazia(p)) return NULL;
  return p->topo->carro;
}

void pilha_checkout(Pilha *p, int horaSaida){

  while(pilha_topo(p)!=NULL && carro_get_hSaida(pilha_topo(p))<=horaSaida){
      printf("\nCarro saindo do pátio 1: ");
      carro_imprimir(pilha_remover(p));
  }
}

bool pilha_busca(Pilha *p, int placa){
  ItemPilha *curr = p->topo;
  while(curr != NULL){
    if(carro_get_placa(curr->carro) == placa) return true;
    curr = curr->prev;
  }
  return false;
}

void pilha_imprimir(Pilha *p){
    ItemPilha* curr = p->topo;
    while(curr!=NULL){
        carro_imprimir(curr->carro);
        curr = curr->prev;
    }
}

void pilha_sorteio(Pilha *p, int index){
    ItemPilha* curr = p->topo;
    int cont=0;
    while(cont<index){
        curr=curr->prev;
        cont++;
    }
    carro_set_desconto(curr->carro, 0.1);
}
