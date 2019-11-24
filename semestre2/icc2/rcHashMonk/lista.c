#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _item{
    char nome[26];
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

bool lista_vazia(Lista* l){
  return l->tamanho==0;
}

Lista* lista_criar(){
    Lista* l;
    Item* sentinela;
    l = (Lista*)malloc(sizeof(Lista));
    sentinela = (Item*)malloc(sizeof(Item));

    if(l==NULL || sentinela==NULL){
        printf("Falta de espaço na memória ao criar a lista.");
    }

    strcpy(sentinela->nome,"\0");
    sentinela->prox = sentinela;
    l->sentinela = sentinela;
    l->fim = l->sentinela;
    l->tamanho = 0;

    return l;
}

Item* item_criar(char nome[26]){
    Item* item;
    item = (Item*)malloc(sizeof(Item));
    if(item==NULL){
        printf("Falta de espaço na memória ao criar o item.");
    }
    strcpy(item->nome, nome);
    item->prox = NULL;

    return item;
}

bool lista_inserir(Lista* l, Item *item){
    if(l == NULL || item == NULL)
        return false;

    Item* curr = l->sentinela->prox;
    Item* prev = l->sentinela;
    while(curr!=l->sentinela){
        prev = curr;
        curr = curr->prox;
    }
    prev->prox = item;
    item->prox = curr;

    l->tamanho++;
    return true;
}

char* lista_busca(Lista* l, char nome[26]){
    if(l == NULL)
        return NULL;

    Item* sentinela = l->sentinela;
    strcpy(sentinela->nome, nome);
    Item* curr = l->sentinela->prox;
    Item* prev = l->sentinela;
    while(strcmp(curr->nome,nome)!=0){
        prev = curr;
        curr = curr->prox;
    }

    return curr->nome;

    /*if(curr!=sentinela){
        DoisItens* resultado = (DoisItens*)malloc(sizeof(DoisItens));
        resultado->prev = prev;
        resultado->curr = curr;
        return resultado;
    }else{
        return NULL;
    }*/
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
