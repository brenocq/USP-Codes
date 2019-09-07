#ifndef LISTA_H
#define LISTA_H
typedef struct _lista LISTA;
LISTA* lista_criar(int tamanho);
int lista_inserir(LISTA* lista, int num);
void lista_imprimir(LISTA* lista);
#endif// LISTA_H
