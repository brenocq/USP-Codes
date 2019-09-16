#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

int main(){
    Lista *l = lista_criar();
    Item *item1 = item_criar(1, 100);
    Item *item2 = item_criar(2, 203);
    Item *item3 = item_criar(3, 301);

    
    lista_inserir(l, item3);
    lista_inserir(l, item2);
    lista_remover(l,2);
    lista_inserir(l, item1);

    lista_print(l);
    lista_deletar(&l);
    return 0;
}