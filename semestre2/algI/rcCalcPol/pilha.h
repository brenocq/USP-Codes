#ifndef PILHA_H
#define PILHA_H
#include <stdbool.h>

typedef struct _pilha Pilha;

Pilha* pilha_criar();
void pilha_deletar(Pilha **p);

int pilha_tamanho(Pilha *p);

bool pilha_inserir(Pilha *p, char *str);
char* pilha_remover(Pilha *p);
bool pilha_busca(Pilha *p, int placa);

bool pilha_vazia(Pilha *p);
bool pilha_cheia(Pilha *p);

char* pilha_topo(Pilha *p);


#endif// PILHA_H
