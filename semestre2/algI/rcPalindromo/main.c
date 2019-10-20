#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

int main(int argc, char const *argv[]) {
  char* frase = (char*)malloc(300*sizeof(char));
  Deque* deque = deque_criar();
  int i;

  // Recebe a frase do terminal
  scanf("%[^.]%*c", frase);

  // Adiciona os caracteres da frase no deque
  for(i=0; frase[i]!='\0'; i++){
    Item* c = item_criar(frase[i]);
    deque_inserir_frente(deque, c);
  }

  while(!deque_vazio(deque)){
    // Checa se um caractere válido do inicio e do final do deque são iguais
    // A função char_valido_* retorna o primeiro caractere que é uma letra seguindo a operação *
    // Eu implementei esta função dentro do TAD deque para ter acesso ao caractere armazenado no item
    char fundo = char_valido_fundo(deque);
    char frente = char_valido_frente(deque);
    if(fundo!=0 && frente!=0 && fundo!=frente){
      printf("Não é palíndromo.\n");
      return 0;
    }
  }
  printf("É palíndromo.\n");
  return 0;
}
