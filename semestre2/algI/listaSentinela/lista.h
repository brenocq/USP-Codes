#ifndef LISTA_H
#define LISTA_H

typedef struct _item Item;
typedef struct _lista Lista;

#define bool int
#define true 1
#define false 0

Lista* lista_criar();
Item* item_criar(int id, int val);
bool lista_inserir(Lista* l, Item *item);
bool lista_remover(Lista* l, int id);
void lista_deletar(Lista **l);

void lista_print(Lista* l);

#endif// LISTA_H