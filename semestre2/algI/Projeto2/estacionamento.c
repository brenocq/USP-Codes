#include "estacionamento.h"
#include "carro.h"
#include "pilha.h"
#include "fila.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

 struct _estacionamento{
   Pilha* pilha;
   Fila* fila;
 };

Estacionamento* estacionamento_criar(){
  Estacionamento* e;
  e->pilha = pilha_criar();
  e->fila = fila_criar();
  return e;
}

void estacionamento_deletar(Estacionamento** e){
  pilha_deletar(&((*e)->pilha));
  fila_deletar(&((*e)->fila));
  free(*e);
}

Carro* estacionamento_checkin(Estacionamento* e){
  int placa;
  int horaChegada;
  int horaSaida;
  float desconto=0;
  printf("Iremos precisar de algumas informações do carro. Por favor insira:\n");
  printf("Placa do carro: ");
  scanf("%d", &placa);
  printf("Hora de chegada: ");
  scanf("%d", &horaChegada);
  printf("Hora de saída: ");
  scanf("%d", &horaSaida);

  // Procura se o carro com esta placa já está estacionado
  bool resPilha = pilha_busca(placa);
  bool resFila = fila_busca(placa)

  if(resPilha || resFila){
    printf("Este carro já está estacionado no pátio.\n");
    return NULL;
  }

  Carro *carro = carro_criar(placa, horaChegada, horaSaida, desconto);
  
  return carro;
}

void estacionamento_checkout(Estacionamento* e, Carro* carro){
  int horaSaida = carro_get_hSaida(carro);
  pilha_checkout(e->pilha, horaSaida);
  fila_checkout(e->fila, horaSaida);
}

bool estacionamento_disponibilidade(Estacionamento* e, Carro* carro){
  bool pilha_vazia = pilha_vazia(e->pilha);
  bool fila_vazia = fila_vazia(e->fila);

  if(carro_get_hSaida(carro)<8 || carro_get_hSaida(carro)>22)
    return false;

  if(pilha_vazia && fila_vazia){
    pilha_inserir(e->pilha, carro);
    return true;
  }else if(pilha_vazia && !fila_vazia){
    pilha_inserir(e->pilha, carro);
    return true;
  }else if(!pilha_vazia && fila_vazia){
    fila_inserir(e->fila, carro);
    return true;
  }else if(!pilha_vazia && !fila_vazia){
    Carro *ultimoPilha = pilha_topo(e->pilha);
    Carro *ultimoFila = fila_fundo(e->fila);
    if(carro_get_hSaida(carro)<=carro_get_hSaida(ultimoPilha) && !pilha_cheia(e->pilha)){
      pilha_inserir(e->pilha, carro);
      return true;
    }else if(carro_get_hSaida(carro)>=carro_get_hSaida(ultimoFila) && !fila_cheia(e->fila)){
      fila_inserir(e->fila, carro);
      return true;
    }
  }
  return false;
}

void estacionamento_rejeicao(Estacionamento* e, Carro* carro, bool disponibilidade){
  if(pilha_cheia(e->pilha) && fila_cheia(e->fila)){
    printf("Não foi possível adicionar o carro. O estacionamento está lotado.\n");
    return;
  }
  if(carro_get_hSaida(carro)<8 || carro_get_hSaida(carro)>22){
    printf("Não foi possível adicionar o carro. Não estamos em horário de funcionamento (8h às 22h).\n");
    return;
  }
  if(!disponibilidade){
    printf("Não foi possível adicionar o carro. O estacionamento não está disponível no momento.\n");
    return;
  }
}
