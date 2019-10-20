#ifndef CARRO_H
#define CARRO_H

typedef struct _carro Carro;

Carro* carro_criar(int placa, int horaChegada, int horaSaida, float desconto);
void carro_deletar(Carro* carro);

int carro_get_placa(Carro *carro);
int carro_get_hChegada(Carro *carro);
int carro_get_hSaida(Carro *carro);
float carro_get_desconto(Carro *carro);

void carro_imprimir(Carro *carro);

#endif// CARRO_H
