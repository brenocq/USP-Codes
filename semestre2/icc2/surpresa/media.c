#include <stdlib.h>
#include <stdio.h>

typedef struct _elemento{
  float value;
  struct _elemento *next;
}elemento;

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

  elemento *print = *ini;
  while(print!=NULL) {
    printf("%f\n", print->value);
    print=print->next;
  }
  return 0;
}
