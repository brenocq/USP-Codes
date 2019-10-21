#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX 10

struct _itemFila{
  Carro *carro;
  struct _itemFila *prox;
};

typedef struct _itemFila ItemFila;

struct _fila{
  ItemFila *frente;
  ItemFila *fundo;// Colocamos um ponteiro para o ultimo para melhorar o cadastro dos carros
  int tamanho;
};

Fila* fila_criar(){
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if(fila==NULL){
        printf("Memória cheia, o programa será encerrado.\n");
        exit(1);
    }

    fila->frente = NULL;
    fila->fundo = NULL;
    fila->tamanho = 0;
    return fila;
}

ItemFila* item_fila_criar(Carro *c){
    ItemFila* item = (ItemFila*)malloc(sizeof(ItemFila));
    if(item==NULL){
        printf("Memória cheia, o programa será encerrado.\n");
        exit(1);
    }

    item->carro = c;
    item->prox = NULL;
    return item;
}

int fila_tamanho(Fila *f){
    return f->tamanho;
}

void fila_deletar(Fila **f){
    ItemFila* curr = (*f)->frente;
    while(curr!=NULL){
        ItemFila* prox = curr->prox;
        free(curr);
        curr = prox;
    }
    free(*f);
}

bool fila_inserir(Fila *f, Carro* carro){
    if(f==NULL || fila_cheia(f))
        return false;

    ItemFila* novo = item_fila_criar(carro);

    if(novo==NULL)
        return false;

    if(f->frente==NULL){
        f->frente = novo;
        f->fundo = novo;
    }else{
        f->fundo->prox = novo;
        f->fundo = novo;
    }
    f->tamanho++;

    return true;
}

Carro* fila_remover(Fila *f){
    if(f==NULL || fila_vazia(f))
        return NULL;

    ItemFila* res = f->frente;

    f->frente = f->frente->prox;
    res->prox = NULL;

    f->tamanho--;
    return res->carro;
}

bool fila_cheia(Fila *f){
    return f->tamanho == MAX;
}

bool fila_vazia(Fila *f){
    return f->tamanho == 0;
}

Carro* fila_fundo(Fila *f){
    if(f==NULL || fila_vazia(f))
        return NULL;

    return f->fundo->carro;
}

Carro* fila_frente(Fila *f){
    if(f==NULL || fila_vazia(f))
        return NULL;

    return f->frente->carro;
}

bool fila_busca(Fila *f, int placa){
    ItemFila* curr = f->frente;
    while(curr!=NULL){
        if(carro_get_placa(curr->carro) == placa){
            return true;
        }
        curr = curr->prox;
    }
    return false;
}

void fila_checkout(Fila *f, int horaSaida){
    while(fila_frente(f)!=NULL &&  carro_get_hSaida(fila_frente(f))<=horaSaida){
        printf("\nCarro saindo do pátio 2: ");
        carro_imprimir(fila_remover(f));//TODO fazer o que pede
    }
}

void fila_imprimir(Fila *f){
    ItemFila* curr = f->frente;
    while(curr!=NULL){
        carro_imprimir(curr->carro);
        curr = curr->prox;
    }
}

void fila_sorteio(Fila *f, int index){
    ItemFila* curr = f->frente;
    int cont=0;
    while(cont<index){
        curr=curr->prox;
        cont++;
    }
    carro_set_desconto(curr->carro, 0.1);
}
