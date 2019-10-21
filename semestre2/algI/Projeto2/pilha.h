#ifndef PILHA_H
#define PILHA_H

#include "carro.h"
#include <stdbool.h>

typedef struct _pilha Pilha;

Pilha* pilha_criar();
void pilha_deletar(Pilha **p);

int pilha_tamanho(Pilha *p);

bool pilha_inserir(Pilha *p, Carro *c);
Carro* pilha_remover(Pilha *p);
bool pilha_busca(Pilha *p, int placa);

bool pilha_vazia(Pilha *p);
bool pilha_cheia(Pilha *p);

Carro* pilha_topo(Pilha *p);

void pilha_checkout(Pilha *p, int horaSaida);

void pilha_imprimir(Pilha *p);
void pilha_sorteio(Pilha *p, int index);


#endif// PILHA_H
