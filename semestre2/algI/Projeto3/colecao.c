#include <stdlib.h>
#include <stdio.h>// DELETAR (somente para debug)
#include "colecao.h"

#define ESQ 0
#define DIR 1

struct _no {
    int valor;
    struct _no* esq;
    struct _no* dir;
    int altura;
};

struct _c {
    No* inicio;
    int estrutura_id;
};

//----- Adiciona -----//
void lista_ord_adiciona(Colecao* c, int valor);
void lista_ultimo_adiciona(Colecao* c, int valor);
void lista_primeiro_adiciona(Colecao* c, int valor);
void arvore_binaria_adiciona(Colecao* c, int valor);
void arvore_avl_adiciona(Colecao* c, int valor);
void arvore_binaria_adiciona_aux(No *ini, int valor);
No *insere_filho(int filho, No *no, int valor);
No* arvore_avl_adiciona_aux(No* raiz, int valor);
//----- Existe -----//
int existe_lista_ord(Colecao* c, int valor);
int existe_lista(Colecao* c, int valor);
int existe_arvore(Colecao* c, int valor);
//----- Existe -----//
void destroi_aux(No *curr);
//----- Existe -----//
int max(int a, int b)
Colecao* cria_colecao(int estrutura_id)
{
	Colecao* col = (Colecao*)malloc(sizeof(Colecao));
	col->inicio = NULL;
	col->estrutura_id = estrutura_id;
  if(estrutura_id==LISTA_ORDENADO || estrutura_id==LISTA_ULTIMO || estrutura_id==LISTA_PRIMEIRO)
	{
		// Cria o nó cabeça para lista e a raiz para árvore
	   No* ini = cria_no(-1);
	   col->inicio = ini;
  }
  return col;
}

No* cria_no(int valor)
{
  No* no = (No*)malloc(sizeof(No));
	no->valor = valor;
	no->esq = NULL;
	no->dir = NULL;
	no->altura = 0;
	return no;
}

void adiciona(Colecao* c, int valor)
{
	if(c==NULL)return;
	switch(c->estrutura_id)
	{
		case LISTA_ORDENADO:
			lista_ord_adiciona(c, valor);
		break;
		case LISTA_ULTIMO:
			lista_ultimo_adiciona(c, valor);
		break;
		case LISTA_PRIMEIRO:
			lista_primeiro_adiciona(c, valor);
		break;
		case ARVORE_BINARIA:
			arvore_binaria_adiciona(c, valor);
		break;
		case ARVORE_AVL:
			//arvore_avl_adiciona(c, valor);
		break;
	}
}

int existe(Colecao* c, int valor)
{
	if(c==NULL)return 0;
	switch(c->estrutura_id)
	{
		case LISTA_ORDENADO:
			return existe_lista_ord(c, valor);
		case LISTA_ULTIMO: case LISTA_PRIMEIRO:
			return existe_lista(c, valor);
		break;
		case ARVORE_BINARIA: case ARVORE_AVL:
			return existe_arvore(c, valor);
		break;
	}
	return 0;
}

void destroi(Colecao *c)
{
  if(c == NULL) return;  
 	int estrutura_id = c->estrutura_id;

	No *curr = c->inicio;
	if(estrutura_id==LISTA_ORDENADO || estrutura_id==LISTA_ULTIMO || estrutura_id==LISTA_PRIMEIRO)
	{
		while(curr!=NULL)
		{
			No* aux = curr->dir;
			free(curr);
			curr = aux;
		}
	}else
	{
		destroi_aux(curr);
	}
	free(c);
	c = NULL;
}

void destroi_aux(No *curr)
{
  if(curr != NULL)
	{
    destroi_aux(curr->dir);
    destroi_aux(curr->esq);
    free(curr);
    curr = NULL;
  }
}

//--------------------------------------//
//-------------- Lista -----------------//
//--------------------------------------//
int existe_lista_ord(Colecao* c, int valor)
{
	No* curr = c->inicio;

	while(curr!=NULL && curr->valor<valor)
		curr = curr->dir;

	if(curr==NULL)
		return 0;
	else if(curr->valor==valor)
		return 1;
	return 0;
}
int existe_lista(Colecao* c, int valor)
{
	No* curr = c->inicio;

	while(curr!=NULL && curr->valor!=valor)
		curr = curr->dir;

	if(curr==NULL)
		return 0;
	else
		return 1;
}
//---------- Lista ordenada ------------//
void lista_ord_adiciona(Colecao* c, int valor){
	No* novo = cria_no(valor);
	No* curr = c->inicio;
  while(curr->dir!=NULL && curr->dir->valor<=valor){
		curr = curr->dir;
	}
	if(curr->dir!=NULL){
		curr->dir->esq = novo;
		novo->dir = curr->dir;
	}
	curr->dir = novo;
	novo->esq = curr;
}
//----------- Lista ultimo ------------//
void lista_ultimo_adiciona(Colecao* c, int valor)
{
	No* novo = cria_no(valor);
	No* curr = c->inicio;
	while(curr->dir!=NULL){
		curr = curr->dir;
	}
	curr->dir = novo;
	novo->esq = curr;
}
//----------- Lista primeiro ----------//
void lista_primeiro_adiciona(Colecao* c, int valor){
	No* novo = cria_no(valor);
	No* curr = c->inicio;
	c->inicio = novo;
	novo->dir = curr;
  curr->esq = novo;
}
//--------------------------------------//
//-------------- Arvore ----------------//
//--------------------------------------//
int existe_arvore(Colecao* c, int valor){
	No* curr = c->inicio;
	while(curr!=NULL){
		if(curr->valor==valor) return 1;
		else if(curr->valor<valor){
			if(curr->dir==NULL) return 0;
			curr = curr->dir;
			continue;
		}else if(curr->valor>valor){
			if(curr->esq==NULL) return 0;
			curr = curr->esq;
			continue;
		}
	}
	return 0;
}
//---------- Arvore binaria -----------//
void arvore_binaria_adiciona(Colecao* c, int valor){
  No *novo = cria_no(valor);
  if(c->inicio == NULL){
    c->inicio = novo;
    return;
  }
  arvore_binaria_adiciona_aux(c->inicio, valor);
}
/*
As duas funcões abaixo são auxiliares para a função
arvore_binaria_adiciona.
*/
No *insere_filho(int filho, No *no, int valor){
  No *novo = cria_no(valor);
  if(novo != NULL){
    if(filho == ESQ)
      no->esq = novo;
    else
      no->dir = novo;
  }
  return novo;
}

void arvore_binaria_adiciona_aux(No *ini, int valor){
  if(valor == ini->valor) return;
  if(valor < ini->valor){
    if(ini->esq == NULL)
      insere_filho(ESQ, ini, valor);
    else
      arvore_binaria_adiciona_aux(ini->esq, valor);
  }
  else{
    if(ini->dir == NULL)
      insere_filho(DIR, ini, valor);
    else
      arvore_binaria_adiciona_aux(ini->dir, valor);
  }
}


//------------ Arvore AVL -------------//
void arvore_avl_adiciona(Colecao* c, int valor)
{
	if(c==NULL)return;
	arvore_avl_adiciona_aux(c->inicio, valor);
}

No* arvore_avl_adiciona_aux(No* raiz, int valor)
{
	if(raiz==NULL)
	{
		raiz = cria_no(valor);
		raiz->altura= 0;
	}else if(valor > raiz->valor)
	{
		raiz->dir = arvore_avl_adiciona_aux(raiz->dir, valor);
		if(arvore_avl_altura(raiz->esq) - arvore_avl_altura(raiz->dir == -2))
		{
			if(valor > raiz->dir->valor)
			{
				raiz = rodar_esq(raiz);
			}else
			{
				raiz = rodar_dir_esq(raiz);
			}
		}
	}else if(valor < raiz->valor)
	{
		raiz->esq = arvore_avl_adiciona_aux(raiz->esq, valor);
		if(arvore_avl_altura(raiz->esq) - arvore_avl_altura(raiz->dir == 2))
		{
			if(valor < raiz->esq->valor)
			{
				raiz = rodar_dir(raiz);
			}else
			{
				raiz = rodar_esq_dir(raiz);
			}
		}
	}
	raiz->altura = max(arvore_avl_altura(raiz->esq), arvore_avl_altura(raiz->dir))+1;
}

int arvore_avl_altura(No* raiz)
{
	if(raiz==NULL) return -1;
	else return raiz->altura;
}

int max(int a, int b)
{
	return a>b?a:b;
}
