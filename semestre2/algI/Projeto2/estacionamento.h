#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

#include "carro.h"
#include <stdbool.h>

typedef struct _estacionamento Estacionamento;

Estacionamento* estacionamento_criar();
void estacionamento_deletar(Estacionamento** e);

Carro* estacionamento_checkin(Estacionamento* e);
void estacionamento_checkout(Estacionamento* e, Carro* carro);
bool estacionamento_disponibilidade(Estacionamento* e, Carro* carro);
void estacionamento_rejeicao(Estacionamento* e, Carro* carro, bool disponibilidade);
void estacionamento_imprimir(Estacionamento* e);

void estacionamento_sorteio(Estacionamento* e, Carro* carro);

#endif// ESTACIONAMENTO_H
