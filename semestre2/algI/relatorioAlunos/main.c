#include <stdlib.h>
#include <stdio.h>
#include "relatorio.h"


int main(int argc, char const *argv[]) {
  Registros *registro = registro_criar();
  Aluno* aluno = aluno_criar(0,5,10,9);
  Aluno* aluno2 = aluno_criar(4,5,10,9);
  Aluno* aluno3 = aluno_criar(1,5,10,9);
  registro_inserir(registro, aluno);
  registro_inserir(registro, aluno2);
  registro_inserir(registro, aluno3);
  registro_imprimir(registro);
  return 0;
}
