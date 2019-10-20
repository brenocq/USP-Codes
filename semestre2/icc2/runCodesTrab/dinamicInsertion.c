#include<stdlib.h>
#include<stdio.h>

typedef struct _item{
  int value;
  struct _item *prox;
}item;

int main(int argc, char const *argv[]) {
  int qtd, i, val;
  scanf("%d", &qtd);
  scanf("%d", &val);

  item** ini = (item**)malloc(sizeof(item*));
  item* first = (item*)malloc(sizeof(item));
  first->value = val;
  ini = &first;

  for (i = 1; i < qtd; i++) {
    item* next = (item*)malloc(sizeof(item));
    scanf("%d", &val);
    next->value = val;

    item* curr = *ini;
    item* prev;

    while(curr!=NULL && curr->value<next->value){
      prev = curr;
      curr = curr->prox;
      //printf("(%d)0\n", val);
    }

    if(curr==*ini){
      //printf("(%d)1\n", val);
      next->prox = curr;
      *ini = next;

    }else{
      if(curr==NULL){
        //printf("(%d)3.1\n", val);
        prev->prox = next;
      }else{
        //printf("(%d)3.1\n", val);
        prev->prox = next;
        next->prox = curr;
      }
    }
  }

  item* curr = *ini;
  int cont = 0;
  while(curr!=NULL && cont<100){
    printf("%d ", curr->value);
    curr=curr->prox;
    cont++;
  }

  return 0;
}
