#include <stdlib.h>
#include <stdio.h>

typedef struct _elemento{
  float value;
  struct _elemento *next;
}elemento;

float mediaIterativa(elemento *ini);
float mediaRecursiva(elemento *ini, int qtd);

int main(int argc, char const *argv[]) {
  int qtd, i;
  float val;

  scanf("%d", &qtd);
  scanf("%f", &val);
  elemento* first = (elemento*)malloc(sizeof(elemento));
  first->value = val;

  elemento** ini = (elemento**)malloc(sizeof(elemento*));
  ini = &first;

  elemento* last = first;
  for (i = 1; i < qtd; i++){
    scanf("%f", &val);
    elemento *ele = (elemento*)malloc(sizeof(elemento));
    ele->value = val;

    last->next = ele;
    last = ele;
  }

  float media1 = mediaIterativa(*ini);
  float media2 = mediaRecursiva(*ini, qtd);

  printf("%.2f\n", media1);
  printf("%.2f\n", media2);

  return 0;
}

float mediaIterativa(elemento *ini){
    float soma = 0;
    int qtd = 0;
    while(ini!=NULL) {
        qtd++;
        soma += ini->value;
        ini=ini->next;
    }
    return soma/qtd;
}

float mediaRecursiva(elemento *ini, int qtd){
    if(ini==NULL){
        return 0;
    }else{
        return (ini->value + mediaRecursiva(ini->next, qtd-1)*(qtd-1)) / qtd;
    }
}
