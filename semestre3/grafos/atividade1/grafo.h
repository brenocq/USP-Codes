#ifndef GRAFO_H
#define GRAFO_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct grafo_ GRAFO;

GRAFO *grafo_criar(int qtdVertices);
void grafo_inserir(GRAFO *grafo, int v0, int v1);
void grafo_remover(GRAFO *grafo, int v0, int v1);
void grafo_exibir(GRAFO *grafo);
void grafo_deletar(GRAFO **grafo);

#endif
