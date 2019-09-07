#include "circulo.h"

#define PI 3.14159

struct circulo_{
  PONTO *ponto_c;
  float raio;
};

CIRCULO *circulo_criar(float x, float y,float raio){
  CIRCULO *circulo;
  PONTO *ponto;
  ponto = ponto_criar(x,y);
  circulo = (CIRCULO*)malloc(sizeof(CIRCULO));
  circulo->ponto_c = ponto;
  circulo->raio = raio;
}

void circulo_apagar(CIRCULO *circulo){
  free(circulo);
}

float circulo_area(CIRCULO *circulo){
  float r = circulo->raio;
  return r*r*PI;
}

float distancia(PONTO *p, CIRCULO *c){
  float deltaX = getX(p)-getX(c->ponto_c);
  float deltaY = getY(p)-getY(c->ponto_c);

  float dist = sqrt(deltaX*deltaX + deltaY*deltaY);
  return dist;
}
