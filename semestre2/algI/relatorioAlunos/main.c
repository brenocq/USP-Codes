#include <stdlib.h>
#include <stdio.h>
#include "relatorio.h"


int main(int argc, char const *argv[]) {
  Registros *registro = registro_criar();
  Aluno* aluno1 = aluno_criar(0,5,10,9);
  Aluno* aluno2 = aluno_criar(4,5,10,9);
  Aluno* aluno3 = aluno_criar(1,5,10,9);

  registro_inserir(registro, aluno1);
  registro_inserir(registro, aluno3);
  registro_remover(registro, 1);
  registro_remover(registro, 0); 
  registro_inserir(registro, aluno2);

  registro_imprimir(registro);

  registro_deletar(registro);
  return 0;
}
