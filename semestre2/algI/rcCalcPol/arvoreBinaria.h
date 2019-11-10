#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H
#include <stdbool.h>

typedef struct _arvBin ArvBin;

ArvBin* arv_criar();
void arv_deletar(ArvBin **a);
void arv_inserir(ArvBin *a, char* str);
float arv_pos_ordem(ArvBin *a);

#endif// ARVOREBINARIA_H
