#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

struct _item{
    int id;
    int val;
    struct _item *prox;
};

struct _lista{
    Item *sentinela;
    Item *fim;
    int tamanho;
};

typedef struct _doisItens{
    Item *prev;
    Item *curr;
} DoisItens;

DoisItens* lista_busca(Lista* l, int id);

Lista* lista_criar(){
    Lista* l;
    Item* sentinela;
    l = (Lista*)malloc(sizeof(Lista));
    sentinela = (Item*)malloc(sizeof(Item));

    if(l==NULL || sentinela==NULL){
        printf("Falta de espaço na memória ao criar a lista.");
    }

    sentinela->id = -1;
    sentinela->val = -1;
    sentinela->prox = sentinela;
    l->sentinela = sentinela;
    l->fim = l->sentinela;
    l->tamanho = 0;

    return l;
}

Item* item_criar(int id, int val){
    Item* item;
    item = (Item*)malloc(sizeof(Item));
    if(item==NULL){
        printf("Falta de espaço na memória ao criar o item.");
    }
    item->id = id;
    item->val = val;
    item->prox = NULL;

    return item;
}

bool lista_inserir(Lista* l, Item *item){
    if(l == NULL || item == NULL)
        return false;

    Item* curr = l->sentinela->prox;
    Item* prev = l->sentinela;
    while(curr!=l->sentinela && curr->id<=item->id){
        prev = curr;
        curr = curr->prox;
    }
    prev->prox = item;
    item->prox = curr;
    l->tamanho++;
    return true;
}

bool lista_remover(Lista* l, int id){
    if(l == NULL)
        return false;

    DoisItens* doisItens = lista_busca(l,id);
    if(doisItens==NULL){
        return false;
    }else{
        doisItens->prev->prox = doisItens->curr->prox;
        doisItens->curr->prox = NULL;
        free(doisItens->curr);
        free(doisItens);
    }
    l->tamanho--;
    return true;
}

DoisItens* lista_busca(Lista* l, int id){
    if(l == NULL)
        return NULL;

    Item* sentinela = l->sentinela;
    sentinela->id = id;
    Item* curr = l->sentinela->prox;
    Item* prev = l->sentinela;
    while(curr->id!=id){
        prev = curr;
        curr = curr->prox;
    }

    if(curr!=sentinela){
        DoisItens* resultado = (DoisItens*)malloc(sizeof(DoisItens));
        resultado->prev = prev;
        resultado->curr = curr;
        return resultado;
    }else{
        return NULL;
    }
}

void lista_deletar(Lista **l){
    if(l == NULL || *l == NULL){
        return;
    }

    Item* curr = (*l)->sentinela;
    Item* prox = NULL;
    (*l)->fim->prox = NULL;
    while(curr!=NULL){
        prox = curr->prox;
        free(curr);
        curr = prox;
    }
    free(*l);
}

void lista_print(Lista* l){
    if(l == NULL){
        return;
    }

    Item* ini = l->sentinela->prox;
    while(ini!=l->sentinela){
        printf("ID:%d  -> val:%d\n", ini->id, ini->val);
        ini = ini->prox;
    }
}
