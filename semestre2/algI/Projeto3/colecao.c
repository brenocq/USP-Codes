#include <stdlib.h>
#include "colecao.h"

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
//----- Existe -----//
int existe_lista_ord(Colecao* c, int valor);
int existe_lista(Colecao* c, int valor);
int existe_arvore(Colecao* c, int valor);


Colecao* cria_colecao(int estrutura_id) 
{
	Colecao* col = (Colecao*)malloc(sizeof(Colecao));
	col->inicio = NULL;
	col->estrutura_id = estrutura_id;
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
	switch(c->estrutura_id){
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
			//arvore_binaria_adiciona(c, valor);
		break;
		case ARVORE_AVL:
			//arvore_avl_adiciona(c, valor);
		break;	
	}
}

int existe(Colecao* c, int valor)
{
	if(c==NULL)return 0;
	switch(c->estrutura_id){
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
void destroi(Colecao* c)
{
    // Implementar
}

//--------------------------------------//
//-------------- Lista -----------------//
//--------------------------------------//
int existe_lista_ord(Colecao* c, int valor){
	No* curr = c->inicio;
	
	while(curr!=NULL && curr->valor<valor)
		curr = curr->dir;

	if(curr==NULL)
		return 0;
	else if(curr->valor==valor)
		return 1;
	return 0;
}
int existe_lista(Colecao* c, int valor){
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

	if(curr==NULL){
		c->inicio = novo;
	}else{
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
}
//----------- Lista ultimo ------------//
void lista_ultimo_adiciona(Colecao* c, int valor){
	No* novo = cria_no(valor);
	No* curr = c->inicio;

	if(curr==NULL){
		c->inicio = novo;
	}else{
		while(curr->dir!=NULL){
			curr = curr->dir;
		}
		curr->dir = novo;
		novo->esq = curr;
	}
}

//---------- Lista primeiro  ----------//
void lista_primeiro_adiciona(Colecao* c, int valor){
	No* novo = cria_no(valor);
	No* curr = c->inicio;

	if(curr==NULL){
		c->inicio = novo;
	}else{
		c->inicio = novo;
		novo->dir = curr;
		curr->esq = novo;
	}
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
	
}
//------------ Arvore AVL -------------//
void arvore_avl_adiciona(Colecao* c, int valor){

}
