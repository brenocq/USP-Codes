#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX 50

struct _fila{
  Item *frente;
  Item *fundo;// Colocamos um ponteiro para o ultimo para melhorar o cadastro dos carros
  int tamanho;
}

struct _item{
  Carro *carro;
  struct _item *prox;
}

Fila* fila_criar(){
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->frente = NULL;
    fila->fundo = NULL;
    fila->tamanho = 0;
    return fila;
}

Item* item_criar(Carro *c){
    Item* item = (Item*)malloc(sizeof(Item));
    item->carro = c;
    item->prox = NULL;
    return item;
}

void fila_deletar(Fila **f){
    Item* curr = *f->frente;
    while(curr!=NULL){
        Item* prox = curr->prox;
        free(curr);
        curr = prox;
    }
    free(*f);
}

bool fila_inserir(Fila *f, Carro* carro){
    if(fila_cheia(f))
        return false;

    Item* novo = item_criar(carro);

    if(novo==NULL)
        return false;

    if(f->frente==NULL){
        f->frente = novo;
        f->fundo = novo;
    }else{
        f->fundo->prox = novo;
        f->fundo = novo;
    }
    f->tamanho++;

    return true;
}

Carro* fila_remover(Fila *f){
    if(fila_vazia(f))
        return NULL;

    Carro* res = fila->frente;

    fila->frente = fila->frente->prox;
    res->prox = NULL;

    f->tamanho--;
    return res;
}

bool fila_cheia(Fila *f){
    return f->tamanho == MAX;
}

bool fila_vazia(Fila *f){
    return f->tamanho == 0;
}

Carro* fila_fundo(Fila *f){
    if(fila_vazia(f))
        return NULL;

    return f->fundo;
}

Carro* fila_frente(Fila *f){
    if(fila_vazia(f))
        return NULL;

    return f->frente;
}

void fila_checkout(Fila *f, int horaSaida){
    while(fila_frente(f)->horaSaida>=horaSaida){
        carro_imprimir(curr->carro);//TODO fazer o que pede
        fila_remover(f);
    }
}
