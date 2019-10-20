#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Eu decidi utilizar uma lista dinamica duplamente encadeada circular com sentinela.
// Foi escolhido lista duplamente encadeada para facilitar a remoção e inserção quando ocorrer troca de posição das abas.
// Escolhi lista circular com sentinela para realizar menos operações durante a busca

struct _item{
    char* titulo;
    char* url;
    struct _item *prox;
    struct _item *prev;
};

struct _lista{
    Item *sentinela;
    int tamanho;
};

Item* lista_busca(Lista* l, char* titulo);

Lista* lista_criar(){
    // Cria a lista
    Lista* l;
    Item* sentinela;
    l = (Lista*)malloc(sizeof(Lista));
    sentinela = (Item*)malloc(sizeof(Item));

    if(l==NULL || sentinela==NULL){
        printf("Falta de espaço na memória ao criar a lista.");
    }

    char titulo[]=".";
    char url[]=".";

    sentinela->titulo = titulo;
    sentinela->url = url;
    sentinela->prox = sentinela;
    sentinela->prev = sentinela;
    l->sentinela = sentinela;
    l->tamanho = 0;

    return l;
}

Item* item_criar(char* titulo, char* url){
    // Cria um item
    Item* item;
    item = (Item*)malloc(sizeof(Item));
    if(item==NULL){
        printf("Falta de espaço na memória ao criar o item.");
    }

    char *_titulo = (char*)calloc(41,sizeof(char));
    char *_url = (char*)calloc(513,sizeof(char));

    strcpy(_titulo, titulo);
    strcpy(_url, url);

    item->titulo = _titulo;
    item->url = _url;
    item->prox = NULL;
    item->prev = NULL;

    return item;
}

bool lista_inserir(Lista* l, Item *item, int pos){
    // Insere um item na lista
    if(l == NULL || item == NULL)
        return false;

    int i;
    Item* prevInserir = l->sentinela->prev;
    for(i=0;i<pos+1;i++){
      prevInserir = prevInserir->prox;
    }


    item->prev = prevInserir;
    item->prox = prevInserir->prox;
    item->prev->prox = item;
    item->prox->prev = item;

    l->tamanho++;
    return true;
}

bool lista_remover(Lista* l, char* titulo){
    // Remove um item da lista
    if(l == NULL)
        return false;

    Item* resBusca = lista_busca(l,titulo);
    if(resBusca==NULL){
        return false;
    }else{
        resBusca->prev->prox = resBusca->prox;
        resBusca->prox->prev = resBusca->prev;
        resBusca->prox = NULL;
        resBusca->prev = NULL;
        free(resBusca);
    }
    l->tamanho--;
    return true;
}

Item* lista_busca(Lista* l, char* titulo){
    // Busca um item na lista
    if(l == NULL)
        return NULL;

    Item* sentinela = l->sentinela;
    strcpy(sentinela->titulo, titulo);
    Item* curr = l->sentinela->prox;
    while(strcmp(curr->titulo,titulo)!=0){
        curr = curr->prox;
    }

    if(curr!=sentinela){
        return curr;
    }else{
        return NULL;
    }
}

void lista_deletar(Lista **l){
    // Deleta a lista
    if(l == NULL || *l == NULL){
        return;
    }

    Item* curr = (*l)->sentinela;
    Item* prox = NULL;
    while(curr!=NULL){
        prox = curr->prox;
        curr->prev = NULL;
        curr->prox = NULL;
        free(curr);
        curr = prox;
    }
    free(*l);
}

void lista_print(Lista* l){
    // Imprime todas as abas
    if(l == NULL){
        return;
    }

    Item* curr = l->sentinela->prox;

    while(curr!=l->sentinela){
        printf("%s %s\n", curr->titulo, curr->url);
        curr = curr->prox;
    }
}

bool lista_troca(Lista* l, char* titulo, int pos){
  // Move uma aba para a posição de desejada
  int i;
  if(pos>=l->tamanho){
    pos = l->tamanho;
  }
  // Recebe o item desejado se existir
  Item* resBusca = lista_busca(l,titulo);
  if(resBusca!=NULL){
    // Retira resBusca da lista
    resBusca->prox->prev = resBusca->prev;
    resBusca->prev->prox = resBusca->prox;

    // Calcula o nó antes da posição de inserção
    Item* prevInserir = l->sentinela;
    for(i=0;i<pos-1;i++){
      prevInserir = prevInserir->prox;
    }

    // Insere resBusca na lista
    resBusca->prev = prevInserir;
    resBusca->prox = prevInserir->prox;
    resBusca->prev->prox = resBusca;
    resBusca->prox->prev = resBusca;
    return true;
  }
  // Não faz nada se a aba não existe
  return false;
}
