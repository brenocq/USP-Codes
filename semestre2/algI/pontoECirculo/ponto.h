#ifndef PONTO_H
#define PONTO_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct ponto_ PONTO;

 PONTO *ponto_criar(float x, float y);
 void ponto_apagar(PONTO *p);
 bool ponto_set(PONTO *p, float x, float y);

 // Foi necessário criar uma função para retornar o X e uma função para retornar
 // o Y porque o TAD círculo precisa acessar estes valores durante o cálculo
 float getX(PONTO *p);
 float getY(PONTO *p);

#endif
