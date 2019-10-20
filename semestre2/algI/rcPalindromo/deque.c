#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Neste exercício eu escolhi utilizar o deque pois ele permite remoções dos dois lados da lista (útil para palíndromo)

#define MAX 200

struct _item{
    char caractere;
    struct _item *prox;
    struct _item *prev;
};

struct _deque{
    Item *head;
    int tamanho;
};

Deque* deque_criar(){
    // Cria o deque
    Deque* d;
    Item* head;
    d = (Deque*)malloc(sizeof(Deque));
    head = (Item*)malloc(sizeof(Item));

    if(d==NULL || head==NULL){
        printf("Falta de espaço na memória ao criar o deque.");
    }

    head->caractere = '.';
    head->prox = head;
    head->prev = head;
    d->head = head;
    d->tamanho = 0;

    return d;
}

Item* item_criar(char c){
    // Cria um item
    Item* item;
    item = (Item*)malloc(sizeof(Item));
    if(item==NULL){
        printf("Falta de espaço na memória ao criar o item.");
    }

    item->caractere = c;
    item->prox = NULL;
    item->prev = NULL;

    return item;
}

bool deque_inserir_frente(Deque* d, Item *item){
    // Insere um item na frente
    if(d == NULL || item == NULL)
        return false;

    if(deque_cheio(d))
      return false;

    Item *head = d->head;

    item->prox = head;
    item->prev = head->prev;
    head->prev->prox = item;
    head->prev = item;

    d->tamanho++;
    return true;
}

bool deque_inserir_fundo(Deque* d, Item *item){
    // Insere um item no fundo
    if(d == NULL || item == NULL)
        return false;

    if(deque_cheio(d))
      return false;

    Item *head = d->head;

    item->prox = head->prox;
    item->prev = head;
    head->prox->prev = item;
    head->prox = item;

    d->tamanho++;
    return true;
}

Item* deque_remover_frente(Deque* d){
    // Remove o item da frente do deque
    if(d == NULL)
        return NULL;

    if(deque_vazio(d))
      return NULL;

    Item* head = d->head;
    Item* result = head->prev;

    result->prev->prox = result->prox;
    result->prox->prev = result->prev;

    result->prox = NULL;
    result->prev = NULL;

    d->tamanho--;
    return result;
}

Item* deque_remover_fundo(Deque* d){
    // Remove o item do fundo do deque
    if(d == NULL)
        return NULL;

    if(deque_vazio(d))
      return NULL;

    Item* head = d->head;
    Item* result = head->prox;

    result->prox->prev = result->prev;
    result->prev->prox = result->prox;

    result->prox = NULL;
    result->prev = NULL;

    d->tamanho--;
    return result;
}

Item* deque_frente(Deque* d){
  // Retorna o item da frente do deque
  if(d == NULL || deque_vazio(d))
      return NULL;

  return d->head->prev;
}

Item* deque_fundo(Deque* d){
  // Retorna o item do fundo do deque
  if(d == NULL || deque_vazio(d))
      return NULL;

  return d->head->prox;
}

bool deque_cheio(Deque* d){
  // Checa se o deque esta cheio
  if(d == NULL)
      return false;
  return d->tamanho >= MAX;
}

bool deque_vazio(Deque* d){
  // Checa se o deque esta vazio
  if(d == NULL)
      return false;

  return d->tamanho <= 0;
}

void deque_print(Deque *d){
    // Imprime todas os caracteres
    if(d == NULL){
        return;
    }

    Item* curr = d->head->prox;

    while(curr!=d->head){
        printf("%c", curr->caractere);
        curr = curr->prox;
    }
    printf("\n");
}

void deque_deletar(Deque **d){
    // Deleta o deque
    if(d == NULL || *d == NULL){
        return;
    }

    Item* curr = (*d)->head;
    Item* prox = NULL;
    while(curr!=NULL){
        prox = curr->prox;
        curr->prev = NULL;
        curr->prox = NULL;
        free(curr);
        curr = prox;
    }
    free(*d);
}

char char_valido_fundo(Deque *d){
  // Primeira letra seguindo a operação deque_remover_fundo. A letra é retornada como minúscula
  while(!deque_vazio(d)){
    Item* fundo = deque_remover_fundo(d);
    char c = fundo->caractere;
    if(c>='A' && c<='Z'){
      c = c + 'a'-'A';
      return c;
    }
    if(c>='a' && c<='z'){
      return c;
    }
  }
  return 0;
}

char char_valido_frente(Deque *d){
  // Primeira letra seguindo a operação deque_remover_frente. A letra é retornada como minúscula
  while(!deque_vazio(d)){
    Item* fundo = deque_remover_frente(d);
    char c = fundo->caractere;
    if(c>='A' && c<='Z'){
      c = c + 'a'-'A';
      return c;
    }
    if(c>='a' && c<='z'){
      return c;
    }
  }
  return 0;
}
