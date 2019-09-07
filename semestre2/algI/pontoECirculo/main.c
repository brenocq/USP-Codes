#include <stdio.h>
#include "ponto.h"
#include "circulo.h"

int main(int argc, char const *argv[]) {
  float p[2];// Info point
  float c[3];// Info circle
  float dist = 0;
  scanf("%f %f %f %f %f",&p[0],&p[1],&c[0],&c[1],&c[2]);
  PONTO *ponto = ponto_criar(p[0],p[1]);
  CIRCULO *circulo = circulo_criar(c[0],c[1],c[2]);

  dist = distancia(ponto, circulo);

  if(dist<c[2]){
    printf("O ponto é interior à circunferência.\nDistância: %.2f\n", dist);
  }else if(dist==c[2]){
    printf("O ponto pertence à circunferência.\nDistância: %.2f\n", dist);
  }else{
    printf("O ponto é exterior à circunferência.\nDistância: %.2f\n", dist);
  }

  ponto_apagar(ponto);
  circulo_apagar(circulo);
  return 0;
}
