#ifndef LISTA_H
#define LISTA_H

typedef struct _item Item;
typedef struct _lista Lista;

#define bool int
#define true 1
#define false 0

Lista* lista_criar();
Item* item_criar(char nome[26]);
bool lista_inserir(Lista* l, Item *item);
char* lista_busca(Lista* l, char nome[26]);
void lista_deletar(Lista **l);

bool lista_vazia(Lista* l);

#endif// LISTA_H
