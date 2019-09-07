#include "ponto.h"
struct ponto_{
  float x;
  float y;
};

PONTO *ponto_criar(float x, float y){
  PONTO *novoPonto;
  novoPonto = (PONTO*)malloc(sizeof(PONTO));
  novoPonto->x=x;
  novoPonto->y=y;
  return novoPonto;
}
void ponto_apagar(PONTO *p){
  free(p);
}
bool ponto_set(PONTO *p, float x, float y){
  if(p!=NULL){
    p->x=x;
    p->y=y;
    return true;
  }else{
    return false;
  }
}

float getX(PONTO *p){
  return p->x;
}
float getY(PONTO *p){
  return p->y;
}
