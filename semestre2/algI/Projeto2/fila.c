#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

struct _fila{
  Item *topo;
}

struct _item{
  Carro *carro;
  struct _item *prox;
}

Fila* fila_criar(){

}

Item* item_criar(Carro *c){

}

void fila_deletar(Fila **f){

}

Carro* fila_inserir(Fila *f){

}

Carro* fila_remover(Fila *f){

}

bool fila_cheia(Fila *f){

}

bool fila_vazia(Fila *f){

}

Carro* fila_fundo(Fila *f){

}

Carro* fila_frente(Fila *f){

}

void fila_checkout(Fila *f, int horaSaida){

}
