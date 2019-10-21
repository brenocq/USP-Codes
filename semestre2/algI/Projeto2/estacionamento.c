#include "estacionamento.h"
#include "carro.h"
#include "pilha.h"
#include "fila.h"

#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_EST 15

 struct _estacionamento{
   Pilha* pilha;
   Fila* fila;
 };

Estacionamento* estacionamento_criar(){
  Estacionamento* e = (Estacionamento*)malloc(sizeof(Estacionamento));
  if(e==NULL){
      printf("Memória cheia, o programa será encerrado.\n");
      exit(1);
  }
  e->fila = fila_criar();
  e->pilha = pilha_criar();
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
  bool resPilha = pilha_busca(e->pilha, placa);
  bool resFila = fila_busca(e->fila, placa);

  if(resPilha || resFila){
    printf("Este carro já está estacionado no pátio.\n");
    return NULL;
  }

  Carro *carro = carro_criar(placa, horaChegada, horaSaida, desconto);

  return carro;
}

void estacionamento_checkout(Estacionamento* e, Carro* carro){
  int horaSaida = carro_get_hChegada(carro);
  pilha_checkout(e->pilha, horaSaida);
  fila_checkout(e->fila, horaSaida);
}

bool estacionamento_disponibilidade(Estacionamento* e, Carro* carro){
  bool pilhaVazia = pilha_vazia(e->pilha);
  bool filaVazia = fila_vazia(e->fila);

  if(carro_get_hSaida(carro)<8 || carro_get_hSaida(carro)>22)
    return false;

  if(pilhaVazia && filaVazia){
    pilha_inserir(e->pilha, carro);
    return true;
  }else if(pilhaVazia && !filaVazia){
    pilha_inserir(e->pilha, carro);
    return true;
  }else if(!pilhaVazia && filaVazia){
    fila_inserir(e->fila, carro);
    return true;
  }else if(!pilhaVazia && !filaVazia){
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
    printf("\nNão foi possível adicionar o carro. O estacionamento está lotado.\n");
    return;
  }
  if(carro_get_hSaida(carro)<8 || carro_get_hSaida(carro)>22 || carro_get_hChegada(carro)<8 || carro_get_hChegada(carro)>22){
    printf("\nNão foi possível adicionar o carro. Não estamos em horário de funcionamento (8h às 22h).\n");
    return;
  }
  if(!disponibilidade){
    printf("\nNão foi possível adicionar o carro. O estacionamento não está disponível no momento.\n");
    return;
  }
}

void estacionamento_imprimir(Estacionamento* e){
    printf("Carros estacionados no pátio 1:\n");
    pilha_imprimir(e->pilha);
    printf("Carros estacionados no pátio 2:\n");
    fila_imprimir(e->fila);
}

void estacionamento_sorteio(Estacionamento* e, Carro* carro){
    int qtdCarrosPatio1 = pilha_tamanho(e->pilha);
    int qtdCarrosPatio2 = fila_tamanho(e->fila);
    int horasSorteio[4] = {9,12,15,18};
    int i;
    srand((unsigned) time(NULL));

    if((qtdCarrosPatio1+qtdCarrosPatio2)>=MAX_EST*0.25){
        for(i=0;i<4;i++){
            if(carro_get_hChegada(carro)==horasSorteio[i]){
                int random = rand()%100;
                random = random%(qtdCarrosPatio1+qtdCarrosPatio2);
                if(random<qtdCarrosPatio1){
                    pilha_sorteio(e->pilha, random);
                }else{
                    fila_sorteio(e->fila, random-qtdCarrosPatio1);
                }
            }
        }
    }
}
