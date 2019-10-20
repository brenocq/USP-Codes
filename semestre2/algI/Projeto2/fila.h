#ifndef FILA_H
#define FILA_H

#include "carro.h"
#include <stdbool.h>

typedef struct _fila Fila;
typedef struct _item Item;

Fila* fila_criar();
Item* item_criar(Carro *c);
void fila_deletar(Fila **f);

bool fila_inserir(Fila *f, Carro* carro);
Carro* fila_remover(Fila *f);

bool fila_cheia(Fila *f);
bool fila_vazia(Fila *f);

Carro* fila_fundo(Fila *f);
Carro* fila_frente(Fila *f);

void fila_checkout(Fila *f, int horaSaida);


#endif// FILA_H
