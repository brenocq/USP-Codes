#ifndef FILA_H
#define FILA_H

#include "carro.h"
#include <stdbool.h>

typedef struct _fila Fila;

Fila* fila_criar();
void fila_deletar(Fila **f);

int fila_tamanho(Fila *f);

bool fila_inserir(Fila *f, Carro* carro);
Carro* fila_remover(Fila *f);

bool fila_cheia(Fila *f);
bool fila_vazia(Fila *f);

Carro* fila_fundo(Fila *f);
Carro* fila_frente(Fila *f);

bool fila_busca(Fila *f, int placa);
void fila_checkout(Fila *f, int horaSaida);

void fila_imprimir(Fila *f);
void fila_sorteio(Fila *f, int index);


#endif// FILA_H
